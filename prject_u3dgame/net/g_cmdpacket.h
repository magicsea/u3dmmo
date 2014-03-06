/*
g_CmdPacket.h: interface for the CG_CmdPacket class.
*/
#ifndef __CG_CMD_PACKET_H__
#define __CG_CMD_PACKET_H__

//#include "Net_Lib_Def.h"
#include "platform.h"
/* define default packet buffer size */
const int DEFAULT_CMD_PACKET_SIZE = 1024;
/* define max packet buffer size */
const int MAX_CMD_PACKET_SIZE	  = 1024 * 32;
/* define some length used in packet class */
const int BYTE_SIZE  = 1;
const int LONG_SIZE  = 4;
const int SHORT_SIZE = 2;
const int FLOAT_SIZE = 4;


#include <string>
using namespace std;
const int OP_READ  = 1;
const int OP_WRITE = 2;
class NET_LIB_API CG_CmdPacket  
{
public:
	CG_CmdPacket();
	virtual ~CG_CmdPacket();


	void BeginWrite();
	void BeginRead(char *p,int len);
	void BeginRead();

	bool Serialize(string &str);
	bool Serialize(long *l);
	bool Serialize(char *c);
	bool Serialize(short *s);
	bool Serialize(float *f);

	bool UTF2GBKWriteString(char *str);
	bool ReadStringGBK2UTF(string& str);

	bool ReadBinary(char **data,int *len);
	bool ReadString(char **str);
	bool ReadFloat(float *f);
	//bool ReadLong64(__int64* pInt);
	bool ReadLong(long *l);
	bool ReadShort(short *s);
	bool ReadByte(char *c);
	
	bool WriteBinary(char *data,int len);
	bool WriteString(char *str);
	bool WriteFloat(float f);
	//bool WriteLong64(__int64 n);//linux dont support __int64
	bool WriteLong(long l);
	bool WriteShort(short s);
	bool WriteByte(char c);
	
	bool  CopyData(char *buf,int len);
	char *GetData();
	int   GetDataSize();
	int   GetMaxSize();
	
	bool  SetSize(int len);
	bool  CloneFrom(CG_CmdPacket *packet);
	void FromWrite2Read();

	bool  IsReading() { return m_op == OP_READ; }
	bool  IsWritting() { return m_op == OP_WRITE; }

	int   m_nReadOffset;
	int   m_op;
	int   m_nLen;

	int   m_nWriteOffset;
	int   m_nMaxSize; 
	
private:
	
	bool  WriteData(void *data,int len);
	bool  ReadData(void *data,int len);
		
	char *m_pData;
	char *m_pReadData;


};

#endif
