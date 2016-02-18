// SuspensionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "SuspensionDlg.h"
#include "MailUtil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuspensionDlg dialog
extern int				g_UserSize;			// recvUser Size
extern set<CString>		g_userSet;			// recvUser

CSuspensionDlg::CSuspensionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuspensionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuspensionDlg)
	m_rect = CRect(0,0,0,0);
	m_InserUser = "";
	//}}AFX_DATA_INIT
}


void CSuspensionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuspensionDlg)
	DDX_Control(pDX, IDC_LIST1, m_ShowList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuspensionDlg, CDialog)
	//{{AFX_MSG_MAP(CSuspensionDlg)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuspensionDlg message handlers

BOOL CSuspensionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ShowList.AddString("Enter esc for nothing to do. LButtonDBclick for inser one user.");
	m_ShowList.SetCurSel(0);
	for(set<CString>::iterator it = g_userSet.begin(); it != g_userSet.end(); it++)
	{
		m_ShowList.AddString(*it);
	}

	m_rect.top = m_rect.bottom;
	m_rect.bottom = m_rect.top + 100;
	MoveWindow(m_rect, 100);
	CRect rect;
	m_ShowList.GetClientRect(rect);
	rect.right = rect.left + m_rect.Width();
	rect.bottom = rect.top + m_rect.Height();
	m_ShowList.MoveWindow(rect);

	return TRUE;  
}

void CSuspensionDlg::SetPos(CRect rect)
{
	m_rect = rect;
}

void CSuspensionDlg::OnDblclkList1() 
{
	int index = m_ShowList.GetCurSel();
	if(index == -1 || index == 0)
		m_InserUser = "";
	else
		m_ShowList.GetText(index, m_InserUser);

	OnOK();
}
