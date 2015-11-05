#pragma once
#include "stdafx.h"
#include "FLVTool.h"



//1. flv�ļ�ͷ
class CFLVHeader 
{
public:
	CFLVHeader(void* buf =NULL);
	~CFLVHeader(void);

	/*��������*/
	void OnData(void* buf);

	/*�Ƿ���flvͷ*/
	bool isFLVHeader() const;

	/*video��־*/
	uchar_t GetTypeflags_audio() const;

	/*audio��־*/
	uchar_t GetTypeflags_video() const;

	/*���FLVͷ*/
	void PrintFLVHead();

private:
	uchar_t m_signature_1;				//'F' (0x46)
	uchar_t m_signature_2;				//'L' (0x4C)
	uchar_t m_signature_3;				//'V' (0x56)
	uchar_t m_version;					//�汾

	//typeflag�ĵ�0λ�͵�2λ,�ֱ��ʾvideo��audio���ڵ����
	//(1��ʾ����,0��ʾ������) 
	uchar_t m_typeflags_video			:1;			//UB [1]	1 = Video tags are present
	uchar_t m_typeflags_reserved		:1;			//UB [1]	Shall be 0
	uchar_t m_typeflags_audio			:1;			//UB [1]	1 = Audio tags are present
	uchar_t m_typeflags_eserved		    :5;			//UB [5]	Shall be 0

	uchar_t dataoffset[4];					//ͷ�ĳ���  ���4���ֽڱ�ʾFLV header ����.
};


//2. ǰһ��tag�ĳ��� 4���ֽ�
typedef uchar_t preTagSize[4]; 