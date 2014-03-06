#pragma once

// C 运行时头文件
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include "Windows.h"

class RDConsoleWindowCL
{
public:
	RDConsoleWindowCL(void);
public:
	~RDConsoleWindowCL(void);

public:
	virtual void   Open(const char * title_) ;
	virtual void   Close() ;
	virtual void   OutputLine(const char* formatStr_ , ...) ;
	virtual void   OutputStr(const char * str_) ;

public:
	static RDConsoleWindowCL * g_colsole     ;
	static RDConsoleWindowCL & GetInstance() ;

protected:
	HANDLE m_hCon ;
};

RDConsoleWindowCL * RDGetConsoleWindow();


// 记录函数堆栈 [11/25/2009 wy]
#define MW_ASSERT_IMPL(expr, msg) \
{ if (!(expr)) { GMwAssertionHandler(#expr, msg, __FILE__, __FUNCTION__, __LINE__); } }

bool GMwAssertionHandler(	const char* pcExpression,
							const char* pcUserMessage,
							const char* pcFile,
							const char* pcFunction,
							const int iLine);