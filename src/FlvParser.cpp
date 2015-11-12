#include "FLVParser.h"
#include "osl_file.h"
#include "osl_log.h"

CFlvParser::CFlvParser(char_t* file_path, uint32_t bufsize)
{
	m_pbuf = new char_t[bufsize];
	Initialize();
	OnData(file_path);
}

CFlvParser::~CFlvParser(void)
{
	Release();
	//�ͷ��ڴ�
	delete[] m_pbuf;
}

/* ��ʼ�� */
void CFlvParser::Initialize()
{
	m_flv_fp = NULL;

}

/* �ر� */
void CFlvParser::Release()
{
	if ( m_flv_fp != NULL )
	{
		osl_file_close(m_flv_fp);
		m_flv_fp = NULL;
	}

}

/*����FLV�ļ�,����*/
void CFlvParser::OnData(char_t* file_path)
{
	if(file_path == NULL)
	{
		return;
	}
	//���ļ�
	m_flv_fp = osl_file_open(file_path, OSL_FILE_READ_ONLY);
	if(m_flv_fp == NULL)
	{
		osl_log_error("err: %s file open failed!!\n", file_path);
	}
	//��ȡflv�ļ�ͷ
	osl_file_read( m_flv_fp, &m_flv_head, sizeof(m_flv_head) );

	//��ȡmeta����
	//��ȡpreTag ��tagͷ
	osl_file_read(m_flv_fp, m_pbuf, sizeof(m_pretag_size) + sizeof(m_tag_head));
	memcpy(&m_pretag_size, m_pbuf,sizeof(m_pretag_size));
	memcpy(&m_tag_head, m_pbuf + sizeof(m_pretag_size), sizeof(m_tag_head));
	//��ȡtag����
	osl_file_read( m_flv_fp, m_pbuf, m_tag_head.GetDatasize() );

	if (m_tag_head.GetTagtype() == TAG_TYPE_SCRIPT)
	{
		m_metadata.OnData(m_pbuf);  //��ȡmeta����
	}

}

/*�Ƿ���FLV�ļ�*/
bool CFlvParser::IsFlvFile()
{
	return m_flv_head.isFLVHeader();
}

/*��ȡNAL ����ACC���� data_type��ʶ��������*/
void CFlvParser::GetNextRealData(char_t** p_pbuf, int32_t* p_bufsize, int32_t* pdata_type)
{	

	//��ʼ��
	*pdata_type = -1 ;
	*p_pbuf = NULL;
	*p_bufsize = 0;

	//��ȡpreTag ��tagͷ
	osl_file_read(m_flv_fp, m_pbuf, sizeof(m_pretag_size) + sizeof(m_tag_head) );

	memcpy(&m_pretag_size, m_pbuf, sizeof(m_pretag_size));
	memcpy(&m_tag_head, m_pbuf + sizeof(m_pretag_size),  sizeof(m_tag_head));
	
	//��ȡtag����
	osl_file_read( m_flv_fp, m_pbuf, m_tag_head.GetDatasize() );
	
	//��Ƶ����
	if(m_tag_head.GetTagtype() == TAG_TYPE_VIDEO)
	{
		//������������
		*pdata_type = AVC_NAL_DATA ;  


		m_videodata.OnData(m_pbuf);
		//NAL����
		if( m_videodata.GetAVC_packet_type() == TAG_AVC_NALU)
		{

			uchar_t* pbuf = m_videodata.GetPdata();
			
			//ǰ�ĸ��ֽ���nal�ĳ���
			uint32_t nal_size = CFLVTool::rev_toi(pbuf, 4);
			memcpy(pbuf, nal_header, 4);  //д��00 00 00 01ͷ, nal���ݴ�, �ظ����Ʒ�ʱ��,Ҳ�˷��ڴ�,
										  //�����ظ�����m_pbuf���ڴ�,��tag���ݵ�ǰ4���ֽ�	
									      //��Ϊ00 00 00 01�������·����ڴ�,ֱ�ӱ��h264��nal����
			*p_pbuf = (char_t*)pbuf;
			*p_bufsize = nal_size + 4;
		}

		//AVC��Ϣͷ ��ȡ sps pps
		else if( m_videodata.GetAVC_packet_type() == TAG_AVC_SEQUENCE_HEADER)
		{
			 m_config_record.OnData(m_videodata.GetPdata());
			
			 //���ö�ȡ�Ĵ�С
			*p_bufsize = 0;

			memcpy(m_pbuf, nal_header, 4);  //д��00 00 00 01ͷ
			*p_bufsize += 4;

			memcpy(m_pbuf + *p_bufsize, m_config_record.GetP_sequenceParameterSetNALUnit(), 
			 	   m_config_record.GetSequenceParameterSetLength() );	 //д��sps
			*p_bufsize += m_config_record.GetSequenceParameterSetLength() ;
			
			memcpy(m_pbuf + *p_bufsize, nal_header, 4);  //д��00 00 00 01ͷ
			*p_bufsize += 4;

			memcpy(m_pbuf + *p_bufsize, m_config_record.GetP_pictureParameterSetNALUnit(),
				  m_config_record.GetPictureParameterSetLength());		 //д��pps
			*p_bufsize += m_config_record.GetPictureParameterSetLength();

			//���÷��ص�buf
			*p_pbuf = m_pbuf;
		}
		
	//��Ƶ����
	}else if(m_tag_head.GetTagtype() == TAG_TYPE_AUDIO)
	{
		//������������
		*pdata_type = ACC_AUDIO_DATA ;

		m_audiodata.OnData(m_pbuf);
		//��Ƶͷ
		if(m_audiodata.GetACC_packet_type() == TAG_AAC_SEQUENCE_HEADER)
		{
			m_audio_config.OnData(m_audiodata.GetPdata());
		}

		*p_bufsize = 0;
	}
}


/*�Ƿ�flv�ļ���ĩ��*/
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

/*��ȡ��ǰtag��ʱ���(��λ:ms)*/
uint32_t CFlvParser::GetTimestamp() const
{
	return m_tag_head.GetTimestamp();
}

uchar_t const CFlvParser::nal_header[4] ={0x00, 0x00, 0x00, 0x01};      //nalͷ�ĸ��ֽ� 00 00 00 01
