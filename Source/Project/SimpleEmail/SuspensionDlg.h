#if !defined(AFX_SUSPENSIONDLG_H__7A8A15D3_C50A_4341_8CB3_142844346CE7__INCLUDED_)
#define AFX_SUSPENSIONDLG_H__7A8A15D3_C50A_4341_8CB3_142844346CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SuspensionDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuspensionDlg dialog

class CSuspensionDlg : public CDialog
{
public:
	CRect	m_rect;
	CString m_InserUser;
public:
	void SetPos(CRect rect);
// Construction
public:
	CSuspensionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSuspensionDlg)
	enum { IDD = IDD_DIALOG_Suspension };
	CListBox	m_ShowList;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuspensionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSuspensionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUSPENSIONDLG_H__7A8A15D3_C50A_4341_8CB3_142844346CE7__INCLUDED_)
