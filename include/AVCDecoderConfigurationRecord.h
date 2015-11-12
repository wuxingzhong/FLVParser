
#pragma once
#include "FLVTool.h"

#define NALU_TYPE_SLICE 1
#define NALU_TYPE_DPA 2
#define NALU_TYPE_DPB 3
#define NALU_TYPE_DPC 4
#define NALU_TYPE_IDR 5   //tag�ж�ȡ�ĵ�һ���ؼ�֡��I֡���󲿷�����һ��SEI��һ��I֡��
//��Щ�����������ж��SEI��һ��I֡������δ��������Ҫע�⣬
#define NALU_TYPE_SEI 6
#define NALU_TYPE_SPS 7
#define NALU_TYPE_PPS 8
#define NALU_TYPE_AUD 9����//���ʷָ���
#define NALU_TYPE_EOSEQ 10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL 12

//AVCDecoderConfigurationRecord 
class CAVCDecoderConfigurationRecord 
{ 
public:
	CAVCDecoderConfigurationRecord(void* buf = NULL);
	~CAVCDecoderConfigurationRecord(void);
	/*��������*/
	void OnData(void* buf);

	/*sps����*/
	int32_t GetSequenceParameterSetLength() const;

	/*��ȡsps spsͷ�ֽ�Ϊ67��67&0x1f = 7 */
	uchar_t* GetP_sequenceParameterSetNALUnit() const;

	/*pps����*/
	int32_t GetPictureParameterSetLength() const ;

	/*��ȡpps��ppsͷ�ֽ�Ϊ68��68&0x1f=8*/
	uchar_t* GetP_pictureParameterSetNALUnit() const ;
	
	/*��ȡNAL����������*/
	uchar_t GetNALUnitLength() const ;

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