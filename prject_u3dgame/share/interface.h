#ifndef __INTERFACE_H__
#define __INTERFACE_H__

// log device
class ILogDevice
{
public:
	ILogDevice() {}
	virtual ~ILogDevice() {}

	virtual bool Init(const char *file) = 0;
	virtual void Exit()	= 0;
	
	virtual void Log(const char *prefix,const char *fmt,...) = 0;

	virtual void EnablePrint(bool enable) = 0;
	virtual void EnableWriteFile(bool enable) = 0;
	virtual void EnableIndex(bool enable) = 0;
	virtual void EnableTime(bool enable) = 0;

	// for vc
	virtual void EnableDebugString(bool enable) = 0;
};

//
// define for debug message 
//
extern	ILogDevice *g_message,*g_warning,*g_core;


#ifdef _DEBUG
#define LOG_MSG
#endif
#define LOG_WARNING
#define LOG_CORE

#ifdef LOG_MSG
	#define MYMSG g_message->Log
#else
	#define MYMSG
#endif

#ifdef LOG_WARNING
	#define WAR g_warning->Log
#else
	#define WAR
#endif

#ifdef LOG_CORE
	#define CORE g_core->Log
	
#else
	#define CORE 
#endif
#ifdef _DEBUG
#define TRY_EXCEPT_RECORD(a) a;
#else
#define TRY_EXCEPT_RECORD(a) try {a;} catch (...) {CORE("EXCEPT: ", "%s %s %d error", __FILE__, __FUNCTION__ ,__LINE__);}// ShowMessage(g_error_str); 
#endif
class ISubSystem
{
public:
	ISubSystem() {}
	virtual ~ISubSystem() {}

	virtual bool Init(char* strPath) = 0;
	virtual void OnFrame(unsigned long time,unsigned long delta) = 0;
	virtual void Exit() = 0;
	virtual const char *GetName() = 0;
};
class CSubLog : public ISubSystem
{
public:
	CSubLog() {}
	virtual ~CSubLog() {}
	
	bool Init(char* strPath);
	void OnFrame(unsigned long time,unsigned long delta);
	void Exit();
	const char *GetName();
};
/*²Î¿¼
void ShowNewCore();
{
	//long iu=(long)&link;
			char str[128];
	sprintf(str,"out %x",(long)&link );
	MYMSG("ÄÚ´æµØÖ·:",str);
}*/
void InitDebug();
void ExitDebug();
#endif
