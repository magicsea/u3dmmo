/*
g_tcplistener.h: interface for the CG_TCPListener class.
*/

#ifndef __CG_TCP_LISTENER_H__
#define __CG_TCP_LISTENER_H__

#include "g_tcpsession.h"

//#include "Net_Lib_Def.h"
class NET_LIB_API CG_TCPListener  
{
public:
	void Close();
	bool StartListen(const char *ip,int port,bool encrypt=true);
	CG_TCPSession *AcceptNewSession();

	CG_TCPListener();
	virtual ~CG_TCPListener();

private:
	long ComputeSeed();
	bool m_bEncrypt;
	CG_NetSocket m_socket;
};

#endif
