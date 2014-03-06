//
// s_cmd.h: interface for the CS_Cmd class.
//
#ifndef __CS_CMD_H__
#define __CS_CMD_H__

#include "gc_AllNet.h"
#include "s_cmdchannel.h"
#include "cmd_region_client.h"

class CS_C2RCmd : public CS_CmdChannel
{
public:
	
public:
	CS_C2RCmd();
	virtual ~CS_C2RCmd();
	static int c2r_login();

	static int c2r_chat();
	static int c2l_login_server();
	static int c2l_even();
};

#endif

