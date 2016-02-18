//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   EncryptUtil.cpp
//* Author   :   liujiquan
//* DateTime :   11/4/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "EncryptUtil.h"
#include "Base64.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   GetHeader
// Param    :   LPCTSTR pszSourceBase64
//              CString& strSource
// Return   :   HEADER
// Comment  :   
// -----------------------------------------------------------//
HEADER GetHeader(LPCTSTR pszSourceBase64, CString& strSource)
{
	if(strstr(pszSourceBase64, THUNDER_HEADER_STR))
	{
		char* pszSource = (char*)pszSourceBase64 +  strlen(THUNDER_HEADER_STR);
		strSource = CString(pszSource);

		return THUNDER_HEADER;
	}
	else if(strstr(pszSourceBase64, QQDL_HEADER_STR))
	{
		char* pszSource = (char*)pszSourceBase64 +  strlen(QQDL_HEADER_STR);
		strSource = CString(pszSource);

		return QQDL_HEADER;
	}
	else if(strstr(pszSourceBase64, Flashget_HEADER_STR))
	{
		char* pszSource = (char*)pszSourceBase64 +  strlen(Flashget_HEADER_STR);
		strSource = CString(pszSource);

		return FLASHGET_HEADER;
	}
	
	return HEADER_NULL;
}


// -----------------------------------------------------------//
// Function :   FormatEncryptData
// Param    :   HEADER header
//              LPTSTR pszSource
//              CString& szDestData
// Return   :   BOOL 
// Comment  :   ftp://dy:dy@xlj.2tu.cc:31111/.rmvb
// -----------------------------------------------------------//
BOOL   FormatEncryptData(HEADER header, LPTSTR pszSource, CString& szDestData)
{
	if(pszSource == NULL || header == HEADER_NULL)				return FALSE;
	
	if(header == THUNDER_HEADER)		// //AAftp://dy:dy@xlj.2tu.cc:31111/.rmvbZ
	{
		
		
		int len = strlen(pszSource);

		char* pBuffer = (char*)malloc(len+2+2+1);
		pBuffer[0] = 'A';
		pBuffer[1] = 'A';
		memcpy(pBuffer+2, pszSource, len);
		pBuffer[len+2] = 'Z';
		pBuffer[len+3] = 'Z';
		pBuffer[len+4] = '\0';

		szDestData = CString(pBuffer);

		free(pBuffer);
		pBuffer = NULL;

		return TRUE;
	}
	else if(header == FLASHGET_HEADER)		// [FLASHGET]ftp://dy:dy@xlj.2tu.cc:31111/[迅雷下载www.2tu.cc]雪国列车.BD1024高清中英双字.rmvb[FLASHGET]
	{
		int len = strlen(pszSource);
		
		char* pBuffer = (char*)malloc(len+2*(strlen("[FLASHGET]"))+1);
		memcpy(pBuffer, "[FLASHGET]", strlen("[FLASHGET]"));
		memcpy(pBuffer+strlen("[FLASHGET]"), pszSource, len);
		memcpy(pBuffer+strlen("[FLASHGET]") + len, "[FLASHGET]", strlen("[FLASHGET]"));
		pBuffer[len+2*(strlen("[FLASHGET]"))] = '\0';
		
		szDestData = CString(pBuffer);
		
		free(pBuffer);
		pBuffer = NULL;

		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------//
// Function :    FormatDecryptData
// Param    :   HEADER header
//              LPTSTR pszSource
//              CString& szDestData
// Return   :   BOOL 
// Comment  :   
// -----------------------------------------------------------//
BOOL   FormatDecryptData(HEADER header, LPTSTR pszSource, CString& szDestData)
{	
	if(pszSource == NULL || header == HEADER_NULL)				return FALSE;
	
	if(header == THUNDER_HEADER)
	{
		if(*(pszSource+2))
		{
			pszSource += 2;									// delete first two byte		
			pszSource[strlen(pszSource) - 2] = '\0';		// delete last two byte
			
			szDestData = CString(pszSource);
			return TRUE;
		}
	}
	else if(header == FLASHGET_HEADER)
	{
		if(strlen(pszSource) <= (strlen("[FLASHGET]")*2 + 1))		return FALSE;
		pszSource += strlen("[FLASHGET]");					//  delete first [FLASHGET]
		pszSource[strlen(pszSource) - strlen("[FLASHGET]")] = '\0';		//  delete last [FLASHGET] and &

		szDestData = CString(pszSource);
		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   DecryptData
// Param    :   CString strSource
// Return   :   CString 
// Comment  :   
// -----------------------------------------------------------//
CString  DecryptData(CString strSource)
{
	CString strDecrptyBase64Source;
	CString strDest;
	HEADER header = GetHeader(strSource.GetBuffer(0), strDest);
	strDest.TrimLeft();
	strDest.TrimRight();
	
	//1
	if(header == HEADER_NULL)
	{	
		strDecrptyBase64Source = GetDecryptBase64(strSource);
	}
	//2
	else if(header == THUNDER_HEADER)
	{
		strDecrptyBase64Source = GetDecryptBase64(strDest);
		FormatDecryptData(THUNDER_HEADER, strDecrptyBase64Source.GetBuffer(0), strDecrptyBase64Source);
	}
	//3
	else if(header == QQDL_HEADER)
	{
		strDecrptyBase64Source = GetDecryptBase64(strDest);
	}
	//4
	else if(header == FLASHGET_HEADER)
	{
		strDecrptyBase64Source = GetDecryptBase64(strDest);
		FormatDecryptData(FLASHGET_HEADER, strDecrptyBase64Source.GetBuffer(0), strDecrptyBase64Source);
	}

	return strDecrptyBase64Source;
}