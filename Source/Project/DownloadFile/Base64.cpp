//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Base64.cpp
//* Author   :   liujiquan
//* DateTime :   11/4/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "Base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   EncryptBase64
// Param    :   LPTSTR pszBase64
//              LPCTSTR pszSource
//              int len
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD EncryptBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len)
{
    if(len <= 0 || pszSource == NULL)   return -1;
    int nCount = 0;
    static BYTE BASE64CODE[] = 
    {
	      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
//		  "中华人民共和国安徽省安庆市宿松县五里乡楊树村窑岭组七号刘继全你好"
    };
	
    int nSize = len % 3 == 0 ? len/3 : len/3+1;
    for(int i = 0; i < nSize ; i++)
    {
        BYTE cSrc0,cSrc1,cSrc2;
        BYTE cDest0,cDest1,cDest2,cDest3;
        if(i*3+1 == len)
        {
            cSrc0 = pszSource[i*3];
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                          
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)];                 
            cDest2 = '=';
            cDest3 = '=';
        }
        else if(i*3+2 == len)
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)];                   
            cDest3 = '=';
        }
        else
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
            cSrc2 = pszSource[i*3+2];   
			
            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)|(cSrc2>>6)];        
            cDest3 = BASE64CODE[(cSrc2 & 0x3f)];    
			
//			BYTE i = cSrc0 >> 2;
//			if(i % 2 == 0)
//			{
//				cDest0 = BASE64CODE[i] ; 
//				cDest1 = BASE64CODE[i+1] ; 
//			}
//			else 
//			{
//				cDest0 = BASE64CODE[i-1] ; 
//				cDest1 = BASE64CODE[i] ; 
//			}
//			i = ((cSrc1&0x0F)<<2)|(cSrc2>>6);
//			if(i % 2 == 0)
//			{
//				cDest2 = BASE64CODE[i];  
//				cDest3 = BASE64CODE[i+1];   
//			}
//			else
//			{
//				cDest2 = BASE64CODE[i-1];  
//				cDest3 = BASE64CODE[i];   
//			}       
        } 
		
        pszBase64[nCount++] = cDest0;
        pszBase64[nCount++] = cDest1;
        pszBase64[nCount++] = cDest2;
        pszBase64[nCount++] = cDest3;
    }
	
	return nCount;
}

// -----------------------------------------------------------//
// Function :   DecryptBase64
// Param    :   LPTSTR pszDesryptSource
//              LPCTSTR pszBase64
//              int len
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD DecryptBase64(LPTSTR pszDesryptSource, LPCTSTR pszBase64, int len)
{
	if(len <= 0 || pszDesryptSource == NULL || pszBase64 == NULL)   return -1;
//	if(len % 4 != 0)												return -1;
	
	int nCount = 0;
	int nSize = len / 4;
	
	for(int i = 0; i < nSize; i++)
	{
		BYTE cSrc0,cSrc1,cSrc2,cSrc3;				// base64
        BYTE cDest0,cDest1,cDest2;					// source
		BYTE  nIndex0, nIndex1, nIndex2, nIndex3;	// BASE64CODE index
		
		cSrc0 = pszBase64[i * 4 + 0];
		cSrc1 = pszBase64[i * 4 + 1];
		cSrc2 = pszBase64[i * 4 + 2];
		cSrc3 = pszBase64[i * 4 + 3];
		if(!GetBase64CodeIndex(cSrc0, nIndex0) || !GetBase64CodeIndex(cSrc1, nIndex1) ||
			!GetBase64CodeIndex(cSrc2, nIndex2) || !GetBase64CodeIndex(cSrc3, nIndex3))
		{
			return -1;
		}
		
		cDest0 = (nIndex0 << 2) | (nIndex1 >> 4 );
		cDest1 = ((nIndex1 & 0x0F) << 4) | ((nIndex2 & 0x3C) >> 2);
		cDest2 = ((nIndex2 & 0x03) << 6) | nIndex3;
		
		pszDesryptSource[i*3 +0] = cDest0;
		pszDesryptSource[i*3 +1] = cDest1;
		pszDesryptSource[i*3 +2] = cDest2;
		
	}
	
	return 0;
}

// -----------------------------------------------------------//
// Function :   GetBase64CodeIndex
// Param    :   BYTE c
//              BYTE& index
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL GetBase64CodeIndex(BYTE c, BYTE& index)
{
	static BYTE BASE64CODE[] = 
    {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    };
	
	if(c == '=')
	{
		index = 0;

		return TRUE;
	}
	for(BYTE i = 0; i < sizeof(BASE64CODE)/sizeof(char); i++)
	{
		if(BASE64CODE[i] == c)
		{
			index = i;
			return TRUE;
		}
	}

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   GetEncryptBase64
// Param    :   CString strSrc
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetEncryptBase64(CString strSrc)
{
	if(strSrc.IsEmpty())		return _T("");
	
	int len = strSrc.GetLength();
	int nSize = len % 3 == 0 ? len/3 : len/3+1;
    TCHAR* szBuffer = (TCHAR*)malloc(nSize*4+sizeof(TCHAR));
	memset(szBuffer, 0x00, nSize*4);
	
    EncryptBase64(szBuffer, strSrc.GetBuffer(0), len);
	szBuffer[nSize*4] = '\0';
    
    CString str(szBuffer);
	free(szBuffer);
	szBuffer = NULL;
	
    return str;
}

// -----------------------------------------------------------//
// Function :   GetDecryptBase64
// Param    :   CString strBase64
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetDecryptBase64(CString strBase64)
{
	if(strBase64.IsEmpty())		return _T("");
	
	int len = strBase64.GetLength();
	int nSize = len / 4;
    TCHAR* szBuffer = (TCHAR*)malloc(nSize*3+sizeof(TCHAR));
	memset(szBuffer, 0x00, nSize*3);
	
    DWORD dwRet = DecryptBase64(szBuffer, strBase64.GetBuffer(0), len);
	szBuffer[nSize*3] = '\0';
	CString str;
    if(dwRet == 0)
	{
		str = CString(szBuffer);
	}
	else
	{
		str = "";
	}
	free(szBuffer);
	szBuffer = NULL;
	
    return str;
}