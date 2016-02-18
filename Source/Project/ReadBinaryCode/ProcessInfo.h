#if !defined(AFX_PROCESSINFO_H__77B3685F_CB06_4EC4_989D_8F4823C59035__INCLUDED_)
#define AFX_PROCESSINFO_H__77B3685F_CB06_4EC4_989D_8F4823C59035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcessInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessInfo dialog
class CProcessInfo : public CDialog
{
// Construction
public:
	CProcessInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessInfo)
	enum { IDD = IDD_DIALOG_POOCESS };
	CListCtrl	m_ProcessList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProcessInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONFlush();
	afx_msg void OnOK();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void GetProcessInfo();
	CString m_strProcessName;
	CString m_strProcessPath;
	DWORD m_dwThreadID;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCESSINFO_H__77B3685F_CB06_4EC4_989D_8F4823C59035__INCLUDED_)
