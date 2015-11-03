#include "MetaData.h"

CMetaData::CMetaData(void* buf)
{
	m_meta =  NULL;
	m_duration = 0.0;
	m_width = 0.0 ;
	m_height = 0.0;
	m_framerate = 0.0 ;

	OnData(buf);
}

CMetaData::~CMetaData(void)
{

}

/*送入数据*/
void CMetaData::OnData(void* buf)
{
	if(buf == NULL)
	{
		return;
	}
	m_meta = (uchar_t*)buf;
	//解析头部
	ParseMeta();
}


void CMetaData::ParseMeta() {

	uint32_t array_size= 0;
	uint32_t offset =  0;

	uint32_t name_len = 0;
	double name_value = 0;
	bool boolValue = false;
	uint32_t i = 0;
	ScriptData scriptData = { 0 };
	scriptData = *(ScriptData*)m_meta;
	offset = sizeof(scriptData);

	if(scriptData.type2 != 0x08) 
	{
		osl_log_error("metadata format failed!!\n");
		return ;
	}
	//数组长度
	array_size = CFLVTool::rev_toi(scriptData.array_size, 4);

	for( i = 0; i < array_size; i++)
	{
		name_value = 0;
		boolValue = false;

		name_len = 0;
		name_len |= m_meta[offset++];
		name_len = name_len << 8;
		name_len |= m_meta[offset++];

		char name[128];

		memset(name, 0, sizeof(name));
		memcpy(name, &m_meta[offset], name_len);
		name[name_len + 1] = '\0';
		offset += name_len;

		switch(m_meta[offset++])
		{
		case 0x0: //Number type
			name_value = CFLVTool::str2double(&m_meta[offset], 8);
			offset += 8;
			break;

		case 0x1: //Boolean type
			if(offset++ != 0x00) {
				boolValue = true;
			}
			break;

		case 0x2: //String type
			name_len = 0;
			name_len |= m_meta[offset++];
			name_len = name_len << 8;
			name_len |= m_meta[offset++];
			offset += name_len;
			break;

		case 0x12: //Long string type
			name_len = 0;
			name_len |= m_meta[offset++];
			name_len = name_len << 8;
			name_len |= m_meta[offset++];
			name_len = name_len << 8;
			name_len |= m_meta[offset++];
			name_len = name_len << 8;
			name_len |= m_meta[offset++];
			offset += name_len;
			break;
		default:
			break;
		}

		if(strncmp(name, "duration", 8)	== 0)
		{
			m_duration = name_value;
		} 
		else if(strncmp(name, "width", 5)	== 0) 
		{
			m_width = name_value;
		} 
		else if(strncmp(name, "height", 6) == 0) 
		{
			m_height = name_value;
		} 
		else if(strncmp(name, "framerate", 9) == 0) 
		{
			m_framerate = name_value;
		} 

	}
}



double CMetaData::GetDuration() 
{
	return m_duration;
}


double CMetaData::GetWidth()
{
	return m_width;
}

double CMetaData::GetHeight()
{
	return m_height;
}

double CMetaData::GetFramerate()
{
	return m_framerate;
}

/*打印信息*/
void CMetaData::print_info() const
{
	printf("m_duration         = %f\n", m_duration);
	printf("m_width            = %f\n", m_width);
	printf("m_height           = %f\n", m_height);
	printf("m_framerate        = %f\n\n", m_framerate);
}