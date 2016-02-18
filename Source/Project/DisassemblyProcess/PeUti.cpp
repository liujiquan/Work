//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   PeUti.cpp
//* Author   :   liujiquan
//* DateTime :   10/30/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "StdAfx.h"
#include "PeUti.h"
/************************************************************************/
/* Define                                                               */
/************************************************************************/
typedef BOOL (WINAPI *FuncIsWow64Process)(HANDLE hProcess, PBOOL Wow64Process);									// IsWow64Process
typedef NTSTATUS (WINAPI *FuncNtQueryInformationProcess)(IN HANDLE ProcessHandle,								// NtQueryInformationProcess
													IN PROCESSINFOCLASS ProcessInformationClass, 
													OUT PVOID ProcessInformation, 
													IN ULONG ProcessInformationLength, 
													OUT PULONG ReturnLength OPTIONAL);
typedef NTSTATUS (WINAPI *FuncNtWow64QueryInformationProcess64)(IN HANDLE ProcessHandle,						// NtWow64QueryInformationProcess64
													IN PROCESSINFOCLASS ProcessInformationClass, 
													OUT PVOID ProcessInformation, 
													IN ULONG ProcessInformationLength, 
													OUT PSIZE_T64 ReturnLength OPTIONAL);
typedef NTSTATUS (WINAPI *FuncNtWow64ReadVirtualMemory64)( IN HANDLE ProcessHandle,								// NtWow64ReadVirtualMemory64
													IN PVOID64_ BaseAddress, 
													OUT PVOID Buffer, 
													IN SIZE_T64 BufferSize, 
												    OUT PSIZE_T64 NumberOfBytesRead OPTIONAL);
typedef DWORD (WINAPI *FuncGetProcessImageFileNameA)(HANDLE hProcess, LPSTR lpImageFileName, DWORD nSize);		// GetProcessImageFileNameA
typedef DWORD (WINAPI *FuncGetProcessImageFileNameW)(HANDLE hProcess, LPWSTR lpImageFileName, DWORD nSize);		// GetProcessImageFileNameW
/************************************************************************/
/* Global Member                                                        */
/************************************************************************/
CStringArray g_DeviceArr;
/************************************************************************/
/* Function                                                                     */
/************************************************************************/
FuncIsWow64Process						pIsWow64Process = NULL;						// IsWow64Process
FuncNtQueryInformationProcess			pNtQueryInformationProcess = NULL;			// NtQueryInformationProcess
FuncNtWow64QueryInformationProcess64	pNtWow64QueryInformationProcess64 = NULL;	// NtWow64QueryInformationProcess64
FuncNtWow64ReadVirtualMemory64			pNtWow64ReadVirtualMemory64 = NULL;			// NtWow64ReadVirtualMemory64
FuncGetProcessImageFileNameA			pGetProcessImageFileNameA = NULL;			// GetProcessImageFileNameA
FuncGetProcessImageFileNameW			pGetProcessImageFileNameW = NULL;			// GetProcessImageFileNameW	
	
BOOL bLoaded = FALSE;
BOOL LoadDlls(void)
{
    if(bLoaded)     return TRUE;

	HMODULE hPsapi = LoadLibrary("psapi.dll");
    HMODULE hKernel32 = LoadLibrary("kernel32.dll");
    HMODULE hNtDll = LoadLibrary("ntdll.dll");
    if(!hPsapi || !hKernel32 || !hNtDll)	{	return FALSE;	}

    pIsWow64Process = (FuncIsWow64Process) GetProcAddress(hKernel32, "IsWow64Process");
    pNtQueryInformationProcess = (FuncNtQueryInformationProcess) GetProcAddress(hNtDll, "NtQueryInformationProcess");
	pNtWow64QueryInformationProcess64 = (FuncNtWow64QueryInformationProcess64) GetProcAddress(hNtDll, "NtWow64QueryInformationProcess64");
    pNtWow64ReadVirtualMemory64 = (FuncNtWow64ReadVirtualMemory64) GetProcAddress(hNtDll, "NtWow64ReadVirtualMemory64");
	pGetProcessImageFileNameA = (FuncGetProcessImageFileNameA)GetProcAddress(hPsapi, "GetProcessImageFileNameA");
	pGetProcessImageFileNameW = (FuncGetProcessImageFileNameW)GetProcAddress(hPsapi, "GetProcessImageFileNameW");

	if(!pIsWow64Process || !pNtQueryInformationProcess || !pGetProcessImageFileNameA || !pGetProcessImageFileNameW)
	{
        if(pNtWow64QueryInformationProcess64 && pNtWow64ReadVirtualMemory64)
        {
            g_WindowsVersion = X64;
        }
		bLoaded = FALSE;
	}
	else
	{
		bLoaded = TRUE;
	}

//	FreeLibrary(hNtDll);
//	FreeLibrary(hKernel32);
//	FreeLibrary(hPsapi);
    return bLoaded;
}

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

// -----------------------------------------------------------//
// Function :   GetProcessFullPath
// Param    :   DWORD dwProcessID
//              TCHAR* szFullPath
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void GetProcessFullPath(DWORD dwProcessID, TCHAR* szFullPath)
{
	if(dwProcessID == 0 || szFullPath == NULL || !pGetProcessImageFileNameA)	return;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
	if(hProcess == INVALID_HANDLE_VALUE)	return ;
	
	TCHAR   szExePathTemp[MAX_PATH] = {0};
	pGetProcessImageFileNameA(hProcess, szExePathTemp, MAX_PATH);
	CString strExePath(szExePathTemp);
	if(strExePath.GetLength() > 24)
	{
		char szDeviceName[24] = {0};
		DWORD dwIndex = 0;
		
		memcpy(szDeviceName, strExePath.GetBuffer(0), 23);
		dwIndex = szDeviceName[22] - '1';
		if(dwIndex >= 0 && g_DeviceArr.GetSize() >= dwIndex + 1)
		{
			strExePath = g_DeviceArr.GetAt(dwIndex) + strExePath.Right(strExePath.GetLength() - 23 - 1);
			memcpy(szFullPath, strExePath.GetBuffer(0), strExePath.GetLength());
		}
	}
	CloseHandle(hProcess);	
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
//  static DWORD dw1 = GetTickCount();
//  static DWORD dw2 = dw1;
    while(bRet)
    {   
//      TRACE2("%s [%d]\n", entry.szExeFile, dw2-dw1);      // SoftMon.exe [28096]
        // AddNew
        processList.Add(entry);
        // MoveNext
        bRet = ::Process32Next(hSnapShot, (PROCESSENTRY32*)&entry);
//      dw1 = dw2;
//      dw2 = GetTickCount();
    }
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
// Function :   GetExeInfo
// Param    :   CString strFilePath
//              PExeMemInfo pExeMemInfo
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
        pExeMemInfo->dwImageBase64 = ntHeader64.OptionalHeader.ImageBase;
		pExeMemInfo->dwAddressOfEntryPoint = ntHeader64.OptionalHeader.AddressOfEntryPoint;
		pExeMemInfo->dwSizeofImage = ntHeader64.OptionalHeader.SizeOfImage;
		pExeMemInfo->dwBaseOfCode = ntHeader64.OptionalHeader.BaseOfCode;
		pExeMemInfo->dwSizeOfCode = ntHeader64.OptionalHeader.SizeOfCode;

		pExeMemInfo->dwImportRVA = ntHeader64.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		pExeMemInfo->dwimportSize = ntHeader64.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
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

		pExeMemInfo->dwImportRVA = ntHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		pExeMemInfo->dwimportSize = ntHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
	}
	free(szBuffer);
	fclose(pFile);
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   ReadProcessAllMemory
// Param    :   HANDLE hProcess
//              DWORD dwSizeOfImage
//              BOOL boolWow64
//              DWORD64& dwImageBase64/* = 0 */
// Return   :   TCHAR*
// Comment  :   
// -----------------------------------------------------------//
TCHAR* ReadProcessAllMemory(HANDLE hProcess, DWORD dwSizeOfImage, BOOL boolWow64, DWORD64& dwImageBase64/* = 0 */)
{   
    if(hProcess == NULL)		return NULL;
    if(!pIsWow64Process )   return NULL;	
//  if(LoadDlls() == FALSE)     return NULL;
    //1
    BOOL bWow64 = FALSE, bWow64_ = FALSE;
    // 32bit exe run at 64bit windows ->TRUE
    // 32bit exe run at 32bit windows ->FALSE
    // 64bit exe run at 64bit windows ->FALSE
    // 64bit exe run at 32bit windows ->FALSE
    bWow64 = pIsWow64Process(hProcess, &bWow64_);  
    //2
    if(boolWow64)
    {	
		if(!pNtWow64QueryInformationProcess64 || !pNtWow64ReadVirtualMemory64)
		{
			return NULL;
		}

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
                dwImageBase64 = (DWORD64)peb64.ImageBaseAddress;
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

// -----------------------------------------------------------//
// Function :   TrimLeft
// Param    :   LPTSTR pszData
// Return   :   LPTSTR
// Comment  :   TrimLeft
// -----------------------------------------------------------//
LPTSTR TrimLeft(LPTSTR pszData)
{
	if(pszData == NULL)	return NULL;
	
	char* szData = pszData;
	while(*(szData) == ' ')	szData++;
	
	return szData;
}

// -----------------------------------------------------------//
// Function :   LPTSTR  FormatString
// Param    :   LPTSTR pszData
//              char c
// Return   :   
// Comment  :   FormatString
// -----------------------------------------------------------//
LPTSTR	FormatString(LPTSTR pszData, char c)
{
    if(pszData == NULL)	return NULL;

    int index = 2;
    while(*(pszData+index) != '\0' && *(pszData+index) == '0')
    {
        *(pszData+index) = c;
        index++;
    }

    return pszData;
}

// -----------------------------------------------------------//
// Function :   Disasmembly_InitData
// Param    :   LPTSTR pszData
//              PASSEMDATA pAssemData
//              DWORD dwImageBase
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL Disasmembly_InitData(LPTSTR pszData, PASSEMDATA pAssemData, DWORD dwImageBase)
{
	if(pszData == NULL || !pAssemData)		return FALSE;
	
	TCHAR szData1[X32PE_ADDRLEN+1] = {0};
	TCHAR szData2[CODEDATALEN+1] = {0};
	TCHAR szData3[ASSEMDATALEN+1] = {0};
	
	char* szData = pszData;
	
	// data1
	char* szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)					return FALSE;
	memcpy(szData1, szData, szDataTemp-szData);
	szData = TrimLeft(szDataTemp);
	
	// data2
	szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)					
	{
		memcpy(szData2, szData, strlen(szData));		//         -56AF	
		pAssemData->dwAddress = 0;
		memcpy(pAssemData->szCodeData, (char*)szData2, strlen((char*)szData2));
		return TRUE;
	}
	memcpy(szData2, szData, szDataTemp-szData);
	szData = TrimLeft(szDataTemp);
	
	
	// data3
	memcpy(szData3, szData, strlen(szData));
	
	sscanf(szData1, "%X", &pAssemData->dwAddress);
	pAssemData->dwAddress += dwImageBase;
	memcpy(pAssemData->szCodeData, (char*)szData2, strlen((char*)szData2));
	memcpy(pAssemData->szAssemData, (char*)szData3, strlen((char*)szData3));
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   Disasmembly_InitData64
// Param    :   LPTSTR pszData
//              PASSEMDATA pAssemData
//              DWORD64 dwImageBase64
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL Disasmembly_InitData64(LPTSTR pszData, PASSEMDATA pAssemData, DWORD64 dwImageBase64)
{
	if(pszData == NULL || !pAssemData)		return FALSE;
	
	TCHAR szData1[X32PE_ADDRLEN+1] = {0};
	TCHAR szData2[CODEDATALEN+1] = {0};
	TCHAR szData3[ASSEMDATALEN+1] = {0};
	
	char* szData = pszData;
	
	// data1
	char* szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)					return FALSE;
	memcpy(szData1, szData, szDataTemp-szData);
	szData = TrimLeft(szDataTemp);
	
	// data2
	szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)					
	{
		memcpy(szData2, szData, strlen(szData));		//         -56AF	
		pAssemData->dwAddress = 0;
		memcpy(pAssemData->szCodeData, (char*)szData2, strlen((char*)szData2));
		return TRUE;
	}
	memcpy(szData2, szData, szDataTemp-szData);
	szData = TrimLeft(szDataTemp);
	
	
	// data3
	memcpy(szData3, szData, strlen(szData));
	
	sscanf(szData1, "%X", &pAssemData->dwAddress64);
	pAssemData->dwAddress64 += dwImageBase64;
	memcpy(pAssemData->szCodeData, (char*)szData2, strlen((char*)szData2));
	memcpy(pAssemData->szAssemData, (char*)szData3, strlen((char*)szData3));
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   void	Sleep_
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
static g_dwSleep = 0;
void	Sleep_()
{
	if(g_dwSleep++ == SLEEPMAX)
	{
		Sleep(1);
//		TRACE1("Sleep %d\n", g_dwSleep);
		g_dwSleep = 0;	
	}
}

// -----------------------------------------------------------//
// Function :   InitImportFunction
// Param    :   LPCTSTR pszBuffer
//              PExeMemInfo pExeMemInfo
//              map<DWORD, CString>& funcRvaMap
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL InitImportFunction(LPCTSTR pszBuffer, PExeMemInfo pExeMemInfo, map<DWORD, CString>& funcRvaMap)
{
	if(!pszBuffer || !pExeMemInfo)			return FALSE;
	if(pExeMemInfo->dwPEVersion == NO_PE)	return FALSE;
	funcRvaMap.clear();
	
	IMAGE_IMPORT_DESCRIPTOR* pImportDesc = NULL;
	pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(pszBuffer + pExeMemInfo->dwImportRVA);
	// FuncName <-----> FuncAddr
	while(pImportDesc->FirstThunk)  
	{  
		char *pszDllName = (char *)((BYTE *)pszBuffer + pImportDesc->Name); 
        IMAGE_THUNK_DATA32 *pThunk = (IMAGE_THUNK_DATA32 *)((BYTE *)pszBuffer + pImportDesc->OriginalFirstThunk);  
        int n = 0;  

        char *pszFunName = NULL;  
        while(pThunk->u1.Function)  
        {  
            pszFunName = (char *)((BYTE *)pszBuffer + (DWORD)pThunk->u1.AddressOfData + 2);  
            PDWORD lpAddr = (DWORD *)((BYTE *)pszBuffer + pImportDesc->FirstThunk) +  n;  
            DWORD dwRVA = (DWORD)lpAddr - (DWORD)(pszBuffer);
            try  
            {  
                if(pszFunName)
                {
                    funcRvaMap[dwRVA+pExeMemInfo->dwImageBase] = CString(pszFunName);			// FuncName <-----> FuncAddr	
                }
            }  
            catch(...)  
            {  
            }  
            n++;  
            pThunk++;  
        }  
       
		pImportDesc++;  
	}
	
	return TRUE;
}

BOOL InitImportFunction64(LPCTSTR pszBuffer, PExeMemInfo pExeMemInfo, map<DWORD64, CString>& funcRvaMap)
{
    if(!pszBuffer || !pExeMemInfo)			return FALSE;
    if(pExeMemInfo->dwPEVersion == NO_PE)	return FALSE;
    funcRvaMap.clear();

    IMAGE_IMPORT_DESCRIPTOR* pImportDesc = NULL;
    pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(pszBuffer + pExeMemInfo->dwImportRVA);
    // FuncName <-----> FuncAddr
    while(pImportDesc->FirstThunk)  
    {  
        char *pszDllName = (char *)((BYTE *)pszBuffer + pImportDesc->Name); 
        IMAGE_THUNK_DATA64 *pThunk = (IMAGE_THUNK_DATA64 *)((BYTE *)pszBuffer + pImportDesc->OriginalFirstThunk);  
        int n = 0;  

        char *pszFunName = NULL;  
        while(pThunk->u1.Function)  
        {  
            pszFunName = (char *)((BYTE *)pszBuffer + (DWORD64)pThunk->u1.AddressOfData + 2);  
            DWORD64 lpAddr = ((DWORD64)((BYTE *)pszBuffer + pImportDesc->FirstThunk)) +  8*n;  
            DWORD64 dwRVA = (DWORD64)lpAddr - (DWORD64)(pszBuffer);
            try  
            {  
                if(pszFunName)
                {
//                  funcRvaMap[dwRVA+pExeMemInfo->dwImageBase64] = CString(pszFunName);			// FuncName <-----> FuncAddr	
                    funcRvaMap[dwRVA] = CString(pszFunName);			// FuncName <-----> FuncAddr	
                }
            }  
            catch(...)  
            {  
            }  
            n++;  
            pThunk++;  
        }  
       
        pImportDesc++;  
    }

    return TRUE;
}