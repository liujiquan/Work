//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   URLEncode.cpp
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   ÖÐÎÄµÄURLEncode Decode (UTF-8/ASCII)
//*-----------------------------------------------------------------------------*/
#include "URLEncode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   TOHEX
// Param    :   BYTE cValue
//              CHAR c
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString TOHEX(BYTE cValue, CHAR c)
{
	CString strTemp;
	
	strTemp.Format("%c%02X", c, cValue);
	
	return strTemp;
}

// -----------------------------------------------------------//
// Function :   FROMHEX
// Param    :   BYTE bHi
//              BYTE bLow
// Return   :   BYTE
// Comment  :   
// -----------------------------------------------------------//
BYTE FROMHEX(BYTE bHi, BYTE bLow)
{
	BYTE bValue;
	TCHAR szBuffer[3] = {0};
	
	sprintf(szBuffer,"%c%c", bHi, bLow);
	sscanf(szBuffer, "%02X", &bValue);
	
	return bValue;
}

// -----------------------------------------------------------//
// Function :   UTF8TOASCII
// Param    :   LPCTSTR szUTF8Data
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString UTF8TOASCII(LPCTSTR szUTF8Data)
{
	if(szUTF8Data == NULL)			return "";
	
	int nLen = strlen(szUTF8Data);
	//->WCHAR  
	WCHAR* pwchar = (WCHAR*)malloc(nLen*sizeof(WCHAR));
	memset(pwchar, 0x00, nLen*sizeof(WCHAR));
	int nUTF8Len = MultiByteToWideChar(CP_ACP, 0, szUTF8Data, nLen, pwchar, nLen*sizeof(WCHAR));
	
	TCHAR* szAscii = (TCHAR*)malloc(nUTF8Len * 4 + 1);
	memset(szAscii, 0x00, nUTF8Len * 4 + 1);
	int nAsciiLen = WideCharToMultiByte(CP_UTF8, 0, pwchar, nUTF8Len, szAscii, nUTF8Len * 4, 0, 0);
	if(nAsciiLen == 0)				return "";
	
	CString str(szAscii);
	free(pwchar);
	free(szAscii);
	pwchar = NULL;
	szAscii = NULL;
	
	return str;
}

// -----------------------------------------------------------//
// Function :   ASCIITOUTF8
// Param    :   LPCTSTR szAsciiData
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString ASCIITOUTF8(LPCTSTR szAsciiData)
{
	if(szAsciiData == NULL)			return "";
	
	int nLen = strlen(szAsciiData);
	
	
	WCHAR* pwchar = (WCHAR*)malloc(nLen*sizeof(WCHAR));
	int nUTF8Len = MultiByteToWideChar(CP_UTF8, 0, szAsciiData, nLen, pwchar, nLen*sizeof(WCHAR));
	
	TCHAR* szAscii = (TCHAR*)malloc(nUTF8Len * 2 + 1);
	memset(szAscii, 0x00, nUTF8Len * 2 + 1);
	int nAsciiLen = WideCharToMultiByte(CP_ACP, 0, pwchar, nUTF8Len, szAscii, nUTF8Len * 2, 0, 0);
	if(nAsciiLen == 0)				return "";
	
	CString str(szAscii);
	free(pwchar);
	free(szAscii);
	pwchar = NULL;
	szAscii = NULL;
	
	return str;
}

// -----------------------------------------------------------//
// Function :   Encode
// Param    :   CString strSource
//              BOOL bUTF8
//              CHAR c
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString Encode(CString strSource, BOOL bUTF8, CHAR c)
{
	strSource.TrimRight();
	strSource.TrimLeft();
	LPCTSTR pszSource = strSource.GetBuffer(0);
	CString str;
	CString strDest = _T("");		// strDest
	
	if(bUTF8)
	{
		str = UTF8TOASCII(pszSource);
		pszSource = str.GetBuffer(0);
	}
	
	
	int index = 0;
	while(pszSource[index] != '\0')
	{
		BYTE bValue = (BYTE)pszSource[index];
		
        if (isalnum(bValue) ||   (bValue == '-') || (bValue == '_') ||  (bValue == '.') || (bValue == '~'))		// 0-9/A-Z/a-z/-/ _/./~
		{   
			strDest += bValue;  
		}
        else if (bValue == ' ')																					// ' ' -> +
        {
			strDest += "+"; 
		}
        else  
        {  
            strDest += TOHEX(bValue, c);    
        }  
        
		index++;
	}
	
	return strDest;
}

// -----------------------------------------------------------//
// Function :   Decode
// Param    :   CString strSource
//              BOOL bUTF8
//              CHAR c
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString Decode(CString strSource, BOOL bUTF8, CHAR c)
{
	strSource.TrimRight();
	strSource.TrimLeft();
	LPCTSTR pszSource = strSource.GetBuffer(0);
	BYTE bValue;
	CString strDest = _T("");
	int index = 0;

	while(pszSource[index] != '\0')
	{
		bValue = (BYTE)pszSource[index];
		if(bValue == '+')		
		{
			bValue = ' ';
			strDest += bValue;
			
			index++;
		}
		else if(bValue == c)
		{	
			BYTE bValueLow = (BYTE)pszSource[index+2];
			BYTE bValueHi =  (BYTE)pszSource[index+1];
			if(bValueLow == '\0' || bValueHi == '\0')
			{
				strDest += bValue;
				strDest += bValueLow;
				strDest += bValueHi;
				break;
			}
			bValue = FROMHEX(bValueHi, bValueLow);
			strDest += bValue;
			
			index += 3;
		}
		else
		{
			strDest += bValue;
			index++;
		}
	}
	if(bUTF8)
	{
		strDest = ASCIITOUTF8(strDest.GetBuffer(0));
	}
	
	return strDest;
}