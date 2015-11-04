#include "stdafx.h"



//AVCDecoderConfigurationRecord 结构的定义：aligned(8) 
class AVCDecoderConfigurationRecord 
{ 
public:
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
	/*送入数据*/
	void OnData(void* buf);

	/*获取视频数据*/
	uchar_t* GetPdata() const;

	/*打印信息*/
	void print_info() const ;

protected:

private:
	/*video 信息*/
	uchar_t m_codec_id   :4;			//编码器id    7 -- H264/AVC
	uchar_t m_frame_type :4;			//frame类型  1 keyframe   2 inter frame
	
	/*video 数据区 H264/AVC*/
	uchar_t m_AVC_packet_type;			//0:  AVC sequence header 1:  AVC NALU  2:  AVC end of sequence
	uchar_t m_composition_time[3];   
	uchar_t* m_pdata;					//AVC_packet_type == 0   AVC_packet_type == 1 One or more NALUs  Else Empty

};




