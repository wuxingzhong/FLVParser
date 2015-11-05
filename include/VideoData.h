#include "stdafx.h"

#define TAG_AVC_SEQUENCE_HEADER	0x00
#define TAG_AVC_NALU			0x01

class  CVideoData
{
public:
	CVideoData(void* buf = NULL);
	~CVideoData(void);
	/*��������*/
	void OnData(void* buf);

	/*��ȡ��Ƶ����*/
	uchar_t* GetPdata() const;
	/*��ȡAVC_packet_type*/
	uchar_t GetAVC_packet_type() const ;
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
