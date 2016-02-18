#if !defined(AFX_INTERNETACCOUNTS_H__9A0FA9E8_8FC6_4F46_91B3_6A3FF5D69FA7__INCLUDED_)
#define AFX_INTERNETACCOUNTS_H__9A0FA9E8_8FC6_4F46_91B3_6A3FF5D69FA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InternetAccounts.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CInternetAccounts dialog
#include "MailUtil.h"

class CInternetAccounts : public CDialog
{
// Construction
public:
	CInternetAccounts(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInternetAccounts)
	enum { IDD = IDD_DIALOG_ACCOUNT };
	CListCtrl	m_AccountList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInternetAccounts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInternetAccounts)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonModify();
	afx_msg void OnClose();
	afx_msg void OnButtonDelete();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void InitAccountListInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERNETACCOUNTS_H__9A0FA9E8_8FC6_4F46_91B3_6A3FF5D69FA7__INCLUDED_)
