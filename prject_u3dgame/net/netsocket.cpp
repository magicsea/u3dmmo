//#include "stdafx.h"
//#include "net_lib_private.h"
//
// g_netsocket.cpp: implementation of the CG_NetSocket class.
//
#include "netsocket.h"
//#include "g_util.h"

#ifdef WIN32
	#pragma comment(lib, "Ws2_32.lib")
	//#pragma comment(lib,"winsock.lib")
#endif
#define LOG_NAME "NetLib:1 "

int CG_NetSocket::m_nCount = 0;

CG_NetSocket::CG_NetSocket()
{
	Reset();
}

CG_NetSocket::~CG_NetSocket()
{
	Close();
}

bool CG_NetSocket::_NetStartUp(int VersionHigh,int VersionLow)
{
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
 
	wVersionRequested = MAKEWORD(VersionHigh,VersionLow);
    err=WSAStartup(wVersionRequested, &wsaData);
	
	/* startup failed */
	if (err!=0)									
	{
		CORE(LOG_NAME,"WSAStartup error");
		WSACleanup();
		return false;
	}

	/* version error */
	if (LOBYTE(wsaData.wVersion)!= VersionLow ||
        HIBYTE(wsaData.wVersion)!= VersionHigh ) 
	{
		CORE(LOG_NAME,"WSAStartup version error");
		WSACleanup();
		return false;
	}
	CORE(LOG_NAME,"WSAStartup ok");
#endif
	return true;
}

bool CG_NetSocket::_NetCleanUp()
{
#ifdef WIN32	
	WSACleanup();
	CORE(LOG_NAME,"WSACleanup ok");
#endif
	return true;
}

bool CG_NetSocket::Initialize(int protocol)
{
	if (m_nCount++==0)
		if (!_NetStartUp(1,1)) return false;

	if (protocol==NETWORK_PROTOCOL_UDP)
	{
		m_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	}
	else 
	{
		m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	}

	if(m_socket==INVALID_SOCKET) 
	{
		return false;
	}
	SetNonBlocking();
	
	//SetSendBufferSize(32*1024);
	//SetRecvBufferSize(16*1024);
	/*
	// test code 
	long arg = 1;
	int ret = setsockopt(m_socket,IPPROTO_TCP,TCP_NODELAYk,(char *)&arg,sizeof(arg));
	if(ret)
	{
		Sys_Log("socket: set tcp_nodelay failed");
	}
	*/
	return true;
}

bool CG_NetSocket::BindAddr(const char *ip,int port)
{
	SOCKADDR_IN addrLocal;
	addrLocal.sin_family=AF_INET;
	addrLocal.sin_port=htons(port);
	if(ip && strcmp(ip,"localhost")!=0)
	{
		addrLocal.sin_addr.s_addr=inet_addr(ip);
	}
	else
	{
		addrLocal.sin_addr.s_addr=htonl(INADDR_ANY);
	}
	if(bind(m_socket,(SOCKADDR *)&addrLocal,sizeof(addrLocal))==SOCKET_ERROR)
	{
		CORE(LOG_NAME,"Bind socket error");
		return false;
	}
	return true;
}

bool CG_NetSocket::Listen()
{
//#ifdef GAME_SERVER
	if(listen(m_socket,SOMAXCONN)==SOCKET_ERROR)
	{
		CORE(LOG_NAME,"NetSocket listen error");
		return false;
	}
//#endif
	
	return true;
}

bool CG_NetSocket::Connect(const char *szAddr, int port, unsigned long ip)
{
	SOCKADDR_IN addrRemote;
	hostent *host=NULL;

	memset(&addrRemote,0,sizeof(addrRemote));
	addrRemote.sin_family=AF_INET;
	addrRemote.sin_port=htons(port);
	
	if(szAddr)
		addrRemote.sin_addr.s_addr = inet_addr(szAddr);
	else
		addrRemote.sin_addr.s_addr = ip;
	
	if(addrRemote.sin_addr.s_addr==INADDR_NONE)
	{
		if(!szAddr) return false;
		host=gethostbyname(szAddr);
		if(!host) return false;
		memcpy(&addrRemote.sin_addr,host->h_addr_list[0],host->h_length);
	}
	
	if(connect(m_socket,(SOCKADDR *)&addrRemote,sizeof(addrRemote))
		==SOCKET_ERROR)
	{
		int err = GETERROR;
		if (err != CONN_INPRROGRESS)
		{
			CORE(LOG_NAME,"Socket connect error = %d",err); 
			return false;
		}
// 		else if (!CanWrite())
// 		{
// 			CORE(LOG_NAME,"Socket connect error ,CanWrite=false"); 
// 			return false;
// 		}
		//return false;
	}
	return true;
}

/*
 * return value 
 * =  0 send failed
 * >  0	bytes send
 * = -1 net dead
 */
int CG_NetSocket::Send(char *buf, int len)
{
	if (!CanWrite()) return 0;
	
	int ret;
	/*
	in linux be careful of SIGPIPE
	*/
	ret = send(m_socket,buf,len,0);
	if (ret==SOCKET_ERROR)
	{
		int err=GETERROR;
		if (err==WSAEWOULDBLOCK) return 0;
		return -1;
	}
	return ret;
}

/*
 * return value 
 * =  0 recv failed
 * >  0	bytes recv
 * = -1 net dead
 */
int CG_NetSocket::Recv(char *buf, int len)
{
	if (CanRead()==false) 
		return 0;

	int ret;
	/* in linux be careful of SIGPIPE */
	ret = recv(m_socket,buf,len,0);
	
	if (ret==0)
	{
		/* remote closed */
		return -1;
	}

	if (ret==SOCKET_ERROR)
	{
		int err=GETERROR;
		if (err!=WSAEWOULDBLOCK)
		{
			return -1;
		}
	}
	return ret;
}

bool CG_NetSocket::CanRead()
{
	fd_set readfds;
	timeval timeout;

	timeout.tv_sec=0;
	timeout.tv_usec=0;
	FD_ZERO(&readfds);
	FD_SET(m_socket,&readfds);
	int ret = select(FD_SETSIZE,&readfds,NULL,NULL,&timeout);
	if(ret > 0 && FD_ISSET(m_socket,&readfds))
		return true;
	else 
		return false;
}

bool CG_NetSocket::CanWrite()
{
	fd_set writefds;
	timeval timeout;

	timeout.tv_sec=0;
	timeout.tv_usec=0;
	FD_ZERO(&writefds);
	FD_SET(m_socket,&writefds);
	int ret = select(FD_SETSIZE,NULL,&writefds,NULL,&timeout);
	if(ret > 0 && FD_ISSET(m_socket,&writefds))
		return true;
	else 
		return false;
}

bool CG_NetSocket::Close()
{
	if (m_socket == INVALID_SOCKET) return false;
	CLOSESOCKET(m_socket);
	Reset();
	if (--m_nCount==0)
		_NetCleanUp();
	return true;
}

SOCKET CG_NetSocket::Accept()
{
	SOCKADDR_IN addr;
	int len = sizeof(addr);
	SOCKET tmp;
	tmp = accept(m_socket,(SOCKADDR *)&addr,(socklen_t *)&len);
	if (tmp == INVALID_SOCKET || tmp == NULL)
	{
		MYMSG(LOG_NAME,"Accept error");
		return NULL;
	}
	m_nCount++;
	return tmp;	
}

bool CG_NetSocket::Attach(SOCKET socket)
{
	m_socket = socket;
	SetNonBlocking();
	return true;
}

int CG_NetSocket::SendTo(char *buf, int len, SOCKADDR_IN *addr)
{
	if (!CanWrite()) return 0;
	
	int ret;
	ret = sendto(m_socket,buf,len,0,(SOCKADDR *)addr,sizeof(SOCKADDR_IN));
	if (ret==SOCKET_ERROR)
	{
		int err=GETERROR;
		if (err!=WSAEWOULDBLOCK)
		{
			return -1;
		}
	}
	return ret;
}

int CG_NetSocket::RecvFrom(char *buf, int len, SOCKADDR_IN *addr ,int *addrlen)
{
	if (!CanRead()) return 0;

	int ret;
	ret = recvfrom(m_socket,buf,len,0,(SOCKADDR *)addr,(socklen_t *)addrlen);
	if (ret==SOCKET_ERROR)
	{
		int err=GETERROR;
		if (err!=WSAEWOULDBLOCK)
		{
			return -1;
		}
	}
	return ret;
}

bool CG_NetSocket::HasExcept()
{
	fd_set exceptfds;
	timeval timeout;

	timeout.tv_sec=0;
	timeout.tv_usec=0;
	FD_ZERO(&exceptfds);
	FD_SET(m_socket,&exceptfds);
	int ret = select(FD_SETSIZE,NULL,NULL,&exceptfds,&timeout);
	if(ret > 0 && FD_ISSET(m_socket,&exceptfds))
		return true;
	else 
		return false;
}

void CG_NetSocket::Reset()
{
	m_socket = INVALID_SOCKET;
}

bool CG_NetSocket::SetNonBlocking()
{
	/* set to nonblocking mode */
	u_long arg;
	arg = 1;
	int ret;
	ret = IOCTLSOCKET(m_socket,FIONBIO,&arg);
	if (ret == SOCKET_ERROR)
	{
		CORE(LOG_NAME,"SetNonBlocking Failed,IOCTLSOCKET = %d",ret);
		return false;
	}
	else
	{
		return true;
	}
}

bool CG_NetSocket::SetSendBufferSize(int len)
{
	int ret;
	ret = setsockopt(m_socket,SOL_SOCKET,SO_SNDBUF,(char *)&len,sizeof(len));
	if (ret == SOCKET_ERROR) return false;
	return true;
}

bool CG_NetSocket::SetRecvBufferSize(int len)
{
	int ret;
	ret = setsockopt(m_socket,SOL_SOCKET,SO_RCVBUF,(char *)&len,sizeof(len));
	if (ret == SOCKET_ERROR) return false;
	return true;
}

/* 
 * get local address 
 */
bool CG_NetSocket::GetLocalAddr(char *addr, short *port, unsigned long *ip)
{
	SOCKADDR_IN addrLocal;
	socklen_t len = sizeof(addrLocal);
	if(getsockname(m_socket,(SOCKADDR*)&addrLocal,&len)==SOCKET_ERROR)
		return false;
	
	char *tmp = inet_ntoa(addrLocal.sin_addr);
	if(!tmp) 
		return false;
	if(addr) 
		strcpy(addr,tmp);
	if(port)
		*port = ntohs(addrLocal.sin_port);
	if(ip) 
		*ip = addrLocal.sin_addr.s_addr;
	return true;
}

/* 
 * get remote address 
 */
bool CG_NetSocket::GetRemoteAddr(char *addr, short *port,unsigned long *ip)
{
	sockaddr_in addrRemote;
	int len = sizeof(addrRemote);
	if(getpeername(m_socket,(sockaddr *)&addrRemote,(socklen_t *)&len)==SOCKET_ERROR)
		return false;
	
	char *tmp = inet_ntoa(addrRemote.sin_addr);
	if(!tmp) 
		return false;
	if(addr)
		strcpy(addr,tmp);
	if(port)
		*port = ntohs(addrRemote.sin_port);
	if(ip)
		*ip = addrRemote.sin_addr.s_addr; 
	return true;
}

bool CG_NetSocket::SetReuseAddr(bool reuse)
{
#ifndef WIN32
	/* only useful in linux */
	int opt = 0;
	unsigned int len = sizeof(opt);

	if(reuse) opt = 1;
	if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,
		(const void*)&opt,len)==SOCKET_ERROR)
	{
		return false;
	}
	else
	{
		return true;
	}
#endif
	return true;
}
