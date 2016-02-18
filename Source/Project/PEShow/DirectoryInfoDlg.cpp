// DirectoryInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "DirectoryInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectoryInfoDlg dialog


CDirectoryInfoDlg::CDirectoryInfoDlg(CWnd* pParent /*=NULL*/)
{

}


void CDirectoryInfoDlg::DoDataExchange(CDataExchange* pDX)
{

}


BEGIN_MESSAGE_MAP(CDirectoryInfoDlg, CDialogBar)
	//{{AFX_MSG_MAP(CDirectoryInfoDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectoryInfoDlg message handlers

// -----------------------------------------------------------//
// Function :   CDirectoryInfoDlg::OnInitDialog
// Param    :   WPARAM wparam
//              LONG lparam
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CDirectoryInfoDlg::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		
	}
	
	CTabCtrl* m_pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	if(m_pTabCtrl == NULL)
	{
		return FALSE;
	}

	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_EXPORT, _T("Export Table"));
	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_IMPORT, _T("Import Table"));
	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_RESOURCE, _T("Resource Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_EXCEPTION, _T("Exception Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_SECURITY, _T("Certificate Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_BASERELOC, _T("Relocation  Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_DEBUG, _T("Debug  Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_ARCHITECTURE, _T("Architecture Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_GLOBALPTR, _T("Global Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_TLS, _T("TLS  Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG, _T("Load Config Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT, _T("Bound Import Table"));
	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_IAT, _T("Import Address Table"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT, _T("Delay Import Descriptor"));
//	m_pTabCtrl->InsertItem(IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR, _T("COM+ Runtime Header"));
//	m_pTabCtrl->InsertItem(15, _T("Reserved"));
    
	CRect rect;
	m_pTabCtrl->GetClientRect(rect);
	rect.top+=20;
	rect.bottom-=4;

	// Import
	m_Page0.Create(IDD_DIALOG_DIR_PAGE_IMPORT, m_pTabCtrl);
	m_Page0.MoveWindow(&rect);
	m_Page0.ShowWindow(SW_SHOW);
	// Export
	m_Page1.Create(IDD_DIALOG_DIR_PAGE_EXPORT, m_pTabCtrl);
	m_Page1.MoveWindow(&rect);
	// Resource
	m_Page2.Create(IDD_DIALOG_DIR_PAGE_RESOURCE, m_pTabCtrl);
	m_Page2.MoveWindow(&rect);
	// Bound Import
	m_Page3.Create(IDD_DIALOG_DIR_PAGE_BOUND_IMPORT, m_pTabCtrl);
	m_Page3.MoveWindow(&rect);

	m_pTabCtrl->SetCurSel(1);

	return TRUE;
}      

// -----------------------------------------------------------//
// Function :   CDirectoryInfoDlg::OnSelchangeTab1
// Param    :   NMHDR* pNMHDR
//              LRESULT* pResult
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDirectoryInfoDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTabCtrl* m_pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	if(m_pTabCtrl == NULL)
	{
		return ;
	}

	UINT nIndex = m_pTabCtrl->GetCurSel();
	if(nIndex == 0)
	{
		m_Page0.ShowWindow(SW_HIDE);
		m_Page1.ShowWindow(SW_SHOW);
		m_Page2.ShowWindow(SW_HIDE);
		m_Page3.ShowWindow(SW_HIDE);
	}
	else if(nIndex == 1)
	{
		m_Page0.ShowWindow(SW_SHOW);
		m_Page1.ShowWindow(SW_HIDE);
		m_Page2.ShowWindow(SW_HIDE);
		m_Page3.ShowWindow(SW_HIDE);
	}
	else if(nIndex == 2)
	{
		m_Page0.ShowWindow(SW_HIDE);
		m_Page1.ShowWindow(SW_HIDE);
		m_Page2.ShowWindow(SW_SHOW);
		m_Page3.ShowWindow(SW_HIDE);
	}
	else if(nIndex == 3)
	{
		m_Page0.ShowWindow(SW_HIDE);
		m_Page1.ShowWindow(SW_HIDE);
		m_Page2.ShowWindow(SW_HIDE);
		m_Page3.ShowWindow(SW_SHOW);
	}
	
	*pResult = 0;
}
