#pragma once

/**
*日志文件内容输出
*输出文件目录为工作目录下
*输出文件名称为，RDLogFile.txt
*/

// C 运行时头文件
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include "Windows.h"
#include "RDConsoleWindowCL.h"

#define  RDLog_enable       RDGetLog()->SetEnable
#define  RDLog_outputLine   RDGetLog()->OutputLine
#define  RDLog_outputStr    RDGetLog()->LogString
#define  RDLog_OpenConsole  RDGetLog()->OpenConsole

//#define  SAFE
//#define  UNSAFE 
//
//#ifdef _DEBUG


#ifdef GAME_CLIENT
#ifdef _DEBUG
#define  SAFE      try{
#define  UNSAFE    }catch(...){	RDLog_outputLine("File:%s  Line:%d  Function:%s" ,__FILE__ , __LINE__ , __FUNCTION__ ) ;RDGetLog()->Close() ;RDGetLog()->Open() ;throw;}
#else
#define  SAFE 
#define  UNSAFE
#endif
//throw; \}
#else
#define  SAFE      try{
#ifdef _DEBUG
#define  UNSAFE    }catch(...){CORE("EXCEPT: ", "%s %s %d error", __FILE__, __FUNCTION__ ,__LINE__);RDGetLog()->Close() ;RDGetLog()->Open() ;throw;}
#else
#define  UNSAFE    }catch(...){CORE("EXCEPT: ", "%s %s %d error", __FILE__, __FUNCTION__ ,__LINE__);}
#endif


#endif

//#else
//#define  SAFE      try{
//#ifdef GAME_CLIENT
//#define  UNSAFE    }catch(...){RDLog_outputLine("File:%s  Line:%d  Function:%s" , __FILE__ , __LINE__ , __FUNCTION__ ) ;}
//#else
//#define  UNSAFE    }catch(...){CORE("EXCEPT: ", "%s %s %d error", __FILE__, __FUNCTION__ ,__LINE__);}
//#endif

	//throw; }
//#define  SAFE
//#define  UNSAFE 
//#endif
	

class RDLogCL
{
public:
	RDLogCL(void);
	~RDLogCL(void);

public:
	virtual bool Open() ;
	virtual bool Close() ;

	//virtual void RegistToLua(LuaWrap * wrapper_) ;
	//virtual void UnRegistToLua(LuaWrap * wrapper_) ;

public :
	virtual void SetEnable  (bool type_) ;
	virtual void OutputLine (const char* formatStr_ , ...) ;
	virtual void LogString  (const char * str_) ;
	virtual void OpenConsole(const char * title_) ;

public:
	/*----------------------lua注册功能----------------------*/
	//DEFINE_TYPENAME("RDLogCL");
	//BEGIN_REGLUALIB("RDLogCL")
	//	END_REGLUALIB()
	//	BEGIN_REGLUALIB_MEMBER()
	//	//LUALIB_ITEM_FUNC("OutputLine"    , void(RDLogCL * , const char * , ...) , &RDLogCL::OutputLine)
	//	LUALIB_ITEM_FUNC("LogString"     , void(RDLogCL * , const char *      ) , &RDLogCL::LogString)
	//	LUALIB_ITEM_FUNC("OpenConsole"   , void(RDLogCL * , const char *      ) , &RDLogCL::OpenConsole)
	//	END_REGLUALIB_MEMBER()
		/*-------------------------------------------------------*/

public:
	static RDLogCL * g_log         ;
	static RDLogCL & GetInstance() ;

public :
	FILE    * m_pFile  ;
	bool      m_enable ;
};
RDLogCL * RDGetLog();
void RDSetLog(void * log_);