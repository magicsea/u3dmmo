#include "RDConsoleWindowCL.h"
#include "../StackWalker/StackWalker.h"
#include "../share/interface.h"

RDConsoleWindowCL * RDConsoleWindowCL::g_colsole = NULL ;

RDConsoleWindowCL * RDGetConsoleWindow()
{
	if(RDConsoleWindowCL::g_colsole == NULL)
		RDConsoleWindowCL::g_colsole = &RDConsoleWindowCL::GetInstance() ;

	return RDConsoleWindowCL::g_colsole ;
}

void RDSetConsoleWindow(void * console_)
{
    RDConsoleWindowCL::g_colsole = (RDConsoleWindowCL *)console_ ;
}

RDConsoleWindowCL::RDConsoleWindowCL(void)
:m_hCon(NULL)
{
}

RDConsoleWindowCL::~RDConsoleWindowCL(void)
{
}

RDConsoleWindowCL & RDConsoleWindowCL::GetInstance()
{
     static RDConsoleWindowCL instance ;
	 return instance ;
}

void RDConsoleWindowCL::Open(const char * title_)
{
	if(m_hCon == NULL)
	{
	    AllocConsole();
	    m_hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		 SetConsoleTitle(title_);
	}
}

void RDConsoleWindowCL::Close()
{
    if(m_hCon != NULL)
	{
        FreeConsole();
        m_hCon = NULL;
	}
}

void RDConsoleWindowCL::OutputStr(const char * str_)
{
    if(m_hCon != NULL)
	{
		DWORD dwWritten=0;
		WriteConsole(m_hCon,str_,strlen(str_),&dwWritten,NULL) ;
	}
}


void RDConsoleWindowCL::OutputLine(const char* formatStr_ , ...) 
{
	char szMsg[1024];
	va_list ap;
	va_start( ap, formatStr_ );
	szMsg[_vsnprintf(szMsg,sizeof(szMsg)-1,formatStr_,ap)] = 0;
	va_end  ( ap );
	int len = (int)strlen(szMsg) ;
	szMsg[len] = '\n' ;
	szMsg[len + 1] = '\0' ;
	OutputStr(szMsg);
}

bool GMwAssertionHandler(	const char* pcExpression,
						 const char* pcUserMessage,
						 const char* pcFile,
						 const char* pcFunction,
						 const int iLine)
{
	MyStackWalker sw; 
	sw.ShowCallstack();
	/*
	string assertDescription;
	assertDescription.Format(
		"表达式: %s\n\n"
		"说明: %s\n\n"
		"文件: %s\n"
		"行号: %d\n"
		"函数: %s\n"
		"堆栈: \n"
		"%s\n",
		pcExpression,
		pcUserMessage,
		pcFile,
		iLine,
		pcFunction,
		sw.GetContent());
	*/
	CORE("严重错误请报告程序","表达式: %s",pcExpression);
	CORE("严重错误","说明: %s",pcUserMessage);
	CORE("严重错误","文件: %s",pcFile);
	CORE("严重错误","行号: %d",iLine);
	CORE("严重错误","函数: %s",pcFunction);
	CORE("严重错误","堆栈:");//堆栈内容太长CORE要爆了，只能重写

	for (int i=0;i<(int)sw.m_oStackStrList.size();i++)
	{
		CORE("堆栈","%s",sw.m_oStackStrList[i].c_str());
	}
	
#ifdef GAME_SERVER
	//printf("%s",sw.GetContent().c_str());
#endif
	/*
	char* pcCaption = "断言";
	int iButtonResult = MessageBox(GMainHWND, buffer, pcCaption, MB_YESNO);


	switch(iButtonResult)
	{
	case IDYES:
		break;
	case IDNO:
		__asm int 3; 
		break;
	}
	*/

	return true;
}