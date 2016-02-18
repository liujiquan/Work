// WriteFloppyDlg.h : header file
//

#if !defined(AFX_WRITEFLOPPYDLG_H__E0C0903B_4EA8_4DF0_97CE_A3390F835579__INCLUDED_)
#define AFX_WRITEFLOPPYDLG_H__E0C0903B_4EA8_4DF0_97CE_A3390F835579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWriteFloppyDlg dialog

class CWriteFloppyDlg : public CDialog
{
// Construction
public:
	CWriteFloppyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteFloppyDlg)
	enum { IDD = IDD_WRITEFLOPPY_DIALOG };
	CComboBox	m_FloppyCmb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteFloppyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
private:
	CBitmap m_bitmap;
	// Generated message map functions
	//{{AFX_MSG(CWriteFloppyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONWriteFloppy();
	afx_msg void OnBUTTONWriteImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEFLOPPYDLG_H__E0C0903B_4EA8_4DF0_97CE_A3390F835579__INCLUDED_)
