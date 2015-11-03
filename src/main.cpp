#include "stdafx.h"
#include "osl_log.h"
#include "osl.h"
#include "osl_file.h"
#include <stdio.h>
#include "FLVHeader.h"
#include "TagHeader.h"
#include "MetaData.h"

//文件路径
char* flv_file = "./test.flv";

int main()
{
	CFLVHeader flv_head;
	preTagSize pretag_size; 
	CTagHeader tag_head;
	CMetaData metadata;
	osl_log_set_target( "console://" );
	int count = 10 ;
	/* 初始化资源 */
	int32_t ret = osl_init( "123");

	if( ret == -1 )
	{
		osl_log_error( "%s[%d], osl_init failed!\n", __FILE__, __LINE__ );
		goto ERROR_EXIT;
	}

	void* fp;
	/* 打开文件, mode=OSL_FILE_READ_ONLY */
	fp = osl_file_open(flv_file, OSL_FILE_READ_ONLY);

	if(fp  == NULL)
	{
		osl_log_info( "%s[%d], osl_file_open faild path = %s\n", __FILE__, __LINE__, flv_file);
		goto ERROR_EXIT;
	}
	

	char_t buf[99999];
	osl_file_read(fp, &flv_head, sizeof(flv_head));

	

	while ( !osl_file_eof( fp ) && count -- )
	{	
		osl_file_read(fp, &pretag_size, sizeof(preTagSize));
		osl_file_read(fp, &tag_head, sizeof(tag_head));
		osl_file_read(fp, buf, tag_head.GetDatasize() );
		if (tag_head.GetTagtype() == 0x12)
		{
			metadata.OnData(buf);
			metadata.print_info();
		}
		//打印
		printf("pretag_size = %u\n", CFLVTool::rev_toi(pretag_size, sizeof(pretag_size) ) );
		tag_head.PrintTagHead();
		//break;
	}
	goto END_EXIT;

END_EXIT:
	osl_log_info( "press any key to continue !!\n");
	getchar();
	return 0;
ERROR_EXIT:
	osl_log_info( "press any key to continue !!\n");
	getchar();
	if(fp != NULL)
	{
		osl_file_close(fp);
	}
	return -1;
}
