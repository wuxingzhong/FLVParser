#include "TagHeader.h"
#include "FLVTool.h"

CTagHeader::CTagHeader(void* buf)
{
	OnData(buf);
}

CTagHeader::~CTagHeader(void)
{

}

void  CTagHeader::OnData(void* buf)
{
	//��ʼ��Ϊ0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	*this = *(CTagHeader*)buf;
}

uint32_t CTagHeader::GetTagtype() const
{ 
	return m_tagtype; 
}

uint32_t  CTagHeader::GetDatasize() const
{
	return CFLVTool::rev_toi(m_datasize, 3 ); 
}

uint32_t CTagHeader::GetTimestamp()  const
{ 
	return CFLVTool::rev_toi(m_timestamp, 3) | (m_timestampextended) << 24; 
}

//���tagͷ
void CTagHeader::PrintTagHead()const
{
	printf("tagtype             = %d\n", GetTagtype());
	printf("datasize            = %d\n", GetDatasize() );
	//������pts
	printf("timestamp           = %d\n", GetTimestamp());
	printf("streamid            = %d\n\n", CFLVTool::rev_toi(m_streamid, 3) ); 
}
