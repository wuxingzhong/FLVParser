#include "AudioData.h"

CAudioData::CAudioData(void* buf)
{
	m_pdata = NULL;
	OnData(buf);
}
CAudioData::~CAudioData(void)
{
	
}
/*��������*/
void CAudioData::OnData(void* buf)
{
	//��ʼ��Ϊ0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//ת������ ��ȡ
	*this = *(CAudioData*)buf;

	/*
	if AAC packet type == 0 
			AudioSpecificConfig   //ֻ��һ���������ڵ�һ��audio tag
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

/*��ȡ��Ƶ����*/
uchar_t* CAudioData::GetPdata() const
{
	return m_pdata; 
}

uchar_t CAudioData::GetACC_packet_type() const 
{ 
	return m_ACC_packet_type; 
}

/*��ӡ��Ϣ*/
void CAudioData::print_info() const 
{
	printf("m_sound_type          = %d\n", m_sound_type);
	printf("m_sound_size          = %d\n", m_sound_size);
	printf("m_rate                = %d\n", m_rate);
	printf("m_sound_format        = %d\n", m_sound_format);
	printf("m_ACC_packet_type     = %d\n", m_ACC_packet_type);
	
	if(m_pdata == NULL) return;

	printf("m_pdata              ");
	for (int i= 0; i< 10; i++)
	{
		printf("%02x ", m_pdata[i]);
	}
	printf("\n\n");
}


