//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, Liujiquan Company。( All rights reserved. )
//* FileName：      MemoryUtil.h
//* Version ：      1.0
//* Author  ：      Liujiquan
//* Date    ：      2014年7月11日
//* Comment ：      内存操作的一些函數
//*-----------------------------------------------------------------------------*/
#ifndef __MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__
#define __MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__
#pragma once

#include <afxtempl.h>
#include <WTypes.h>
#include <TlHelp32.h>

//////////////////////////////////////////////////////////////////////////
// 宏                                                                  
#define PAGE_SIZE       0x00001000              // 計算機默認頁大小 4MB     4 * 1024
#define ADDRESS_BEGIN   0x000A0000              // 内存範圍BEGIN
#define ADDRESS_END     0x80000000              // 内存範圍END
//////////////////////////////////////////////////////////////////////////
// 結構體
static CArray<DWORD, DWORD> g_dwAddressArrTemp;        // 臨時存儲
static int          g_findFlag;
static HANDLE       g_findhProcess;
static TCHAR        g_findText[MAX_PATH];
typedef struct tag_SEARCHDATA                           // 臨時參數結構體 [線程傳參數出現錯亂]
{
    int     flag;
    TCHAR   findText[MAX_PATH];
    HANDLE  hProcess;
public:
    tag_SEARCHDATA(HANDLE process, int nFlag, LPCTSTR pszFinText)
    {
        hProcess = process;
        flag = nFlag;
        memset(findText, 0x00, MAX_PATH);
        memcpy(findText, pszFinText, strlen(pszFinText) > MAX_PATH ? MAX_PATH : strlen(pszFinText));
    }
    tag_SEARCHDATA& operator=(tag_SEARCHDATA& entry)
    {
        this->hProcess = entry.hProcess;
        this->flag = entry.flag;
        memset(this->findText, 0x00, MAX_PATH);
        memcpy(this->findText, entry.findText, MAX_PATH);

        return *this;
    }
}SEARCHDATA, *PSEARCHDATA;
////////////////////////////////////////////////////////////////////////////
// 調用函數
static BOOL g_IsSearching = FALSE;                     // 當前存在搜索線程
BOOL GfxGetSearchStatus();                                                                                  // 獲取當前搜索status
void FlushAddress(CArray<DWORD, DWORD>& dwAddrArr);                                                         // 刷新Address
BOOL OnBeginSearch(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr);           // 開始搜索
BOOL OnResetSearch(HANDLE& hProcess);                                                                       // 重置
BOOL OnModifyMemory(HANDLE hProcess, DWORD dwAddress, int flag, LPCTSTR modifyText);                        // 修改内存    
//////////////////////////////////////////////////////////////////////////
// 搜索線程
static HANDLE g_Thead = NULL;                          // 線程句柄 
static DWORD WINAPI ThreadFunc_(LPVOID param);                                                              // 線程函數                   
DWORD WINAPI ThreadFunc(HANDLE hProcess, int flag, LPCTSTR findtext);                                       // 線程函數實現
//////////////////////////////////////////////////////////////////////////////
// 輔助函數
BOOL ImproveTokenPrivilege();                                                                               // 提升本程序的權限
static BOOL g_bFirstSerach = TRUE;              // 首次搜索flag 
void SearchMemoryAddress(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr);     // 搜索進程數據地址集合
BOOL BoolMemoryDataIsOK(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext);                     // 指定内存是否OK
BOOL WriteBuffer(HANDLE hProcess, DWORD dwAddr, LPCTSTR buffer, UINT nSize);                                // 内存寫數據
BOOL Compare(LPCTSTR szSrc, LPCTSTR szSrc2, UINT nLen);                                                     // 字符串比較
void ReadMemory(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext, CArray<int, int>& indexArr); // 搜索指定數據的地址集合
//////////////////////////////////////////////////////////////////////////
// 數據比較函數
void FindByte(LPCTSTR szSrc, BYTE byteData, UINT nSize, CArray<int, int>& indexArr);                        // 搜索BYTE
void FindSHORT(LPCTSTR szSrc, SHORT shortData, UINT nSize, CArray<int, int>& indexArr);                     // 搜索SHORT
void FindINT(LPCTSTR szSrc, INT intData, UINT nSize, CArray<int, int>& indexArr);                           // 搜索INT
void FindFLOAT(LPCTSTR szSrc, float floatData, UINT nSize, CArray<int, int>& indexArr);                     // 搜索FLOAT
void FindDOUBLE(LPCTSTR szSrc, DOUBLE doubleData, UINT nSize, CArray<int, int>& indexArr);                  // 搜索DOUBLE
void FindStr(LPCTSTR szSrc, LPCTSTR szFind, UINT nSize, CArray<int, int>& indexArr);                        // 搜索字符串
//////////////////////////////////////////////////////////////////////////
// 進程exe搜索函數
typedef struct tagPROCESSENTRY32_
{
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;          // this process
    ULONG_PTR th32DefaultHeapID;
    DWORD   th32ModuleID;           // associated exe
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;    // this process's parent process
    LONG    pcPriClassBase;         // Base priority of process's threads
    DWORD   dwFlags;
    CHAR    szExeFile[MAX_PATH];    // Path
// 2014.07.11 Ver1.00 【PROCESSENTRY32賦値運算符重載】Start
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

        return *this;
    }
// 2014.07.11 Ver1.00 【PROCESSENTRY32賦値運算符重載】End
} PROCESSENTRY32_;
void FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList);                                 // 進程exe搜索函數
///////////////////////////////////////////////////////////////////
// Message
#define SEARCH_MSG  WM_USER+1
static HWND m_ParentHwnd;
void SetParentHwnd(HWND hwnd);
#endif//__MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__