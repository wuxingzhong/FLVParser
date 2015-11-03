//3. tagHeader
#pragma once
class  CTagHeader
{
public:
	CTagHeader(void* buf = NULL);
	~CTagHeader(void);

	/*送入数据*/
	void OnData(void* buf);

	/*获取tag类型 0x8 = audio,0x9 = video,0x12 = script */
	uint32_t GetTagtype() const;

	/*获取tag数据大小*/
	uint32_t  GetDatasize() const;

	/*获取时间戳 PTS  PTS= Timestamp | TimestampExtended<<24 */
	uint32_t GetTimestamp() const;

	/*输出FLV头*/
	void PrintTagHead() const;
	
private:
	uchar_t m_tagtype;					//0x8 = audio,0x9 = video,0x12 = script 
	uchar_t m_datasize[3];				//信息长度
	uchar_t m_timestamp[3];				//时间戳   真正数据的PTS是 PTS= Timestamp | TimestampExtended<<24.
	uchar_t m_timestampextended;		//时间戳的扩展
	uchar_t m_streamid[3];				//通常是0

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
	//初始化为0 
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

//输出tag头
void CTagHeader::PrintTagHead()const
{
	printf("tagtype             = %d\n", GetTagtype());
	printf("datasize            = %d\n", GetDatasize() );
	//真正的pts
	printf("timestamp           = %d\n", GetTimestamp());
	printf("streamid            = %d\n\n", CFLVTool::rev_toi(m_streamid, 3) ); 
}
