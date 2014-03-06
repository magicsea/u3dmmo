#ifndef _GC_ALLNET_H_
#define _GC_ALLNET_H_
#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <list>
#include <string>
//#include "g_debug.h"
#include "../net/platform.h"
#include "../net/g_tcpsession.h"
#include "../net/g_tcplistener.h"
//#include "interface.h"
//#include "cmd_region_client.h"
#include "../net/g_cmdpacket.h"
//#include "md5.h"
//#include "gc_math.h"
//#include "gc_iniset.h"
//#include "../Common/CommonPublic.h"
#include <assert.h>
//#include "../../Lib_3rdParty/vld-1.9/include/vld.h"
//
//#pragma comment (lib, "vld.lib")
//#include "s_cmdchannel.h"
#include "netcmdbase.h"
#include "session_bind_base.h"
#include "cmd_region_client.h"
#pragma warning (disable : 4996)
struct SConfig
{
	string client_listen_ip;
	bool   local_login;
	ULONG   unlogin_timeout;
	short  client_listen_port;
	ULONG   r2c_interval;
	ULONG   c2r_interval;
	long   cl_max_buffer;
	long   cl_pre_buffer;
};

//NET_LIB_API extern SConfig g_cfg;
//NET_LIB_API extern CSubLog g_slog;
typedef int (*TFunction)(void);

#ifndef _G_RELEASE
#define _G_RELEASE
#define SAFE_REP(r) if(!(r)) return false;
#define _RELEASE(A)			if( (A) != NULL ) { (A) -> Release(); (A) = NULL; }
#define _DELETE(X)			if( (X) != NULL ) { delete (X); (X) = NULL; } 
#define _DELETE_ARRAY(X)	if( (X) != NULL ) { delete[] (X); (X) = NULL; } 
#define _FREE(X)			if( (X) != NULL ) { free(X); (X)=NULL; } 
#define ZERO_MEM_ARRAY(X)  memset(X,0,sizeof(X))
#endif
NET_LIB_API extern char* g_strGamePathRes;//[256];//�����е�Ŀ¼����Դ����

#endif
