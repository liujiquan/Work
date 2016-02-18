// FormatBinaryCodeDlg.h : header file
//

#if !defined(AFX_FORMATBINARYCODEDLG_H__6AB412B5_1F4B_4CF5_8E36_72A4466E842C__INCLUDED_)
#define AFX_FORMATBINARYCODEDLG_H__6AB412B5_1F4B_4CF5_8E36_72A4466E842C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFormatBinaryCodeDlg dialog
#include "MyEdit.h"
class CFormatBinaryCodeDlg : public CDialog
{
// Construction
public:
	CFormatBinaryCodeDlg(CWnd* pParent = NULL);	// standard constructor
	~CFormatBinaryCodeDlg();
// Dialog Data
	//{{AFX_DATA(CFormatBinaryCodeDlg)
	enum { IDD = IDD_FORMATBINARYCODE_DIALOG };
	CMyEdit	m_Edit2;
	CMyEdit	m_Edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatBinaryCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFormatBinaryCodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL ReleaseNasmExe();
	void DeleteNasmExe();
	LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	void DoSomeThing();
private:
	CString m_strFileName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATBINARYCODEDLG_H__6AB412B5_1F4B_4CF5_8E36_72A4466E842C__INCLUDED_)
