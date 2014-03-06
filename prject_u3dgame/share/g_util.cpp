#include "g_util.h"

ILogDevice *g_message,*g_warning,*g_core;

CG_LogDevice::CG_LogDevice()
{
   m_bInit = false;
   m_idx = 0;

   EnableTime(true);
   EnableIndex(false);
   EnableDebugString(false);
   EnableWriteFile(true);
   EnablePrint(true);
}

CG_LogDevice::~CG_LogDevice()
{

}

bool CG_LogDevice::Init(const char *file)
{
	char tmpTime[32],tmpDate[32];
	_strtime(tmpTime);
    _strdate(tmpDate);
 
	m_bInit = true;
	if(file)
	{
		m_file.open(file,ios::out);
		if(m_file.good()) m_bOpenFile = true;
		Log("Log: ","Log file %s create at [%s %s]",file,tmpDate,tmpTime);
	}

	return true;
}

void CG_LogDevice::Exit()
{

}

void CG_LogDevice::Log(const char *prefix,const char *format,...)
{
	if (!m_bInit) return;
	m_idx++;

	int pos = 0;
	
	if(m_bIndex)
	{
		pos += sprintf(m_buf+pos,"[%5d]",m_idx);
	}
	if(m_bTime)
	{
		char tmpTime[32];
		_strtime(tmpTime);
		pos += sprintf(m_buf+pos,"[%s]",tmpTime);
	}
	if(prefix)
	{
		pos += sprintf(m_buf+pos,"%s",prefix);
	}
	va_list args;
	va_start(args, format);
	pos += VSNPRINTF(m_buf+pos,DEFAULT_LOG_BUF_SIZE-50,format, args);
	
	m_buf[pos]	 = '\r';
	m_buf[pos+1] = '\n';
	m_buf[pos+2] = '\0';

#ifdef WIN32
	if(m_bDebugString) OutputDebugString(m_buf);
#endif

	if(m_bPrint) printf("%s",m_buf);
	if(m_bOpenFile && m_bWriteFile)
	{
		m_file.write(m_buf,pos+2);
		m_file.flush();
	}
	va_end(args);
}

void CG_LogDevice::EnablePrint(bool enable)
{
	m_bPrint = enable;
}

void CG_LogDevice::EnableWriteFile(bool enable)
{
	m_bWriteFile = enable;
}

void CG_LogDevice::EnableIndex(bool enable)
{
	m_bIndex = enable;
}

void CG_LogDevice::EnableTime(bool enable)
{
	m_bTime = enable;
}

void CG_LogDevice::EnableDebugString(bool enable)
{
	m_bDebugString = enable;
}
