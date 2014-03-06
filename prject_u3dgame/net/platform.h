#ifndef __G_PLATFORM_H__
#define __G_PLATFORM_H__

#define NET_LIB_API
#define CORE  printf
#define MYMSG printf
#define _CRT_SECURE_NO_DEPRECATE
//#include "Net_Lib_Def.h"
#pragma warning (disable : 4793)

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>
#include <time.h>

#ifdef WIN32
	#include <windows.h>
#undef _countof
	#define _countof(array) (sizeof(array)/sizeof(array[0]))

	#define VSNPRINTF(a,b,c,d) _vsnprintf(a,b,c,d)

	/* thread operate*/
	#define CREATE_THREAD(func,arg)		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)func,(void*)arg,NULL,NULL)
	#define CREATE_THREAD_RET(ret)		((ret)==0)
	#define LOCK_CS(p)					EnterCriticalSection(p)	
	#define UNLOCK_CS(p)				LeaveCriticalSection(p)
	#define INIT_CS(p)					InitializeCriticalSection(p)
	#define DELETE_CS(p)				DeleteCriticalSection(p)					
	#define TYPE_CS						CRITICAL_SECTION 
	
	#define SLEEP(x)	Sleep(x)
#else
	#define LINUX
	#include <sys/time.h>
	#include <stddef.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <sys/wait.h>


	typedef int            BOOL;
	typedef unsigned char  BYTE;
	typedef unsigned short WORD;
	typedef unsigned int   DWORD;
	typedef unsigned long  ULONG;
	#define TRUE  1
	#define FALSE 0

	#define VSNPRINTF(a,b,c,d) vsnprintf(a,b,c,d)
	/* thread operate */
	#include <pthread.h>
	#include <semaphore.h>
	extern pthread_t _pthreadid;
	#define CREATE_THREAD(func,arg)		pthread_create(&_pthreadid,NULL,func,(void*)arg)
	#define CREATE_THREAD_RET(ret)		((ret)!=0)
	#define LOCK_CS(p)					sem_wait(p)	
	#define UNLOCK_CS(p)				sem_post(p)
	#define INIT_CS(p)					sem_init(p,0,1)
	#define DELETE_CS(p)				sem_destroy(p)					
	#define TYPE_CS						sem_t	

	#define SLEEP(x)	sleep(x/1000)	
#endif

void Sys_CreateConsole(int width, int height);
NET_LIB_API unsigned long Sys_GetTime();
NET_LIB_API unsigned long Sys_GetSec();
void Sys_Init();
void Sys_EnableLog(bool enable);
void Sys_Log(char *format,...);
void Sys_Sleep(int ms);
int	Sys_LzwComp(void *in,unsigned in_len,void *out);
int	Sys_LzwUncomp(void *in,unsigned in_len,void *out);

int Sys_EscapeString(const char *from,char escape,char *to,int len);
int Sys_GetString(const char *from,char escape,char *to,int len);

//trans utf and gbk
unsigned short iconv_convert(
	void *src,
	unsigned int src_len,
	char *src_charset,
	void *dest,
	unsigned int dest_len,
	char *dest_charset
	);

#include <map>
#include <list>
#include <vector>
#include <string>


using namespace std;
#ifdef WIN32
#include <hash_map>
using namespace stdext;
#else
//4.1.1gnu_cxx
//#include <ext/hash_map> 
//using namespace __gnu_cxx;
//4.6gnu_cxx
//#include <unordered_map>
#define hash_map map
#endif



/* type define */

struct eqstr {
  bool operator()(const char* s1,const char* s2) const {
    return strcmp(s1, s2) == 0;
  }
};

struct eqcstr {
  bool operator()(string &s1,string &s2) const {
    return s1 == s2;
  }
};

struct equlong {  
	bool operator()(const long u1, const long u2) const {
		return (u1==u2);
	};
};

//const int DEFAULT_LOG_BUF_SIZE = 1024;
#endif
