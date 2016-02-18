// DownloadFileDlg.h : header file
//

#if !defined(AFX_DOWNLOADFILEDLG_H__484B3874_B97C_4DB7_9A1A_282D9321D032__INCLUDED_)
#define AFX_DOWNLOADFILEDLG_H__484B3874_B97C_4DB7_9A1A_282D9321D032__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDownloadFileDlg dialog
#include <afxinet.h>
class CDownloadFileDlg : public CDialog
{
// Construction
public:
	CDownloadFileDlg(CWnd* pParent = NULL);	// standard constructor
	~CDownloadFileDlg();
// Dialog Data
	//{{AFX_DATA(CDownloadFileDlg)
	enum { IDD = IDD_DOWNLOADFILE_DIALOG };
	CProgressCtrl	m_Progress;
	CString	m_Server;
	CString	m_maxSize;
	CString	m_curSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDownloadFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonDownload();
	afx_msg void OnMenuitemAbout();
	afx_msg void OnMenuitemSet();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strDownLoadFilePath;
	CString m_strFileName;
	CString m_strFilePath;
	CInternetSession m_session;			// Session
    CHttpFile*		m_pHttpFile;		// HttpFile
	DWORD			m_FileSize;			// FileSize
	BOOL			m_bDownLoad;		// bDownLoad
	BOOL			m_bPause;			// pause
	BOOL			m_bClose;
	HANDLE			m_handleArr[1024];
public:
	FILE*			m_pReadFile;
	DWORD			m_dwReadSize;
	DWORD			m_dwReadMaxSize;
	TCHAR*			m_szReadBuffer;
	CRITICAL_SECTION m_criticalSection;
public:
	UINT			m_nThreadCount;
	UINT			m_ReadSize;
	DWORD WINAPI ThreadFunc();
};
DWORD WINAPI _ThreadFunc(LPVOID lparam);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOADFILEDLG_H__484B3874_B97C_4DB7_9A1A_282D9321D032__INCLUDED_)
