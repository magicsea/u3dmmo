#include "g_util.h"
#include "interface.h"

bool CSubLog::Init(char* strPath)
{
	Sys_Init();
	Sys_EnableLog(true);
	
	g_message = new CG_LogDevice;
	g_warning = new CG_LogDevice;
	g_core	  = new CG_LogDevice;
	
	char strFileName[256];
	sprintf(strFileName,"%s\\message.txt",strPath);
	g_message->Init(strFileName);
	g_message->EnablePrint(true);
	g_message->EnableWriteFile(true);
	
	sprintf(strFileName,"%s\\warning.txt",strPath);
	g_warning->Init(strFileName);
	g_warning->EnablePrint(true);
	g_warning->EnableWriteFile(true);
	
	sprintf(strFileName,"%s\\core.txt",strPath);
	g_core->Init(strFileName);
	g_core->EnablePrint(true);
	g_core->EnableWriteFile(true);
	
	// search all class

	return true;
}

void CSubLog::OnFrame(unsigned long time,unsigned long delta)
{
	
}

void CSubLog::Exit()
{
	delete g_message;
	delete g_warning;
	delete g_core;
}

const char *CSubLog::GetName()
{
	return "log";
}