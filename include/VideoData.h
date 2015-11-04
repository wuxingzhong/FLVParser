#include "stdafx.h"



//AVCDecoderConfigurationRecord �ṹ�Ķ��壺aligned(8) 
class AVCDecoderConfigurationRecord 
{ 
public:
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
	//bit(8*sequenceParameterSetLength) sequenceParameterSetNALUnit;

	uchar_t m_numOfPictureParameterSets;

	uchar_t m_pictureParameterSetLength;
	//	bit(8*pictureParameterSetLength) pictureParameterSetNALUnit; 
	//} 
};

class  CVideoData
{
public:
	CVideoData(void* buf = NULL);
	~CVideoData(void);
	/*��������*/
	void OnData(void* buf);

	/*��ȡ��Ƶ����*/
	uchar_t* GetPdata() const;

	/*��ӡ��Ϣ*/
	void print_info() const ;

protected:

private:
	/*video ��Ϣ*/
	uchar_t m_codec_id   :4;			//������id    7 -- H264/AVC
	uchar_t m_frame_type :4;			//frame����  1 keyframe   2 inter frame
	
	/*video ������ H264/AVC*/
	uchar_t m_AVC_packet_type;			//0:  AVC sequence header 1:  AVC NALU  2:  AVC end of sequence
	uchar_t m_composition_time[3];   
	uchar_t* m_pdata;					//AVC_packet_type == 0   AVC_packet_type == 1 One or more NALUs  Else Empty

};




