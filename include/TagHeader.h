//3. tagHeader
#pragma once
#include "stdafx.h"

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

