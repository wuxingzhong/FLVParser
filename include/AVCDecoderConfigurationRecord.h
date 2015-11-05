
#pragma once
#include "FLVTool.h"
//AVCDecoderConfigurationRecord 结构的定义：aligned(8) 
class CAVCDecoderConfigurationRecord 
{ 
public:
	CAVCDecoderConfigurationRecord(void* buf = NULL);
	~CAVCDecoderConfigurationRecord(void);
	/*送入数据*/
	void OnData(void* buf);

	/*sps长度*/
	int32_t GetSequenceParameterSetLength() const;

	/*获取sps*/
	uchar_t* GetP_sequenceParameterSetNALUnit() const;

	/*pps长度*/
	int32_t GetPictureParameterSetLength() const ;

	/*获取pps*/
	uchar_t* GetP_pictureParameterSetNALUnit() const ;

private:
	uchar_t m_configurationVersion;					//版本号
	uchar_t m_AVCProfileIndication;					//sps[1]
	uchar_t m_profile_compatibility;				//sps[2]
	uchar_t m_AVCLevelIndication;					//sps[3]

	//是 H.264 视频中 NALU 的长度，计算方法是 1 + (lengthSizeMinusOne & 0x3, 即低2位) , 实际计算结果一直是4
	uchar_t m_lengthSizeMinusOne			:2;		//NALUnitLength的长度-1, 一般为3 
	uchar_t m_reserved1						:6;		//111111 


	uchar_t m_numOfSequenceParameterSets	:5;		//sps个数, 一般为1
	uchar_t m_reserved2 					:3;		//111; 


	uchar_t m_sequenceParameterSetLength[2];
	

	uchar_t* m_p_sequenceParameterSetNALUnit;		//= new uchar_t[sequenceParameterSetLength]

	uchar_t m_numOfPictureParameterSets;

	uchar_t m_pictureParameterSetLength[2];

	uchar_t* m_p_pictureParameterSetNALUnit;		//= new uchar_t[pictureParameterSetLength] 

};