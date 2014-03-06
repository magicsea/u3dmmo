//#include "MwPch.h"
//#include "StdAfx.h"
#include "gc_allnet.h"
#include "session_bind_base.h"
//#include <string>

GC_Session_Bind::GC_Session_Bind():mState(UN_CONNECT)
{
	m_iReceiveTime=0;
	m_pCallBackObject = NULL;
	m_cbfOnConnect = NULL;
	m_cbfOnDisConnect = NULL;
	m_cbfOnNetClose = NULL;
}

GC_Session_Bind::~GC_Session_Bind()
{
	
}
bool GC_Session_Bind::IsLogin()
{
	if(mState==ALREADY_LOGIN)
		return true;
	return false;
}
void GC_Session_Bind::OnConnect(bool ret)
{
	if(ret)
	{
		mState=ALREADY_CONNECT;
	}
	else
	{
	}

	if (m_pCallBackObject&&m_cbfOnConnect)
	{
		(m_pCallBackObject->*(m_cbfOnConnect))(this,ret);
	}
	return;
}

bool GC_Session_Bind::Connect(const char* pHostIP, int iPort)
{
	if(mState==UN_CONNECT)
	{   
		int port = iPort;
		const char* pIP = pHostIP;
		if (pIP==0)
		{
			return false;

		}
		if(CG_TCPSession::Connect((char*)pIP, port))
		{
			return true;
		}
	}
	return false;
}
void GC_Session_Bind::OnDisconnect()
{
	mState=UN_CONNECT;
	if (m_pCallBackObject&&m_cbfOnDisConnect)
	{
		(m_pCallBackObject->*(m_cbfOnDisConnect))(this);
	}
}
void GC_Session_Bind::OnClose(bool bMessage)//
{
	Close();

	mState=UN_CONNECT;

	if (m_pCallBackObject&&m_cbfOnNetClose)
	{
		(m_pCallBackObject->*(m_cbfOnNetClose))(this,bMessage);
	}
}

void GC_Session_Bind::OnReceive(CG_CmdPacket *packet)
{
	m_iReceiveTime=Sys_GetTime();
	short CommandID;
	if(!packet->ReadShort(&CommandID)) return;
    this->DoCmd(CommandID, packet);
	return;
}
bool GC_Session_Bind::DoCmd(short cmdID, CG_CmdPacket *pPacket)
{
    hash_map<short, NETCMD_FUN>::iterator it;
    it = m_Bind.find(cmdID);
    if (it!=m_Bind.end())
    {
        return ((*it).second)(cmdID, pPacket);
    }
  //obj fun
	hash_map<short,NETCMD_FUN_OBJ>::iterator itFunobj;
	itFunobj=m_BindObjFun.find(cmdID);
	if (itFunobj!=m_BindObjFun.end())
	{
		hash_map<short, CNetCmdBase*>::iterator itObj = m_BindObj.find(cmdID);
		CNetCmdBase* pObj = itObj->second;
		if (pObj)
		{
			return (pObj->*(itFunobj->second))(cmdID, pPacket);
		}
	}

    return false;
}
void GC_Session_Bind::OnLogin()
{
    mState=ALREADY_LOGIN;
}

void GC_Session_Bind::OnRejectLogin()
{
    mState=ALREADY_CONNECT;
	
}
bool GC_Session_Bind::IsBind(short cmdID)
{
    return (m_Bind.find(cmdID)!=m_Bind.end());
}

void GC_Session_Bind::BindCmd(short cmdID, NETCMD_FUN pFun)
{
    m_Bind[cmdID] = pFun;
}
void GC_Session_Bind::BindCmdObj(short cmdID, NETCMD_FUN_OBJ pFun,CNetCmdBase* obj)
{
	if(!obj)return;
	m_BindObjFun[cmdID]=pFun;
	m_BindObj[cmdID]=obj;
}
void GC_Session_Bind::UnbindCmd(short cmdID)
{
    hash_map<short, NETCMD_FUN>::iterator it;
    it = m_Bind.find(cmdID);
    if (it!=m_Bind.end())
    {
        m_Bind.erase(it);
    }
}

CG_CmdPacket* GC_Session_Bind::BeginWrite()
{
    mSendCommand.BeginWrite();
    return &mSendCommand;
}

bool GC_Session_Bind::Send(CG_CmdPacket* pPacket)
{
	return SendPacket(pPacket);
}

void GC_Session_Bind::regCallBackFunc(CNetCmdBase* pObj1,CBF_OnConnect cbf1,CBF_OnDisConnect cbf2,CBF_OnNetClose cbf3)
{
	if(pObj1)
	{
		m_pCallBackObject = pObj1;
		m_cbfOnConnect = cbf1;
		m_cbfOnDisConnect = cbf2;
		m_cbfOnNetClose = cbf3;
	}
}

/////////////////////////////////////////////////////////////////////////////////


