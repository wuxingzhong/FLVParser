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
#define NALU_TYPE_IDR 5   //tag�ж�ȡ�ĵ�һ���ؼ�֡��I֡���󲿷�����һ��SEI��һ��I֡��
//��Щ�����������ж��SEI��һ��I֡������δ��������Ҫע�⣬
#define NALU_TYPE_SEI 6
#define NALU_TYPE_SPS 7
#define NALU_TYPE_PPS 8
#define NALU_TYPE_AUD 9����//���ʷָ���
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

	/* ��ʼ�� */
	void Initialize();

	/* �ر� */
	void Release();

	/*����FLV�ļ�,����*/
	void OnData(char_t* file_path);

	/*�Ƿ���FLV�ļ�*/
	bool IsFlvFile();

	/*��ȡNAL ����ACC���� data_type��ʶ��������*/
	void GetNextRealData(char_t** p_pbuf, int32_t* p_bufsize, int32_t* pdata_type);

	/*�Ƿ�flv�ļ���ĩ��*/
	bool IsFlvEOF();

	/*��ȡ��ǰtag��ʱ���(��λ:ms)*/
	uint32_t GetTimestamp() const;
	
private:
	char_t* m_pbuf;                             //������
	void* m_flv_fp;						        //flv�ļ�
	CFLVHeader m_flv_head;				        //flvͷ
	preTagSize m_pretag_size;				    //ǰһ��tag�Ĵ�С
	CTagHeader m_tag_head;				        //tagͷ
	CMetaData m_metadata;					    //meta����

	CVideoData m_videodata;				        //��Ƶ����
	CAVCDecoderConfigurationRecord m_config_record; //AVC��Ƶ����

	CAudioData m_audiodata;				        //��Ƶ����
	CAudioSpecificConfig m_audio_config;	    //��Ƶ��������
	static uchar_t const nal_header[4];         //nalͷ�ĸ��ֽ� 00 00 00 01
};