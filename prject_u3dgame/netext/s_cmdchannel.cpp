//
// s_cmdchannel.cpp: implementation of the CS_CmdChannel class.
//
#include "gc_AllNet.h"
#include "s_cmdchannel.h"

CS_CmdChannel::CS_CmdChannel()
{

}

CS_CmdChannel::~CS_CmdChannel()
{

}

bool CS_CmdChannel::AddCmd(SCmd *cmd)
{
	m_cmdList.push_back(*cmd);
	return true;
}

bool CS_CmdChannel::AddCmd(TFunction func,int id,const char *name,const char *desc)
{
	SCmd cmd;
	cmd.func    = func;
	cmd.cmdId   = id;
	cmd.cmdName = name;
	cmd.desc	= desc;
	
	m_cmdList.push_back(cmd);
	return true;
}

SCmd *CS_CmdChannel::GetCmdByName(const char *name)
{
	for(int i=0;i<(int)m_cmdList.size();i++)
	{
		if(m_cmdList[i].cmdName==name) return &m_cmdList[i]; 
	}
	return NULL;
}

SCmd *CS_CmdChannel::GetCmdById(int id)
{
	for(int i=0;i<(int)m_cmdList.size();i++)
	{
		if (m_cmdList[i].cmdId==id) return &m_cmdList[i];
	}
	return NULL;
}

int CS_CmdChannel::GetCmdCount()
{
	return m_cmdList.size();
}

bool CS_CmdChannel::RecvCmd(short cmdId)
{
	int ret=0;
	SCmd *src;
	
	src = GetCmdById(cmdId);
	if(!src)
	{
		MYMSG("CS_CmdChannel: ","channel %s : unknow cmd = %d",m_channelName.c_str(),cmdId);
		return false;
	}
#ifndef _DEBUG
	try
	{
		ret = src->func();
	} 
	catch (...)
	{
		CORE("EXCEPT:", "%s %s %d error,cmdId=%d", __FILE__, __FUNCTION__ ,__LINE__,cmdId);
	}
#else
		ret = src->func();

#endif

	//ret = src->func();
	
	// check result
	if(ret != ERROR_NONE)
	{
		MYMSG("CS_CmdChannel: ","channel %s : cmd id = %d,ret = %d",m_channelName.c_str(),cmdId,ret);
		return false;
	}
	return true;
}

/*
CG_CmdPacket *CS_CmdChannel::InitPacket()
{
	m_sendCmd.BeginWrite();
	m_sendCmd.WriteByte(m_channelId);
	return &m_sendCmd;
}
*/