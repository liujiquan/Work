#if !defined(AFX_SENDMAILDLG_H__7DF19A87_114D_4D2D_AA42_007BD09B2AB4__INCLUDED_)
#define AFX_SENDMAILDLG_H__7DF19A87_114D_4D2D_AA42_007BD09B2AB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendMailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg dialog
#include "ExtendEdit.h"
#include "MailUtil.h"
#include "ExtendListBox.h"
#include "ExtendRichEdit.h"
#include "ExtendRichEditCtrl.h"
#include "ExtendButton.h"
#include "SuspensionDlg.h"
class CSendMailDlg : public CDialogBar
{
// Construction
public:
	CSendMailDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendMailDlg)
	enum { IDD = IDD_DIALOG_SENDMAIL };
	CExtendRichEditCtrl	m_richEditText;
	CExtendListBox	m_FileArrlistEdit;
	CExtendEdit	m_SubjectEdit;
	CExtendSuspensionEdit	m_BCCEdit;
	CExtendSuspensionEdit	m_CCEdit;
	CExtendSuspensionEdit	m_ToEdit;
	CComboBox	m_ServerCmb;
	CExtendEdit	m_TextEdit;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSendMailDlg)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
	afx_msg void OnPopupTo();
	afx_msg void OnPopupCc();
	afx_msg void OnPopupBcc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void InitInstance();	
	void FlushServerInfo();
	Account* CSendMailDlg::GetEmailServerAccount();
	CString GetEmailTO();				
	CString GetEmailCC();
	CString GetEmailBCC();
	CString GetEmailSubject();
	void GetEmailText(CArray<TEXTINFO, TEXTINFO>& textArr);
	CStringArray& GetEmailFileArr();
// 2015.03.03 Ver10.9.0.2 [Remember User] Start
	void InsertUser(CWnd* editWnd);
// 2015.03.03 Ver10.9.0.2 [Remember User] End
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMAILDLG_H__7DF19A87_114D_4D2D_AA42_007BD09B2AB4__INCLUDED_)
