#include "User.h"
#include "s_cmdchannel.h"
#include "s_cmd.h"
#include "public.h"

CUser::CUser():
m_session(NULL),
m_iUserId(0)
{
	init();
}
CUser::~CUser()
{
	releaseData();
}
void CUser::init()
{
	m_iUserId = 0;
	memset(m_iAttr,0,sizeof(m_iAttr));
	m_strUserName="noname";
}
void CUser::releaseData()
{
	SAFE_DELETE(m_session);
}
void CUser::setAttr(int idx,long iValue)
{
	if (idx<0||idx>=USER_ATTR_MAX)
		return ;
	m_iAttr[idx]=iValue;
}
long CUser::getAttr(int idx)
{
	if (idx<0||idx>=USER_ATTR_MAX)
		return 0;
	return m_iAttr[idx];
}
bool CUser::revCmd(CG_CmdPacket *Cmd)
{
	if(!m_session)
		return false;
	return m_session->SendPacket(Cmd);
}