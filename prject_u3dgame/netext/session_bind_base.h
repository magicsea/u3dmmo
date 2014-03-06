/*
�ͻ��˷�װ�ĶԻ���
*/

#ifndef __GC_SESSION_BIND_H__
#define __GC_SESSION_BIND_H__

#include "gc_allnet.h"
#include "../net/platform.h"
#include <string>
#include "netcmdbase.h"
using namespace std;
#pragma warning( disable: 4996 )
typedef bool (*NETCMD_FUN)(short cmdID, CG_CmdPacket *pPacket);

class GC_Session_Bind:public CG_TCPSession
{
public:
	GC_Session_Bind();
	virtual ~GC_Session_Bind();
	enum STATE{UN_CONNECT,ALREADY_CONNECT,LOGIN_NAME,LOGIN_PASSWORD,ALREADY_LOGIN};
	
    bool CanChat()  { return (mState==ALREADY_LOGIN);}
	bool Connect(const char* pHostIP=0, int iPort=0);

	CG_CmdPacket                mSendCommand;
	STATE mState;

	
public:
    CG_CmdPacket* BeginWrite();
    bool Send(CG_CmdPacket* pPacket);
public:
    bool IsBind(short cmdID);
    void BindCmd(short cmdID, NETCMD_FUN pFun);
    void UnbindCmd(short cmdID);
	hash_map<short, NETCMD_FUN> m_Bind;


	//obj bind
	void BindCmdObj(short cmdID, NETCMD_FUN_OBJ pFun,CNetCmdBase* obj);
	hash_map<short, NETCMD_FUN_OBJ> m_BindObjFun;
	hash_map<short, CNetCmdBase*> m_BindObj;



	long m_iReceiveTime;
private:
	virtual void OnReceive(CG_CmdPacket *packet);
	virtual void OnDisconnect();
	virtual void OnConnect(bool ret);
	bool DoCmd(short cmdID, CG_CmdPacket *pPacket);
public:
	bool IsLogin();
public:
    void OnLogin();
    void OnRejectLogin();
	void OnClose(bool bMessage=true);
public:
	void setTag(int var){m_iTag=var;};
	int getTag(){return m_iTag;};

	void regCallBackFunc(CNetCmdBase* pObj1,CBF_OnConnect cbf1,CBF_OnDisConnect cbf2=NULL,CBF_OnNetClose cbf3=NULL);
private:
	int m_iTag;

	//call back function
	CNetCmdBase* m_pCallBackObject;
	CBF_OnConnect m_cbfOnConnect;
	CBF_OnDisConnect m_cbfOnDisConnect;
	CBF_OnNetClose m_cbfOnNetClose;
};

/////////////////////////////////////////////////////////////////////////////////
#endif//__GC_SESSION_BIND_H__
