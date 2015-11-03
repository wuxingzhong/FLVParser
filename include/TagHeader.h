//3. tagHeader
#pragma once
#include "stdafx.h"

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

