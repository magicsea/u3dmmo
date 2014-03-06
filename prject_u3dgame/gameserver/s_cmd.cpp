//
// s_cmd.cpp: implementation of the CS_Cmd class.
//
#include "s_cmd.h"
#include "GameWorld.h"
#include "User.h"
#include "interface.h"

extern CSubLog g_slog;
extern CG_CmdPacket *g_sendCmd;
CS_C2RCmd::CS_C2RCmd()
{
}

CS_C2RCmd::~CS_C2RCmd()
{

}

int CS_C2RCmd::c2r_chat()
{
	CG_CmdPacket* cmd=CMD();
	char channel = 0;
	if(!cmd->ReadByte(&channel))
		return ERROR_READ_DATA;		
	CORE("","c2r_chat %d",channel);
	switch(channel)
	{
	case CHAT_CHANNEL_NORMAL:
		{
// 			g_sendCmd->BeginWrite();
// 			g_sendCmd->WriteShort(r2c_chat);
// 			g_sendCmd->WriteByte(channel);
// 			g_sendCmd->WriteLong(GIVER()->m_iId);
// 			g_sendCmd->WriteString((char*)GIVER()->Name());
// 			g_sendCmd->WriteString(msg);
			//GIVER()->revCmd(cmd);
			GetApp()->sendAllUser(cmd);
		}
		break;
	case CHAT_CHANNEL_SYSTEM:
		{
			char *msg=NULL;
			if(!cmd->ReadString(&msg))
				return ERROR_READ_DATA;
			CORE("","c2r_chat %d:%s",channel,msg);
			GetApp()->sendAllUser(cmd);

// 			g_sendCmd->BeginWrite();
// 			g_sendCmd->WriteShort(r2c_chat);
// 			g_sendCmd->WriteByte(channel);
// 			g_sendCmd->WriteString("abcd");
// 			GetApp()->sendAllUser(g_sendCmd);
		}
		break;
	}
	
	return ERROR_NONE;
}

int CS_C2RCmd::c2r_login()
{
	CG_CmdPacket* cmd=CMD();
	if(!cmd)
		return ERROR_READ_DATA;
	char *name=NULL;
	char *pwd=NULL;
	char *mac =NULL;
	char code=0;
	if(!cmd->ReadString(&name))
		return ERROR_READ_DATA;
	int len=strlen(name);
	if(len<2 || len>20)
		return false;

	if(!cmd->ReadString(&pwd))
		return ERROR_READ_DATA;
	len=strlen(pwd);

	CORE("C2RCmd:","user login name=%s,pwd=%s,start...",name, pwd);

	if(len<5||len>40)
	{
		CORE("C2RCmd:","user login name=%s,pwd=%s,password too short",name, pwd);
		return ERROR_READ_DATA;
	}
	if(!cmd->ReadByte(&code))
		return ERROR_READ_DATA;

	MYMSG("C2RCmd: ","user login name=%s,pwd=%s,copy=%d",name,pwd,(int)code);
	if(code!=GAME_COPY_RIGHT)
	{
		return ERROR_NONE;
	}
// 	LINK()->username = name;
// 	LINK()->pwd = pwd;
// 	LINK()->code = code;

	time_t t;
	time(&t);
	
	MYMSG("C2RCmd: ","user login name=%s,pwd=%s",name,pwd);
	char iResult=GetApp()->LoginIn(LINK(),name,pwd);
	MYMSG("C2RCmd: ","user login name=%s,pwd=%s,result%d",name,pwd,iResult);
	if(iResult!=LOGIN_IN_OK)
	{
		g_sendCmd->BeginWrite();
		g_sendCmd->WriteShort(r2c_login_ret);
		g_sendCmd->WriteByte(iResult);
		LINK()->session->SendPacket(g_sendCmd);
	}
	
	return ERROR_NONE;
}
int CS_C2RCmd::c2l_login_server()
{
	CG_CmdPacket* cmd=CMD();
	if(!cmd)
		return ERROR_READ_DATA;
	MYMSG("C2RCmd: ","login_server");
	char iCommand;
	if(!cmd->ReadByte(&iCommand))
		return ERROR_READ_DATA;

	switch(iCommand)
	{
		case LOGIN_CREATE:
		case LOGIN_DELETE:
			break;
		case LOGIN_SELECT_ROLE:
			{
				char sindex=0;
				if(!cmd->ReadByte(&sindex))//选择第几个角色
					return ERROR_READ_DATA;
				
				//GIVER()->SelectRole(sindex);
			}
			break;
		default:
			return ERROR_UNKNOWN;
			break;
	}
	return ERROR_NONE;
}

int CS_C2RCmd::c2l_even()//客户端过来的命令
{
	CG_CmdPacket* cmd=CMD();
	if(!cmd)
		return ERROR_READ_DATA;
	char iCommand;
	if(!cmd->ReadByte(&iCommand))
		return ERROR_READ_DATA;
	MYMSG("even","c2l_even iCommand%d",iCommand);
	switch(iCommand)
	{
	case CSL_EVEN_BIND_MAC:
		{
			char *tempstr =NULL;
			if(!cmd->ReadString(&tempstr))
				return ERROR_READ_DATA;
			//TRY_EXCEPT_RECORD(GIVER()->SetMacBind(tempstr));
		}
	}
	return ERROR_NONE;
}
