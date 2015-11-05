#pragma once
#include "stdafx.h"
class CAudioSpecificConfig
{
public:
	CAudioSpecificConfig(void* buf = NULL);
	~CAudioSpecificConfig(void);
	/*送入数据*/
	void OnData(void* buf);
	
	/*获取SFI*/
	uchar_t GetSamplingFrequencyIndex() const;

private:
	uchar_t m_samplingFrequencyIndex1	:3; // m_samplingFrequencyIndex1<<1  | m_samplingFrequencyIndex2 
	uchar_t m_audioObjectType			:5; //编码结构类型 AAC-LC 为2

	uchar_t m_extensionFlag				:1;
	uchar_t m_dependsOnCoreCoder		:1;
	uchar_t m_frameLengthFlag			:1;
	uchar_t m_channelConfiguration		:4;
	uchar_t m_samplingFrequencyIndex2	:1;

};
