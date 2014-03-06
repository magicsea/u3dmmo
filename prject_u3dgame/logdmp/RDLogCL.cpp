#include "RDLogCL.h"

#include <Dbghelp.h>
#pragma comment(lib,"dbghelp.lib")

RDLogCL * RDLogCL::g_log = NULL ;

// 异常处理函数
LONG WINAPI SDErrorUnhandledExceptionFilter(_EXCEPTION_POINTERS * pExceptionInfo);

RDLogCL * RDGetLog()
{
	if(RDLogCL::g_log == NULL)
		RDLogCL::g_log = &RDLogCL::GetInstance() ;

	return RDLogCL::g_log ;
}

void RDSetLog(void * log_)
{
    RDLogCL::g_log = (RDLogCL *)log_ ;
}

RDLogCL::RDLogCL(void)
:m_pFile(NULL)
,m_enable(true)
{
	SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER) SDErrorUnhandledExceptionFilter );

	Open() ;

	OutputLine("\n") ;
	OutputLine("/*-----------------RDLogStart----------------*/") ;

	SYSTEMTIME time ;
	GetSystemTime(&time) ;
	OutputLine("LogStartTime : %d年%d月%d日 , 星期%d" , time.wYear , time.wMonth , time.wDay , time.wDayOfWeek) ;
	OutputLine("               %d:%d:%d" , time.wHour , time.wMinute , time.wSecond) ;
	OutputLine("") ;
}

RDLogCL::~RDLogCL(void)
{
	Close() ;
}

RDLogCL & RDLogCL::GetInstance()
{
	static RDLogCL instance ;
	return instance ;
}

bool RDLogCL::Open() 
{
	char path[255] ;
    char fileName[255] ;

	::GetCurrentDirectory(255 , path) ;
	sprintf(fileName , "%s\\RDLogFile.txt" , path) ;

	m_pFile = fopen(fileName , "at") ;

	if(m_pFile == NULL)
		return false ;

	//将文件指针移动到文件结尾处
    fseek(m_pFile , 0 , SEEK_END) ;

	return true ;
}
bool RDLogCL::Close() 
{
    if(m_pFile != NULL)
	{
		fclose(m_pFile) ;
	}

	return true ;
}

void RDLogCL::OutputLine(const char* formatStr_ , ...) 
{
	if(m_enable == false)
		return ;

	char szMsg[1024];
	va_list ap;
	va_start( ap, formatStr_ );
	szMsg[_vsnprintf(szMsg,sizeof(szMsg)-1,formatStr_,ap)] = 0;
	va_end  ( ap );
	int len = (int)strlen(szMsg) ;
	szMsg[len] = '\n' ;
	szMsg[len + 1] = '\0' ;
	LogString(szMsg);
}

void RDLogCL::LogString(const char * str_)
{
	if(m_enable == false)
		return ;

	if(m_pFile == NULL)
		return ;

	SYSTEMTIME time ;
	GetLocalTime(&time) ;
    char temp[255] ;
	sprintf(temp , "[%02d:%02d:%02d:%03d] -- " , time.wHour , time.wMinute , time.wSecond , time.wMilliseconds) ;
	fwrite(temp , strlen(temp) , 1 , m_pFile) ;
	RDGetConsoleWindow()->OutputStr(temp) ;

	fwrite(str_ , strlen(str_) ,1, m_pFile) ;

    RDGetConsoleWindow()->OutputStr(str_) ;
}

void RDLogCL::OpenConsole(const char * title_)
{
	RDGetConsoleWindow()->Open(title_) ;
}

//void RDLogCL::RegistToLua(LuaWrap * wrapper_)
//{
//}
//
//void RDLogCL::UnRegistToLua(LuaWrap * wrapper_)
//{
//}

void RDLogCL::SetEnable(bool type_)
{
    m_enable = type_ ;
}

// 异常处理函数
LONG WINAPI SDErrorUnhandledExceptionFilter(_EXCEPTION_POINTERS * pExceptionInfo)
{
	// 此函数为全进程有效
	HANDLE								hFile;
	BOOL								bResult;
	MINIDUMP_EXCEPTION_INFORMATION		sException;
	MINIDUMP_USER_STREAM_INFORMATION	sUserStreamInfo;
	MINIDUMP_USER_STREAM				sUserStream[8];		// 最多8个用户流
//	char								strSystemInfo[1024*4];
	void *								pScreenShot = NULL;
	char        msgBuf[MAX_PATH];
//	char        szFile[MAX_PATH];
	char szDumpPath[_MAX_PATH];
//	char szScratch[_MAX_PATH];
	SYSTEMTIME  sysTime;
	GetLocalTime(&sysTime);
	sprintf(msgBuf,"%d_%d_%d_%d_%d_%d",sysTime.wYear,sysTime.wMonth,sysTime.wDay,
		sysTime.wHour,sysTime.wMinute,sysTime.wSecond);

	char path[255] ;

	::GetCurrentDirectory(255 , path) ;
	sprintf(szDumpPath , "%s//%s.dmp" , path,msgBuf) ;


	//string strModalPath = CFileMgr::GetModulePath()+ "\\Log\\";		
	//_tcscpy(szDumpPath,strModalPath.c_str());
	//_tcscat(szDumpPath,msgBuf);
	//_tcscat(szDumpPath,".dmp");

	// 	// 创建临时DUMP文件
	// 	//hFile = ::CreateFile(szDumpPath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	// 	hFile = CreateFile(szDumpPath,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	// 
	// 创建临时DUMP文件
	//hFile = CreateFile("TempDump.dmp",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	hFile = CreateFile(szDumpPath,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if( hFile == INVALID_HANDLE_VALUE ) return false;

	if( pExceptionInfo )
	{
		sException.ClientPointers		= TRUE;
		sException.ThreadId				= GetCurrentThreadId();
		sException.ExceptionPointers	= pExceptionInfo;
	}


	// 用户数据流
	sUserStreamInfo.UserStreamCount	= 0;
	sUserStreamInfo.UserStreamArray = sUserStream;

	// 写DUMP
	bResult = MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MiniDumpNormal,
		(pExceptionInfo?&sException:NULL),
		(sUserStreamInfo.UserStreamCount?&sUserStreamInfo:NULL),
		NULL
		);

	// 清理环境
	CloseHandle(hFile);

	//char UploadExeName[255] ;

	//sprintf(UploadExeName , "FtpUpload.exe %s.dmp" , msgBuf) ;

	//WinExec(UploadExeName,SW_SHOW);


	return EXCEPTION_EXECUTE_HANDLER;
}
