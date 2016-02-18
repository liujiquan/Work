// TesWinBrowseDlg.h : header file
//

#if !defined(AFX_TESWINBROWSEDLG_H__3B419BD2_AFC3_4A70_89B5_545BA8F01AB2__INCLUDED_)
#define AFX_TESWINBROWSEDLG_H__3B419BD2_AFC3_4A70_89B5_545BA8F01AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTesWinBrowseDlg dialog

class CTesWinBrowseDlg : public CDialog
{
// Construction
public:
	CTesWinBrowseDlg(CWnd* pParent = NULL);	// standard constructor
	~CTesWinBrowseDlg();
// Dialog Data
	//{{AFX_DATA(CTesWinBrowseDlg)
	enum { IDD = IDD_TESWINBROWSE_DIALOG };
	CString	m_strFilePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesWinBrowseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTesWinBrowseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESWINBROWSEDLG_H__3B419BD2_AFC3_4A70_89B5_545BA8F01AB2__INCLUDED_)
