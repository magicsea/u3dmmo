#include "GameWorld.h"
#include "tinyxml.h"
#include "public.h"
#include "interface.h"
#include "s_cmdchannel.h"
#include "s_cmd.h"
#include "User.h"

extern CG_CmdPacket *g_sendCmd;
extern bool g_bGameRun;
extern SConfig g_cfg;
extern CSubLog g_slog;
CGameWorld g_pAppServer;

CGameWorld* GetApp()
{
	return &g_pAppServer;
}
CGameWorld::CGameWorld()
{
	m_activeLink = NULL;
	m_cmdGiver = NULL;

	m_activeCmd = new CG_CmdPacket;
	m_activeCmd->SetSize(MAX_CMD_PACKET_SIZE);
}
CGameWorld::~CGameWorld()
{
	releaseAll();
}

bool CGameWorld::init()
{
	m_iTime = Sys_GetTime();


	const char* pFilePath = "setup.xml";

	TiXmlDocument xmlDoc(pFilePath);
	if (!xmlDoc.LoadFile())
	{
		CORE("init:","load setup.xml error");
		return false;
	}
	TiXmlElement *root = xmlDoc.RootElement();  
	if (root==NULL)
	{
		CORE("init:","init error RootElement");
		return false;
	}
	


	if (!initConfig(root->FirstChildElement("config")))
	{
		CORE("init:","initConfig error");
		return false;
	}

	if (!initNet(root->FirstChildElement("net")))
	{
		CORE("init:","initNet error");
		return false;
	}

	if (!initDB(root->FirstChildElement("db")))
	{
		CORE("init:","initDB error");
		return false;
	}

	if (!initData())
	{
		return false;
	}


	return true;

}
void CGameWorld::run()
{
	ULONG dtime;
	static ULONG frame = 0;
	m_iOldTime = Sys_GetTime();
	ULONG endTime = Sys_GetTime() + (30 * 1000);

	while(g_bGameRun)
	{
		m_iOldTime = m_iTime;
		m_iTime = Sys_GetTime();

		process();

		if(m_iTime - m_iSyncTime >= g_cfg.r2c_interval)
		{
			m_iSyncTime = m_iTime;
			time_t nTime =0;
			time(&nTime);
		}


		dtime = m_iTime - m_iOldTime;

		float fDeltaTime = float(dtime) / 1000.0f;
		//OnRun(fDeltaTime);

		if(dtime < 10)
		{
			Sys_Sleep(10);
		}
		else if(dtime > 300)
		{
			printf("frame time = %d \r\n",dtime);
		}

	}
}

void CGameWorld::releaseAll()
{
	releaseNet();
	releaseUserData();
}
bool CGameWorld::initConfig(TiXmlElement* pRoot)
{
	CORE("init:","initConfig..");
	return true;
}
bool CGameWorld::initData()
{
	CORE("init:","initData..");
	return true;
}
bool CGameWorld::initDB(TiXmlElement* pRoot)
{
	CORE("init:","initDB..");
	return true;
}
bool CGameWorld::initNet(TiXmlElement* pRoot)
{
	CORE("init:","initNet..");
	g_cfg.client_listen_ip = "localhost";
	g_cfg.client_listen_port = 0;//8888;
	g_cfg.unlogin_timeout = 60;
	g_cfg.local_login = true;
	g_cfg.c2r_interval = 500;
	g_cfg.r2c_interval = 250;
	g_cfg.cl_pre_buffer = 3;
	g_cfg.cl_max_buffer = 1;

	//read config
	CORE("init:","initNet read config..");
	if(!pRoot)
		return false;
	m_strListenIp="0.0.0.0";
	TiXmlElement* pEleCon = pRoot->FirstChildElement("ip");
	if (pEleCon)
	{
		m_strListenIp = pEleCon->GetText();
	}
	string strport="7200";
	TiXmlElement* pEleConPort = pRoot->FirstChildElement("port");
	if (pEleConPort)
	{
		strport = pEleConPort->GetText();
	}
	m_iListenPort = atol(strport.c_str());

	g_cfg.client_listen_ip = m_strListenIp;
	g_cfg.client_listen_port = m_iListenPort;
	//start listen
	CORE("init:","start listen(%s,%d)..",m_strListenIp.c_str(),m_iListenPort);
	if(!m_ClientListener.StartListen(m_strListenIp.c_str(),
		m_iListenPort,true))
	{
		CORE("监听端口失败: ","start listen ip=%s,port = %d",m_strListenIp.c_str(),m_iListenPort);
		return false;
	}
	else
	{
		CORE("开始监听端口: ","start listen  ip=%s,port = %d",m_strListenIp.c_str(),m_iListenPort);
	}
	InitChannel();
	return true;
}
void CGameWorld::releaseNet()
{
	list<SNetLink*>::iterator it = m_unloginLink.begin();
	for (;it!=m_unloginLink.end();it++)
	{
		SNetLink* link = (*it);
		if (link)
		{
			if (link->session)
			{
				SAFE_DELETE(link->session);
			}
			SAFE_DELETE(link);
		}
	}
	m_unloginLink.clear();
}
void CGameWorld::InitChannel()
{

	m_channelUnlogin.m_channelName = "unlogin channel";
	m_channelLogin.m_channelName   = "login channel";
	//m_channelScene.m_channelName   = "scene channel";
	// cmd used when unlogin
	m_channelUnlogin.AddCmd(CS_C2RCmd::c2r_login,c2r_login,"login","");
	//m_channelUnlogin.AddCmd(CS_C2RCmd::s2l_login_scene,s2l_login_scene,"login_scene","");

	// cmd valid when login finish 
	m_channelLogin.AddCmd(CS_C2RCmd::c2r_chat,c2r_chat,"chat","");
	m_channelLogin.AddCmd(CS_C2RCmd::c2l_login_server,c2l_login_server,"login_server","");
	m_channelLogin.AddCmd(CS_C2RCmd::c2l_even, c2l_even, "c2l_even", "");
}
void CGameWorld::process()
{
	TRY_EXCEPT_RECORD(processListener());
	TRY_EXCEPT_RECORD(processLink());
	TRY_EXCEPT_RECORD(processUser());
}
void CGameWorld::processListener()
{
	int cnt = 0;
	SNetLink *link;
	CG_TCPSession *session;

	// avoid accept too many link in one cycle
	while(cnt++ < 10)	
	{
		session = m_ClientListener.AcceptNewSession();
		if(!session) break;
		link = new SNetLink;
		link->connectTime = Sys_GetSec();
		link->session = session;
		//link->id = CreateId();
		link->valid = true;
		short port=0;
		unsigned long ip =0;
		if(!session->GetRemoteAddr (link->strIp, &port,&ip))
		{
			sprintf(link->strIp,"无效ip\0");
		}
		m_unloginLink.push_back(link);

		MYMSG("ProcessNewLink: ","new user connected");
	}
}
void CGameWorld::processLink()
{
	short cmdId;
	SNetLink *link;
	CG_TCPSession *session;
	list<SNetLink*>::iterator it;

	for(it=m_unloginLink.begin();it!=m_unloginLink.end();)
	{
		link    = (*it);
		LINK()  = link;
		session = link->session;
		if(!link->valid || Sys_GetSec()-link->connectTime>g_cfg.unlogin_timeout)
		{
			MYMSG("ProcessNetLink: ","remove unlogin link");
			delete session;
			delete link;
			it = m_unloginLink.erase(it);

			continue;
		}
		session->DefProc();
		if(session->IsDead())
		{
			link->valid = false;
			it++;
			continue;
		}

		while(session->GetPacket(m_activeCmd))
		{
			MYMSG("ProcessNetLink: ","GetPacket");
			if(!m_activeCmd->ReadShort(&cmdId))
			{
				link->valid = false;
				break;
			}

			MYMSG("ProcessNetLink: ","GetPacket_RS:%d",cmdId);
			if(!m_channelUnlogin.RecvCmd(cmdId))
				link->valid = false;
		}
		it++;
	}
}

void CGameWorld::processUser()
{
	short cmdId;
	CG_TCPSession *session;
	map<long,CUser*>::iterator it;
	CUser *user;
	vector<long> vDeadUser;
	for(it=m_oUsers.begin();it!=m_oUsers.end();)
	{
		user    = it->second;
		GIVER() = user;//user->m_dummy;//(CS_RegionCreature*)
		session = user->m_session;
		if(session)
		{
			session->DefProc();
			//check dead
			if(session->IsDead()/* || GIVER()->m_bClose*/) 
			{
				//user->m_session = NULL;
				user->m_netDeadTime = m_iTime;

				if(session->GetState() == NET_STATE_DEAD)
					CORE("User Disconnect:", "userid=%d",user->getUserId());

				//deleteUser(user->getUserId());
				vDeadUser.push_back(user->getUserId());
				//_DELETE(session);
				//continue;
			}
			else
			{
				bool bQuit = false;
				while(session->GetPacket(m_activeCmd)) 
				{	
					if(!m_activeCmd->ReadShort(&cmdId))
						break;
					m_channelLogin.RecvCmd(cmdId);
				}
				if(session->GetState() == NET_STATE_ERROR)
					CORE("Unknown package format", "%d",user->getUserId());
			}
		}
		it++;
	}

	//释放掉线的
	for (int i=0;i<(int)vDeadUser.size();i++)
	{
		long userid = vDeadUser[i];
		if (userid>0)
		{
			deleteUser(userid);
			CORE("delete user:", "userid=%d",userid);
		}
	}
}

bool CGameWorld::initUserData()
{
	CORE("init:","initUserData...");
	return true;
}
void CGameWorld::releaseUserData()
{
	map<long,CUser*>::iterator it;
	for (it=m_oUsers.begin();it!=m_oUsers.end();it++)
	{
		CUser* pUser = it->second;
		SAFE_DELETE(pUser);
	}
	m_oUsers.clear();
}
void CGameWorld::addUser(CUser* pUser)
{
	if(!pUser)
		return;
	CUser* pUser1 = getUser(pUser->getUserId());
	if (pUser1)
	{
		return;
	}

	m_oUsers[pUser->getUserId()]=pUser;
}
void CGameWorld::deleteUser(long iUserId)
{
	map<long,CUser*>::iterator it = m_oUsers.find(iUserId);
	if (it==m_oUsers.end())
		return ;
	CUser* pUser = it->second;
	m_oUsers.erase(it);
	SAFE_DELETE(pUser);
}
CUser* CGameWorld::getUser(long iUserId)
{
	map<long,CUser*>::iterator it = m_oUsers.find(iUserId);
	if (it==m_oUsers.end())
		return NULL;
	return it->second;
}


long CGameWorld::createId()
{
	static long st_id_maker = 0;
	st_id_maker++;
	return st_id_maker;
}
char CGameWorld::LoginIn(SNetLink* pLink,const char* strAccout,const char* strPwd)
{
	if (!pLink||!pLink->session)
		return LOGIN_PWD_ERROR;
	CUser* pUser = new CUser();
	pUser->setUserId(createId());
	pUser->Name(strAccout);//测试用
	pUser->setSession(pLink->session);

	pLink->valid = false;
	pLink->session = NULL;

	addUser(pUser);

	g_sendCmd->BeginWrite();
	g_sendCmd->WriteShort(r2c_login_ret);
	g_sendCmd->WriteByte(LOGIN_IN_OK);
	g_sendCmd->WriteLong(pUser->getUserId());
	g_sendCmd->WriteString((char*)pUser->Name());
	pUser->revCmd(g_sendCmd);
	return LOGIN_IN_OK;
}
void CGameWorld::sendAllUser(CG_CmdPacket *Cmd)
{
	map<long,CUser*>::iterator it = m_oUsers.begin();
	for (;it!=m_oUsers.end();it++)
	{
		CUser* pUser = it->second;
		if (pUser)
		{
			pUser->revCmd(Cmd);
		}
	}
}
