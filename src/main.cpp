#include "stdafx.h"
#include "osl_log.h"
#include "osl.h"
#include "osl_file.h"
#include <stdio.h>
#include "FLVHeader.h"
#include "TagHeader.h"
#include "MetaData.h"
#include "VideoData.h"
#include "AudioData.h"
#include "AVCDecoderConfigurationRecord.h"
#include "AudioSpecificConfig.h"

#define NALU_TYPE_SLICE 1
#define NALU_TYPE_DPA 2
#define NALU_TYPE_DPB 3
#define NALU_TYPE_DPC 4
#define NALU_TYPE_IDR 5   //tag中读取的第一个关键帧（I帧）大部分是有一个SEI和一个I帧，
						  //有些不常见的是有多个SEI和一个I帧，这里未作处理，需要注意，
#define NALU_TYPE_SEI 6
#define NALU_TYPE_SPS 7
#define NALU_TYPE_PPS 8
#define NALU_TYPE_AUD 9　　//访问分隔符
#define NALU_TYPE_EOSEQ 10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL 12



//文件路径
char* flv_file = "./test.flv";
char* H264_file = "d:/test.h264";

int main()
{
	CFLVHeader flv_head;
	preTagSize pretag_size; 
	CTagHeader tag_head;
	CMetaData metadata;

	CVideoData videodata;
	CAVCDecoderConfigurationRecord config_record;

	CAudioData audiodata;
	CAudioSpecificConfig audio_config;
	osl_log_set_target( "console://" );

	int count = 20 ;
	/* 初始化资源 */
	int32_t ret = osl_init( "123");

	if( ret == -1 )
	{
		osl_log_error( "%s[%d], osl_init failed!\n", __FILE__, __LINE__ );
		goto ERROR_EXIT;
	}

	void* fp;
	void* fp_h264 ;
	/* 打开文件, mode=OSL_FILE_READ_ONLY */
	fp = osl_file_open(flv_file, OSL_FILE_READ_ONLY);

	if(fp  == NULL)
	{
		osl_log_info( "%s[%d], osl_file_open faild path = %s\n", __FILE__, __LINE__, flv_file);
		goto ERROR_EXIT;
	}
	

	char_t buf[99999];
	osl_file_read(fp, &flv_head, sizeof(flv_head));
	
	
	//写H264
	uchar_t header[4] ={0,0,0,1};
	fp_h264 = osl_file_open(H264_file, OSL_FILE_WRITE_ONLY);
	if(fp_h264  == NULL)
	{
		osl_log_info( "%s[%d], osl_file_open faild path = %s\n", __FILE__, __LINE__, flv_file);
		goto ERROR_EXIT;
	}

	while ( !osl_file_eof( fp ) )
	{	
		osl_file_read(fp, &pretag_size, sizeof(preTagSize));
		osl_file_read(fp, &tag_head, sizeof(tag_head));
		osl_file_read(fp, buf, tag_head.GetDatasize() );
		if (tag_head.GetTagtype() == TAG_TYPE_SCRIPT)
		{
			metadata.OnData(buf);
			//metadata.print_info();
		}else if(tag_head.GetTagtype() == TAG_TYPE_VIDEO)
		{
			videodata.OnData(buf);
			if( videodata.GetAVC_packet_type() == TAG_AVC_SEQUENCE_HEADER)
			{
				
				config_record.OnData(videodata.GetPdata());
				osl_file_write(fp_h264, header, 4);  //写入00 00 00 01头

				osl_file_write(fp_h264, 
				config_record.GetP_sequenceParameterSetNALUnit(), 
				config_record.GetSequenceParameterSetLength());	 //写入sps
				
				osl_file_write(fp_h264, header, 4);  //写入00 00 00 01头
				osl_file_write(fp_h264, 
				config_record.GetP_pictureParameterSetNALUnit(),
				config_record.GetPictureParameterSetLength());		//写入pps
				
			}
			else if( videodata.GetAVC_packet_type() == TAG_AVC_NALU)
			{
			
				uchar_t* pbuf = videodata.GetPdata();
				
				uint32_t nal_size = CFLVTool::rev_toi(pbuf, 4);
				//printf("%d= == = = = = == = \n", nal_size);
				pbuf +=4;
				osl_file_write(fp_h264, header, 4);  //写入00 00 00 01头
				osl_file_write(fp_h264, pbuf, nal_size);  //写入nal

			}
			//videodata.print_info();
		}else if(tag_head.GetTagtype() == TAG_TYPE_AUDIO)
		{
			audiodata.OnData(buf);
			if(audiodata.GetACC_packet_type() == TAG_AAC_SEQUENCE_HEADER)
			{
				audio_config.OnData(audiodata.GetPdata());
			}
			//audiodata.print_info();
		}
		//打印
		//printf("pretag_size = %u\n", CFLVTool::rev_toi(pretag_size, sizeof(pretag_size) ) );
		//tag_head.PrintTagHead();
		//break;
	}
	goto END_EXIT;

END_EXIT:
	osl_log_info( "press any key to continue !!\n");
	getchar();
	if(fp != NULL)
	{
		osl_file_close(fp);
	}
	if(fp_h264 != NULL)
	{
		osl_file_close(fp_h264);
	}
	return 0;
ERROR_EXIT:
	osl_log_info( "press any key to continue !!\n");
	getchar();
	if(fp != NULL)
	{
		osl_file_close(fp);
	}
	if(fp_h264 != NULL)
	{
		osl_file_close(fp_h264);
	}
	return -1;
}
