#include "AdtsHeader.h"

CAdtsHeader::CAdtsHeader()
{
	memset(this, 0 , sizeof(*this));
	syncword1 = 0xff                    ;  //同步头总是0xFFF,代表着一个ADTS帧的开始
	syncword2 = 0x0f                    ;  //syncword1 << 4 | syncword2

	protection_absent = 1               ;
	layer = 0x00                        ;  //always: '00'
	ID = 0x00                           ;  //Version: 0 f

	private_bit = 0                     ;
	copyright_identification_start = 0  ;
	copyright_identification_bit = 0    ;
	home = 0                            ;
	original_copy = 0                   ;  

	adts_buffer_fullness1 = 0xff        ; //0x7FF 说明是码率可变的码流
	adts_buffer_fullness2 = 0xff        ; 
	number_of_raw_data_blocks_in_frame = 0;

};

CAdtsHeader::~CAdtsHeader(void)
{

}

/*设置adts头信息
 *channel_cfg    声道数
 *sampling_fre   采样率下标
 *profile        AAC的级别
 */

void CAdtsHeader::SetAdtsInfo(uchar_t channel_cfg, uchar_t sampling_fre, uchar_t profile)
{
	channel_configuration1 = channel_cfg >> 2 & 0x01;  //表示声道数 
	channel_configuration2 = channel_cfg & 0x03     ;  

	sampling_frequency_index = sampling_fre         ;  //表示使用的采样率下标

	profile = profile                               ;  //表示使用哪个级别的AAC,定义了3种
}

/*aac_stream_len ACC原始流长度*/
void CAdtsHeader::SetAacFrameLength( int32_t aac_stream_len )
{
	aac_stream_len += ADTS_HEADER_SIZE              ;  // + pce_size
	aac_frame_length1 = aac_stream_len >>11 &0x03   ;
	aac_frame_length2 = aac_stream_len >>3 & 0xff   ; 
	aac_frame_length3 = aac_stream_len & 0x07       ;  //一个ADTS帧的长度包括ADTS头和AAC原始流
}
