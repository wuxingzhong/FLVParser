#include "stdafx.h"
#include "osl.h"
#include "FLVHeader.h"
#include "TagHeader.h"
#include "MetaData.h"
#include "VideoData.h"
#include "AudioData.h"
#include "AVCDecoderConfigurationRecord.h"
#include "AudioSpecificConfig.h"

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


#define AVC_NAL_DATA  TAG_TYPE_VIDEO
#define ACC_AUDIO_DATA TAG_TYPE_AUDIO

class CFlvParser
{
public:
	CFlvParser(char_t* file_path = NULL, uint32_t bufsize = 1024*90);
	~CFlvParser(void);

	/* 初始化 */
	void Initialize();

	/* 关闭 */
	void Release();

	/*送入FLV文件,分析*/
	void OnData(char_t* file_path);

	/*是否是FLV文件*/
	bool IsFlvFile();

	/*获取NAL 或者ACC数据 data_type标识数据类型*/
	void GetNextRealData(char_t** p_pbuf, int32_t* p_bufsize, int32_t* pdata_type);

	/*是否到flv文件的末端*/
	bool IsFlvEOF();

	/*获取当前tag的时间戳(单位:ms)*/
	uint32_t GetTimestamp() const;
	
private:
	char_t* m_pbuf;                             //缓冲区
	void* m_flv_fp;						        //flv文件
	CFLVHeader m_flv_head;				        //flv头
	preTagSize m_pretag_size;				    //前一个tag的大小
	CTagHeader m_tag_head;				        //tag头
	CMetaData m_metadata;					    //meta数据

	CVideoData m_videodata;				        //视频数据
	CAVCDecoderConfigurationRecord m_config_record; //AVC视频配置

	CAudioData m_audiodata;				        //音频数据
	CAudioSpecificConfig m_audio_config;	    //音频数据配置
	static uchar_t const nal_header[4];         //nal头四个字节 00 00 00 01
};