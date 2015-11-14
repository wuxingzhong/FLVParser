#include "AVCDecoderConfigurationRecord.h"
#define NALU_TYPE_SLICE 1
#define NALU_TYPE_DPA 2
#define NALU_TYPE_DPB 3
#define NALU_TYPE_DPC 4
#define NALU_TYPE_IDR 5   //tag中读取的第一个关键帧（I帧）大部分是有一个SEI和一个I帧，
//有些不常见的是有多个SEI和一个I帧，这里未作处理，需要注意，
#define NALU_TYPE_SEI 6
#define NALU_TYPE_SPS 7
#define NALU_TYPE_PPS 8
#define NALU_TYPE_AUD 9　　//访问分隔符
#define NALU_TYPE_EOSEQ 10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL 12


CAVCDecoderConfigurationRecord::CAVCDecoderConfigurationRecord(void* buf)
{
	memset(this, 0, sizeof(*this));
	m_p_sequenceParameterSetNALUnit = NULL;
	m_p_pictureParameterSetNALUnit = NULL;
	OnData(buf);
}


/*析构函数*/
CAVCDecoderConfigurationRecord::~CAVCDecoderConfigurationRecord(void)
{

	if(m_p_sequenceParameterSetNALUnit !=NULL )
	{
		delete[] m_p_sequenceParameterSetNALUnit;
	}
	if(m_p_pictureParameterSetNALUnit!=NULL )
	{
		delete[] m_p_pictureParameterSetNALUnit;
	}
}
/*送入数据*/
void CAVCDecoderConfigurationRecord::OnData(void* buf)
{
	int len_sps;
	int len_pps;
	int offset = 0;
	uchar_t* pbuf = (uchar_t*)buf;
	if(pbuf == NULL)
	{
		return ;
	}
	//释放上一次的内存
	if(m_p_sequenceParameterSetNALUnit !=NULL )
	{
		delete[] m_p_sequenceParameterSetNALUnit;
		m_p_sequenceParameterSetNALUnit = NULL ;
	}
	if(m_p_pictureParameterSetNALUnit!=NULL )
	{
		delete[] m_p_pictureParameterSetNALUnit;
		m_p_pictureParameterSetNALUnit = NULL;
	}

	//转换数据
	*this = *(CAVCDecoderConfigurationRecord*)pbuf;
	
	offset = 8;
	//修正数据
	len_sps = GetSequenceParameterSetLength() ;

	m_p_sequenceParameterSetNALUnit = new uchar_t[len_sps];
  
	memcpy(m_p_sequenceParameterSetNALUnit,pbuf + offset, len_sps);
	offset += len_sps;
	m_numOfPictureParameterSets = *(pbuf + offset);
	offset ++;
	memcpy(m_pictureParameterSetLength , pbuf+ offset, 2);
	offset += 2;
	len_pps = GetPictureParameterSetLength();
	if(len_pps >2000)
	{
		printf("asdfsdafdsf");
	}
	m_p_pictureParameterSetNALUnit = new uchar_t[len_pps];
	memcpy(m_p_pictureParameterSetNALUnit,pbuf + offset, len_pps);

}

/*sps长度*/
int32_t CAVCDecoderConfigurationRecord::GetSequenceParameterSetLength() const 
{
	return CFLVTool::rev_toi(m_sequenceParameterSetLength, sizeof(m_sequenceParameterSetLength)); 
}

/*获取sps*/
uchar_t* CAVCDecoderConfigurationRecord::GetP_sequenceParameterSetNALUnit() const
{ 
	return m_p_sequenceParameterSetNALUnit; 
}

/*pps长度*/
int32_t CAVCDecoderConfigurationRecord::GetPictureParameterSetLength() const 
{ 
	return CFLVTool::rev_toi(m_pictureParameterSetLength, sizeof(m_pictureParameterSetLength)); 
}

/*获取pps*/
uchar_t* CAVCDecoderConfigurationRecord::GetP_pictureParameterSetNALUnit() const 
{ 
	return m_p_pictureParameterSetNALUnit;
}

/*获取NAL包长度描述*/
uchar_t CAVCDecoderConfigurationRecord::GetNALUnitLength() const 
{ 
	return m_lengthSizeMinusOne + 1;
}
