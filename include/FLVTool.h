#pragma once
#include "stdafx.h"

class CFLVTool
{
public:
	CFLVTool(void);
	~CFLVTool(void);
	/*�ı��С�� תΪuint��*/
	static uint32_t rev_toi(const void* p, int len);
	/*�ı��С�� �ַ���תdouble*/
	static double str2double(const uchar_t* hex, const uint32_t len);
};
