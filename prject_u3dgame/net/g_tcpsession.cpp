//#include "stdafx.h"
//#include "net_lib_private.h"
//
// g_tcpsession.cpp: implementation of the CG_TCPSession class.
//
#include "g_tcpsession.h"
//#include "g_util.h"
CG_CmdPacket  CG_TCPSession::m_sendCmdPkt;
CG_CmdPacket  CG_TCPSession::m_recvCmdPkt;
CG_NetPacket  CG_TCPSession::m_sendNetPkt;
CG_NetPacket  CG_TCPSession::m_recvNetPkt;

#define LOG_NAME "NetLib: "
CG_TCPSession::CG_TCPSession()
{
	m_bAndroid = false;
	m_sendCmdPkt.SetSize(MAX_CMD_PACKET_SIZE);
	m_recvCmdPkt.SetSize(MAX_CMD_PACKET_SIZE);
	m_bEncrypt  = false;
	m_bCompress = true;
	m_readBuf = m_writeBuf = NULL;
	Reset();
}

CG_TCPSession::~CG_TCPSession()
{
	delete []m_readBuf;
	delete []m_writeBuf;
}

void CG_TCPSession::OnConnect(bool ret)
{

}

void CG_TCPSession::OnDisconnect()
{

}

void CG_TCPSession::OnReceive(CG_CmdPacket *packet)
{

}

void CG_TCPSession::Process()
{
	DefProc();
	bool ret = false;
	
	switch (m_state)
	{
		case NET_STATE_CONNECTED:
			while(GetPacket(&m_recvCmdPkt))
			{
				OnReceive(&m_recvCmdPkt);
    		}
			break;

		case NET_STATE_ERROR:
		case NET_STATE_DEAD:
			OnDisconnect();
			Close();
			break;

		case NET_STATE_WAITING_SEED://��������
			/* try get encrypt seed */
			if(RecvPacket(&m_recvNetPkt))
			{
				m_recvNetPkt.AttachCmdPacket(&m_recvCmdPkt);
				if(m_recvNetPkt.IsSysPacket())
				{
					HandleSysPacket(&m_recvCmdPkt);
				}
			}
			break;
			
		case NET_STATE_CONNECTING:
			if(m_socket.HasExcept())//socket�Ƿ��ֹ��д
			{
				MYMSG(LOG_NAME,"connecting failed");
				Close();
				OnConnect(false);
				break;
			}
			else if( Sys_GetTime() - m_connTime > NET_CONNECT_TIMEOUT)
			{
				MYMSG(LOG_NAME,"connecting timeout");
				Close();
				OnConnect(false);
				break;
			}

			if(m_socket.CanWrite()) 
			{
				ret = true;
			}
			else
			{
				break;
			}
#ifdef LINUX 
			/* in linux should check again */
			int err,len;
			len = sizeof(err);
			if(getsockopt(m_socket.m_socket,SOL_SOCKET,SO_ERROR,
				(void *)&err,(socklen_t*)&len) != SOCKET_ERROR) 
			{
				if(err != 0) ret = false;
			}
			else
				ret = false;
#endif		
			if(ret)
			{//���ӳɹ����ȴ�����
				m_state = NET_STATE_WAITING_SEED;
				m_startTime = Sys_GetTime();
			    m_lastSendTime = m_startTime;
				m_lastRecvTime = m_startTime;
			}
			else
			{
				OnConnect(false);
				Close();
			}
 			break;
	}
}

bool CG_TCPSession::Connect(char *remote, int port, char *bindIp,int bindPort)
{
	if(!m_socket.Initialize(NETWORK_PROTOCOL_TCP))
		return false;
	if(!m_socket.BindAddr(bindIp,bindPort))
		return false;
		
	if(m_socket.Connect(remote,port))
	{
		m_state = NET_STATE_CONNECTING;
		m_connTime = Sys_GetTime();
		return true;
	}
	return false;
}

void CG_TCPSession::Close()
{
	Reset();
}

void CG_TCPSession::Reset()
{
	m_bAndroid = true;
	m_rtt = 0;

	delete []m_readBuf;
	delete []m_writeBuf;

	m_readBuf = new char[MAX_BUFFER_SIZE];
	m_readBufSize = MAX_BUFFER_SIZE;

	m_writeBuf = new char[MAX_BUFFER_SIZE];
	m_writeBufSize = MAX_BUFFER_SIZE;
	m_maxBufSize   = MAX_BUFFER_SIZE;

	m_socket.Close();
	m_socket.Reset();
	
	m_seedLen = 0;
	m_sendSeq = 0;
	m_recvSeq = 0;
	m_sendBytes = 0;
	m_recvBytes = 0;
	m_state = NET_STATE_ZERO;
	m_writeLen = m_writeBeg = m_writeEnd = 0;
	m_readLen = m_readPos = 0;
	SetBufSize(MAX_BUFFER_SIZE/1024+1);
}

void CG_TCPSession::Attach(SOCKET socket)
{
	m_socket.Attach(socket);
	m_state = NET_STATE_CONNECTED;
	m_startTime = Sys_GetTime();
	m_lastRecvTime = m_startTime;
	m_lastSendTime = m_startTime;
}

bool CG_TCPSession::SendPacket(CG_CmdPacket *packet,bool flush,bool sys)
{
	if (m_state != NET_STATE_CONNECTED) 
	{
		//CORE("","SendPacket:(m_state=%d)",m_state);
		return false;
	}

	m_sendNetPkt.AddCmdPacket(packet);
	m_sendNetPkt.SetSeq(m_sendSeq);
	
	char* str1=m_sendNetPkt.GetBuffer();
	int it1=0;
	it1=m_sendNetPkt.GetTotalSize();
	/* dont's encrypt sys packet */
	if(sys)
	{
		m_sendNetPkt.SetSysPacket();
	}
	else
	{
		/* check if need encrypt and compress */
		if(m_bCompress) m_sendNetPkt.Compress();
		if(m_bEncrypt) m_sendNetPkt.Encrypt(m_seed,m_seedLen);
		
	}
	
	char* str2=m_sendNetPkt.GetBuffer();
	int it2=0;
	it2=m_sendNetPkt.GetTotalSize();
	/* add to send buffer */
	if(!PushData(m_sendNetPkt.GetBuffer(),m_sendNetPkt.GetTotalSize())) 
	{
		//CORE("","SendPacket:(PushData:%d:%d)",m_sendNetPkt.GetBuffer(),m_sendNetPkt.GetTotalSize());
		return false;
	}
	
	/* compute next seq number */
	m_sendSeq++;
	//m_sendSeq+=2;
	if(m_sendSeq > MAX_NET_PACKET_SEQ) m_sendSeq = 1;

	/* flush data */
	if(flush) FlushData();
	return true;
}

int CG_TCPSession::GetAvgFluxIn()
{
	int time = (Sys_GetTime() - m_startTime)/1000;
	if(time == 0) time = 1;
	return GetBytesIn()/time;
}

int CG_TCPSession::GetAvgFluxOut()
{
	int time = (Sys_GetTime() - m_startTime)/1000;
	if(time == 0) time = 1;
	return (GetBytesOut()/time);
}

int CG_TCPSession::GetBytesIn()
{
	return m_recvBytes;
}

int CG_TCPSession::GetBytesOut()
{
	return m_sendBytes;
}

bool CG_TCPSession::GetPacket(CG_CmdPacket *packet)
{
	while(RecvPacket(&m_recvNetPkt))
	{
		/* attach a cmd packet for read */
		m_recvNetPkt.AttachCmdPacket(packet);
		if(m_recvNetPkt.IsSysPacket())
		{
			/* if a system msg packet,handle it */
			HandleSysPacket(packet);
		    continue;
		}
		else
		{
			/* get a user data packet,return */
			return true;
		}
	}
	return false;
}

bool CG_TCPSession::ReadData()
{
	if (m_readLen == 0)	
	{
		m_readPos = 0;
	}
	else if (m_readLen > 0 && m_readPos != 0)
	{
		memmove(m_readBuf,m_readBuf+m_readPos,m_readLen);
		m_readPos = 0;
	}
	
	/* m_readPos always = 0 */
	int ret;
	ret = m_socket.Recv(m_readBuf+m_readLen,m_readBufSize-m_readLen);
	if (ret > 0)
	{
		m_readLen += ret;
		m_recvBytes += ret;
		/* reset recv time */
		m_lastRecvTime = Sys_GetTime();
		return true;
	}
	else if(ret == 0)
	{
		return false;
	}
	else
	{
		m_state = NET_STATE_DEAD;
		MYMSG(LOG_NAME,"ReadData error %d",ret);
	}
	return false;
}

void CG_TCPSession::FlushData()
{
	/* flush data in buffer */
	int ret;
	if (m_writeLen == 0) return;

	/* reset last send time */
	/*
	m_lastSendTime = Sys_GetTime();
	*/
	if (m_writeEnd > m_writeBeg)
	{
		ret = m_socket.Send(m_writeBuf+m_writeBeg,m_writeLen);
		if (ret >= 0)
		{
			m_sendBytes += ret;
			m_writeLen -= ret;
			m_writeBeg = (m_writeBeg+ret)%m_writeBufSize;
		}
		else if (ret == -1)
		{
			m_state = NET_STATE_DEAD;
			MYMSG(LOG_NAME,"FlushData 1-error %d",ret);
			return;
		}
	}
	else  /* end < begin */
	{
		ret = m_socket.Send(m_writeBuf+m_writeBeg,m_writeBufSize-m_writeBeg);
		if (ret >= 0)
		{
			m_sendBytes += ret;
			m_writeLen -= ret;
			m_writeBeg = (m_writeBeg+ret)%m_writeBufSize;
			if(m_writeBeg!=0) return;
		}
		else if (ret == -1)
		{
			m_state = NET_STATE_DEAD;
			MYMSG(LOG_NAME,"FlushData 2-error %d",ret);
			return;
		}
		
		ret = m_socket.Send(m_writeBuf,m_writeEnd);
		if (ret >= 0)
		{
			m_sendBytes += ret;
			m_writeLen -= ret;
			m_writeBeg = (m_writeBeg+ret)%m_writeBufSize;
		}
		else if (ret == -1)
		{
			m_state = NET_STATE_DEAD;
			MYMSG(LOG_NAME,"FlushData 3-error %d",ret);
			return;
		}
	}
}

bool CG_TCPSession::PushData(char *buf, int len)
{
	int tlen = len;
	/* first check if can hold data */
	if(len >= m_writeBufSize - m_writeLen) 
	{
		if (!ResizeBuf(m_writeLen + len +1)) 
		{
			return false;
		}
	}
	m_writeLen+=len;
	while(len--)
	{
		m_writeBuf[m_writeEnd++] = *buf++;
		if (m_writeEnd == m_writeBufSize)
			m_writeEnd = 0;
	}
	return true;
}

void CG_TCPSession::SetBufSize(int kb)
{
	m_maxBufSize = kb*1000;
}

bool CG_TCPSession::ResizeBuf(int min)
{
	int newSize = min*2;
	if (min >= m_maxBufSize) 
		return false;
	if (newSize>m_maxBufSize)
		newSize = m_maxBufSize;
	MYMSG(LOG_NAME,"Resize socket buf to %d",newSize);
	char *buf = new char[newSize];

	/* copy src data */
	if (m_writeLen > 0)
	{
		if(m_writeEnd > m_writeBeg)
			memcpy(buf,m_writeBuf+m_writeBeg,m_writeLen);
		else
		{
			int nLen = m_writeBufSize - m_writeBeg;
			memcpy(buf,m_writeBuf+m_writeBeg,nLen);
			memcpy(buf+nLen,m_writeBuf,m_writeLen - nLen);
		}
	}
	delete []m_writeBuf;
	m_writeBuf = buf;
	m_writeBeg = 0;
	m_writeEnd = m_writeLen;
	m_writeBufSize = newSize;
	return true;
}

int CG_TCPSession::GetState()
{
	return m_state;
}

bool CG_TCPSession::IsDead()
{
	return (m_state == NET_STATE_DEAD || m_state == NET_STATE_ERROR);
}

void CG_TCPSession::DefProc()
{
	if(m_state != NET_STATE_CONNECTED && m_state != NET_STATE_WAITING_SEED) return;
	
	if(m_state == NET_STATE_CONNECTED)
	{
		long now = Sys_GetTime();
		if(now - m_lastSendTime > NET_KEEP_ALIVE_INTERVAL)
		{
			KeepAlive(now);
			m_lastSendTime = now;
		}
		if(now - m_lastRecvTime > NET_TIMEOUT)
		{
			MYMSG(LOG_NAME,"Tcp session dead reason = timeout");
			m_state = NET_STATE_DEAD;
			return;
		}
		FlushData();
	}
	ReadData();
}

bool CG_TCPSession::RecvPacket(CG_NetPacket *packet)
{
	int ret;
	ret = packet->BeginRead(m_readBuf+m_readPos,m_readLen);
	if(ret > 0)
	{
		m_readLen -= ret;
		m_readPos += ret;
		if(packet->IsEncrypt())  
		{
			packet->Decrypt(m_seed,m_seedLen);
		}
		if (!m_bAndroid)
		{
			if(m_recvSeq != packet->GetSeq())
			{
				CORE(LOG_NAME,"Error seq = %d,expect = %d,close session", packet->GetSeq(), m_recvSeq); 
				m_state = NET_STATE_ERROR;
				return false;
			}
			m_recvSeq++;
			if(m_recvSeq > MAX_NET_PACKET_SEQ) m_recvSeq = 1;
		}
		if(packet->IsCompress()) 
		{
			if(!packet->Uncompress()) return false;
		}
		return true;
	}
	else if(ret == 0)
	{
		return false;
	}
	else 
	{
		CORE(LOG_NAME,"RecvPacket packet begin read failed (%d)",ret); 
		/* the packet flag error,not belong to this session */
		m_state = NET_STATE_ERROR;
		return false;
	}
	return false;
}

int CG_TCPSession::HandleSysPacket(CG_CmdPacket *packet)
{
	short type=0;
	long  param=0;

	if(!packet->ReadShort(&type)) return NULL;
	switch(type)
	{
		case SYS_PACKET_KEEP_ALIVE:
			if(!packet->ReadLong(&param)) return NULL;
			// Sys_Log("recv keep alive msg");
			m_sendCmdPkt.BeginWrite();
			m_sendCmdPkt.WriteShort(SYS_PACKET_ALIVE_ACK);
			m_sendCmdPkt.WriteLong(param);
			m_sendCmdPkt.WriteByte(1);
			SendPacket(&m_sendCmdPkt,true,true);
			break;

		case SYS_PACKET_ALIVE_ACK:
			if(!packet->ReadLong(&param)) return NULL;
			// Sys_Log("recv alive ack msg");
			m_rtt = Sys_GetTime() - param;
			break;

		case SYS_PACKET_SET_SEED:
			{
				if(!packet->ReadLong(&param)) return NULL;
				SetSeed(param);
				m_state = NET_STATE_CONNECTED;
				OnConnect(true);
			}
	    	break;

		default :
			return NULL;
	}
	return type;
}

void CG_TCPSession::SetSeed(long seed)
{
	// Sys_Log("net: set seed = %d",seed);
	if(seed == 0)
	{
		m_bEncrypt = false;
		return;
	}

	int i;
	for(i=0;i<MAX_NET_SEED_SIZE;i++)
	{
		//m_seed[i] = ((char)seed % 255)+1;
        //__Gu_Lu__Begin__ remove warning C4244: '=' : conversion from 'long' to 'char'
        m_seed[i] = (char)((seed % 255)+1);
        //__Gu_Lu__End__
		seed /= 19;
	}
	m_seedLen = i;
	m_bEncrypt = true;
}

void CG_TCPSession::SendSeed(long seed)
{
	CORE("SendSeed:","%d",seed);
	m_sendCmdPkt.BeginWrite();
	m_sendCmdPkt.WriteShort(SYS_PACKET_SET_SEED);
	m_sendCmdPkt.WriteLong(seed);
	SendPacket(&m_sendCmdPkt,true,true);
	SetSeed(seed);
}

void CG_TCPSession::KeepAlive(long now)
{
	CORE("KeepAlive:","%d",now);
	m_sendCmdPkt.BeginWrite();
	m_sendCmdPkt.WriteShort(SYS_PACKET_KEEP_ALIVE);
	m_sendCmdPkt.WriteLong(now);
	m_sendCmdPkt.WriteByte(1);
	SendPacket(&m_sendCmdPkt,true,true);
}

int CG_TCPSession::GetRtt()
{
	return m_rtt;
}
bool CG_TCPSession::GetLocalAddr(char *addr, short *port,unsigned long *ip )
{
	return m_socket.GetLocalAddr(addr, port,ip );
}
bool CG_TCPSession::GetRemoteAddr(char *addr, short *port,unsigned long *ip )
{
	return m_socket.GetRemoteAddr(addr, port,ip );
}

