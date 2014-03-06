//#include "stdafx.h"
//#include "net_lib_private.h"
//
// g_NetPacket.cpp: implementation of the CG_NetPacket class.
//
#include "g_netpacket.h"
//#include "g_util.h"

#define LOG_NAME "NetLib: "
CG_NetPacket::CG_NetPacket()
{
	m_pktFlag = &m_buffer[0];
	m_pktSeq  = (unsigned short*)&m_buffer[3];
	m_pktDataSize = (unsigned short*)&m_buffer[1];	
}

CG_NetPacket::~CG_NetPacket()
{

}

void CG_NetPacket::AddCmdPacket(CG_CmdPacket *packet)
{
	unsigned short dataSize = packet->GetDataSize();
	*m_pktFlag = PROTOCOL_FLAG<<PROTOCAL_FLAG_OFFSET;
	*m_pktDataSize = dataSize;
	memcpy(m_buffer+NET_PACKET_HEAD_SIZE,packet->GetData(),dataSize);
	m_totalSize = NET_PACKET_HEAD_SIZE + dataSize;
}

void CG_NetPacket::AttachCmdPacket(CG_CmdPacket *packet)
{
	packet->BeginRead(m_buffer+NET_PACKET_HEAD_SIZE,*m_pktDataSize);
}

// -1	Error
//  0	Process Next Time
// >0	Len
int CG_NetPacket::BeginRead(char *p,int len)
{
	if (len < NET_PACKET_HEAD_SIZE) return 0;
	m_pktFlag = &p[0];
	m_pktSeq  = (unsigned short*)&p[3];
	m_pktDataSize = (unsigned short*)&p[1];	
	
	if (*m_pktFlag>>PROTOCAL_FLAG_OFFSET != PROTOCOL_FLAG)
	{
		CORE(LOG_NAME,"NetPacket flag error");
		return -1;
	}
	
	if (*m_pktDataSize <= 0 || *m_pktDataSize > MAX_CMD_PACKET_SIZE) 
	{
		CORE(LOG_NAME,"NetPacket size error (%d)",*m_pktDataSize);
		return -1;
	}

	int total = *m_pktDataSize + NET_PACKET_HEAD_SIZE;

	if (len < total) 
	{
		// Sys_Log("NetPacket Error 2: len = %d,s = %d",len,s);
		return 0;
	}
	// copy to self buffer 
	memcpy(m_buffer,p,total);
	m_pktFlag = &m_buffer[0];
	m_pktSeq  = (unsigned short*)&m_buffer[3];
	m_pktDataSize = (unsigned short*)&m_buffer[1];
	m_totalSize = total;
	return total;
}

void CG_NetPacket::Encrypt(char *seed,int len)
{
	if (!IS_OPEN_ENCODE)
		return;
	// encrypt here 
	int i,k;
	for(i=NET_PACKET_ENCRYPT_OFFSET,k=0;i<m_totalSize;i++,k++)
	{
		if(k==len) k=0;
		m_buffer[i]^=seed[k];
	}
	*m_pktFlag |= FLAG_ENCRYPT;
}

void CG_NetPacket::Decrypt(char *seed,int len)
{
	if (!IS_OPEN_ENCODE)
		return;
	// decrypt here 
	int i,k;
	for(i=NET_PACKET_ENCRYPT_OFFSET,k=0;i<m_totalSize;i++,k++)
	{
		if(k==len) k=0;
		m_buffer[i]^=seed[k];
	}
	*m_pktFlag &= (~FLAG_ENCRYPT);
}

bool CG_NetPacket::IsEncrypt()
{
	if (!IS_OPEN_ENCODE)
		return false;
	return (*m_pktFlag & FLAG_ENCRYPT);
}

bool CG_NetPacket::Compress()
{
	if (!IS_OPEN_COMPRESS)
		return true;
	// compress here 
	unsigned long destLen = COMPRESS_BUF_SIZE;
	destLen = Sys_LzwComp(m_buffer+NET_PACKET_HEAD_SIZE,*m_pktDataSize,m_comBuf);
	if(destLen >= *m_pktDataSize) 
	{
		return false;
	}
	// Sys_Log("compress src = %d, dest = %d",*m_pktDataSize,destLen);
	memcpy(m_buffer+NET_PACKET_HEAD_SIZE,m_comBuf,destLen);
	*m_pktDataSize = (short)destLen;
	m_totalSize = destLen+NET_PACKET_HEAD_SIZE;
	
	*m_pktFlag |= FLAG_COMPRESS;
	return true;
}

bool CG_NetPacket::Uncompress()
{
	if (!IS_OPEN_COMPRESS)
		return true;
	// uncompress here 
	unsigned long destLen = COMPRESS_BUF_SIZE;
	destLen = Sys_LzwUncomp(m_buffer+NET_PACKET_HEAD_SIZE,*m_pktDataSize,m_comBuf);
	if(destLen >= MAX_NET_PACKET_SIZE || destLen <= 0)
	{
		return false;
	}
	memcpy(m_buffer+NET_PACKET_HEAD_SIZE,m_comBuf,destLen);
	*m_pktDataSize = (short)destLen;
	m_totalSize = destLen + NET_PACKET_HEAD_SIZE;

	*m_pktFlag &= (~FLAG_COMPRESS);
	return true;
}

bool CG_NetPacket::IsCompress()
{
	if (!IS_OPEN_COMPRESS)
		return false;
	if(*m_pktFlag & FLAG_COMPRESS) return true;
	return false;
}

void CG_NetPacket::SetSysPacket()
{
	*m_pktFlag |= FLAG_SYSTEM;
}

bool CG_NetPacket::IsSysPacket()
{
	if(*m_pktFlag & FLAG_SYSTEM) return true;
	return false;
}


