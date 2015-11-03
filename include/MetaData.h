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

	/*��������*/
	void OnData(void* buf);
	
	/*������ʱ��*/
	double GetDuration();

	/*֡���*/
	double GetWidth();

	/*֡�߶�*/
	double GetHeight();
	
	/*֡��*/
	double GetFramerate();
	
	/*��ӡ��Ϣ*/
	void print_info();

private:
	uchar_t *m_meta;
    double m_duration;
    double m_width;
    double m_height;
    double m_framerate;

	/*����Meta*/
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

