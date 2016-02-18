// ModifyMemoryDlg.cpp : 
//
#include "stdafx.h"
#include "ModifyMemory.h"
#include "ModifyMemoryDlg.h"
#include ".\modifymemorydlg.h"
#include "MemoryUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4312)
CModifyMemoryDlg::CModifyMemoryDlg(CWnd* pParent)
	: CDialog(CModifyMemoryDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    
    m_bRun = TRUE;
    m_Process = NULL;
}

void CModifyMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_Process, m_ProcessList);
    DDX_Control(pDX, IDC_LIST2, m_MemAddrList);
    DDX_Control(pDX, IDC_COMBO1, m_CmbDataType);
}

BEGIN_MESSAGE_MAP(CModifyMemoryDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_RESTART, OnBnClickedBtnRestart)
    ON_BN_CLICKED(IDC_BTN_Refresh, OnBnClickedBtnRefresh)
    ON_BN_CLICKED(IDC_BTN_RUN, OnBnClickedBtnRun)
    ON_BN_CLICKED(IDC_BTN_MODIFY, OnBnClickedBtnModify)
    ON_MESSAGE(SEARCH_MSG, OnSearchFinish)
END_MESSAGE_MAP()

BOOL CModifyMemoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);
    // InitInfo
    InitInfo();
	return TRUE;
}

void CModifyMemoryDlg::OnPaint() 
{
	CDialog::OnPaint();
}

HCURSOR CModifyMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::InitInfo
// Param                
// Return  :    void   
// meaning :    初始化信息
// -----------------------------------------------------------//
void   CModifyMemoryDlg::InitInfo()
{   
    // 提升本程序的權限
    ImproveTokenPrivilege();
    SetParentHwnd(m_hWnd);

    //ProcessList
    m_ProcessList.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(1, "ProcessID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(2, "ParenetPrcessID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(3, "ModuleID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(4, "ThreadCount", LVCFMT_LEFT, 100);
    m_ProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    // 首次獲取Process信息
    GetProcessInfo();
    // DataType
    m_CmbDataType.AddString(_T("BYTE(1字節)"));
    m_CmbDataType.AddString(_T("SHORT(2字節)"));
    m_CmbDataType.AddString(_T("INT(4字節)"));
    m_CmbDataType.AddString(_T("FLOAT(4字節浮點型)"));
    m_CmbDataType.AddString(_T("DOUBLE(8字節浮點型)"));
    m_CmbDataType.AddString(_T("字符串"));
    m_CmbDataType.SetCurSel(0);
}

// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::GetProcessInfo
// Param                
// Return  :    void    
// meaning :    獲取線程信息 
// -----------------------------------------------------------//
void    CModifyMemoryDlg::GetProcessInfo()
{
    m_ProcessList.DeleteAllItems();

    // 獲取線程信息
    CArray<PROCESSENTRY32_, PROCESSENTRY32_> processList;
    FlushProcessInfo(processList);
    int nSize = processList.GetCount();
    for(int i = 0; i < nSize; i++)
    {
        PROCESSENTRY32_ entry = processList.GetAt(i);
        m_ProcessList.InsertItem(i, "");
        // SetValue
        CString str(entry.szExeFile);
        m_ProcessList.SetItemText(i, 0, str);
        str.Format("%d", entry.th32ProcessID);
        m_ProcessList.SetItemText(i, 1, str);
        str.Format("%d", entry.th32ParentProcessID);
        m_ProcessList.SetItemText(i, 2, str);
        str.Format("%d", entry.th32ModuleID);
        m_ProcessList.SetItemText(i, 3, str);
        str.Format("%d", entry.cntThreads);
        m_ProcessList.SetItemText(i, 4, str);
    }
}


// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::OnBnClickedBtnRefresh
// Param                
// Return  :    void 
// meaning :    刷新進程
// -----------------------------------------------------------//
void CModifyMemoryDlg::OnBnClickedBtnRefresh()
{
    GetProcessInfo();
}

// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::OnBnClickedBtnRestart
// Param                
// Return  :    void 
// meaning :    重新開始
// -----------------------------------------------------------//
void CModifyMemoryDlg::OnBnClickedBtnRestart()
{
    BOOL b = GfxGetSearchStatus();
    if(b)
    {
        MessageBox("當前搜索還沒有結束. 請等待.");
        return;
    }

    OnResetSearch(m_Process);
}

// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::OnBnClickedBtnRun
// Param                
// Return  :    void 
// meaning :    開始
// -----------------------------------------------------------//
void CModifyMemoryDlg::OnBnClickedBtnRun()
{   
    BOOL b = GfxGetSearchStatus();
    if(b)
    {
        MessageBox("當前搜索還沒有結束. 請等待.");
        return;
    }
    

    // 搜索文本
    CString strFindText;
    GetDlgItem(IDC_EDIT_FINDTEXT)->GetWindowText(strFindText);
    if(strFindText.IsEmpty())
    {
        MessageBox("搜索文本為空.");
        return;
    }
    // 搜索類型
    int dataType = m_CmbDataType.GetCurSel();
    if(dataType == -1)
    {
        MessageBox("搜索數據類型沒有選擇.");
        return;
    }

    if(m_Process == NULL)
    {
        // ThreadExe
        int index = m_ProcessList.GetSelectionMark(); 
        if(index == -1) 
        {
            MessageBox("請選擇進程exe.");
            return;
        }
        // 進程
        CString strThreadID = m_ProcessList.GetItemText(index, 1);
        DWORD dwProcessID;      // 進程ID
        dwProcessID = (DWORD)(atoi(strThreadID.GetBuffer(0)));
        m_Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
        if(m_Process == NULL)
        {
            MessageBox("打開進程失敗.");
            return;
        }
    }
    GetDlgItem(IDC_BTN_RUN)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_RESTART)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(FALSE);
    OnBeginSearch(m_Process, dataType, strFindText.GetBuffer(0), m_AddressArr);  
}

// -----------------------------------------------------------//
// Function:    CModifyMemoryDlg::OnBnClickedBtnModify
// Param                
// Return  :    void 
// meaning :    修改内存
// -----------------------------------------------------------//
void CModifyMemoryDlg::OnBnClickedBtnModify()
{
    BOOL b = GfxGetSearchStatus();
    if(b)
    {
        MessageBox("當前搜索還沒有結束. 請等待.");
        return;
    }
    // 内存地址
    CString str;
    int i = m_MemAddrList.GetCurSel();
    if(i == -1) 
    {
        MessageBox("請選擇内存地址.");
        return;
    }
    m_MemAddrList.GetText(i, str);
    DWORD dwAddr;
    sscanf(str, "%X", &dwAddr);  

    // modify文本
    CString modifyText;
    GetDlgItem(IDC_EDIT_FINDTEXT)->GetWindowText(modifyText);
    if(modifyText.IsEmpty())
    {
        MessageBox("請輸入修改的文本.");
        return; 
    }

    // 搜索類型
    int dataType = m_CmbDataType.GetCurSel();
    if(dataType == -1)
    {
        MessageBox("搜索數據類型沒有選擇.");
        return;
    }
    
    if(OnModifyMemory(m_Process, dwAddr, dataType, modifyText.GetBuffer(0)))
    {
        MessageBox("OK");
    }
}

LRESULT CModifyMemoryDlg::OnSearchFinish(WPARAM wparam, LPARAM lparam)
{   
    while(m_MemAddrList.GetCount() != 0)
    {
        m_MemAddrList.DeleteString(m_MemAddrList.GetCount()-1);
    }
     FlushAddress(m_AddressArr);

     for(int i = 0; i < m_AddressArr.GetCount(); i++)
     {
         DWORD dw = m_AddressArr.GetAt(i);
         CString str;
         str.Format("%08X", dw);
         m_MemAddrList.AddString(str);
     }
    
     GetDlgItem(IDC_BTN_RUN)->EnableWindow(TRUE);
     GetDlgItem(IDC_BTN_RESTART)->EnableWindow(TRUE);
     GetDlgItem(IDC_BTN_MODIFY)->EnableWindow(TRUE);
     MessageBox("搜索完成.");
    
     return 0;
}
