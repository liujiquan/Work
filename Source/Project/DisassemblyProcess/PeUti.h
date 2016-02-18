//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PeUti.h
//* Author   :   liujiquan
//* DateTime :   10/30/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __PEUTI_H_2459134951B94A1895E650CFD52F4215__
#define __PEUTI_H_2459134951B94A1895E650CFD52F4215__
#pragma once
//////////////////////////////////////////////////////////////////////////
//Include
#include <afxtempl.h>
#include <TLHELP32.H>
#include "Psapi.h"
#include "ntdll.h"
#include <list>
#include <map>
using namespace std;

/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define NO_PE				0
#define X86                 0x0032
#define X64                 0x0064
#define X64_PE				0x8664							// 62bits PE
#define X32_PE				0x014c							// 32bits PE
#define NDISASM_EXE_NAME	"_ndisasm.exe"
#define BINARY_FILE_NAME	_T("7A43A012-B913-435d-A6D7-4281190EBB37.bin")
#define ASSEMBLY_FILENAME	_T("7A43A012-B913-435d-A6D7-4281190EBB37.txt")
#define X32PE_ADDRLEN		8
#define X64PE_ADDRLEN		16
#define	CODEDATALEN			128
#define	ASSEMDATALEN		128
#define CODEDATAWIDTH		24
#define SLEEPMAX			256
/************************************************************************/
/* Struct                                                               */
/************************************************************************/
//2)
#ifdef DWORD64
#undef DWORD64
typedef struct tag_DWORD64s
{
	DWORD dwValue1;
	DWORD dwValue2;
}DWORD64;
typedef unsigned __int64  *PDWORD64;
//typedef DWORD64 PDWORD64;
#define HIDWORD(dwword64)	(DWORD)(dwword64 >> 32) 
#define LODWORD(dwword64)	(DWORD)(dwword64) 

#endif

//1) PROCESSENTRY32_ struct
void GetProcessFullPath(DWORD dwProcessID, TCHAR* szFullPath);
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
		GetProcessFullPath(this->th32ProcessID, this->szExePath);
	
        return *this;
    }
} PROCESSENTRY32_;

//2) ExeMemInfo struct
typedef struct tag_ExeMemInfo
{
	DWORD dwPEVersion;				// PEVersion
	DWORD dwImageBase;				// ImageBase
    DWORD64 dwImageBase64;			// SizeofImage [X64]
	DWORD dwAddressOfEntryPoint;	// AddressOfEntryPoint
	DWORD dwSizeofImage;			// SizeofImage
	DWORD dwBaseOfCode;				// BaseOfCode
	DWORD dwSizeOfCode;				// SizeOfCode

	DWORD dwImportRVA;				// IMAGE_DIRECTORY_ENTRY_IMPORT adddress
	DWORD dwimportSize;				// IMAGE_DIRECTORY_ENTRY_IMPORT Size
}ExeMemInfo, *PExeMemInfo;

//3) ASSEMDATA struct
typedef struct tag_ASSEMDATA
{
	DWORD	dwAddress;					// address
	DWORD64 dwAddress64;				// address [X64]
	TCHAR	szCodeData[CODEDATALEN];	// codedata
	TCHAR	szAssemData[ASSEMDATALEN];	// assemblydata
	// constructor
	tag_ASSEMDATA()
	{
		memset(this, 0x00, sizeof(tag_ASSEMDATA));
	}
	// operator=
	tag_ASSEMDATA& operator= (tag_ASSEMDATA& entry)
	{
		memcpy(this, &entry, sizeof(tag_ASSEMDATA));
		return *this;
	}
}ASSEMDATA, *PASSEMDATA;
/************************************************************************/
/* Global Member                                                        */
/************************************************************************/
extern CStringArray g_DeviceArr;
static DWORD g_WindowsVersion = X86;            // windows envirment
static DWORD g_FirstTime = 0;
static DWORD g_LastTime = 0;		
/************************************************************************/
/* Global Function                                                      */
/************************************************************************/
BOOL	ImproveTokenPrivilege();																						// ImproveTokenPrivilege
void	GetDeviceString(CStringArray& strDeviceArr);																	// GetDeviceString
void	FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList);										// FlushProcessInfo
BOOL	LoadDlls(void);																									// LoadDlls
BOOL	GetExeInfo(CString strFilePath, PExeMemInfo pExeMemInfo);														// GetExeInfo
DWORD	GetPEVersion(TCHAR* szBuffer);																					// GetPEVersion
TCHAR*	ReadProcessAllMemory(HANDLE hProcess, DWORD dwSizeOfImage, BOOL boolWow64, DWORD64& dwImageBase64);				// ReadProcessAllMemory
BOOL	Disasmembly_InitData(LPTSTR pszData, PASSEMDATA pAssemData, DWORD dwImageBase);									// Disasmembly_InitData
BOOL	Disasmembly_InitData64(LPTSTR pszData, PASSEMDATA pAssemData, DWORD64 dwImageBase64);							// Disasmembly_InitData64
LPTSTR	TrimLeft(LPTSTR pszData);																						// TrimLeft
LPTSTR	FormatString(LPTSTR pszData, char c);                                                                           // FormatString
void	Sleep_();																										// Sleep_
BOOL	InitImportFunction(LPCTSTR pszBuffer, PExeMemInfo pExeMemInfo, map<DWORD, CString>& funcRvaMap);				// InitImportFunction
BOOL	InitImportFunction64(LPCTSTR pszBuffer, PExeMemInfo pExeMemInfo, map<DWORD64, CString>& funcRvaMap64);          // InitImportFunction64 
#endif//__PEUTI_H_2459134951B94A1895E650CFD52F4215__
