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

/*送入数据*/
void CVideoData::OnData(void* buf)
{
	//初始化为0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	//转换数据
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


/*获取视频数据*/

uchar_t* CVideoData::GetPdata() const 
{ 
	return m_pdata; 
}

/*打印信息*/
void CVideoData::print_info() const 
{
	printf("m_frame_type         = %d\n", m_frame_type);
	printf("m_codec_id           = %d\n", m_codec_id);
	printf("m_AVC_packet_type    = %d\n", m_AVC_packet_type);
	printf("m_composition_time   = %d\n", CFLVTool::rev_toi(m_composition_time, 3) );
	printf("m_pdata              = %02x\n\n", *m_pdata);
}
