#include "AVCDecoderConfigurationRecord.h"

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
	}
	if(m_p_pictureParameterSetNALUnit!=NULL )
	{
		delete[] m_p_pictureParameterSetNALUnit;
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
	return m_lengthSizeMinusOne +1;
}
