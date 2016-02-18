#if !defined(AFX_INSERTUSER_H__3C8898C8_6F82_4774_97E6_BE82052E198C__INCLUDED_)
#define AFX_INSERTUSER_H__3C8898C8_6F82_4774_97E6_BE82052E198C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertUser dialog

class CInsertUser : public CDialog
{
// Construction
public:
	CInsertUser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertUser)
	enum { IDD = IDD_DIALOG_INSERTUSER };
	CListBox	m_FromList;
	CListBox	m_ToList;
	CString		m_UserInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertUser)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkLISTFrom();
	afx_msg void OnDblclkLISTTo();
	afx_msg void OnButtonDel();
	afx_msg void OnButtonAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTUSER_H__3C8898C8_6F82_4774_97E6_BE82052E198C__INCLUDED_)
