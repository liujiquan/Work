// AccembFindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadBinaryCode.h"
#include "AccembFindDlg.h"
#include "AssemblyDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccembFindDlg dialog


CAccembFindDlg::CAccembFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccembFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccembFindDlg)
	m_FindDirect = 0;
	//}}AFX_DATA_INIT
}


void CAccembFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccembFindDlg)
	DDX_Control(pDX, IDC_COMBO_FINDTEXT, m_FindCmb);
	DDX_Radio(pDX, IDC_RADIO_DOWN, m_FindDirect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccembFindDlg, CDialog)
	//{{AFX_MSG_MAP(CAccembFindDlg)
	ON_BN_CLICKED(IDC_BUTTON_FIND_NEXT, OnButtonFindNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccembFindDlg message handlers

BOOL CAccembFindDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_FindCmb.SetWindowText(m_strFindText);
	for(int i = 0; i < m_findStrArr.GetSize(); i++)
	{
		m_FindCmb.AddString(m_findStrArr.GetAt(i));
	}
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CAccembFindDlg::OnButtonFindNext
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CAccembFindDlg::OnButtonFindNext() 
{
	UpdateData(TRUE);
	
	DWORD dwFlag = 0x00;
	
	// up down all
	switch(m_FindDirect)
	{
	case 0:	dwFlag |= FR_DOWN; break;
	case 1: dwFlag |= 0x00000000; break;
	case 2: dwFlag |= FR_WHOLEWORD; break;
	}
	
	// match world word
	if(((CButton*)GetDlgItem(IDC_CHECK_MATCHALL))->GetCheck())
	{
		dwFlag |= FR_WHOLEWORD;
	}
	else
	{
		dwFlag |= FR_NOWHOLEWORD;
	}
	// match case
	if(((CButton*)GetDlgItem(IDC_CHECK_MATCHCASE))->GetCheck())
	{
		dwFlag |= FR_MATCHCASE;
	}
	else 
	{
		dwFlag |= FR_NOMATCHCASE;
	}
	
	CString strFindData;
	m_FindCmb.GetWindowText(strFindData);
	BOOL bRet = ((CAssemblyDlg*)GetParent())->FindData(dwFlag, strFindData);

	if(bRet) ::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
}
