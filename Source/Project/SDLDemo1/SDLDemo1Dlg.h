// SDLDemo1Dlg.h : header file
//

#if !defined(AFX_SDLDEMO1DLG_H__DB4A6F8C_B9C7_41C4_8EB5_0EC500DC2323__INCLUDED_)
#define AFX_SDLDEMO1DLG_H__DB4A6F8C_B9C7_41C4_8EB5_0EC500DC2323__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSDLDemo1Dlg dialog

class CSDLDemo1Dlg : public CDialog
{
// Construction
public:
	CSDLDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSDLDemo1Dlg)
	enum { IDD = IDD_SDLDEMO1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDLDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSDLDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDLDEMO1DLG_H__DB4A6F8C_B9C7_41C4_8EB5_0EC500DC2323__INCLUDED_)
