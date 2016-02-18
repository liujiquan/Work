// SendMailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "SendMailDlg.h"
#include "MailUtil.h"
// 2015.03.03 Ver10.9.0.2 [Remember User] Start
#include "InsertUser.h"
// 2015.03.03 Ver10.9.0.2 [Remember User] End
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg dialog
extern int				g_AccountSize;			// account size
extern vector<Account>	g_AccountVector;		// account

CSendMailDlg::CSendMailDlg(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CSendMailDlg)
	//}}AFX_DATA_INIT
}
void CSendMailDlg::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSendMailDlg)
	DDX_Control(pDX, IDC_RICHEDIT_TEXT, m_richEditText);
	DDX_Control(pDX, IDC_LIST_FileArr, m_FileArrlistEdit);
	DDX_Control(pDX, IDC_EDIT_Subject, m_SubjectEdit);
	DDX_Control(pDX, IDC_EDIT_BCC, m_BCCEdit);
	DDX_Control(pDX, IDC_EDIT_CC, m_CCEdit);
	DDX_Control(pDX, IDC_EDIT_TO, m_ToEdit);
	DDX_Control(pDX, IDC_COMBO1, m_ServerCmb);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CSendMailDlg, CDialogBar)
	//{{AFX_MSG_MAP(CSendMailDlg)
	ON_BN_CLICKED(IDC_POPUP_TO, OnPopupTo)
	ON_BN_CLICKED(IDC_POPUP_CC, OnPopupCc)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDC_POPUP_BCC, OnPopupBcc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg message handlers
BOOL CSendMailDlg::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		return FALSE;	
	}
	m_richEditText.Initlize();

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::InitInstance
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSendMailDlg::InitInstance()
{
	int index = 0;
	for(vector<Account>::iterator it = g_AccountVector.begin(); it != g_AccountVector.end(); it++)
	{
		m_ServerCmb.AddString(it->szSendServer);
		if(index == 0)	m_ServerCmb.SetCurSel(0);
		index++;
	}
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::FlushServerInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSendMailDlg::FlushServerInfo()
{
	for(int i = m_ServerCmb.GetCount() - 1; i >= 0 ; i--)
	{
		m_ServerCmb.DeleteString(i);
	}
	
	int index = 0;
	for(vector<Account>::iterator it = g_AccountVector.begin(); it != g_AccountVector.end(); it++)
	{
		m_ServerCmb.AddString(it->szSendServer);
		if(index == 0)	m_ServerCmb.SetCurSel(0);
		index++;
	}
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailServerAccount
// Return   :   Account*
// Comment  :   
// -----------------------------------------------------------//
Account* CSendMailDlg::GetEmailServerAccount()
{
	int index = m_ServerCmb.GetCurSel();
	if(index == -1)		return NULL;

	return  &g_AccountVector.at(index);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailTO
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString CSendMailDlg::GetEmailTO()
{
	CString str;
	GetDlgItem(IDC_EDIT_TO)->GetWindowText(str);

	return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailCC
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString CSendMailDlg::GetEmailCC()
{
	CString str;
	GetDlgItem(IDC_EDIT_CC)->GetWindowText(str);
	
	return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailBCC
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString CSendMailDlg::GetEmailBCC()
{
	CString str;
	GetDlgItem(IDC_EDIT_BCC)->GetWindowText(str);
	
	return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailSubject
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString CSendMailDlg::GetEmailSubject()
{
	CString str;
	GetDlgItem(IDC_EDIT_Subject)->GetWindowText(str);
	
	return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailText
// Param    :   CArray<TEXTINFO
//              TEXTINFO>& textArr
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSendMailDlg::GetEmailText(CArray<TEXTINFO, TEXTINFO>& textArr)
{
	m_richEditText.Split(textArr);
//	CString str;
//	GetDlgItem(IDC_EDIT_TEXT)->GetWindowText(str);
//	
//	return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::GetEmailFileArr
// Return   :   CStringArray&
// Comment  :   
// -----------------------------------------------------------//
CStringArray& CSendMailDlg::GetEmailFileArr()
{
	return m_FileArrlistEdit.m_strFileNameArr;
}

// 2015.03.03 Ver10.9.0.2 [Remember User] Start
// -----------------------------------------------------------//
// Function :   CSendMailDlg::OnPopupTo
// Return   :   void
// Comment  :   To
// -----------------------------------------------------------//
void CSendMailDlg::OnPopupTo() 
{
	InsertUser(GetDlgItem(IDC_EDIT_TO));
	((CButton*)GetDlgItem(IDC_POPUP_TO))->SetCheck(FALSE);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::OnPopupCc
// Return   :   void
// Comment  :   CC
// -----------------------------------------------------------//
void CSendMailDlg::OnPopupCc() 
{
	InsertUser(GetDlgItem(IDC_EDIT_CC));
	((CButton*)GetDlgItem(IDC_POPUP_CC))->SetCheck(FALSE);	
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::OnPopupBcc
// Return   :   void
// Comment  :   BCC
// -----------------------------------------------------------//
void CSendMailDlg::OnPopupBcc() 
{
	InsertUser(GetDlgItem(IDC_EDIT_BCC));
	((CButton*)GetDlgItem(IDC_POPUP_BCC))->SetCheck(FALSE);	
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::InsertUser
// Param    :   CWnd* editWnd
// Return   :   void
// Comment  :   InsertUser
// -----------------------------------------------------------//
void CSendMailDlg::InsertUser(CWnd* editWnd)
{
	CString strUserInfo;
	editWnd->GetWindowText(strUserInfo);

	CInsertUser dlg(this);
	dlg.m_UserInfo = strUserInfo;
	if(dlg.DoModal() == IDOK)
	{
		editWnd->SetWindowText(dlg.m_UserInfo);
	}
}
// 2015.03.03 Ver10.9.0.2 [Remember User] End