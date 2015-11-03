//3. tagHeader
#pragma once
class  CTagHeader
{
public:
	CTagHeader(void* buf = NULL);
	~CTagHeader(void);

	/*��������*/
	void OnData(void* buf);

	/*��ȡtag���� 0x8 = audio,0x9 = video,0x12 = script */
	uint32_t GetTagtype() const;

	/*��ȡtag���ݴ�С*/
	uint32_t  GetDatasize() const;

	/*��ȡʱ��� PTS  PTS= Timestamp | TimestampExtended<<24 */
	uint32_t GetTimestamp() const;

	/*���FLVͷ*/
	void PrintTagHead() const;
	
private:
	uchar_t m_tagtype;					//0x8 = audio,0x9 = video,0x12 = script 
	uchar_t m_datasize[3];				//��Ϣ����
	uchar_t m_timestamp[3];				//ʱ���   �������ݵ�PTS�� PTS= Timestamp | TimestampExtended<<24.
	uchar_t m_timestampextended;		//ʱ�������չ
	uchar_t m_streamid[3];				//ͨ����0

};

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
