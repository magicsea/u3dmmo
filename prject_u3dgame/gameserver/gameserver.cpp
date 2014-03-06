// gameserver.cpp: 主项目文件。

#include "stdafx.h"
#include "stdio.h"
#include "gc_allnet.h"
#include "GameWorld.h"
#include "interface.h"
//using namespace System;



//#define CORE printf
bool g_bGameRun = false;

SConfig g_cfg;
CSubLog g_slog;
CG_CmdPacket   *g_sendCmd=NULL;
char g_strLogPath[256];

bool startup();
void run();
void gameend();
int _tmain(int argc, _TCHAR* argv[])
{
    //Console::WriteLine(L"Hello World");
	printf("game server start...\n");
	if (!startup())
	{
		CORE("","startup error...\n");
		getchar();
		return -1;
	}

	CORE("","game server start ok!\n");
	g_bGameRun = true;

	run();

	CORE("","game server closed\n");
	gameend();
    return 0;
}
char* g_strGamePathRes=NULL;
bool startup()
{
	g_strGamePathRes = new char[512];
	memset(g_strGamePathRes,0,512);
	GetCurrentDirectory(512,g_strGamePathRes);
	//GetModuleFileName(NULL,strDir,512);
	char strTime[32];
	time_t t;
	time(&t);	
	struct tm* when = localtime(&t);	
	sprintf(strTime, "0_%d.%d_%d", when->tm_mon+1, when->tm_mday, when->tm_hour);	

	sprintf(g_strLogPath,"%s\\serverlog\\%s",g_strGamePathRes,strTime);
	CreateDirectory(g_strLogPath, NULL);

	g_slog.Init(g_strLogPath);
	CORE("region: ","游戏路径%s",g_strGamePathRes);

	g_sendCmd = new CG_CmdPacket;
	g_sendCmd->SetSize(MAX_CMD_PACKET_SIZE);

	bool bInitOk = GetApp()->init();
	return bInitOk;
}

void run()
{
	GetApp()->run();
}

void gameend()
{
	GetApp()->releaseAll();
}
