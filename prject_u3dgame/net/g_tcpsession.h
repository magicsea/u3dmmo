/*
g_tcpsession.h: interface for the CG_TCPSession class.
*/
#ifndef __CG_TCP_SESSION_H__
#define __CG_TCP_SESSION_H__

#include "netsocket.h"
#include "g_netpacket.h"

const int MAX_BUFFER_SIZE		= MAX_NET_PACKET_SIZE;
const int MAX_NET_SEED_SIZE		= 16;

enum ENetState
{
	NET_STATE_ZERO			= 0,
	NET_STATE_CONNECTING	= 1,
	NET_STATE_WAITING_SEED	= 2,
	NET_STATE_CONNECTED		= 3,
	NET_STATE_DEAD			= 4,
	NET_STATE_ERROR			= 5,
};

const int NET_CONNECT_TIMEOUT		= 30*1000;
const int NET_KEEP_ALIVE_INTERVAL	= 30*1000;
#ifdef _DEBUG
	const int NET_TIMEOUT			= 900*1000;
#else
	const int NET_TIMEOUT			= 900*1000;
#endif

//#include "Net_Lib_Def.h"

class NET_LIB_API CG_TCPSession  
{
public:
	CG_TCPSession();
	virtual ~CG_TCPSession();
	
	bool m_bAndroid;
	void Attach(SOCKET socket);//����һ��socket
	bool GetPacket(CG_CmdPacket *packet);//�õ�һ������ݰ�
	bool IsDead();//�Ƿ��Ѿ�����
	bool Connect(char *remote,int port,char *bindIp=0,int bindPort=0);//���ӷ��������������Լ�һ��ʱ���ж��Ƿ���������
	bool SendPacket(CG_CmdPacket *packet,bool flush=true,bool sys=false);//����һ������ݰ�
	
	int  GetRtt();
	int  GetState();//�õ�����״̬
	int  GetBytesOut();
	int  GetBytesIn();
	int  GetAvgFluxOut();//�õ�������
	int  GetAvgFluxIn();//�õ�������
	
	void DefProc();//��Ϣѭ������//state�Ѿ����ӻ��ǵȴ�seed�ú������Ч
	void Reset();
	void Close();//�رջỰ
	void Process();//��Ϣѭ�������DefProc��һ��
	void SetBufSize(int kb);//���û������С
	void SendSeed(long seed);//��������

	//bool IsConnected(){return (NET_STATE_CONNECTED==m_state)?true:false;}
	
	//����3������������ʵ��
	virtual void OnReceive(CG_CmdPacket *packet);
	virtual void OnDisconnect();
	virtual void OnConnect(bool ret);
	//---------------------//

	
	void KeepAlive(long now);//���߶Է����ּ���״̬

	bool GetLocalAddr (char *addr, short *port,unsigned long *ip = NULL);
	bool GetRemoteAddr(char *addr, short *port,unsigned long *ip = NULL);
	void FlushData();//
public:
	int  HandleSysPacket(CG_CmdPacket *packet);//����ϵͳ����
	bool RecvPacket(CG_NetPacket *packet);
	bool ReadData();//��ȡ���
	bool PushData(char *buf,int len);//������ݵ�������
	bool ResizeBuf(int min);//���������Сֵ
	void SetSeed(long seed);//���ñ�session����

	
	CG_NetSocket  m_socket;
	/* share packet */
	static CG_CmdPacket  m_sendCmdPkt;	
	static CG_CmdPacket  m_recvCmdPkt;
	static CG_NetPacket  m_sendNetPkt;	//���?�İ�
	static CG_NetPacket  m_recvNetPkt;  //�����յİ�
	
	ENetState	  m_state;//״̬
	unsigned long m_startTime;//��ʼ��ʱ��
	unsigned long m_lastRecvTime;//����յ���ʱ��
	unsigned long m_lastSendTime;//����͵�ʱ��
	unsigned long m_connTime;//�������ӵ�ʱ��
	
	char *m_readBuf;//���Ļ���
	int	  m_readBufSize;
	int   m_readPos;
	int   m_readLen;
		
	char *m_writeBuf;//д�Ļ���
	int   m_writeBufSize;
	int	  m_writeLen;
	int   m_writeBeg;
	int	  m_writeEnd;
	
	char m_seed[MAX_NET_SEED_SIZE];//���ܵ�����
	int  m_seedLen;//���ӳ���
	int  m_maxBufSize;
public:	
	bool m_bEncrypt;//�Ƿ����
	bool m_bCompress;//�Ƿ�ѹ��
private:
	unsigned short m_sendSeq;
	unsigned short m_recvSeq;

	int   m_sendBytes;
	int   m_recvBytes;
	int   m_rtt;
};

#endif
