//
// s_cmdchannel.h: interface for the CS_CmdChannel class.
//
#ifndef __CS_CMD_CHANNEL_H__
#define __CS_CMD_CHANNEL_H__


//#include "g_cmdpacket.h"
#include "gc_AllNet.h"
struct SCmd
{
	TFunction  func;
	int		   cmdId;
	string	   cmdName;
	string	   desc;
};

const int ERROR_NONE	   = 0;
const int ERROR_READ_DATA  = 1;
const int ERROR_WRITE_DATA = 2;
const int ERROR_UNKNOWN    = -1;
	
class CS_CmdChannel
{
public:
	// CG_CmdPacket *InitPacket();
	int   GetCmdCount();
	bool  RecvCmd(short cmdId);
	bool  AddCmd(SCmd *cmd);
	bool  AddCmd(TFunction func,int id,const char *name,const char *desc);
	SCmd *GetCmdById(int id);
	SCmd *GetCmdByName(const char *name);
	CS_CmdChannel();
	virtual ~CS_CmdChannel();
	
	// char   m_channelId;
	string m_channelName;
	
private:
	vector<SCmd>  m_cmdList;
	// CG_CmdPacket  m_sendCmd;
};

#endif
