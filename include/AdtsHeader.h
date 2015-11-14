#pragma once
#include "stdafx.h"

#define ADTS_HEADER_SIZE 7

/*ACC - ADTS 头*/
//ADTS的头信息 7个字节的Adtsheader
// 
class CAdtsHeader
{
public:
	CAdtsHeader(void);
	~CAdtsHeader(void);
	
	/*设置adts头信息
	 *channel_cfg    声道数
	 *sampling_fre   采样率下标
	 *profile        AAC的级别
	 */
	void SetAdtsInfo(uchar_t channel_cfg, uchar_t sampling_fre, uchar_t profile );

	/*设置 aac_stream_len ACC原始流长度*/
	void SetAacFrameLength( int32_t aac_stream_len );


private:
	/* adts_fixed_header */
	uchar_t syncword1                           ;  //同步头总是0xFFF,代表着一个ADTS帧的开始

	uchar_t protection_absent                  :1;
	uchar_t layer                              :2;  //always: '00'
	uchar_t ID                                 :1;  //Version: 0 f
	uchar_t syncword2                          :4;  //syncword1 << 4 | syncword2

	uchar_t channel_configuration1             :1;  //表示声道数 
	uchar_t private_bit                        :1;
	uchar_t sampling_frequency_index           :4;  //表示使用的采样率下标
	uchar_t profile                            :2;  //表示使用哪个级别的AAC,定义了3种 0 1 2

	/* adts_variable_header */
	uchar_t aac_frame_length1                   :2; //一个ADTS帧的长度包括ADTS头和AAC原始流
	uchar_t copyright_identification_start      :1;
	uchar_t copyright_identification_bit        :1;
	uchar_t home                                :1;
	uchar_t original_copy                       :1;  
	uchar_t channel_configuration2              :2;  //表示声道数 

	uchar_t aac_frame_length2                     ; 

	uchar_t adts_buffer_fullness1               :5; //0x7FF 说明是码率可变的码流
	uchar_t aac_frame_length3                   :3; //aac_frame_length1<<11 |aac_frame_length2 <<3 
	// |aac_frame_length3

	uchar_t number_of_raw_data_blocks_in_frame  :2;
	uchar_t adts_buffer_fullness2               :6; //0x7FF 说明是码率可变的码流

};