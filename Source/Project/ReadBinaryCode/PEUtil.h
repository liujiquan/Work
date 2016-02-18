//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PEUtil.h
//* Author   :   liujiquan
//* DateTime :   10/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __PEUTIL_H_2459134951B94A1895E650CFD52F4215__
#define __PEUTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <afxtempl.h>
#include <TLHELP32.H>
#include "Psapi.h"
/************************************************************************/
/* Macro                                                                */
/************************************************************************/
#define LINE_SZIE			8
#define NO_PE				0
#define X64_PE				0x8664							// 62bits PE
#define X32_PE				0x014c							// 32bits PE
#define NDISASM_EXE_NAME	"_ndisasm.exe"
#define BINARY_FILE_NAME	_T("7A43A012-B913-435d-A6D7-4281190EBB37.bin")
#define ASSEMBLY_FILENAME	_T("7A43A012-B913-435d-A6D7-4281190EBB37.txt")
/************************************************************************/
/* Member                                                               */
/************************************************************************/
extern CStringArray g_DeviceArr;
/************************************************************************/
/* Struct                                                               */
/************************************************************************/
//DWORDDWORD
typedef struct tag_DWORDDWORD
{   
    union
    {
        struct 
        {
            DWORD dwValue1;
            DWORD dwValue2;
        }dwValue;
        ULONGLONG llValue;
    };
}DWORDDWORD, *PDWORDDWORD;
//1) ExeMemInfo struct
typedef struct tag_ExeMemInfo
{
	DWORD dwPEVersion;				// PEVersion
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
	DWORD dwImageBase;				// ImageBase
    ULONGLONG  dwImageBase64;       // SizeofImage [X64]
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End
	DWORD dwAddressOfEntryPoint;	// AddressOfEntryPoint
	DWORD dwSizeofImage;			// SizeofImage
	DWORD dwBaseOfCode;				// BaseOfCode
	DWORD dwSizeOfCode;				// SizeOfCode
}ExeMemInfo, *PExeMemInfo;
//2) PROCESSENTRY32_ struct
typedef struct tagPROCESSENTRY32_
{
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;          // this process
    DWORD	th32DefaultHeapID;
    DWORD   th32ModuleID;           // associated exe
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;    // this process's parent process
    LONG    pcPriClassBase;         // Base priority of process's threads
    DWORD   dwFlags;
    CHAR    szExeFile[MAX_PATH];    // Name
	TCHAR	szExePath[MAX_PATH];	// Path
public:
    tagPROCESSENTRY32_& operator=(tagPROCESSENTRY32_& entry)
    {
        this->dwSize = entry.dwSize;
        this->cntUsage = entry.cntUsage;
        this->th32ProcessID = entry.th32ProcessID;
        this->th32DefaultHeapID = entry.th32DefaultHeapID;
        this->th32ModuleID = entry.th32ModuleID;
        this->cntThreads = entry.cntThreads;
        this->th32ParentProcessID = entry.th32ParentProcessID;
        this->pcPriClassBase = entry.pcPriClassBase;
        this->dwFlags = entry.dwFlags;
        this->pcPriClassBase = entry.pcPriClassBase;
        memcpy(this->szExeFile, entry.szExeFile, MAX_PATH);
		memset(this->szExePath, 0x00, MAX_PATH);
		
		if(this->th32ProcessID)
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->th32ProcessID);
			if(hProcess)
			{
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
                TCHAR   szExePathTemp[MAX_PATH] = {0};
                TCHAR*  pszExePath = szExePathTemp;
                DWORD   dwSize = MAX_PATH;
                HMODULE module = LoadLibrary("psapi.dll");
                FARPROC pGetProcessImageFileName = NULL;
#ifdef UNICODE  
                pGetProcessImageFileName = (FARPROC)GetProcAddress(module, "GetProcessImageFileNameW");
#else           
                pGetProcessImageFileName = (FARPROC)GetProcAddress(module, "GetProcessImageFileNameA");  
#endif // !UNICODE
                _asm
                {
                    push dwSize
                    push pszExePath
                    push hProcess
                    call pGetProcessImageFileName
                }
                FreeLibrary(module);
//              GetProcessImageFileName(hProcess, pszExePath, MAX_PATH);
                CString strExePath(pszExePath);
                if(strExePath.GetLength() > 24)
                {
                    char szDeviceName[24] = {0};
                    DWORD dwIndex = 0;

                    memcpy(szDeviceName, strExePath.GetBuffer(0), 23);
                    dwIndex = szDeviceName[22] - '1';
                    if(dwIndex >= 0 && g_DeviceArr.GetSize() >= dwIndex + 1)
                    {
                        strExePath = g_DeviceArr.GetAt(dwIndex) + strExePath.Right(strExePath.GetLength() - 23 - 1);
                        
                        memcpy(this->szExePath, strExePath.GetBuffer(0), strExePath.GetLength());
                    }
                }
                
//              ShowModule(this->th32ProcessID, this->szExeFile, this->szExePath);
//				GetModuleFileNameEx(hProcess, (HMODULE)(this->th32ModuleID), this->szExePath, MAX_PATH);
/*				HMODULE module = LoadLibrary("psapi.dll");
				FARPROC pGetModuleFileNameExA = (FARPROC)GetProcAddress(module, "GetModuleFileNameExA");
				DWORD dwSize = MAX_PATH;
				TCHAR* szPath = this->szExePath;
				HMODULE hmodule = (HMODULE)(this->th32ModuleID);
				_asm
				{
					push dwSize
					push szPath
					push hmodule
					push hProcess
					call pGetModuleFileNameExA
				}
				FreeLibrary(module);
*/
                CloseHandle(hProcess);
			}
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End
		}
		
        return *this;
    }
} PROCESSENTRY32_;
/************************************************************************/
/* Function                                                             */
/************************************************************************/
CString GetNewFileName(CString strFileName, CString strDownLoadFilePath, UINT nCount);	// GetNewFileName
BOOL FileExists(LPCTSTR szFilePath);													// FileExists
BOOL GetExeInfo(CString strFilePath, PExeMemInfo pExeMemInfo);							// GetExeInfo
DWORD GetPEVersion(TCHAR* szBuffer);													// GetPEVersion
DWORD GetImageBase(TCHAR* szBuffer);													// GetImageBase
TCHAR* ReadProcessAllMemory(HANDLE hProcess, DWORD dwImageBase, DWORD dwAddressOfEntryPoint, DWORD dwSizeOfImage);	// ReadProcessAllMemory
void FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList);			// FlushProcessInfo
BOOL ImproveTokenPrivilege();															// ImproveTokenPrivilege
TCHAR ToChar(BYTE c);
BOOL CreateNewFile(TCHAR* szBuffer, DWORD dwFileSize, CString& strFileName);				// CreateNewFile
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
void ShowModule(DWORD PID,char *strExeName, char* strExePath);
void GetDeviceString(CStringArray& strDeviceArr);
TCHAR* ReadProcessAllMemory64(HANDLE hProcess, ULONGLONG dwImageBase, DWORD dwAddressOfEntryPoint, DWORD dwSizeOfImage);	// ReadProcessAllMemory64
TCHAR* ReadProcessAllMemory32_64(HANDLE hProcess, DWORD dwSizeOfImage, BOOL boolWow64);                                        // X64_PE/X32_PE
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End
#endif//__PEUTIL_H_2459134951B94A1895E650CFD52F4215__
