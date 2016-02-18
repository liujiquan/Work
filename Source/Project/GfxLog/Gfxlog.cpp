//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Gfxlog.cpp
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>
#include "Gfxlog.h"


char	g_FileName[MAX_PATH*10] = {0};
char	g_szFilePath[MAX_PATH*10] = {0};
FILE	*pFile = NULL;
/************************************************************************/
/* Version 1.0                                                                 */
/************************************************************************/
	void GfxPutLog(const char *format,...)
{
	CRITICAL_SECTION section;
	InitializeCriticalSection(&section);
	EnterCriticalSection(&section);
	//////////////////////////////////////////////
	time_t tNow = time(NULL);
	struct tm *ptmNow = localtime(&tNow);
	sprintf(g_FileName,("%d_%d_%d"), ptmNow->tm_year+1990, ptmNow->tm_mon+1, ptmNow->tm_mday);
	char szBuffer[MAX_PATH] = {0};
	if(_access("C:\\Gfxlog", 3) == -1)	// the dir is not exist and create it; 
	{
		_mkdir("C:\\Gfxlog");	// create dir
	}
	sprintf(szBuffer, "C:\\Gfxlog\\%s.txt", g_FileName);
	memset(g_szFilePath, 0x00 ,MAX_PATH);
	memcpy(g_szFilePath, szBuffer, strlen(szBuffer));

	if(pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
	pFile = fopen(g_szFilePath,"a+");
	if(pFile)
	{
		fseek(pFile, 0L, SEEK_END);		
	
		char szText[MAX_PATH*4] = {0};
		va_list args;
		va_start(args,format);
		::sprintf(szText,("%2d:%2d:%2d->>"),ptmNow->tm_hour,ptmNow->tm_min,ptmNow->tm_sec);
		int len = strlen(szText);
		_vsnprintf(szText + len, MAX_PATH*4-len,format, args);
		va_end(args);
		szText[strlen(szText)] ='\n';

		fwrite(szText, strlen(szText), sizeof(char),pFile);
		
		long fileLen = 0L;
		if(pFile)
		{
			fseek(pFile, 0L, SEEK_END);			
			fileLen= ftell(pFile);		
		}
		fclose(pFile);
		if(fileLen >= 100*1024*1024)		//>100MB
		{
			int offset = fileLen - 100*1024*1024;
			HANDLE hFile = ::CreateFile(g_szFilePath,FILE_GENERIC_READ|FILE_GENERIC_WRITE,
				0,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);				
			if(!hFile)
			{
				fclose(pFile);
				return;
			}
			HANDLE hFileMap = ::CreateFileMapping(hFile,NULL
				,PAGE_READWRITE, 0, 0,NULL);									
			LPVOID lpMap = ::MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,
				0,0,0);															
			DWORD dwFileSize = ::GetFileSize(hFile,NULL) - offset;			
			//	offset +=(int)lpMap;
			INT_PTR ptr = (int)lpMap + offset;
			memcpy(lpMap, (LPVOID)ptr, dwFileSize);								
			//	BOOL bRet = FlushViewOfFile(lpMap, dwFileSize);			
			::UnmapViewOfFile(lpMap);										
			CloseHandle(hFileMap);											
			SetFilePointer(hFile, dwFileSize,NULL,FILE_BEGIN);				
			SetEndOfFile(hFile);	
			CloseHandle(hFile);												
		}
	}
	////////////////////////////////////////
	LeaveCriticalSection(&section);
	DeleteCriticalSection(&section);
}
/************************************************************************/
/* Version 2.0 2014/05/08 10F58                                                                     */
/************************************************************************/
void GetFormatData(char (&szFormatArr)[100][100], char* szSrc, int& nCount);
void sprintf_getdata(char* szDest, char* szFormat, ...);
	void GfxPutLog2(char *format,...)
{
	CRITICAL_SECTION section;
	InitializeCriticalSection(&section);
	EnterCriticalSection(&section);
	//////////////////////////////////////////////
	time_t tNow = time(NULL);
	struct tm *ptmNow = localtime(&tNow);
	sprintf(g_FileName, ("%d_%d_%d"), ptmNow->tm_year+1990, ptmNow->tm_mon+1, ptmNow->tm_mday);
	char szBuffer[MAX_PATH] = {0};
	if(_access("C:\\Gfxlog", 3) == -1)	// the dir is not exist and create it; 
	{
		_mkdir("C:\\Gfxlog");	// create dir
	}
	sprintf(szBuffer, "C:\\Gfxlog\\%s.txt", g_FileName);
	memset(g_szFilePath, 0x00 ,MAX_PATH);
	memcpy(g_szFilePath, szBuffer, strlen(szBuffer));
	
	if(pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
	pFile = fopen(g_szFilePath,"a+");
	if(pFile)
	{
		fseek(pFile, 0L, SEEK_END);		

		char szText[MAX_PATH*4] = {0};
		::sprintf(szText,("%2d:%2d:%2d->>"),ptmNow->tm_hour,ptmNow->tm_min,ptmNow->tm_sec);
		int len = strlen(szText);
		//
		char szTemp[MAX_PATH*2] = {0};
		sprintf_getdata(szTemp, format);
		memcpy(szText + len,szTemp,strlen(szTemp));
		szText[strlen(szText)] ='\n';

		fwrite(szText, strlen(szText), sizeof(char),pFile);

		long fileLen = 0L;
		if(pFile)
		{
			fseek(pFile, 0L, SEEK_END);		
			fileLen= ftell(pFile);		
		}
		fclose(pFile);
		if(fileLen >= 100*1024*1024)		//>100MB
		{
			int offset = fileLen - 100*1024*1024;
			HANDLE hFile = ::CreateFile(g_szFilePath,FILE_GENERIC_READ|FILE_GENERIC_WRITE,
				0,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);				
			if(!hFile)
			{
				fclose(pFile);
				return;
			}
			HANDLE hFileMap = ::CreateFileMapping(hFile,NULL
				,PAGE_READWRITE, 0, 0,NULL);									
			LPVOID lpMap = ::MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,
				0,0,0);															
			DWORD dwFileSize = ::GetFileSize(hFile,NULL) - offset;				
			//	offset +=(int)lpMap;
			INT_PTR ptr = (int)lpMap + offset;
			memcpy(lpMap, (LPVOID)ptr, dwFileSize);								
			//	BOOL bRet = FlushViewOfFile(lpMap, dwFileSize);					
			::UnmapViewOfFile(lpMap);											
			CloseHandle(hFileMap);												
			SetFilePointer(hFile, dwFileSize,NULL,FILE_BEGIN);					
			SetEndOfFile(hFile);	
			CloseHandle(hFile);													
		}
	}
	////////////////////////////////////////
	LeaveCriticalSection(&section);
	DeleteCriticalSection(&section);
}
/************************************************************************/
/* Version 3.0   2014/05/08 11:21                                                                      */
/************************************************************************/
	void GfxPutLog3(char *newFileName,char *format,...)
{
	CRITICAL_SECTION section;
	InitializeCriticalSection(&section);
	EnterCriticalSection(&section);
	//////////////////////////////////////////////
	time_t tNow = time(NULL);
	struct tm *ptmNow = localtime(&tNow);
	sprintf(g_FileName, ("%d_%d_%d_%s"), ptmNow->tm_year+1990, ptmNow->tm_mon+1, ptmNow->tm_mday,newFileName);
	char szBuffer[MAX_PATH] = {0};
	if(_access("C:\\Gfxlog", 3) == -1)	// the dir is not exist and create it; 
	{
		_mkdir("C:\\Gfxlog");	// create dir
	}
	sprintf(szBuffer, "C:\\Gfxlog\\%s.txt", g_FileName);
	memset(g_szFilePath, 0x00 ,MAX_PATH);
	memcpy(g_szFilePath, szBuffer, strlen(szBuffer));

	if(pFile)
	{
		fclose(pFile);
		pFile = NULL;
	}
	pFile = fopen(g_szFilePath,"a+");
	if(pFile)
	{
		fseek(pFile, 0L, SEEK_END);			

		char szText[MAX_PATH*200+1] = {0};
		::sprintf(szText,("%2d:%2d:%2d->>"),ptmNow->tm_hour,ptmNow->tm_min,ptmNow->tm_sec);
		int nOldlen = strlen(szText);
		if(nOldlen >= MAX_PATH*200)
		{
			nOldlen = MAX_PATH*200;
		}
		char szDest[MAX_PATH*200] = {0};
		int nManLen = 0;
		va_list va;
		va_start(va, format);
		char data[100][100];
		int nCount;
		memset(data, 0x00, 100*100);
		GetFormatData(data, format, nCount);
		for(int i = 0; i < nCount; i++)
		{
			int nDatalen = strlen(data[i]);
			if(nDatalen  <= 0)	continue;
			if(nDatalen >= MAX_PATH*200 - nManLen)
			{
				nDatalen = MAX_PATH*200 - nManLen;
			}
			if(i%2 == 1)
			{
				if(memcmp(data[i], "%d", sizeof("%d")) == 0)		//%d
				{
					int n = va_arg(va, int);
					char nData[10] = {0};
					sprintf(nData,"%d",n);
					memcpy(szDest+nManLen, (char*)nData, strlen(nData));
					nManLen+=strlen(nData);
				}
				else if(memcmp(data[i], "%ld", sizeof("%ld")) == 0)//%ld
				{
					long n = va_arg(va, long);
					char nData[10] = {0};
					sprintf(nData,"%ld",n);
					memcpy(szDest+nManLen, (char*)nData, strlen(nData));
					nManLen+=strlen(nData);
				}
				else if(memcmp(data[i], "%f", sizeof("%f")) == 0)  //%f
				{
					float n = (float)va_arg(va, double);//float/long/int error
					char nData[10] = {0};
					sprintf(nData,"%.2f",n);
					memcpy(szDest+nManLen, (char*)nData, strlen(nData));
					nManLen+=strlen(nData);
				}
				else if(memcmp(data[i], "%s", sizeof("%s")) == 0)  //%s
				{
					char* pData = va_arg(va, char*);
					int nstrLen = strlen(pData);
					if(nstrLen > MAX_PATH*200 - nManLen)
					{
						nstrLen = MAX_PATH*200 - nManLen;
					}
					memcpy(szDest+nManLen, (char*)pData, nstrLen);
					nManLen += nstrLen;
				}
				else if(memcmp(data[i], "%c", sizeof("%c")) == 0)  //%c
				{
					char c = va_arg(va, char);
					memcpy(szDest+nManLen, (char*)&c, sizeof(c));
					nManLen+=sizeof(c);
				}
			}
			else
			{
				memcpy(szDest+nManLen, data[i], nDatalen);
				nManLen += nDatalen;
			}
		}
		va_end(va);
		int nDestLen = strlen(szDest);
		memcpy(szText + nOldlen,szDest, nDestLen > MAX_PATH*200 - nOldlen ? MAX_PATH*200 - nOldlen : nDestLen);
		szText[strlen(szText)] ='\n';

		fwrite(szText, strlen(szText), sizeof(char),pFile);

		long fileLen = 0L;
		if(pFile)
		{
			fseek(pFile, 0L, SEEK_END);		
			fileLen= ftell(pFile);		
		}
		fclose(pFile);

		// The File is too large to delete some content.
		if(fileLen >= 100*1024*1024)		// > 100MB
		{
			int offset = fileLen - 100*1024*1024;
			HANDLE hFile = ::CreateFile(g_szFilePath,FILE_GENERIC_READ|FILE_GENERIC_WRITE,
				0,NULL,OPEN_EXISTING ,FILE_ATTRIBUTE_NORMAL,NULL);			
			if(!hFile)
			{
				fclose(pFile);
				return;
			}
			HANDLE hFileMap = ::CreateFileMapping(hFile,NULL
				,PAGE_READWRITE, 0, 0,NULL);								
			LPVOID lpMap = ::MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,
				0,0,0);														
			DWORD dwFileSize = ::GetFileSize(hFile,NULL) - offset;			
			//	offset +=(int)lpMap;
			INT_PTR ptr = (int)lpMap + offset;
			memcpy(lpMap, (LPVOID)ptr, dwFileSize);							
			//	BOOL bRet = FlushViewOfFile(lpMap, dwFileSize);					
			::UnmapViewOfFile(lpMap);											
			CloseHandle(hFileMap);												
			SetFilePointer(hFile, dwFileSize,NULL,FILE_BEGIN);				
			SetEndOfFile(hFile);	
			CloseHandle(hFile);												
		}
	}
	////////////////////////////////////////
	LeaveCriticalSection(&section);
	DeleteCriticalSection(&section);
}

// Decode String
// "ID:%d,Name:%s,Age:%ld,Col:%f .....%c",12,"liujiquan",201402,200.2,'A' 
// "ID:12,Name:liujiquan,Age:201402,Col:200.2 .....''A",12,"liujiquan",201402,200.2,'A'
void sprintf_getdata(char* szDest, char* szFormat, ...)
{
	if(szDest == NULL || szFormat == NULL)
	{
		return;
	}

	int nManLen = 0;
	va_list va;
	va_start(va, szFormat);
	char data[100][100];
	int nCount;
	memset(data, 0x00, 100*100);
	GetFormatData(data, szFormat, nCount);
	for(int i = 0; i < nCount; i++)
	{
		int len = strlen(data[i]);
		if(i%2 == 1)
		{
			if(memcmp(data[i], "%d", sizeof("%d")) == 0)		//%d
			{
				int n = va_arg(va, int);
				char nData[10] = {0};
				sprintf(nData,"%d",n);
				memcpy(szDest+nManLen, (char*)nData, strlen(nData));
				nManLen+=strlen(nData);
			}
			else if(memcmp(data[i], "%ld", sizeof("%ld")) == 0)//%ld
			{
				long n = va_arg(va, long);
				char nData[10] = {0};
				sprintf(nData,"%ld",n);
				memcpy(szDest+nManLen, (char*)nData, strlen(nData));
				nManLen+=strlen(nData);
			}
			else if(memcmp(data[i], "%f", sizeof("%f")) == 0)  //%f
			{
				float n = (float)va_arg(va, double);// cant use
				char nData[10] = {0};
				sprintf(nData,"%.2f",n);
				memcpy(szDest+nManLen, (char*)nData, strlen(nData));
				nManLen+=strlen(nData);
			}
			else if(memcmp(data[i], "%s", sizeof("%s")) == 0)  //%s
			{
				char* pData = va_arg(va, char*);
				memcpy(szDest+nManLen, (char*)pData, strlen(pData));
				nManLen+=strlen(pData);
			}
			else if(memcmp(data[i], "%c", sizeof("%c")) == 0)  //%c
			{
				char c = va_arg(va, char);
				memcpy(szDest+nManLen, (char*)&c, sizeof(c));
				nManLen+=sizeof(c);
			}
		}
		else
		{
			memcpy(szDest+nManLen, data[i], len);
			nManLen += len;
		}
	}
	va_end(va);
}

// Split String -> %d","%s","%ld","%f", "%c
#define FORMAT_SIZE 5
char FROMAT[5][4] = {"%d","%s","%ld","%f", "%c"};
void GetFormatData(char (&szFormatArr)[100][100],char* szFromat, int& nCount)
{
	nCount = 0;
	if(szFormatArr == NULL || szFromat == NULL)
		return;

	char* p1 = szFromat;
	char* p2 = NULL;
	while(true)
	{
		if(p1 == NULL)		break;
		int i = 0;
		for(i = 0; i < 5; i++)
		{
			p2 = strstr(p1, FROMAT[i]);
			if(p2)			break;
		}
		if(p2)
		{
			memcpy(szFormatArr[nCount++],p1, p2-p1);				//Name:
			memcpy(szFormatArr[nCount++],p2, strlen(FROMAT[i]));	//%d

			p1 = p2 + strlen(FROMAT[i]);
			continue;
		}
		memcpy(szFormatArr[nCount++], p1, strlen(p1));
		break;
	}
}