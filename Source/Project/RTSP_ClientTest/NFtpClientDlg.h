// NFtpClientDlg.h : header file
//

#if !defined(AFX_NFTPCLIENTDLG_H__36193287_A9C4_4CF7_98E7_13DE4BA7A826__INCLUDED_)
#define AFX_NFTPCLIENTDLG_H__36193287_A9C4_4CF7_98E7_13DE4BA7A826__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
// CNFtpClientDlg dialog

class CNFtpClientDlg : public CDialog
{
// Construction
public:
	CNFtpClientDlg(CWnd* pParent = NULL);	// standard constructor
	void StartUp();
	void CleanUp();
// Dialog Data
	//{{AFX_DATA(CNFtpClientDlg)
	enum { IDD = IDD_NFTPCLIENT_DIALOG };
	CString	m_strUser;
	CString	m_strPass;
	CString	m_strIP;
	CString	m_strDownPara;
	CString	m_strGetdPara;
	CString	m_strGetpPara;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNFtpClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNFtpClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnGetd();
	afx_msg void OnGetp();
	afx_msg void OnDown();
	afx_msg void OnAbort();
	afx_msg void OnQuit();
	virtual void OnCancel();
	afx_msg void OnSendData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	SOCKET m_hSocket;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NFTPCLIENTDLG_H__36193287_A9C4_4CF7_98E7_13DE4BA7A826__INCLUDED_)
