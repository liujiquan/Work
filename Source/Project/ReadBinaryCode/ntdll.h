//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ntdll.h
//* Author   :   liujiquan
//* DateTime :   10/29/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __NTDLL_H_2459134951B94A1895E650CFD52F4215__
#define __NTDLL_H_2459134951B94A1895E650CFD52F4215__

#pragma once
typedef LONG NTSTATUS;
typedef LONG KPRIORITY;

#if (_MSC_VER < 1300)
typedef ULONG *ULONG_PTR;
#endif

typedef enum _PROCESSINFOCLASS
{
    ProcessBasicInformation,
    ProcessQuotaLimits,
    ProcessIoCounters,
    ProcessVmCounters,
    ProcessTimes,
    ProcessBasePriority,
    ProcessRaisePriority,
    ProcessDebugPort,
    ProcessExceptionPort,
    ProcessAccessToken,
    ProcessLdtInformation,
    ProcessLdtSize,
    ProcessDefaultHardErrorMode,
    ProcessIoPortHandlers,
    ProcessPooledUsageAndLimits,
    ProcessWorkingSetWatch,
    ProcessUserModeIOPL,
    MaxProcessInfoClass
} PROCESSINFOCLASS;

typedef PVOID PPEB_LDR_DATA;
typedef PVOID PPEB_FREE_BLOCK;

#if !defined(_WIN64)
#if (_MSC_VER < 1300)
typedef unsigned __int64 PCHAR64;
typedef unsigned __int64 HANDLE64;
typedef unsigned __int64 PVOID64_;
#else
typedef char * __ptr64 PCHAR64;
typedef void * __ptr64 HANDLE64;
typedef void * __ptr64 PVOID64_;
#endif
typedef PVOID64_ PPEB_LDR_DATA64;
typedef PVOID64_ PPEB_FREE_BLOCK64;
typedef unsigned __int64 SIZE_T64, *PSIZE_T64;
#endif

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PCHAR Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;

#if !defined(_WIN64)
typedef struct _UNICODE_STRING64 {
    USHORT Length;
    USHORT MaximumLength;
    PCHAR64 Buffer;
} UNICODE_STRING64;
typedef UNICODE_STRING64 *PUNICODE_STRING64;
#endif

typedef struct _CURRENT_DIRECTORY {
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURRENT_DIRECTORY, *PCURRENT_DIRECTORY;

#if !defined(_WIN64)
typedef struct _CURRENT_DIRECTORY64 {
    UNICODE_STRING64 DosPath;
    HANDLE64 Handle;
} CURRENT_DIRECTORY64, *PCURRENT_DIRECTORY64;
#endif

typedef struct _PROCESS_PARAMETERS {
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURRENT_DIRECTORY CurrentDirectory; 
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PVOID Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
} PROCESS_PARAMETERS, *PPROCESS_PARAMETERS;

#if !defined(_WIN64)
typedef struct _PROCESS_PARAMETERS64 {
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE64 ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE64 StandardInput;
    HANDLE64 StandardOutput;
    HANDLE64 StandardError;
    CURRENT_DIRECTORY64 CurrentDirectory;
    UNICODE_STRING64 DllPath;
    UNICODE_STRING64 ImagePathName;
    UNICODE_STRING64 CommandLine;
    PVOID64_ Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING64 WindowTitle;
    UNICODE_STRING64 DesktopInfo;
    UNICODE_STRING64 ShellInfo;
    UNICODE_STRING64 RuntimeData;
} PROCESS_PARAMETERS64
#if (_MSC_VER < 1300)
;
typedef unsigned __int64 PPROCESS_PARAMETERS64;
#else
, *PPROCESS_PARAMETERS64;
#endif
#endif

typedef struct _PEB {
    BOOLEAN InheritedAddressSpace;
    HANDLE Mutant;              
    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PPROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PVOID FastPebLock;
    PVOID FastPebLockRoutine;
    PVOID FastPebUnlockRoutine;
    PVOID Spare[4];
    PPEB_FREE_BLOCK FreeList;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID ReadOnlySharedMemoryHeap;
    PVOID *ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    LARGE_INTEGER CriticalSectionTimeout;
} PEB, *PPEB;

#if !defined(_WIN64)
typedef struct _PEB64 {
    BOOLEAN InheritedAddressSpace;
    HANDLE64 Mutant;            
    PVOID64_ ImageBaseAddress;
    PPEB_LDR_DATA64 Ldr;
#if (_MSC_VER < 1300)
    PPROCESS_PARAMETERS64 ProcessParameters;
#else
    PROCESS_PARAMETERS64 *__ptr64 ProcessParameters;
#endif
    PVOID64_ SubSystemData;
    PVOID64_ ProcessHeap;
    PVOID64_ FastPebLock;
    PVOID64_ FastPebLockRoutine;
    PVOID64_ FastPebUnlockRoutine;
    PVOID64_ Spare[4];
    PPEB_FREE_BLOCK64 FreeList;
    ULONG TlsExpansionCounter;
    PVOID64_ TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID64_ ReadOnlySharedMemoryBase;
    PVOID64_ ReadOnlySharedMemoryHeap;
    PVOID64_ *ReadOnlyStaticServerData;
    PVOID64_ AnsiCodePageData;
    PVOID64_ OemCodePageData;
    PVOID64_ UnicodeCaseTableData;
    LARGE_INTEGER CriticalSectionTimeout;
} PEB64
#if (_MSC_VER < 1300)
;
typedef unsigned __int64 PPEB64;
#else
, * __ptr64 PPEB64;
#endif
#endif

typedef struct _PROCESS_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    PPEB PebBaseAddress;
    ULONG_PTR AffinityMask;
    KPRIORITY BasePriority;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;
typedef PROCESS_BASIC_INFORMATION *PPROCESS_BASIC_INFORMATION;

#if !defined(_WIN64)
typedef struct _PROCESS_BASIC_INFORMATION64 {
    NTSTATUS ExitStatus;
    PPEB64 PebBaseAddress;
    ULONG64 AffinityMask;
    KPRIORITY BasePriority;
    ULONG64 UniqueProcessId;
    ULONG64 InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION64;
typedef PROCESS_BASIC_INFORMATION64 *PPROCESS_BASIC_INFORMATION64;
#endif

#endif//__NTDLL_H_2459134951B94A1895E650CFD52F4215__