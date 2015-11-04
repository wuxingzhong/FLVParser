#include "VideoData.h"
#include "FLVTool.h"

CVideoData::CVideoData( void* buf )
{
	m_pdata = NULL;
	OnData(buf);
}

CVideoData::~CVideoData(void)
{

}

/*��������*/
void CVideoData::OnData(void* buf)
{
	//��ʼ��Ϊ0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//ת������
	*this = *(CVideoData*)buf;
	/*
	IF AVCPacketType == 0
	AVCDecoderConfigurationRecord
	IF AVCPacketType == 1
	One or more NALUs (Full frames are required)
	*/

	if(m_AVC_packet_type == 0 || m_AVC_packet_type == 1)
	{
		m_pdata = (uchar_t*)buf + 5;
	}
	else
	{
		m_pdata = NULL;
	}
}


/*��ȡ��Ƶ����*/

uchar_t* CVideoData::GetPdata() const 
{ 
	return m_pdata; 
}

/*��ӡ��Ϣ*/
void CVideoData::print_info() const 
{
	printf("m_frame_type         = %d\n", m_frame_type);
	printf("m_codec_id           = %d\n", m_codec_id);
	printf("m_AVC_packet_type    = %d\n", m_AVC_packet_type);
	printf("m_composition_time   = %d\n", CFLVTool::rev_toi(m_composition_time, 3) );
	printf("m_pdata              = %02x\n\n", *m_pdata);
}
