#include "AudioSpecificConfig.h"

CAudioSpecificConfig::CAudioSpecificConfig(void* buf )
{
	OnData(buf);
}
CAudioSpecificConfig::~CAudioSpecificConfig(void)
{

}
/*��������*/
void CAudioSpecificConfig::OnData(void* buf)
{
	//��ʼ��Ϊ0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//ת������ ��ȡ
	*this = *(CAudioSpecificConfig*)buf;
}

/*��ȡSFI*/
uchar_t CAudioSpecificConfig::GetSamplingFrequencyIndex() const 
{
	return m_samplingFrequencyIndex1<<1 | m_samplingFrequencyIndex2;
}

/*��ȡ AudioObjectType*/
uchar_t CAudioSpecificConfig::GetAudioObjectType() const
{
	return m_audioObjectType;
}
/*��ȡchannelConfiguration*/
uchar_t CAudioSpecificConfig::GetChannelConfiguration() const
{
	return m_channelConfiguration;
}