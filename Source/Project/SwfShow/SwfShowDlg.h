// SwfShowDlg.h : header file
//

#if !defined(AFX_SWFSHOWDLG_H__6B2E0BC6_F004_4DDD_B87C_48443F3DC1C4__INCLUDED_)
#define AFX_SWFSHOWDLG_H__6B2E0BC6_F004_4DDD_B87C_48443F3DC1C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "swfutil.h"
/////////////////////////////////////////////////////////////////////////////
// CSwfShowDlg dialog

class CSwfShowDlg : public CDialog
{
// Construction
public:
	CSwfShowDlg(CWnd* pParent = NULL);	// standard constructor
	~CSwfShowDlg();
// Dialog Data
	//{{AFX_DATA(CSwfShowDlg)
	enum { IDD = IDD_SWFSHOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwfShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSwfShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONOpenFile();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMySuperGrid	m_SuperGrid;

	TCHAR	m_szFileName[MAX_PATH];		// FileName
	long	m_dwFileSize;				// FileSize
	BYTE*	m_szBuffer;					// buffer
public:
	void AnalyzeSwf();
	int ReadHeader(BYTE buffer[]);
	int ReadTagInfo(BYTE buffer[], int nHeaderSize);
	//BOOL UnCompressFile();
	void InitGridColumn();	
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWFSHOWDLG_H__6B2E0BC6_F004_4DDD_B87C_48443F3DC1C4__INCLUDED_)
