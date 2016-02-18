// SendMailDlg.h : header file
//

#if !defined(AFX_SENDMAILDLG_H__0925E660_9FBE_4227_9353_62F9464E5838__INCLUDED_)
#define AFX_SENDMAILDLG_H__0925E660_9FBE_4227_9353_62F9464E5838__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg dialog
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class CSendMailDlg : public CDialog
{
// Construction
public:
	CSendMailDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSendMailDlg)
	enum { IDD = IDD_SENDMAIL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSendmail();
	afx_msg void OnButtonFind();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CString m_Server;
    int m_Port;
    CString m_From;
    CString m_To;
    CString m_UserName;
    CString m_Pwd;
    CString m_Title;
    CString m_Data;
    CListBox m_Info;
private:
    SOCKET server;
    struct sockaddr_in ServerAddr;
	public:
	void Init();
	void Connect();
	void Login();
	void SendBegin();
	void SendText();
	void SendFile();
    void SendEnd();

	void SendSmaple();
	void FindJpgFile(CString strPath, CString  strFilter);
	void SendFile2(CString strFileName);
	void SendFile3(CString strFileName, CString strFilePath);


	void SendPrepare();
	void SendTextAndFile();
};
//////////////////////////////////////////////////////////////////////////
BOOL SendData(SOCKET sock, LPCTSTR szBuffer);
int GetStatus(SOCKET sock);
DWORD ToBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len);
CString GetBasp64(CString strSrc );


#define DATA    "From: <%s>\r\n\
To: <%s>\r\n\
Date: %s\r\n\
Subject:%s\r\n\
Mime-Version: 1.0\r\n\
Content-Type: multipart/mixed; boundary=\"INVT\"\r\n"

//Send 
#define DATA_TEXT   "--INVT\r\n\
Content-type: text/plain;charset=\"UTF-8\"\r\n\r\n\
      %s\r\n"

  //Send 
#define DATA_FILE   "--INVT\r\n\
Content-type: application/octet-stream;\r\n\
Content-Transfer-Encoding: basp64;\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"

#define DATA_FILE3   "--INVT\r\n\
Content-type: image/jpeg;\r\n\
Content-Transfer-Encoding: binary;\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"

#define DATA_TEXT_FILE   "--INVT\r\n\
Content-type: application/octet-stream;\r\n\
Content-Transfer-Encoding: basp64;\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"

#define DATA_TEXT_FILE2   "--INVT\r\n\
Content-type: application/octet-stream;\r\n\
  name=\"%s\"\r\n\
Content-Transfer-Encoding: basp64\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"

#define DATA_PREPARE \
"HELO 10.10.1.9\r\n\
AUTO LOGIN\r\n\
MAIL FROM: <liujiquan@ase.com.cn>\r\n\
RCPT TO: <liujiquan@ase.com.cn>\r\n\
DATA\r\n\
From: <liujiquan@ase.com.cn>\r\n\
To: <liujiquan@ase.com.cn>\r\n\
Date: 2014/09/26 11:16\r\n\
Subject:One Mail\r\n\
Mime-Version: 1.0\r\n\
Content-Type: multipart/mixed; boundary=\"INVT\"\r\n"







		

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMAILDLG_H__0925E660_9FBE_4227_9353_62F9464E5838__INCLUDED_)
