#ifndef __CG_UTIL_H__
#define __CG_UTIL_H__

#include <fstream>
#include "../net/platform.h"
#include "interface.h"
const int DEFAULT_LOG_BUF_SIZE = 1024;

class CG_LogDevice : public ILogDevice
{
public:
	CG_LogDevice(); 
	virtual ~CG_LogDevice();

	bool Init(const char *file);
	void Exit();
	
	void Log(const char *prefix,const char *format,...);
	
	void EnablePrint(bool enable);
	void EnableIndex(bool enable);
	void EnableWriteFile(bool enable);
	void EnableTime(bool enable);

	// for vc
	void EnableDebugString(bool enable);

private:
	fstream m_file;
	bool m_bOpenFile;
	bool m_bWriteFile;
	bool m_bPrint;
	bool m_bDebugString;
	bool m_bTime;
	bool m_bIndex;
	bool m_bInit;
	
	int  m_idx;
	char m_name[128];
	char m_format[128];
	char m_buf[DEFAULT_LOG_BUF_SIZE];
};

#endif
