// ProcessInfo.cpp : implementation file
//

#include "stdafx.h"
#include "DisassemblyProcess.h"
#include "ProcessInfo.h"
#include "PeUti.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessInfo dialog


CProcessInfo::CProcessInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessInfo)
	//}}AFX_DATA_INIT
}


void CProcessInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessInfo)
	DDX_Control(pDX, IDC_LIST1, m_ProcessList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcessInfo, CDialog)
	//{{AFX_MSG_MAP(CProcessInfo)
	ON_BN_CLICKED(IDC_BUTTON_Flush, OnBUTTONFlush)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessInfo message handlers
BOOL CProcessInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// TODO: Add extra initialization here
	ImproveTokenPrivilege();
    if(g_DeviceArr.GetSize() == 0)
    {
        GetDeviceString(g_DeviceArr);
    }
	//ProcessList
    m_ProcessList.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(1, "ProcessID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(2, "ParenetPrcessID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(3, "ModuleID", LVCFMT_LEFT, 100);
    m_ProcessList.InsertColumn(4, "ThreadCount", LVCFMT_LEFT, 100);
	m_ProcessList.InsertColumn(5, "Path", LVCFMT_LEFT, 500);
    m_ProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	GetProcessInfo();

	return TRUE;  
}

// -----------------------------------------------------------//
// Function :   CProcessInfo::GetProcessInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CProcessInfo::GetProcessInfo()
{
    m_ProcessList.DeleteAllItems();
    // 
    CArray<PROCESSENTRY32_, PROCESSENTRY32_> processList;
    FlushProcessInfo(processList);
    int nSize = processList.GetSize();
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
        m_ProcessList.SetItemText(i, 5, entry.szExePath);
    }
}

// -----------------------------------------------------------//
// Function :   CProcessInfo::OnOK
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CProcessInfo::OnOK() 
{
	int nIndex = m_ProcessList.GetSelectionMark();
	if(nIndex == -1)
	{
		MessageBox("Please Select Process.");
		return;
	}
	m_strProcessName = m_ProcessList.GetItemText(nIndex, 0);
	m_strProcessPath = m_ProcessList.GetItemText(nIndex, 5);
	CString str;
	str = m_ProcessList.GetItemText(nIndex, 1);
	sscanf(str, "%d", &m_dwThreadID);

	CDialog::OnOK();
}

// -----------------------------------------------------------//
// Function :   CProcessInfo::OnBUTTONFlush
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CProcessInfo::OnBUTTONFlush() 
{
	GetProcessInfo();
}

// -----------------------------------------------------------//
// Function :   CProcessInfo::OnDblclkList1
// Param    :   NMHDR* pNMHDR
//              LRESULT* pResult
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CProcessInfo::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOK();
	*pResult = 0;
}
