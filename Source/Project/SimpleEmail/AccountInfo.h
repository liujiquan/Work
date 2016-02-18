#if !defined(AFX_ACCOUNTINFO_H__1C7C578F_1F20_4DA2_85EB_FDCCF4F14705__INCLUDED_)
#define AFX_ACCOUNTINFO_H__1C7C578F_1F20_4DA2_85EB_FDCCF4F14705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccountInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccountInfo dialog
#include "MailUtil.h"
class CAccountInfo : public CDialog
{
// Construction
public:
	CAccountInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountInfo)
	enum { IDD = IDD_DIALOG_ACCOUNTINFO };
	CString	m_DisplayName;
	CString	m_EmaiAddr;
	CString	m_SendServer;
	CString	m_RecvServer;
	int		m_sendPort;
	int		m_recvPort;
	CString	m_UserName;
	CString	m_Pwd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountInfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	Account m_AccountInfo;
	int		m_nFlag;					// 0 Add 1Modify
public:
	void SetAccountInfo(Account& account, int nFlag = 0);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTINFO_H__1C7C578F_1F20_4DA2_85EB_FDCCF4F14705__INCLUDED_)
