#include "FLVParser.h"
#include "osl_file.h"
#include "osl_log.h"

CFlvParser::CFlvParser(char_t* file_path, uint32_t bufsize)
{
	m_bufsize = bufsize;
	m_pbuf = new char_t[bufsize];
	Initialize();
	OnData(file_path);
	memset (&m_config_record, 0, sizeof(m_config_record));
	memset(&m_audio_config, 0, sizeof(m_audio_config));
}

CFlvParser::~CFlvParser(void)
{
	Release();
	//释放内存
	delete[] m_pbuf;
}

/* 初始化 */
void CFlvParser::Initialize()
{
	m_flv_fp = NULL;

}

/* 关闭 */
void CFlvParser::Release()
{
	if ( m_flv_fp != NULL )
	{
		osl_file_close(m_flv_fp);
		m_flv_fp = NULL;
	}

}

/*送入FLV文件,分析*/
void CFlvParser::OnData(char_t* file_path)
{
	if(file_path == NULL)
	{
		return;
	}
	//打开文件
	m_flv_fp = osl_file_open(file_path, OSL_FILE_READ_ONLY);
	if(m_flv_fp == NULL)
	{
		osl_log_error("err: %s file open failed!!\n", file_path);
	}
	//读取flv文件头
	osl_file_read( m_flv_fp, &m_flv_head, sizeof(m_flv_head) );

	//读取meta数据
	//读取preTag 和tag头
	osl_file_read(m_flv_fp, m_pbuf, sizeof(m_pretag_size) + sizeof(m_tag_head));
	memcpy(&m_pretag_size, m_pbuf,sizeof(m_pretag_size));
	memcpy(&m_tag_head, m_pbuf + sizeof(m_pretag_size), sizeof(m_tag_head));
	//读取tag内容
	osl_file_read( m_flv_fp, m_pbuf, m_tag_head.GetDatasize() );

	if (m_tag_head.GetTagtype() == TAG_TYPE_SCRIPT)
	{
		m_metadata.OnData(m_pbuf);  //获取meta数据
	}

}

/*是否是FLV文件*/
bool CFlvParser::IsFlvFile()
{
	return m_flv_head.isFLVHeader();
}

/*获取NAL 或者ACC数据 data_type标识数据类型*/
void CFlvParser::GetNextRealData(char_t** p_pbuf, int32_t* p_bufsize, int32_t* pdata_type)
{	

	//初始化
	*pdata_type = -1 ;
	*p_pbuf = NULL;
	*p_bufsize = 0;

	//读取preTag 和tag头
	osl_file_read(m_flv_fp, m_pbuf, sizeof(m_pretag_size) + sizeof(m_tag_head) );

	memcpy(&m_pretag_size, m_pbuf, sizeof(m_pretag_size));
	memcpy(&m_tag_head, m_pbuf + sizeof(m_pretag_size),  sizeof(m_tag_head));
	
	//读取tag内容
	if(m_tag_head.GetDatasize() > (uint32_t)m_bufsize)
	{
		
		osl_log_error( "m_tag_head.GetDatasize() > m_bufsize pbuf is too small!  need = %d\n",
			           m_tag_head.GetDatasize());
		//丢掉
		osl_file_read( m_flv_fp, m_pbuf, m_bufsize );
		osl_file_read( m_flv_fp, m_pbuf, m_tag_head.GetDatasize() - m_bufsize );
		return;
	}
	osl_file_read( m_flv_fp, m_pbuf, m_tag_head.GetDatasize() );
	
	//视频数据
	if(m_tag_head.GetTagtype() == TAG_TYPE_VIDEO)
	{
		//设置数据类型
		*pdata_type = AVC_NAL_DATA ;  


		m_videodata.OnData(m_pbuf);
		//NAL数据
		if( m_videodata.GetAVC_packet_type() == TAG_AVC_NALU)
		{

			uchar_t* pbuf = m_videodata.GetPdata();
			
			//前四个字节是nal的长度
			uint32_t nal_size = CFLVTool::rev_toi(pbuf, 4);
			memcpy(pbuf, nal_header, 4);  //写入00 00 00 01头, nal数据大, 重复复制费时间,也浪费内存,
										  //这里重复利用m_pbuf的内存,将tag数据的前4个字节	
									      //作为00 00 00 01不用重新分配内存,直接变成h264的nal数据
			*p_pbuf = (char_t*)pbuf;
			*p_bufsize = nal_size + 4;
		}

		//AVC信息头 获取 sps pps
		else if( m_videodata.GetAVC_packet_type() == TAG_AVC_SEQUENCE_HEADER )
		{

			 m_config_record.OnData(m_videodata.GetPdata());
			
			 //设置读取的大小
			*p_bufsize = 0;

			memcpy(m_pbuf, nal_header, 4);  //写入00 00 00 01头
			*p_bufsize += 4;

			memcpy(m_pbuf + *p_bufsize, m_config_record.GetP_sequenceParameterSetNALUnit(), 
			 	   m_config_record.GetSequenceParameterSetLength() );	 //写入sps
			*p_bufsize += m_config_record.GetSequenceParameterSetLength() ;
			
			memcpy(m_pbuf + *p_bufsize, nal_header, 4);  //写入00 00 00 01头
			*p_bufsize += 4;

			memcpy(m_pbuf + *p_bufsize, m_config_record.GetP_pictureParameterSetNALUnit(),
				  m_config_record.GetPictureParameterSetLength());		 //写入pps
			*p_bufsize += m_config_record.GetPictureParameterSetLength();

			//设置返回的buf
			*p_pbuf = m_pbuf;
		}
		
	//音频数据
	}else if(m_tag_head.GetTagtype() == TAG_TYPE_AUDIO )
	{
		m_audiodata.OnData(m_pbuf);
		 //音频数据
		if(m_audiodata.GetACC_packet_type() == TAG_AAC_RAW_DATA) 
		{
			//设置数据类型
			*pdata_type = ACC_AUDIO_DATA ;
			*p_bufsize = m_tag_head.GetDatasize() -2;  // -2 剪去 m_audiodata的前面两个字节长度
			m_adtshead.SetAacFrameLength(*p_bufsize);  //设置ACC原始流长度
			
			memcpy(m_pbuf + 7, m_audiodata.GetPdata(), *p_bufsize);  //该语句一定要先于下面的memcpy语句
			
			memcpy(m_pbuf, &m_adtshead, ADTS_HEADER_SIZE);

			*p_bufsize += ADTS_HEADER_SIZE ;  //+ m_adtshead的长度 

			*p_pbuf = m_pbuf;
		}

		//音频头
		else if(m_audiodata.GetACC_packet_type() == TAG_AAC_SEQUENCE_HEADER )
		{
			m_audio_config.OnData(m_audiodata.GetPdata());

			/*获取SamplingFrequencyIndex(*/
			uchar_t sampling_fre = m_audio_config.GetSamplingFrequencyIndex() ;
			/*获取 AudioObjectType*/
			uchar_t profile = m_audio_config.GetAudioObjectType();
			/*获取channelConfiguration*/
			uchar_t channel_cfg = m_audio_config.GetChannelConfiguration();

			m_adtshead.SetAdtsInfo(channel_cfg, sampling_fre, profile);

		}
	}
}


/*是否到flv文件的末端*/
bool CFlvParser::IsFlvEOF()
{
	if(m_flv_fp == NULL )
	{
		return true;
	}
	if( osl_file_eof(m_flv_fp) )
	{
		return true;
	}
	return false;
}

/*获取当前tag的时间戳(单位:ms)*/
uint32_t CFlvParser::GetTimestamp() const
{
	return m_tag_head.GetTimestamp();
}

uchar_t const CFlvParser::nal_header[4] ={0x00, 0x00, 0x00, 0x01};      //nal头四个字节 00 00 00 01
