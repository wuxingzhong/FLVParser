#include "AdtsHeader.h"

CAdtsHeader::CAdtsHeader()
{
	memset(this, 0 , sizeof(*this));
	syncword1 = 0xff                    ;  //ͬ��ͷ����0xFFF,������һ��ADTS֡�Ŀ�ʼ
	syncword2 = 0x0f                    ;  //syncword1 << 4 | syncword2

	protection_absent = 1               ;
	layer = 0x00                        ;  //always: '00'
	ID = 0x00                           ;  //Version: 0 f

	private_bit = 0                     ;
	copyright_identification_start = 0  ;
	copyright_identification_bit = 0    ;
	home = 0                            ;
	original_copy = 0                   ;  

	adts_buffer_fullness1 = 0xff        ; //0x7FF ˵�������ʿɱ������
	adts_buffer_fullness2 = 0xff        ; 
	number_of_raw_data_blocks_in_frame = 0;

};

CAdtsHeader::~CAdtsHeader(void)
{

}

/*����adtsͷ��Ϣ
 *channel_cfg    ������
 *sampling_fre   �������±�
 *profile        AAC�ļ���
 */

void CAdtsHeader::SetAdtsInfo(uchar_t channel_cfg, uchar_t sampling_fre, uchar_t profile)
{
	channel_configuration1 = channel_cfg >> 2 & 0x01;  //��ʾ������ 
	channel_configuration2 = channel_cfg & 0x03     ;  

	sampling_frequency_index = sampling_fre         ;  //��ʾʹ�õĲ������±�

	profile = profile                               ;  //��ʾʹ���ĸ������AAC,������3��
}

/*aac_stream_len ACCԭʼ������*/
void CAdtsHeader::SetAacFrameLength( int32_t aac_stream_len )
{
	aac_stream_len += ADTS_HEADER_SIZE              ;  // + pce_size
	aac_frame_length1 = aac_stream_len >>11 &0x03   ;
	aac_frame_length2 = aac_stream_len >>3 & 0xff   ; 
	aac_frame_length3 = aac_stream_len & 0x07       ;  //һ��ADTS֡�ĳ��Ȱ���ADTSͷ��AACԭʼ��
}
