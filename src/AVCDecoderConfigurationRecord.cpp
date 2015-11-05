#include "AVCDecoderConfigurationRecord.h"

CAVCDecoderConfigurationRecord::CAVCDecoderConfigurationRecord(void* buf = NULL)
{
	memset(this, 0, sizeof(*this));
	m_p_sequenceParameterSetNALUnit = NULL;
	m_p_pictureParameterSetNALUnit = NULL;
	OnData(buf);
}
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
	if(buf == NULL)
	{
		return ;
	}
	//转换数据
	*this = *(CAVCDecoderConfigurationRecord*)buf;
	
	//释放上一次的内存
	if(m_p_sequenceParameterSetNALUnit !=NULL )
	{
		delete[] m_p_sequenceParameterSetNALUnit;
	}
	if(m_p_pictureParameterSetNALUnit!=NULL )
	{
		delete[] m_p_pictureParameterSetNALUnit;
	}
	offset = 8;
	//修正数据
	len_sps = GetSequenceParameterSetLength() ;
	m_p_sequenceParameterSetNALUnit = new uchar_t[len_sps];
  
	memcpy(m_p_sequenceParameterSetNALUnit,buf + offset, len_sps);
	offset += len_sps;
	m_numOfPictureParameterSets = (uchar_t)(buf + offset);
	offset ++;
	m_pictureParameterSetLength = (uchar_t)(buf + offset);
	offset += 2;
	len_pps = GetPictureParameterSetLength();
	m_p_pictureParameterSetNALUnit = new uchar_t[len_pps];
	memcpy(m_p_pictureParameterSetNALUnit,buf + offset, len_pps);

}

int32_t CAVCDecoderConfigurationRecord::GetSequenceParameterSetLength() const 
{
	return CFLVTool::rev_toi(m_sequenceParameterSetLength, sizeof(m_sequenceParameterSetLength)); 
}
int32_t CAVCDecoderConfigurationRecord::GetPictureParameterSetLength() const 
{ 
	return CFLVTool::rev_toi(m_pictureParameterSetLength, sizeof(m_pictureParameterSetLength)); 
}