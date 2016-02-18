// PlayRadioDlg.h : header file
//
//{{AFX_INCLUDES()
#include "wmpplayer4.h"
//}}AFX_INCLUDES

#if !defined(AFX_PLAYRADIODLG_H__8B578E6A_C4F7_4232_B1B7_9B5235077DCF__INCLUDED_)
#define AFX_PLAYRADIODLG_H__8B578E6A_C4F7_4232_B1B7_9B5235077DCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPlayRadioDlg dialog
#include <WINSOCK2.H>
class CPlayRadioDlg : public CDialog
{
// Construction
public:
	CPlayRadioDlg(CWnd* pParent = NULL);	// standard constructor
	~CPlayRadioDlg();
// Dialog Data
	//{{AFX_DATA(CPlayRadioDlg)
	enum { IDD = IDD_PLAYRADIO_DIALOG };
	CWMPPlayer4	m_PlayCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayRadioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlayRadioDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton_Download();
	afx_msg void OnButton4();
	afx_msg void OnButtonClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BOOL		m_bRunning;
	HANDLE		m_hThread;
	static DWORD WINAPI _ThreadFunc(LPVOID lparam);
	DWORD WINAPI ThreadFunc();	

	BOOL		m_bDownloading;
	HANDLE		m_hDownloadThread;
	static DWORD WINAPI _DownloadThreadFunc(LPVOID lparam);
	DWORD WINAPI DownloadThreadFunc();

private:
	SOCKET m_ServerSock;
	DWORD  m_dwRecvMaxCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYRADIODLG_H__8B578E6A_C4F7_4232_B1B7_9B5235077DCF__INCLUDED_)
