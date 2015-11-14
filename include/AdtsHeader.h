#pragma once
#include "stdafx.h"

#define ADTS_HEADER_SIZE 7

/*ACC - ADTS ͷ*/
//ADTS��ͷ��Ϣ 7���ֽڵ�Adtsheader
// 
class CAdtsHeader
{
public:
	CAdtsHeader(void);
	~CAdtsHeader(void);
	
	/*����adtsͷ��Ϣ
	 *channel_cfg    ������
	 *sampling_fre   �������±�
	 *profile        AAC�ļ���
	 */
	void SetAdtsInfo(uchar_t channel_cfg, uchar_t sampling_fre, uchar_t profile );

	/*���� aac_stream_len ACCԭʼ������*/
	void SetAacFrameLength( int32_t aac_stream_len );


private:
	/* adts_fixed_header */
	uchar_t syncword1                           ;  //ͬ��ͷ����0xFFF,������һ��ADTS֡�Ŀ�ʼ

	uchar_t protection_absent                  :1;
	uchar_t layer                              :2;  //always: '00'
	uchar_t ID                                 :1;  //Version: 0 f
	uchar_t syncword2                          :4;  //syncword1 << 4 | syncword2

	uchar_t channel_configuration1             :1;  //��ʾ������ 
	uchar_t private_bit                        :1;
	uchar_t sampling_frequency_index           :4;  //��ʾʹ�õĲ������±�
	uchar_t profile                            :2;  //��ʾʹ���ĸ������AAC,������3�� 0 1 2

	/* adts_variable_header */
	uchar_t aac_frame_length1                   :2; //һ��ADTS֡�ĳ��Ȱ���ADTSͷ��AACԭʼ��
	uchar_t copyright_identification_start      :1;
	uchar_t copyright_identification_bit        :1;
	uchar_t home                                :1;
	uchar_t original_copy                       :1;  
	uchar_t channel_configuration2              :2;  //��ʾ������ 

	uchar_t aac_frame_length2                     ; 

	uchar_t adts_buffer_fullness1               :5; //0x7FF ˵�������ʿɱ������
	uchar_t aac_frame_length3                   :3; //aac_frame_length1<<11 |aac_frame_length2 <<3 
	// |aac_frame_length3

	uchar_t number_of_raw_data_blocks_in_frame  :2;
	uchar_t adts_buffer_fullness2               :6; //0x7FF ˵�������ʿɱ������

};