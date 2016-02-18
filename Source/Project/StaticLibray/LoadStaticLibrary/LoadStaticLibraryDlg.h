// LoadStaticLibraryDlg.h : header file
//

#if !defined(AFX_LOADSTATICLIBRARYDLG_H__34654842_E3AD_4E79_A44D_990F95982AF3__INCLUDED_)
#define AFX_LOADSTATICLIBRARYDLG_H__34654842_E3AD_4E79_A44D_990F95982AF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLoadStaticLibraryDlg dialog

class CLoadStaticLibraryDlg : public CDialog
{
// Construction
public:
	CLoadStaticLibraryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLoadStaticLibraryDlg)
	enum { IDD = IDD_LOADSTATICLIBRARY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadStaticLibraryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLoadStaticLibraryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADSTATICLIBRARYDLG_H__34654842_E3AD_4E79_A44D_990F95982AF3__INCLUDED_)
