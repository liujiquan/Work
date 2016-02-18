// SaoleiDlg.h : header file
//

#if !defined(AFX_SAOLEIDLG_H__A85E0EB7_88C1_4D89_9DFC_189D467BB185__INCLUDED_)
#define AFX_SAOLEIDLG_H__A85E0EB7_88C1_4D89_9DFC_189D467BB185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSaoleiDlg dialog

class CSaoleiDlg : public CDialog
{
// Construction
public:
	CSaoleiDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSaoleiDlg)
	enum { IDD = IDD_SAOLEI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaoleiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSaoleiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAOLEIDLG_H__A85E0EB7_88C1_4D89_9DFC_189D467BB185__INCLUDED_)
