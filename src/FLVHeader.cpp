#include "FLVHeader.h"
CFLVHeader::CFLVHeader(void* buf)
{	
	OnData(buf);
}

CFLVHeader::~CFLVHeader(void)
{

}

/*��������*/
void CFLVHeader::OnData(void* buf)
{
	//��ʼ��Ϊ0 
	memset(this, 0, sizeof(*this));
	if(buf == NULL)
	{
		return ;
	}
	*this = *(CFLVHeader*)buf;
}

/*�Ƿ���flvͷ*/
bool CFLVHeader::isFLVHeader() const
{
	if(m_signature_1 == 'F' && m_signature_1 == 'L' && m_signature_1 == 'V')
	{
		return true;
	}
	return false;
}

unsigned char CFLVHeader::GetTypeflags_video() const 
{
	return m_typeflags_video; 
}
unsigned char CFLVHeader::GetTypeflags_audio() const 
{ 
	return m_typeflags_audio;
}


//���FLVͷ
void CFLVHeader::PrintFLVHead()
{
	printf("signature_1         = %c\n", m_signature_1);
	printf("signature_2         = %c\n", m_signature_2);
	printf("signature_3         = %c\n", m_signature_3);
	printf("version             = %d\n", m_version);
	printf("typeflags_video     = %d\n", m_typeflags_video);
	printf("typeflags_reserved  = %d\n", m_typeflags_reserved);
	printf("typeflags_audio     = %d\n", m_typeflags_audio);
	printf("typeflags_eserved   = %d\n", m_typeflags_eserved);

	unsigned char* p = dataoffset;
	printf("dataoffset          = %d\n\n", CFLVTool::rev_toi(p,4));
}