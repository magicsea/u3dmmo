//
//  xmlMgr.h
//  logon
//
//  Created by  on 12-12-11.
//  Copyright (c) 2012年 SkySoul. All rights reserved.
//

#ifndef logon_xmlMgr_h
#define logon_xmlMgr_h


#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

//#include "LogonStdAfx.h"
#include "../share/alldef.h"

class xmlManager
{
public:
    static xmlXPathObjectPtr getNodeSet(xmlDocPtr doc, const xmlChar *szXpath);
    static string** readSheet(const char *fileName, const char *sheetName, bool showDebugInfo, int & rowNumber, int & columnNumber);
    static void freeStringArray(string** stringArray, int rowNumber, int columnNumber);
    
    
    // every read pairs a release()
    // c++ -> lua
    // read
    static bool read(string,string);
    static int keyCount(){ return maxKeyNos; } // 每条纪录的具体field
    static int count(){ return maxNos; }
    static string getString(int uid, int key) // 根据ID和项目查找对应的数值；
    {
        if((key<0)||(uid<0))
        {
            //LOG_ERROR("xmlRead input prams is error",uid,key);
			printf("xmlRead input prams is error",uid,key);
            return "";
        }
        if (key >= maxKeyNos || uid >= maxNos || s_strArray==NULL) return "";
        return s_strArray[uid][key];
    }
    static int maxKeyNos;  // 纪录的filed树木
    static int maxNos;  // 纪录的条目
    static string** s_strArray;
};

#endif
