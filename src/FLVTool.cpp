#include "FLVTool.h"

CFLVTool::CFLVTool(void)
{

}
CFLVTool::~CFLVTool(void)
{

}

/*改变大小端 转为uint型*/
uint32_t CFLVTool::rev_toi(const void* p, int len)
{
	uint32_t ret = 0;
	uchar_t*  pbuf = (uchar_t* )p;
	int count = 0;

	if(p == NULL  || len <= 0 )
	{
		return ret;
	}

	//修正
	if(len > 4)
	{
		len = 4;
	}

	while (count < len)
	{
		ret |= (uint32_t)( pbuf[count] ) << (8* (len - count - 1) );
		count ++ ;
	}
	return ret;
}

/*改变大小端 字符串转double*/
double CFLVTool::str2double(const uchar_t* hex, const uint32_t len) 
{

	double ret = 0;
	uchar_t hexstr[8];
	uint32_t i = 0;
	//修正
	if(len > 8)
	{
		(uint32_t)len = 8;
	}

	for( i = 0; i < len; i++) 
	{
		hexstr[i] = hex[len - i - 1];
	}
	//转为double
	ret = *(double*)hexstr;
	return ret;
}