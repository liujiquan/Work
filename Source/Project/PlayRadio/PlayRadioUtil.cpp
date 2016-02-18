//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PlayRadioUtil.cpp
//* Author   :   liujiquan
//* DateTime :   11/5/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "PlayeRadioUti.h"
#include <time.h>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   randomize_guid
// Param    :   unsigned char *buf
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void randomize_guid(unsigned char *buf)
{
    int digit, dig;
    time_t curtime;
	
    *buf++='{';
    time(&curtime);
    srand(curtime);
    for (digit=0; digit <32; digit++)
    {
        if (digit==8 || digit == 12 || digit == 16 || digit == 20) *buf++='-';
		
        dig = rand()%0xf;
        if (dig<10)
            *buf++='0'+dig;
        else
            *buf++='A'+(dig-10);
    }
    *buf++='}';
    *buf++='\0';
}

// -----------------------------------------------------------//
// Function :   randomizeGuid
// Return   :   LPCTSTR
// Comment  :   
// -----------------------------------------------------------//
unsigned char* randomizeGuid()
{
	unsigned char szBuffer[MAX_PATH] = {0};

	randomize_guid(szBuffer);

	return (unsigned char*)szBuffer;
}

// -----------------------------------------------------------//
// Function :   AnalyzeUrl
// Param    :   LPCTSTR szUrl
//              LPSTR pszServerName
//              LPSTR pszFileName
//              u_short& nPort
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL AnalyzeUrl(LPCTSTR szUrl, LPSTR pszServerName, LPSTR pszFileName, u_short& nPort)
{
	if(!szUrl || !pszServerName || !pszFileName)	return FALSE;
	
	TCHAR szPort[8] = {0};
	nPort = DEFAULT_PORT;
	char* pszUrl = (LPTSTR)szUrl;
	
	if(!strncmp("http://", pszUrl, 7)) pszUrl = pszUrl + 7;
	char* pTemp = strchr(pszUrl, '/');
	if(pTemp == NULL)								return FALSE;
	
	memcpy(pszServerName, pszUrl, pTemp - pszUrl);		// szServerName
	memcpy(pszFileName, pTemp, strlen(pTemp));			// szFile
	
	pTemp = strchr(pszServerName, ':');
	if(pTemp)
	{
		memcpy(szPort, pTemp + 1, strlen(pszServerName) - (pTemp - pszServerName) - 1);
		nPort = atoi(szPort);
		pszServerName[pTemp-pszServerName] = '\0';
	}
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   AnalyzePacket
// Param    :   LPCTSTR szBuffer
//              PREQUESTINFO pRequestInfo
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL AnalyzePacket(LPCTSTR szBuffer, PREQUESTINFO pRequestInfo)
{
	if(szBuffer == NULL || pRequestInfo == NULL)		return FALSE;
	
	memset(pRequestInfo, 0x00, sizeof(REQUESTINFO));
	if(strstr(szBuffer, "HTTP/1.1 200 OK"))	pRequestInfo->dwStatus = REQUEST_STATUS_200;
	if(strstr(szBuffer, "video/x-msvideo"))	pRequestInfo->Content_Type = REQUEST_CONTENTTYPE_video;
	
	char* pszContentLen = strstr(szBuffer, "Content-Length: ");
	if(pszContentLen == NULL)							return FALSE;
	
	pszContentLen += strlen("Content-Length: ");
	pRequestInfo->Content_Length = atol(pszContentLen);

	char* pEnd = strstr(szBuffer, "\r\n\r\n");
	if(pEnd == NULL)									return FALSE;
	pRequestInfo->dwHeaderLen = pEnd - (szBuffer + 1) + sizeof("\r\n\r\n");

	return TRUE;
}