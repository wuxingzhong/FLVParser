#include "stdafx.h"




/*
class AudioSpecificConfig
{
	uchar_t m_audioObjectType :5; //����ṹ���� AAC-LC Ϊ2
	
	uchar_t 
};
*/




class  CAudioData
{
public:
	CAudioData(void* buf = NULL);
	~CAudioData(void);
	/*��������*/
	void OnData(void* buf);

	/*��ȡ��Ƶ����*/
	uchar_t* GetPdata() const;

	/*��ӡ��Ϣ*/
	void print_info() const ;

protected:

private:
	/*Audio ��Ϣ*/
	uchar_t  m_sound_type	:1;			//���� 0--sndMono   1--sndStereo
	uchar_t  m_sound_size	:1;			//���� 0--8bits     1--16bits
	uchar_t  m_rate			:2;			//������ 0--5.5kHz  1--11KHz 2--22kHz  3--44kHz
	uchar_t  m_sound_format	:4;			//��Ƶ�������� 10 -- AAC

	
	/*audio  ������*/
	uchar_t  m_ACC_packet_type;			//0--AAC sequence header        1--AAC raw  data   
	uchar_t* m_pdata;

};

