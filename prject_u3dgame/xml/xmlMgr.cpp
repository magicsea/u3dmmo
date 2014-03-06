//
//  xmlMgr.cpp
//  logon
//
//  Created by  on 12-12-11.
//  Copyright (c) 2012年 SkySoul. All rights reserved.
//

#include <iostream>
#include "xmlMgr.h"
//#include "git_version.h"
#include <libxml/xpath.h>
#define LOG_ERROR printf
//	def("readXML",&xmlManager::read),
//	def("xmlKeyCounts",&xmlManager::keyCount),
//	def("xmlCounts",&xmlManager::count),
//	def("xmlValue",&xmlManager::getString)
xmlXPathObjectPtr xmlManager::getNodeSet(xmlDocPtr doc, const xmlChar *szXpath)
{
    
    xmlXPathContextPtr context;    //XPATH上下文指针
    
    xmlXPathObjectPtr result;       //XPATH对象指针，用来存储查询结果
    
    context = xmlXPathNewContext(doc);     //创建一个XPath上下文指针 
    //    xmlns="urn:schemas-microsoft-com:office:spreadsheet"
    //    xmlns:o="urn:schemas-microsoft-com:office:office"
    //    xmlns:x="urn:schemas-microsoft-com:office:excel"
    //    xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet"
    //    xmlns:html="http://www.w3.org/TR/REC-html40"
    //    xmlns:x2="http://schemas.microsoft.com/office/excel/2003/xml"
    int status;
    status = xmlXPathRegisterNs(context, BAD_CAST"ns", BAD_CAST"urn:schemas-microsoft-com:office:spreadsheet"); 
    status = xmlXPathRegisterNs(context, BAD_CAST"o", BAD_CAST"urn:schemas-microsoft-com:office:office"); 
    status = xmlXPathRegisterNs(context, BAD_CAST"x", BAD_CAST"urn:schemas-microsoft-com:office:excel"); 
    status = xmlXPathRegisterNs(context, BAD_CAST"ss", BAD_CAST"urn:schemas-microsoft-com:office:spreadsheet"); 
    status = xmlXPathRegisterNs(context, BAD_CAST"html", BAD_CAST"http://www.w3.org/TR/REC-html40"); 
    status = xmlXPathRegisterNs(context, BAD_CAST"x2", BAD_CAST"http://schemas.microsoft.com/office/excel/2003/xmle"); 
    
    if (context == NULL)
    {
        //Log.Debug("XML", "context is NUL\n");
		printf("context is NUL\n");
        return NULL;
    }
    
    result = xmlXPathEvalExpression(szXpath, context); //查询XPath表达式，得到一个查询结果
    
    xmlXPathFreeContext(context);             //释放上下文指针
    
    if (result == NULL)
    {   
        //Log.Debug("XML", "xmlXPathEvalExpression return NULL\n");
		printf("xmlXPathEvalExpression return NULL\n");
        return NULL; 
    }
    
    if (xmlXPathNodeSetIsEmpty(result->nodesetval))   //检查查询结果是否为空
    {
        xmlXPathFreeObject(result);
        //Log.Debug("XML", "nodeset is empty\n");
		printf("nodeset is empty\n");
        return NULL;
    }
    
    return result;   
    
}


string** xmlManager::readSheet(const char *fileName, const char *sheetName, bool showDebugInfo, int & l1, int & l2)
{
    xmlDocPtr doc;
    if (showDebugInfo)
    {
        LOG_ERROR("XML", "Read File: %s, Sheet: %s", fileName, sheetName);
    }
    //        xmlNodePtr root;
    // load an exist xml file.
    //char* config_file = (char*)CONFDIR "/logon.conf";
    doc = xmlParseFile(fileName);
    if (doc == NULL )
    {
        LOG_ERROR("Document not parsed successfully. \n");
        return NULL;
    }
    
    //Read Task prototype data
    char* _Xpath = new char[200];
    sprintf(_Xpath, "//ns:Worksheet[@ss:Name='%s']/ns:Table/ns:Row", sheetName);
    xmlChar *szXpath =BAD_CAST (_Xpath);
    
    xmlXPathObjectPtr app_result = xmlManager::getNodeSet(doc,szXpath);
    
    delete _Xpath;
    
    if (NULL == app_result)
    {
        string msg = ":reading file failed!! ";
        msg+=fileName;
        msg+=" . ";
        msg+=sheetName;
        LOG_ERROR(msg.c_str());
        return NULL;
    }
    
    vector<map<int,string>*> strs;
    
    //int count = app_result->nodesetval->nodeNr;
    xmlNodeSetPtr nodeset = app_result->nodesetval;
    
    //int num = nodeset->nodeNr;
    
    //[TASK_DATA_LENGTH];
    int maxColumn = 0;
    for (int i = 0; i < nodeset->nodeNr; i++)
    {
        map<int,string>* row = new map<int,string>;
        strs.push_back(row);
        
        xmlNodePtr cellNode = nodeset->nodeTab[i]->children;
        
        //            Log.Debug("XML", "%s %i\n", nodeset->nodeTab[i]->name, i);
        //Log.Debug("XML", "%s\n", cellNode->name);
        
        int index = 1;
        while (NULL != cellNode)
        {
            string value_str;
            if (cellNode->type == XML_ELEMENT_NODE
                && !xmlStrcmp(cellNode->name, BAD_CAST "Cell")
                //&& NULL != cellNode->children
                )
            {
                if (xmlHasNsProp(cellNode, BAD_CAST "Index", BAD_CAST "urn:schemas-microsoft-com:office:spreadsheet"))
                {
                    xmlChar* szAttr = xmlGetNsProp(cellNode, BAD_CAST "Index", BAD_CAST "urn:schemas-microsoft-com:office:spreadsheet");
                    index = atoi((char *)szAttr);
                }
                
                if (NULL != cellNode->children) {
                    string value_str = (char*)xmlNodeGetContent(cellNode->children);
                    (*row)[index] = value_str;
                }
                
                if (maxColumn < index)
                {
                    maxColumn = index;
                }
                index++;
            }
            cellNode = cellNode->next;
        }
        
    }
    
    
    xmlXPathFreeObject(app_result);
    
    xmlFreeDoc(doc);

    int a = (int)strs.size();
    int b = maxColumn;
    string ** strArray = new string*[a];
    for (int i = 0; i < a; i++) {
        strArray[i] = new string[b];
    }
    
    for (int i = 0; i < a; i++) {
        map<int,string>::iterator itr = (strs.at(i))->begin();
        //int l = strs.at(i)->size();
        for (; itr != (strs.at(i))->end(); itr++)
        {
            strArray[i][(*itr).first - 1] = (*itr).second;
            //Log.Debug("XML", "row %i, column %i: %s", i + 1, (*itr).first, (*itr).second.c_str());

        }
        //Log.Debug("XML", "/////////////////////////////////");

        delete (strs.at(i));
    }
    
    if (showDebugInfo)
    {
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++)
            {
                if (!strArray[i][j].empty())
                {
                    LOG_ERROR("XML", "row %i, column %i: %s", i + 1, j + 1, strArray[i][j].c_str());
                }
                
            }
            LOG_ERROR("XML", "/////////////////////////////////");
            
        }
    }
    
    l1 = a;
    l2 = b;
    
    return strArray;
}


void xmlManager::freeStringArray(string** stringArray, int l1, int l2)
{
//    int l1 = sizeof(stringArray);
//    int l2 = sizeof(stringArray[0]);
//    int l3 = sizeof(stringArray[0][0]);
//    int a = sizeof(stringArray) / sizeof(stringArray[0]);
//    int b = sizeof(stringArray[0]) / sizeof(stringArray[0][0]);
    for (int i = 0; i < l1; i++) {
        delete[] stringArray[i];
    }
    delete [] stringArray;
    stringArray = NULL;
}


///////////////////////////////////////////////////////////////////////////////
string ** xmlManager::s_strArray=NULL;
int xmlManager::maxKeyNos = 0;
int xmlManager::maxNos = 0;

bool xmlManager::read(string fileName, string sheetName)
{
    // release the pre one;
    if(s_strArray!=NULL)
    {
        for (int i = 0; i < maxNos; i++) {
            delete[] s_strArray [i];
        }
        delete [] s_strArray;
        s_strArray = NULL;
    }
    
    s_strArray = readSheet(fileName.c_str(),
                           sheetName.c_str(),
                           false,
                           maxNos,
                           maxKeyNos);
    
    if (s_strArray)
    {
        return true;
    }
}

