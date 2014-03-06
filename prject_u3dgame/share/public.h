#ifndef __PUBLIC_FILE_HEADER__ 
#define __PUBLIC_FILE_HEADER__
#include "alldef.h"


#define CC_RETURN_IF(cond) if(cond) return
#define CC_RETURN_IF_FALSE(cond) if(cond) return false
#define CC_RETURN_NULL_IF_FALSE(cond) if(cond) return false

#define TRY_EXCEPT_RECORD(a) try {a;} catch (...) {CORE("EXCEPT: ", "%s %s %d error", __FILE__, __FUNCTION__ ,__LINE__);}

#define SAFE_DELETE(x) if (x){delete x;x = NULL;}

#define SAFE_DELETE_VECTOR(x) for (int i=0;i<(int)x.size();i++)\
{SAFE_DELETE(x[i]);x.clear();}

#define SAFE_REMOVE_VECTOR_NODE(nodetype,x,node)\
{\
	vector<nodetype>::iterator it = x.begin();\
	for (;it!=x.end();it++)\
{\
	nodetype tmp = (*it);\
	if(tmp==node)\
{\
	x.erase(it);\
	break;\
}\
}\
}



#define SAFE_DELETE_MAP(firsttype,secondtype,x)\
{\
	map<firsttype,secondtype>::iterator it = x.begin();\
	for (;it!=x.end();it++)\
{\
	secondtype tmp = it->second;\
	SAFE_DELETE(tmp);\
}\
	x.clear();\
}


#define CC_SAFE_RELEASE_OBJ(p)           if(p)\
	(p)=NULL;


//normal function
#define VECTOR_VISIT_BEGIN(vlist,tmpnode) for (int i=0;i<(int)vlist.size();i++)\
{\
	tmpnode = vlist[i];
#define VECTOR_VISIT_END			}

#define CC_SYNTHESIZE_NOSET(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var);


#define CC_SYNTHESIZE_RETAIN_SET(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var)\
{if(!var)return;\
	m_pAnimation = var;\
	m_pAnimation->retain();}

//map的快捷定义，附带几种常用方法。要求：secondtype必须有getID()方法，且为指针
#define CC_SYNTHESIZE_MAP(firsttype,secondtype, varName, funName)\
	map<firsttype,secondtype> varName;\
public: void freeAll##funName(void)\
{\
	SAFE_DELETE_MAP(firsttype,secondtype,varName);\
}\
	void delete##funName(firsttype iId)\
{\
	map<firsttype,secondtype>::iterator it = varName.find(iId);\
	if (it!=varName.end())\
{\
	SAFE_DELETE(it->second);\
	varName.erase(it);\
}\
}\
	secondtype find##funName(firsttype iId)\
{\
	map<firsttype,secondtype>::iterator it = varName.find(iId);\
	if (it==varName.end())\
	return NULL;\
	return it->second;\
}\
	bool insert##funName(secondtype pCre)\
{\
	CC_RETURN_IF_FALSE(!pCre);\
	CC_RETURN_IF_FALSE( find##funName(pCre->getID()));\
	varName[pCre->getID()]=pCre;\
	return true;\
}

//vector的快捷定义，附带几种常用方法。要求：varType必须有getID()方法，且为指针
#define CC_SYNTHESIZE_VECTOR(keytype,varType,varName,funName)\
	vector<varType> varName;\
public: \
	void freeAll##funName(void)\
{\
	SAFE_DELETE_VECTOR(varName);\
}\
	void delete##funName(keytype iId)\
{\
	vector<varType>::iterator it = varName.begin();\
	for (;it!=varName.end();it++)\
{\
	varType tmpdata = *it;\
	if (tmpdata->getID()==iId)\
{\
	SAFE_DELETE(tmpdata);\
	varName.erase(it);\
	return;\
}\
}\
}\
	varType find##funName(keytype iId)\
{\
	vector<varType>::iterator it = varName.begin();\
	for (;it!=varName.end();it++)\
{\
	varType tmpdata = *it;\
	if (tmpdata->getID()==iId)\
{\
	return tmpdata;\
}\
}\
	return NULL;\
}

#define FLOAT_EQU(v1,v2) (abs(v1-v2)<0.0001f)
#define CCP_EQU(v1,v2) (FLOAT_EQU(v1.x,v2.x)&&FLOAT_EQU(v1.y,v2.y))

//==================================CPub==================================
class CPub
{
public:
	static void test(){;};
protected:
private:
};


#endif//__PUBLIC_FILE_HEADER__