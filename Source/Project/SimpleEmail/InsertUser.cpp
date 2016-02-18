// InsertUser.cpp : implementation file
//
#include "stdafx.h"
#include "SimpleEmail.h"
#include "InsertUser.h"
#include "MailUtil.h"
#include "InsertInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int				g_UserSize;			// recvUser Size
extern set<CString>		g_userSet;			// recvUser
/////////////////////////////////////////////////////////////////////////////
// CInsertUser dialog
CInsertUser::CInsertUser(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertUser)
	//}}AFX_DATA_INIT
	m_UserInfo = _T("");
}

void CInsertUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertUser)
	DDX_Control(pDX, IDC_LIST_From, m_FromList);
	DDX_Control(pDX, IDC_LIST_To, m_ToList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInsertUser, CDialog)
	//{{AFX_MSG_MAP(CInsertUser)
	ON_LBN_DBLCLK(IDC_LIST_From, OnDblclkLISTFrom)
	ON_LBN_DBLCLK(IDC_LIST_To, OnDblclkLISTTo)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CInsertUser message handlers
// -----------------------------------------------------------//
// Function :   CInsertUser::OnInitDialog
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CInsertUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// FromUser
	for(set<CString>::iterator it = g_userSet.begin(); it != g_userSet.end(); it++)
	{
		m_FromList.AddString(*it);
	}

	// ToUser
	CStringArray toArr;
	SplitString(m_UserInfo, toArr, SPLITCHAR);
	for(int i = 0; i < toArr.GetSize(); i++)
	{
		m_ToList.AddString(toArr.GetAt(i));
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CInsertUser::OnDblclkLISTFrom
// Return   :   void
// Comment  :   Add
// -----------------------------------------------------------//
void CInsertUser::OnDblclkLISTFrom() 
{
	int nIndex = m_FromList.GetCurSel();
	if(nIndex == -1)	return;

	CString strText;
	m_FromList.GetText(nIndex, strText);

	m_ToList.AddString(strText);
}

// -----------------------------------------------------------//
// Function :   CInsertUser::OnDblclkLISTTo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInsertUser::OnDblclkLISTTo() 
{
	int nIndex = m_ToList.GetCurSel();
	if(nIndex == -1)	return;
	
	m_ToList.DeleteString(nIndex);
}

// -----------------------------------------------------------//
// Function :   CInsertUser::OnButtonDel
// Return   :   void
// Comment  :   Delete Setting.ini
// -----------------------------------------------------------//
void CInsertUser::OnButtonDel() 
{
	int nIndex = m_FromList.GetCurSel();
	if(nIndex == -1)	return;
	
	CString strText;
	m_FromList.GetText(nIndex, strText);
	m_FromList.DeleteString(nIndex);

	for(set<CString>::iterator it = g_userSet.begin(); it != g_userSet.end(); it++)
	{
		if(*it == strText)
		{
			g_userSet.erase(it);
			break;
		}
	}
}

// -----------------------------------------------------------//
// Function :   CInsertUser::OnButtonAdd
// Return   :   void
// Comment  :   Insert Setting.ini
// -----------------------------------------------------------//
void CInsertUser::OnButtonAdd() 
{
	CInsertInfoDlg insertDlg;
	insertDlg.SetInsertFlag(10);
	insertDlg.DoModal();

	m_FromList.AddString(insertDlg.m_InserInfo);
	g_userSet.insert(insertDlg.m_InserInfo);
}

// -----------------------------------------------------------//
// Function :   CInsertUser::OnOK
// Return   :   void
// Comment  :   OK
// -----------------------------------------------------------//
void CInsertUser::OnOK() 
{
	CString strText = _T("");
	m_UserInfo = _T("");

	for(int i = 0; i < m_ToList.GetCount(); i++)
	{
		m_ToList.GetText(i, strText);
		
		if(i == m_ToList.GetCount() - 1)
		{
			m_UserInfo = m_UserInfo + strText;
		}
		else
		{
			m_UserInfo = m_UserInfo + strText + SPLITCHAR;
		}
	}

	CDialog::OnOK();
}
