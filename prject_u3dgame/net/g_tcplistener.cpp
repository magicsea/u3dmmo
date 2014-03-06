//#include "stdafx.h"
//#include "net_lib_private.h"
/*
g_tcplistener.cpp: implementation of the CG_TCPListener class.
*/

#include "g_tcplistener.h"
//#include "g_util.h"
CG_TCPListener::CG_TCPListener()
{

}

CG_TCPListener::~CG_TCPListener()
{

}

bool CG_TCPListener::StartListen(const char *ip, int port,bool encrypt)
{
	m_socket.Initialize(NETWORK_PROTOCOL_TCP);
	m_socket.SetReuseAddr(true);
	if(!m_socket.BindAddr(ip,port)) return false;
	
	// initialize random seed 
	srand(Sys_GetTime());
	m_bEncrypt = encrypt;
	return m_socket.Listen();
}

CG_TCPSession *CG_TCPListener::AcceptNewSession()
{
	if(!m_socket.CanRead()) return false;
	SOCKET socket = m_socket.Accept();
	if(!socket) return false;
	
	CG_TCPSession *tmp = new CG_TCPSession;
	tmp->Attach(socket);
	
	// set encrypt seed 
	tmp->SendSeed(ComputeSeed());
	return tmp;
}

void CG_TCPListener::Close()
{
	m_socket.Close();
}

long CG_TCPListener::ComputeSeed()
{
	long seed = 0;
	if(!m_bEncrypt) return seed;
	seed |= rand()<<16;
	seed |= rand();
	return seed;
}
