
#pragma once
#include "FLVTool.h"

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

//AVCDecoderConfigurationRecord 
class CAVCDecoderConfigurationRecord 
{ 
public:
	CAVCDecoderConfigurationRecord(void* buf = NULL);
	~CAVCDecoderConfigurationRecord(void);
	/*送入数据*/
	void OnData(void* buf);

	/*sps长度*/
	int32_t GetSequenceParameterSetLength() const;

	/*获取sps sps头字节为67，67&0x1f = 7 */
	uchar_t* GetP_sequenceParameterSetNALUnit() const;

	/*pps长度*/
	int32_t GetPictureParameterSetLength() const ;

	/*获取pps，pps头字节为68，68&0x1f=8*/
	uchar_t* GetP_pictureParameterSetNALUnit() const ;
	
	/*获取NAL包长度描述*/
	uchar_t GetNALUnitLength() const ;

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