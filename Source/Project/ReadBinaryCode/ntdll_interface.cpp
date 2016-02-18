#include <windows.h>
#include "ntdll.h"
#include "ntdll_interface.h"
#define Ptr64ToPtr( p )         ((void *) p)

typedef BOOL (__stdcall *ISWOW64PROCESS)(HANDLE hProcess, PBOOL Wow64Process);
typedef NTSTATUS (__stdcall *NTQUERYINFORMATIONPROCESS)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength OPTIONAL);
#if !defined(_WIN64)
typedef NTSTATUS (__stdcall *NTWOW64QUERYINFORMATIONPROCESS64)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PSIZE_T64 ReturnLength OPTIONAL);
typedef NTSTATUS (__stdcall *NTWOW64READVIRTUALMEMORY64)( IN HANDLE ProcessHandle, IN PVOID64_ BaseAddress, OUT PVOID Buffer, IN SIZE_T64 BufferSize, OUT PSIZE_T64 NumberOfBytesRead OPTIONAL);
#endif

ISWOW64PROCESS pIsWow64Process = 0;
NTQUERYINFORMATIONPROCESS pNtQueryInformationProcess = 0;
#if !defined(_WIN64)
NTWOW64QUERYINFORMATIONPROCESS64 pNtWow64QueryInformationProcess64 = 0;
NTWOW64READVIRTUALMEMORY64 pNtWow64ReadVirtualMemory64 = 0;
#endif

BOOL bLoaded = FALSE;
BOOL LoadDlls(void)
{
    HMODULE hKernel32 = GetModuleHandle("kernel32.dll");
    HMODULE hNtDll = GetModuleHandle("ntdll.dll");
    if ((0 == hKernel32 ) || (0 == hNtDll))
    {
        return FALSE;
    }
    pIsWow64Process = (ISWOW64PROCESS) GetProcAddress(hKernel32, "IsWow64Process");
    pNtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS) GetProcAddress(hNtDll, "NtQueryInformationProcess");
#if !defined(_WIN64)
    pNtWow64QueryInformationProcess64 = (NTWOW64QUERYINFORMATIONPROCESS64) GetProcAddress(hNtDll, "NtWow64QueryInformationProcess64");
    pNtWow64ReadVirtualMemory64 = (NTWOW64READVIRTUALMEMORY64) GetProcAddress(hNtDll, "NtWow64ReadVirtualMemory64");
#endif
    bLoaded = TRUE;
    return (0 != pNtQueryInformationProcess);
}
/*
NTProcessInformation::NTProcessInformation(HANDLE hProcess)
:      x_Pid(-1)
,      x_PPid(-1)
,      x_ExitStatus(STILL_ACTIVE)
,      x_PebAddress(0)
,      x_hProcess(hProcess)
,      x_OK(false)
,      x_UseWow64Apis(false)
{
    CommonConstruct();
}

NTProcessInformation::NTProcessInformation(DWORD pid)
:      x_Pid(-1)
,      x_PPid(-1)
,      x_ExitStatus(STILL_ACTIVE)
,      x_PebAddress(0)
,      x_hProcess(0)
,      x_OK(false)
,      x_UseWow64Apis(false)
{
    x_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    CommonConstruct();
}

void NTProcessInformation::CommonConstruct(void)
{
    if (!bLoaded)
    {
        if (!LoadDlls())
        {return;}
    }
    DWORD err;
    PROCESS_BASIC_INFORMATION info;
    ULONG realsize;

    if (ERROR_SUCCESS != (err = pNtQueryInformationProcess(x_hProcess, ProcessBasicInformation, (PVOID) &info, sizeof(info), &realsize)))
    {return;}
    if (0 == info.PebBaseAddress)
    {
#if defined(_WIN64)
        return;
#else
        PROCESS_BASIC_INFORMATION64 info64;
        SIZE_T64 realsize64;

        if (!IsWow64Process(GetCurrentProcess()))
        {return;}
        if (0 == pNtWow64QueryInformationProcess64)
        {return;}
        if (ERROR_SUCCESS != (err = pNtWow64QueryInformationProcess64(x_hProcess, ProcessBasicInformation, (PVOID) &info64, sizeof(info64), &realsize64)))
        {return;}
        x_Pid = (ULONG_PTR) info64.UniqueProcessId;
        x_PPid = (ULONG_PTR) info64.InheritedFromUniqueProcessId;
        x_ExitStatus = info64.ExitStatus;
        x_PebAddress = info64.PebBaseAddress;
        x_OK = true;
        x_UseWow64Apis = true;
#endif
    }
    else
    {
        x_Pid = info.UniqueProcessId;
        x_PPid = info.InheritedFromUniqueProcessId;
        x_ExitStatus = info.ExitStatus;
        x_PebAddress = info.PebBaseAddress;
        x_OK = true;
    }
}

bool NTProcessInformation::IsWow64Process(HANDLE hProcess)
{
    if (pIsWow64Process)
    {
        BOOL IsWow64 = FALSE;

        if (pIsWow64Process(hProcess ? hProcess : x_hProcess, &IsWow64))
        {return IsWow64 ? true : false;}
    }
    return false;
}

NTPEB::NTPEB(HANDLE hProcess)
:      x_ProcessParameters(0)
,      x_OK(false)
,      x_UseWow64Apis(false)
,      x_hProcess(0)
{
    NTProcessInformation info(hProcess);
    CommonConstruct(info);
}

NTPEB::NTPEB(DWORD pid)
:      x_ProcessParameters(0)
,      x_OK(false)
,      x_UseWow64Apis(false)
,      x_hProcess(0)
{
    NTProcessInformation info(pid);
    CommonConstruct(info);
}

NTPEB::NTPEB(NTProcessInformation &ntpi)
:      x_ProcessParameters(0)
,      x_OK(false)
,      x_UseWow64Apis(false)
,      x_hProcess(0)
{
    CommonConstruct(ntpi);
}

void NTPEB::CommonConstruct(NTProcessInformation &ntpi)
{
    if (!bLoaded)
    {
        if (!LoadDlls())
        {return;}
    }
    x_hProcess = ntpi.hProcess;
    if (ntpi.UseWow64Apis)
    {
#if defined(_WIN64)
        return;
#else
        PEB64 peb64;
        SIZE_T64 realsize64;
        NTSTATUS err;
        if (ERROR_SUCCESS != (err = pNtWow64ReadVirtualMemory64(x_hProcess, (VOID * __ptr64)ntpi.getpa(), &peb64, sizeof(PEB64), &realsize64)))
        {return;}
        x_UseWow64Apis = true;
        x_ProcessParameters = peb64.ProcessParameters;
#endif
    }
    else
    {
        PEB peb;
        SIZE_T realsize;
        if (FALSE == ReadProcessMemory(x_hProcess, Ptr64ToPtr(ntpi.getpa()), &peb, sizeof(PEB), &realsize))
        {return;}
        x_ProcessParameters = peb.ProcessParameters;
    }
    x_OK = true;
}

NTProcessParameters::NTProcessParameters(HANDLE hProcess)
:      x_OK(false)
{
    NTPEB peb(hProcess);
    CommonConstruct(peb);
}

NTProcessParameters::NTProcessParameters(DWORD pid)
:      x_OK(false)
{
    NTPEB peb(pid);
    CommonConstruct(peb);
}

NTProcessParameters::NTProcessParameters(NTPEB &peb)
:      x_OK(false)
{
    CommonConstruct(peb);
}

void NTProcessParameters::CommonConstruct(NTPEB &peb)
{
    if (!bLoaded)
    {
        if (!LoadDlls())
        {return;}
    }
    if (peb.UseWow64Apis)
    {
#if defined(_WIN64)
        return;
#else
        PROCESS_PARAMETERS64 ProcParams64;
        SIZE_T64 realsize64;
        NTSTATUS err;

        if (ERROR_SUCCESS != (err = pNtWow64ReadVirtualMemory64(peb.hProcess, peb.getpp(), &ProcParams64, sizeof(PROCESS_PARAMETERS64), &realsize64)))
        {return;}
        SIZE_T64 len = ProcParams64.CurrentDirectory.DosPath.Length;
        wchar_t *buffer = new wchar_t[(SIZE_T) (len+1)];
        if (ERROR_SUCCESS != (err = pNtWow64ReadVirtualMemory64(peb.hProcess, ProcParams64.CurrentDirectory.DosPath.Buffer, buffer, len * sizeof(wchar_t), &realsize64)))
        {return;}
        buffer[realsize64/2] = '/0';
        x_pwd = buffer;
        delete [] buffer;
#endif
    }
    else
    {
        PROCESS_PARAMETERS ProcParams;
        SIZE_T realsize;

        if (FALSE == ReadProcessMemory(peb.hProcess, Ptr64ToPtr(peb.getpp()), &ProcParams, sizeof(PROCESS_PARAMETERS), &realsize))
        {return;}                                    
        SIZE_T len = ProcParams.CurrentDirectory.DosPath.Length;
        wchar_t *buffer = new wchar_t[len+1];
        if (FALSE == ReadProcessMemory(peb.hProcess, ProcParams.CurrentDirectory.DosPath.Buffer, buffer, len*sizeof(wchar_t), &realsize))
        {return;}
        buffer[realsize/2] = '/0';
        x_pwd = buffer;
        delete [] buffer;
    }
    x_OK = true;
}
*/