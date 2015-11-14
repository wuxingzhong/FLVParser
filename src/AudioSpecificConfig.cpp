#include "AudioSpecificConfig.h"

CAudioSpecificConfig::CAudioSpecificConfig(void* buf )
{
	OnData(buf);
}
CAudioSpecificConfig::~CAudioSpecificConfig(void)
{

}
/*送入数据*/
void CAudioSpecificConfig::OnData(void* buf)
{
	//初始化为0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//转换数据 提取
	*this = *(CAudioSpecificConfig*)buf;
}

/*获取SFI*/
uchar_t CAudioSpecificConfig::GetSamplingFrequencyIndex() const 
{
	return m_samplingFrequencyIndex1<<1 | m_samplingFrequencyIndex2;
}

/*获取 AudioObjectType*/
uchar_t CAudioSpecificConfig::GetAudioObjectType() const
{
	return m_audioObjectType;
}
/*获取channelConfiguration*/
uchar_t CAudioSpecificConfig::GetChannelConfiguration() const
{
	return m_channelConfiguration;
}