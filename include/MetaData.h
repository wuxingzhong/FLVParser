#pragma once
#include "stdafx.h"
#include "osl_log.h"
#include "osl_string.h"
#include "FLVTool.h"
class CMetaData
{
public:
	CMetaData(void* buf = NULL);
	~CMetaData(void);

	/*送入数据*/
	void OnData(void* buf);
	
	/*持续的时间*/
	double GetDuration();

	/*帧宽度*/
	double GetWidth();

	/*帧高度*/
	double GetHeight();
	
	/*帧率*/
	double GetFramerate();
	
	/*打印信息*/
	void print_info();

private:
	uchar_t *m_meta;
    double m_duration;
    double m_width;
    double m_height;
    double m_framerate;

	/*解析Meta*/
	void ParseMeta();

	//4. ScriptData
	typedef struct tag_ScriptData
	{
		unsigned char type1;						//0x02
		unsigned char string_size[2];				//0x0a
		unsigned char string_data[10];				//onmetadata
		unsigned char type2;						//0x08
		unsigned char array_size[4];				

	}ScriptData;

};

