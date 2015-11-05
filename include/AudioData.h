#include "stdafx.h"


class CAudioSpecificConfig
{
public:
private:
	uchar_t m_samplingFrequencyIndex1	:3; //m_samplingFrequencyIndex2 <<3 | m_samplingFrequencyIndex1
	uchar_t m_audioObjectType			:5; //编码结构类型 AAC-LC 为2

	uchar_t m_extensionFlag				:1;
	uchar_t m_dependsOnCoreCoder		:1;
	uchar_t m_frameLengthFlag			:1;
	uchar_t m_channelConfiguration		:4;
	uchar_t m_samplingFrequencyIndex2	:1;

};





class  CAudioData
{
public:
	CAudioData(void* buf = NULL);
	~CAudioData(void);
	/*送入数据*/
	void OnData(void* buf);

	/*获取音频数据*/
	uchar_t* GetPdata() const;

	/*打印信息*/
	void print_info() const ;

protected:

private:
	/*Audio 信息*/
	uchar_t  m_sound_type	:1;			//类型 0--sndMono   1--sndStereo
	uchar_t  m_sound_size	:1;			//精度 0--8bits     1--16bits
	uchar_t  m_rate			:2;			//采样率 0--5.5kHz  1--11KHz 2--22kHz  3--44kHz
	uchar_t  m_sound_format	:4;			//音频编码类型 10 -- AAC

	
	/*audio  数据区*/
	uchar_t  m_ACC_packet_type;			//0--AAC sequence header        1--AAC raw  data   
	uchar_t* m_pdata;

};

