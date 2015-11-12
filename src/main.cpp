#include "stdafx.h"
#include "osl_log.h"
#include "osl.h"
#include "osl_file.h"
#include <stdio.h>
#include "FLVParser.h"


//文件路径
char* flv_file = "./test.flv";
char* H264_file = "./test.h264";


//在一段内存中查找 出现的一段字节码 返回发现的字节码起始位置 ,为发现返回NULL
uchar_t* MemFind(uchar_t* pmain, int32_t main_len, uchar_t* psub, int32_t sub_len)
{
	int32_t offset = 0;
	while( (offset + sub_len)< main_len )
	{
		if ( memcmp(pmain + offset, psub, sub_len) == 0)
		{
			break ;
		}
		offset ++;
	}
	if( main_len <= (offset + sub_len) )
	{
		return NULL;
	}
	return pmain + offset;

}

int main()
{
	char_t* pbuf = NULL;
	int32_t readsize = 0;
	int32_t data_type ;

	osl_log_set_target( "console://" );
	printf("%s\n", "ts_format of  begin!!!!");

	void* fp_h264;
	CFlvParser flvparser;

	/* 初始化资源 */
	int32_t ret = osl_init( "123");
	if( ret == -1 )
	{
		osl_log_error( "%s[%d], osl_init failed!\n", __FILE__, __LINE__ );
		goto ERROR_EXIT;
	}


	fp_h264 = osl_file_open(H264_file, OSL_FILE_WRITE_ONLY);

	flvparser.Initialize();
	flvparser.OnData(flv_file);

	//是否是flv文件
	if( !flvparser.IsFlvFile() ) 
	{
		osl_log_error( "%s[%d],  this file is not a flv file!\n", __FILE__, __LINE__ );
		goto ERROR_EXIT;
	}
	while( !flvparser.IsFlvEOF() )
	{

		flvparser.GetNextRealData(&pbuf, &readsize, &data_type);
		if(data_type == AVC_NAL_DATA)
		{
			//写H264
			printf("time === %u\n", flvparser.GetTimestamp());
			osl_file_write(fp_h264, pbuf, readsize);
		}
		else if(data_type == ACC_AUDIO_DATA)
		{
			printf("audio____time === %u\n", flvparser.GetTimestamp());
		}

	}
	
	goto END_EXIT;

END_EXIT:
	osl_log_info( "press any key to continue !!\n");
	getchar();
	osl_file_close(fp_h264);
	flvparser.Release();
	return 0;
ERROR_EXIT:
	getchar();
	osl_file_close(fp_h264);
	flvparser.Release();
	return -1;
}
