#pragma once
#include "stdafx.h"
#include "FLVTool.h"



//1. flv文件头
class CFLVHeader 
{
public:
	CFLVHeader(void* buf =NULL);
	~CFLVHeader(void);

	/*送入数据*/
	void OnData(void* buf);

	/*是否是flv头*/
	bool isFLVHeader() const;

	/*video标志*/
	uchar_t GetTypeflags_audio() const;

	/*audio标志*/
	uchar_t GetTypeflags_video() const;

	/*输出FLV头*/
	void PrintFLVHead();

private:
	uchar_t m_signature_1;				//'F' (0x46)
	uchar_t m_signature_2;				//'L' (0x4C)
	uchar_t m_signature_3;				//'V' (0x56)
	uchar_t m_version;					//版本

	//typeflag的第0位和第2位,分别表示video与audio存在的情况
	//(1表示存在,0表示不存在) 
	uchar_t m_typeflags_video			:1;			//UB [1]	1 = Video tags are present
	uchar_t m_typeflags_reserved		:1;			//UB [1]	Shall be 0
	uchar_t m_typeflags_audio			:1;			//UB [1]	1 = Audio tags are present
	uchar_t m_typeflags_eserved		    :5;			//UB [5]	Shall be 0

	uchar_t dataoffset[4];					//头的长度  最后4个字节表示FLV header 长度.
};


//2. 前一个tag的长度 4个字节
typedef uchar_t preTagSize[4]; 