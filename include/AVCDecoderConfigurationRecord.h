
#pragma once
#include "FLVTool.h"
//AVCDecoderConfigurationRecord �ṹ�Ķ��壺aligned(8) 
class CAVCDecoderConfigurationRecord 
{ 
public:
	CAVCDecoderConfigurationRecord(void* buf = NULL);
	~CAVCDecoderConfigurationRecord(void);
	/*��������*/
	void OnData(void* buf);

	/*sps����*/
	int32_t GetSequenceParameterSetLength() const;

	/*��ȡsps*/
	uchar_t* GetP_sequenceParameterSetNALUnit() const;

	/*pps����*/
	int32_t GetPictureParameterSetLength() const ;

	/*��ȡpps*/
	uchar_t* GetP_pictureParameterSetNALUnit() const ;

private:
	uchar_t m_configurationVersion;					//�汾��
	uchar_t m_AVCProfileIndication;					//sps[1]
	uchar_t m_profile_compatibility;				//sps[2]
	uchar_t m_AVCLevelIndication;					//sps[3]

	//�� H.264 ��Ƶ�� NALU �ĳ��ȣ����㷽���� 1 + (lengthSizeMinusOne & 0x3, ����2λ) , ʵ�ʼ�����һֱ��4
	uchar_t m_lengthSizeMinusOne			:2;		//NALUnitLength�ĳ���-1, һ��Ϊ3 
	uchar_t m_reserved1						:6;		//111111 


	uchar_t m_numOfSequenceParameterSets	:5;		//sps����, һ��Ϊ1
	uchar_t m_reserved2 					:3;		//111; 


	uchar_t m_sequenceParameterSetLength[2];
	

	uchar_t* m_p_sequenceParameterSetNALUnit;		//= new uchar_t[sequenceParameterSetLength]

	uchar_t m_numOfPictureParameterSets;

	uchar_t m_pictureParameterSetLength[2];

	uchar_t* m_p_pictureParameterSetNALUnit;		//= new uchar_t[pictureParameterSetLength] 

};