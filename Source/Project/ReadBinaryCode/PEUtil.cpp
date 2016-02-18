//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PEUtil.cpp
//* Author   :   liujiquan
//* DateTime :   10/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "PEUtil.h"
#include "ntdll_interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// -----------------------------------------------------------//
// Function :   ImproveTokenPrivilege
// Return   :   BOOL 
// Comment  :   
// -----------------------------------------------------------//
BOOL ImproveTokenPrivilege() 
{
    HANDLE hToken = NULL;
    LUID luid;
    TOKEN_PRIVILEGES tp;
	
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        // LookupPrivilegeValue
        if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
        {
            tp.PrivilegeCount = 1;
            tp.Privileges->Luid = luid;
            tp.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
			
            // AdjustTokenPrivileges
            if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
            {
                DWORD dwError = GetLastError();
                if(dwError == 0)
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

// -----------------------------------------------------------//
// Function :   FlushProcessInfo
// Param    :   CArray<PROCESSENTRY32_
//              PROCESSENTRY32_>& processList
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList)
{
    PROCESSENTRY32_ entry;
    memset(&entry, 0x00, sizeof(PROCESSENTRY32_));
    entry.dwSize = sizeof(PROCESSENTRY32_);
    BOOL bRet = FALSE;
	
    // 
    HANDLE hSnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hSnapShot == NULL)
    {
        return;
    }
    bRet = ::Process32First(hSnapShot, (PROCESSENTRY32*)&entry);
    while(bRet)
    {
        // AddNew
        processList.Add(entry);
        // MoveNext
        bRet = ::Process32Next(hSnapShot, (PROCESSENTRY32*)&entry);
    }
}

// -----------------------------------------------------------//
// Function :   ToChar
// Param    :   BYTE c
// Return   :   TCHAR
// Comment  :   
// -----------------------------------------------------------//
TCHAR ToChar(BYTE c)
{
	if(c >= 0 && c <= 32)
	{
		return '.';
	}
	else if(c>=127 && c <=160)
	{
		return '.';
	}
	return c;
}

// -----------------------------------------------------------//
// Function :   CreateNewFile
// Param    :   TCHAR* szBuffer
//              DWORD dwFileSize
//              CString strFileName
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CreateNewFile(TCHAR* szBuffer, DWORD dwFileSize, CString& strFileName)
{
	if(szBuffer == NULL || dwFileSize == 0 || strFileName.IsEmpty())
	{
		return FALSE;
	}
	
	CString newFileName(strFileName);
	int index = newFileName.ReverseFind('\\');
	if(index == -1)
	{
		index = newFileName.ReverseFind('/');
	}
	if(index != -1)
	{	
		CString strFilePath = newFileName.Left(index+1);
		newFileName = newFileName.Right(newFileName.GetLength()-index-1);
		newFileName = strFilePath +  GetNewFileName(newFileName, strFilePath, 0);
		DeleteFile(newFileName);
		
		FILE* pFile;
		pFile = fopen(newFileName.GetBuffer(0), "wb");
		if(pFile)
		{
			fwrite(szBuffer, 1, dwFileSize, pFile);
			fclose(pFile);
		}
		
		strFileName = newFileName;
		return TRUE; 
	}
	
	return FALSE;
}

// -----------------------------------------------------------//
// Function :   GetNewFileName
// Param    :   CString strFileName
//              CString strDownLoadFilePath
//              UINT nCount
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetNewFileName(CString strFileName, CString strDownLoadFilePath, UINT nCount)
{
	if(strDownLoadFilePath.IsEmpty() || strFileName.IsEmpty())	return _T("");
	
	CString strFileNameTemp = strFileName;
	if(nCount > 0)
	{
		strFileNameTemp.Format(_T("(%d)%s"), nCount, strFileName);						// FileName
	}
	CString strFilePath = strDownLoadFilePath + strFileNameTemp;						// FilePath
	if(FileExists(strFilePath.GetBuffer(0)))
	{
		nCount++;
		return GetNewFileName(strFileName, strDownLoadFilePath, nCount);
	}
	
	return strFileNameTemp;
}

// -----------------------------------------------------------//
// Function :   FileExists
// Param    :   LPCTSTR szFilePath
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#include <io.h>
BOOL FileExists(LPCTSTR szFilePath)
{
	if(_access(szFilePath, 0) == -1)
	{
		return FALSE;	
	}
	return TRUE;
}


// -----------------------------------------------------------//
// Function :   GetExeInfo
// Param    :   CString strFilePath
//              DWORD& dwImageBase
//              DWORD& dwAddressOfEntryPoint
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL GetExeInfo(CString strFilePath, PExeMemInfo pExeMemInfo)
{
	FILE *pFile = fopen(strFilePath, "rb");
	if(pFile == NULL)		return FALSE;
	DWORD dwLength;
	fseek(pFile, 0, SEEK_SET);
	fseek(pFile, 0, SEEK_END);
	dwLength = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	TCHAR * szBuffer = (TCHAR*)malloc(dwLength* sizeof(TCHAR));	
	memset(szBuffer, 0x00, dwLength);
	fread(szBuffer,  dwLength,sizeof(TCHAR), pFile);
	// Get ImageBase AddressOfEntryPoint
	DWORD PEVersion = GetPEVersion(szBuffer);
	if(PEVersion == NO_PE)
	{
		free(szBuffer);
		fclose(pFile);
		return FALSE;
	}
	// Exe Info
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
	
	memcpy(&dosHeader, szBuffer, sizeof(dosHeader));
	memset(pExeMemInfo, 0x00, sizeof(ExeMemInfo));
	if(PEVersion == X64_PE)
	{
		memcpy(&ntHeader64, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
		pExeMemInfo->dwPEVersion = X64_PE;
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
//		pExeMemInfo->dwImageBase = ntHeader64.OptionalHeader.ImageBase;
        pExeMemInfo->dwImageBase64 = ntHeader64.OptionalHeader.ImageBase;
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End
		pExeMemInfo->dwAddressOfEntryPoint = ntHeader64.OptionalHeader.AddressOfEntryPoint;
		pExeMemInfo->dwSizeofImage = ntHeader64.OptionalHeader.SizeOfImage;
		pExeMemInfo->dwBaseOfCode = ntHeader64.OptionalHeader.BaseOfCode;
		pExeMemInfo->dwSizeOfCode = ntHeader64.OptionalHeader.SizeOfCode;
	}
	else
	{
		memcpy(&ntHeader, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		pExeMemInfo->dwPEVersion = X32_PE;
		pExeMemInfo->dwImageBase = ntHeader.OptionalHeader.ImageBase;
		pExeMemInfo->dwAddressOfEntryPoint = ntHeader.OptionalHeader.AddressOfEntryPoint;
		pExeMemInfo->dwSizeofImage = ntHeader.OptionalHeader.SizeOfImage;
		pExeMemInfo->dwBaseOfCode = ntHeader.OptionalHeader.BaseOfCode;
		pExeMemInfo->dwSizeOfCode = ntHeader.OptionalHeader.SizeOfCode;
	}

	free(szBuffer);
	fclose(pFile);

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   GetPEVersion
// Return   :   void
// Comment  :   GetPEVersion
// -----------------------------------------------------------//

DWORD GetPEVersion(TCHAR* szBuffer)
{
	if(szBuffer == NULL)	return 0;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	memcpy(&dosHeader, szBuffer, sizeof(dosHeader));
	if(dosHeader.e_magic != 0x5A4D)
	{
		return NO_PE;
	}
	memcpy(&ntHeader, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	if(ntHeader.FileHeader.Machine == X32_PE)
	{
		return X32_PE;
	}
	else if(ntHeader.FileHeader.Machine == X64_PE)
	{
		return X64_PE;
	}

	return 0;
}

// -----------------------------------------------------------//
// Function :   GetImageBase
// Param    :   TCHAR* szBuffer
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD GetImageBase(TCHAR* szBuffer)
{
	if(szBuffer == NULL)	return 0;
	
	// Exe Info
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
	
	DWORD PEVersion = GetPEVersion(szBuffer);
	if(PEVersion == NO_PE)	return 0;

	memcpy(&dosHeader, szBuffer, sizeof(dosHeader));
	// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(PEVersion == X64_PE)
	{
		memcpy(&ntHeader64, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
		return ntHeader64.OptionalHeader.ImageBase;
	}
	else
	{
		memcpy(&ntHeader, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		return ntHeader.OptionalHeader.ImageBase;
	}
	
	return 0;
}

#include "Psapi.h"
// -----------------------------------------------------------//
// Function :   ReadProcessAllMemory
// Param    :   HANDLE hProcess
//              DWORD dwImageBase
//              DWORD dwAddressOfEntryPoint
//              DWORD& dwFileSize
// Return   :   TCHAR*
// Comment  :   
// -----------------------------------------------------------//
TCHAR* ReadProcessAllMemory(HANDLE hProcess, DWORD dwImageBase, DWORD dwAddressOfEntryPoint, DWORD dwSizeOfImage)
{
	if(hProcess == NULL)		return NULL;
	
//	HMODULE module = LoadLibrary("psapi.dll");
//	FARPROC pGetProcessMemoryInfo = (FARPROC)GetProcAddress(module, "GetProcessMemoryInfo");
//	PROCESS_MEMORY_COUNTERS mem;
//	LPVOID hMem = &mem;
//	DWORD dwLen = sizeof(PROCESS_MEMORY_COUNTERS);
//	_asm
//	{
//		push dwLen
//		push hMem
//		push hProcess
//		call pGetProcessMemoryInfo
//	}
//	FreeLibrary(module);
//	
//	DWORD dwMemSize = mem.WorkingSetSize;	// memory 9.264K
	DWORD baseAddr = dwImageBase;
	TCHAR* szMemBuffer = (TCHAR*)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, dwSizeOfImage);
	memset(szMemBuffer, 0x00, dwSizeOfImage);
	
//	DWORD dwOldProtected;
//	if(VirtualProtectEx(hProcess, (LPVOID)baseAddr, dwSizeOfImage, PAGE_READONLY, &dwOldProtected))
//	{
		BOOL bRet = ::ReadProcessMemory(hProcess, (LPCVOID)baseAddr, szMemBuffer, dwSizeOfImage, NULL);
//		VirtualProtectEx(hProcess, (LPVOID)baseAddr, dwSizeOfImage, dwOldProtected, NULL);
//	}

	return szMemBuffer;
}

//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
extern ISWOW64PROCESS pIsWow64Process;
extern NTQUERYINFORMATIONPROCESS pNtQueryInformationProcess;
#if !defined(_WIN64)
extern NTWOW64QUERYINFORMATIONPROCESS64 pNtWow64QueryInformationProcess64;
extern NTWOW64READVIRTUALMEMORY64 pNtWow64ReadVirtualMemory64 ;
#endif

// -----------------------------------------------------------//
// Function :   ReadProcessAllMemory64
// Param    :   HANDLE hProcess
//              ULONGLONG dwImageBase
//              DWORD dwAddressOfEntryPoint
//              DWORD dwSizeOfImage
// Return   :   TCHAR*
// Comment  :   64 bits
// -----------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////
// Error dwSizeofImage
TCHAR* ReadProcessAllMemory64(HANDLE hProcess, ULONGLONG dwImageBase, DWORD dwAddressOfEntryPoint, DWORD dwSizeOfImage)
{
    TCHAR* szMemBuffer = (TCHAR*)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, dwSizeOfImage);
    memset(szMemBuffer, 0x00, dwSizeOfImage);

    SIZE_T64 realsize64;
    NTSTATUS err = pNtWow64ReadVirtualMemory64(hProcess, (PVOID64_)dwImageBase, szMemBuffer, dwSizeOfImage, &realsize64);
    if(err == ERROR_SUCCESS)
    {
        return szMemBuffer;;
    }
    
    GlobalFree(szMemBuffer);
    szMemBuffer = NULL;
    return NULL;
}

// -----------------------------------------------------------//
// Function :   ReadProcessAllMemory32_64
// Param    :   HANDLE hProcess
//              DWORD dwSizeOfImage
//              BOOL boolWow64
// Return   :   TCHAR*
// Comment  :   32Bits / 64Bits
// -----------------------------------------------------------//
TCHAR* ReadProcessAllMemory32_64(HANDLE hProcess, DWORD dwSizeOfImage, BOOL boolWow64)
{   
    if(hProcess == NULL)		return NULL;

    if(LoadDlls() == FALSE)     return NULL;
    //1
    BOOL bWow64 = FALSE, bWow64_ = FALSE;
    // 32bit exe run at 64bit windows ->TRUE
    // 32bit exe run at 32bit windows ->FALSE
    // 64bit exe run at 64bit windows ->TRUE
    // 64bit exe run at 32bit windows ->FALSE
    bWow64 = pIsWow64Process(hProcess, &bWow64_);  
    //2
    if(boolWow64)
    {
        DWORD dwRet;
        PROCESS_BASIC_INFORMATION64 info64;
        SIZE_T64 realsize64;

        dwRet = pNtWow64QueryInformationProcess64(hProcess, ProcessBasicInformation, (PVOID)&info64, sizeof(PROCESS_BASIC_INFORMATION64), &realsize64);
        if(dwRet != ERROR_SUCCESS)
        {
            return NULL;
        }
        PEB64 peb64;
        NTSTATUS err;
        // Get PE Block
        err = pNtWow64ReadVirtualMemory64(hProcess, (PVOID64_)info64.PebBaseAddress, &peb64, sizeof(PEB64), &realsize64);
        if(err == ERROR_SUCCESS)
        {
            TCHAR* szMemBuffer = (TCHAR*)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, dwSizeOfImage);
            memset(szMemBuffer, 0x00, dwSizeOfImage);

            PVOID64_ value = (PVOID64_)peb64.ImageBaseAddress;
            err = pNtWow64ReadVirtualMemory64(hProcess, (PVOID64_)peb64.ImageBaseAddress, szMemBuffer, dwSizeOfImage, &realsize64);
            if(err == ERROR_SUCCESS)
            {
                return szMemBuffer;
            }
        }
    }
    else
    {
        DWORD dwRet;
        PROCESS_BASIC_INFORMATION info;
        ULONG realsize;

        dwRet = pNtQueryInformationProcess(hProcess, ProcessBasicInformation, (PVOID)&info, sizeof(PROCESS_BASIC_INFORMATION), &realsize);
        if(dwRet != ERROR_SUCCESS)
        {
            return NULL;
        }

        PEB peb;
        // Get PE Block
        BOOL bRet = ReadProcessMemory(hProcess, (PVOID)info.PebBaseAddress, &peb, sizeof(PEB), &realsize);
        if(bRet == TRUE)
        {
            TCHAR* szMemBuffer = (TCHAR*)GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, dwSizeOfImage);
            memset(szMemBuffer, 0x00, dwSizeOfImage);

            bRet = ReadProcessMemory(hProcess, (PVOID)peb.ImageBaseAddress, szMemBuffer, dwSizeOfImage, &realsize);
            if(bRet)
            {
                return szMemBuffer;
            }
        }
    }

    return NULL;
}
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End

//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
void ShowModule(DWORD PID,char *strExeName, char* strExePath)
{   
    if(strstr(strExeName, "MineSweeper.exe"))
    {
        int a = 0;
    }
    HANDLE hSnapShot;
    BOOL fOk;
    hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,PID);      // read X86[32bits]
    if(hSnapShot == INVALID_HANDLE_VALUE)
    {
        DWORD dwError = GetLastError();
        if(dwError == 299)  // X64[64bits]
        {
            return;
        }
    }
    MODULEENTRY32 me={sizeof(me)};
    for(fOk=Module32First(hSnapShot,&me);fOk;fOk=Module32Next(hSnapShot,&me))
    {
        if (strstr(me.szExePath,strExeName) != NULL)
        {
            memcpy(strExePath, me.szExePath, strlen( me.szExePath));
            TRACE1("%s\n",me.szExePath);
            return;
        }
    }
}

// -----------------------------------------------------------//
// Function :   GetDeviceString
// Param    :   CStringArray& strDeviceArr
// Return   :   void
// Comment  :   GetDeviceString
// -----------------------------------------------------------//
void GetDeviceString(CStringArray& strDeviceArr)
{
    TCHAR szBuffer[MAX_PATH] = {0};
    DWORD dwLen = GetLogicalDriveStrings(0, NULL);
    if(dwLen)
    {
        char* DStr = new char[dwLen];
        DWORD dwRet = GetLogicalDriveStrings(dwLen, (LPTSTR)DStr);
        for(int i = 0; i < dwLen/4; i++)
        {
            char* pszDevice = DStr + i * 4;
            if(GetDriveType(pszDevice) == DRIVE_FIXED)
            {
                strDeviceArr.Add(CString(pszDevice)); 
            }
        }
        delete []DStr;
    }
}

//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End