// ReadBinaryCodeDlg.h : header file
//

#if !defined(AFX_READBINARYCODEDLG_H__FBFD4EA3_18BC_44C2_9141_A50738FADE42__INCLUDED_)
#define AFX_READBINARYCODEDLG_H__FBFD4EA3_18BC_44C2_9141_A50738FADE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DropFileEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CReadBinaryCodeDlg dialog

class CReadBinaryCodeDlg : public CDialog
{
// Construction
public:
	CReadBinaryCodeDlg(CWnd* pParent = NULL);	// standard constructor
	~CReadBinaryCodeDlg();
// Dialog Data
	//{{AFX_DATA(CReadBinaryCodeDlg)
	enum { IDD = IDD_READBINARYCODE_DIALOG };
	CDropFileEdit	m_FilePath;
	UINT	m_LineSize;
	CString	m_BaseAddr;
	CString	m_ReadSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadBinaryCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CReadBinaryCodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEditFilepath();
	afx_msg void OnBUTTONFlush();
	afx_msg void OnBUTTONCreateFile();
	afx_msg void OnBUTTONOpenProcess();
	afx_msg void OnButtonAssem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_newFileName;
	CString m_strFileName;
	CString m_strFilePath;
	TCHAR*	m_FileMemory;
	DWORD	m_FileSize;
    BOOL    m_bOpenProcess;
public:
	LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	BOOL _OpenFile(LPCTSTR pszFileName);
	void InitMemoryInfo(LPCTSTR pBuffer, DWORD nSize, DWORD dwBaseAddr = 0x00);

	BOOL ReleaseNasmExe();
	void DeleteNasmExe();
};
/************************************************************************/
/* Function                                                             */
/************************************************************************/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READBINARYCODEDLG_H__FBFD4EA3_18BC_44C2_9141_A50738FADE42__INCLUDED_)
