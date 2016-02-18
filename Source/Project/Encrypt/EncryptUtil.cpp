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


// RSHash
long GeneralHashFunctionLibrary::RSHash(CString  str)
{
	int b=378551;
	int a=63689;
	long hash=0;
	for(int i=0;i<str.GetLength();i++)
	{
		hash=hash*a+str.GetAt(i);
		a=a*b;
	}
	return hash;
}
/*JSHash*/
long GeneralHashFunctionLibrary::JSHash(CString  str)
{
	long hash=1315423911;
	for(int i=0;i<str.GetLength();i++)
	hash^=((hash<<5)+str.GetAt(i)+(hash>>2));
	return hash;
}
/*PJWHash*/
long GeneralHashFunctionLibrary::PJWHash(CString  str)
{
	long BitsInUnsignedint =(long )(4*8);
	long ThreeQuarters=(long )((BitsInUnsignedint *3)/4);
	long OneEighth=(long )(BitsInUnsignedint /8);
	long HighBits=(long )(0xFFFFFFFF)<<(BitsInUnsignedint -OneEighth);
	long hash=0;long test=0;
	for(int i=0;i<str.GetLength();i++)
	{
		hash=(hash<<OneEighth)+str.GetAt(i);
		if((test=hash&HighBits)!=0)
		hash=((hash^(test>>ThreeQuarters))&(~HighBits));
	}
	return hash;
}
/*ELFHash*/
long GeneralHashFunctionLibrary::ELFHash(CString  str)
{
	long hash=0;
	long x=0;
	for(int i=0;i<str.GetLength();i++)
	{
		hash=(hash<<4)+str.GetAt(i);
		if((x=hash&0xF0000000L)!=0)
		hash^=(x>>24);
		hash&=~x;
	}
	return hash;
}
/*BKDRHash*/
long GeneralHashFunctionLibrary::BKDRHash(CString  str)
{
	long seed=131;//31131131313131131313etc..
	long hash=0;
	for(int i=0;i<str.GetLength();i++)
		hash=(hash*seed)+str.GetAt(i);
	return hash;
}
/*SDBMHash*/
long GeneralHashFunctionLibrary::SDBMHash(CString  str)
{
	long hash=0;
	for(int i=0;i<str.GetLength();i++)
		hash=str.GetAt(i)+(hash<<6)+(hash<<16)-hash;
	return hash;
}
/*DJBHash*/
long GeneralHashFunctionLibrary::DJBHash(CString  str)
{
	long hash=5381;
	for(int i=0;i<str.GetLength();i++)
		hash=((hash<<5)+hash)+str.GetAt(i);
	return hash;
}
/*DEKHash*/
long GeneralHashFunctionLibrary::DEKHash(CString  str)
{
	long hash=str.GetLength();
	for(int i=0;i<str.GetLength();i++)
		hash=((hash<<5)^(hash>>27))^str.GetAt(i);
	return hash;
}
/*BPHash*/
long GeneralHashFunctionLibrary::BPHash(CString  str)
{
	long hash=0;
	for(int i=0;i<str.GetLength();i++)
		hash=hash<<7^str.GetAt(i);
	return hash;
}
/*FNVHash*/
long GeneralHashFunctionLibrary::FNVHash(CString  str)
{
	long fnv_prime=0x811C9DC5;
	long hash=0;
	for(int i=0;i<str.GetLength();i++)
		hash*=fnv_prime;hash^=str.GetAt(i);
	return hash;
}
/*APHash*/
long GeneralHashFunctionLibrary::APHash(CString  str)
{
	long hash=0xAAAAAAAA;
	for(int i=0;i<str.GetLength();i++)
	{
		if((i&1)==0)
			hash^=((hash<<7)^str.GetAt(i)^(hash>>3));
		else
			hash^=(~((hash<<11)^str.GetAt(i)^(hash>>5)));
	}
	return hash;
}

// HashCode
long GeneralHashFunctionLibrary::HashCode(CString  str, int nIndex/* = 0*/)
{
	switch(nIndex)
	{
		case HASHCODE_RSHash:		return RSHash(str);
		case HASHCODE_JSHash:		return JSHash(str);
		case HASHCODE_PJWHash:		return PJWHash(str);
		case HASHCODE_ELFHash:		return ELFHash(str);
		case HASHCODE_BKDRHash:		return BKDRHash(str);
		case HASHCODE_SDBMHash:		return SDBMHash(str);
		case HASHCODE_DJBHash:		return DJBHash(str);
		case HASHCODE_DEKHash:		return DEKHash(str);
		case HASHCODE_BPHash:		return BPHash(str);
		case HASHCODE_FNVHash:		return FNVHash(str);
		case HASHCODE_APHash:		return APHash(str);
	}
	return 0;
}