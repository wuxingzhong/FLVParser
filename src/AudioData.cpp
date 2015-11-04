#include "AudioData.h"

CAudioData::CAudioData(void* buf)
{
	m_pdata = NULL;
	OnData(buf);
}
CAudioData::~CAudioData(void)
{
	
}
/*送入数据*/
void CAudioData::OnData(void* buf)
{
	//初始化为0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//转换数据 提取
	*this = *(CAudioData*)buf;

	/*
	if AAC packet type == 0 
			AudioSpecificConfig   //只有一个，出现在第一个audio tag
	else if AAC packet type == 1 
			Raw AAC frame data 
	*/

	if(m_ACC_packet_type == 0 || m_ACC_packet_type == 1)
	{
		m_pdata = (uchar_t*)buf + 2;
	}
	else
	{
		m_pdata = NULL;
	}

}

/*获取音频数据*/
uchar_t* CAudioData::GetPdata() const
{
	return m_pdata; 
}

/*打印信息*/
void CAudioData::print_info() const 
{
	printf("m_sound_type          = %d\n", m_sound_type);
	printf("m_sound_size          = %d\n", m_sound_size);
	printf("m_rate                = %d\n", m_rate);
	printf("m_sound_format        = %d\n", m_sound_format);
	printf("m_ACC_packet_type     = %d\n", m_ACC_packet_type);
	printf("m_pdata               = %02x\n\n", *m_pdata);
}
