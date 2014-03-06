#ifndef __SERVER_USER_H__
#define __SERVER_USER_H__
#include "alldef.h"
const int USER_ATTR_LEVEL = 0;
const int USER_ATTR_EXP = 1;
const int USER_ATTR_MONEY = 2;
const int USER_ATTR_MAX = 10;

class CG_TCPSession;
class CG_CmdPacket;
class CUser
{
public:
	CUser();
	~CUser();
	void init();
	void releaseData();
public:
	void setAttr(int idx,long iValue);
	long getAttr(int idx);

	void setUserId(long val){m_iUserId=val;};
	long getUserId(){return m_iUserId;};
	
	const char* Name(){return m_strUserName.c_str();};
	void Name(const char* val){m_strUserName=val;};
private:
	long m_iAttr[USER_ATTR_MAX];
	long m_iUserId;
	string m_strUserName;

public:
	bool revCmd(CG_CmdPacket *Cmd);
	void setSession(CG_TCPSession* pSession){m_session=pSession;};
	CG_TCPSession *m_session;
	long m_netDeadTime;
};
#endif//__SERVER_USER_H__