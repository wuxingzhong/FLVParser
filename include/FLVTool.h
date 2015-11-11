#pragma once
#include "stdafx.h"

class CFLVTool
{
public:
	CFLVTool(void);
	~CFLVTool(void);
	/*改变大小端 转为uint型*/
	static uint32_t rev_toi(const void* p, int len);
	/*改变大小端 字符串转double*/
	static double str2double(const uchar_t* hex, const uint32_t len);
};
