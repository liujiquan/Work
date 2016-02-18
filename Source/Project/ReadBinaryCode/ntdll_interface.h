//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ntdll_interface.h
//* Author   :   liujiquan
//* DateTime :   10/29/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __NTDLL_INTERFACE_H_2459134951B94A1895E650CFD52F4215__
#define __NTDLL_INTERFACE_H_2459134951B94A1895E650CFD52F4215__

#include <windows.h>
#include "ntdll.h"
#include <string>
/*
class NTProcessInformation
{
public:
    NTProcessInformation(HANDLE hProcess = GetCurrentProcess());
    NTProcessInformation(DWORD pid);
    bool _declspec(property(get=getok)) ok;
    __w64 ULONG_PTR __declspec(property(get=getpid)) pid;
    __w64 ULONG_PTR __declspec(property(get=getppid)) ppid;
    HANDLE __declspec(property(get=gethprocess)) hProcess;
    bool __declspec(property(get=getusewow64apis)) UseWow64Apis;
    VOID * __ptr64 __declspec(property(get=getpa)) PebBaseAddress;
    inline ULONG_PTR getpid(void) {return x_Pid;}
    inline ULONG_PTR getppid(void) {return x_PPid;}
    inline VOID * __ptr64 getpa(void) {return x_PebAddress;}
    inline bool getok(void) {return x_OK;}
    inline bool getusewow64apis(void) {return x_UseWow64Apis;}
    inline HANDLE gethprocess(void) {return x_hProcess;}
    bool IsWow64Process(HANDLE hProcess = 0);
protected:
    void CommonConstruct(void);
    __w64 ULONG_PTR x_Pid;
    __w64 ULONG_PTR x_PPid;
    DWORD x_ExitStatus;
    VOID * __ptr64 x_PebAddress;
    HANDLE x_hProcess;
    bool x_OK;
    bool x_UseWow64Apis;
};

class NTPEB
{
public:
    NTPEB(HANDLE hProcess = GetCurrentProcess());
    NTPEB(DWORD pid);
    NTPEB(NTProcessInformation &ntpi);
    bool _declspec(property(get=getok)) ok;
    bool __declspec(property(get=getusewow64apis)) UseWow64Apis;
    HANDLE __declspec(property(get=gethprocess)) hProcess;
    VOID * __ptr64 __declspec(property(get=getpp)) ProcessParameters;
    inline VOID * __ptr64 getpp(void) {return x_ProcessParameters;}
    inline bool getok(void) {return x_OK;}
    inline bool getusewow64apis(void) {return x_UseWow64Apis;}
    inline HANDLE gethprocess(void) {return x_hProcess;}
protected:
    void CommonConstruct(NTProcessInformation &ntpi);
    VOID * __ptr64 x_ProcessParameters;
    bool x_OK;
    bool x_UseWow64Apis;
    HANDLE x_hProcess;
};

class NTProcessParameters
{
public:
    NTProcessParameters(HANDLE hProcess = GetCurrentProcess());
    NTProcessParameters(DWORD pid);
    NTProcessParameters(NTPEB &peb);
    bool _declspec(property(get=getok)) ok;
    std::wstring _declspec(property(get=getcwd)) cwd;
    inline std::wstring getcwd(void) {return x_pwd;}
    inline bool getok(void) {return x_OK;}
protected:
    void CommonConstruct(NTPEB &peb);
    std::wstring x_pwd;
    bool x_OK;
};
*/
/************************************************************************/
/* Macro                                                                     */
/************************************************************************/
typedef BOOL (__stdcall *ISWOW64PROCESS)(HANDLE hProcess, PBOOL Wow64Process);
typedef NTSTATUS (__stdcall *NTQUERYINFORMATIONPROCESS)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PULONG ReturnLength OPTIONAL);
#if !defined(_WIN64)
typedef NTSTATUS (__stdcall *NTWOW64QUERYINFORMATIONPROCESS64)(IN HANDLE ProcessHandle, IN PROCESSINFOCLASS ProcessInformationClass, OUT PVOID ProcessInformation, IN ULONG ProcessInformationLength, OUT PSIZE_T64 ReturnLength OPTIONAL);
typedef NTSTATUS (__stdcall *NTWOW64READVIRTUALMEMORY64)( IN HANDLE ProcessHandle, IN PVOID64_ BaseAddress, OUT PVOID Buffer, IN SIZE_T64 BufferSize, OUT PSIZE_T64 NumberOfBytesRead OPTIONAL);
#endif
/************************************************************************/
/* Function                                                                     */
/************************************************************************/
BOOL LoadDlls(void);
#endif//#define __NTDLL_INTERFACE_H_2459134951B94A1895E650CFD52F4215__