// CMailDemo3Dlg.h : ヘッダー ファイル
//
#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class CCMailDemo3Dlg : public CDialog
{
public:
	CCMailDemo3Dlg(CWnd* pParent = NULL);	
	enum { IDD = IDD_CMAILDEMO3_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
// 実装
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
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
    afx_msg void OnBnClickedButton1();
};

BOOL SendData(SOCKET sock, LPCTSTR szBuffer);
int GetStatus(SOCKET sock);
void ToBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len);
CString GetBasp64(CString strSrc );

#define DATA    "From: <%s>\r\n\
To: <%s>\r\n\
Date: %s\r\n\
Subject:%s\r\n\
Mime-Version: 1.0\r\n\
Content-Type: multipart/mixed; boundary=\"INVT\"\r\n"

#define DATA_TEXT   "--INVT\r\n\
Content-type: text/plain\r\n\r\n\
%s\r\n\r\n"
//charset=\"gb2312\"\r\n\r\n\


#define DATA_FILE   "--INVT\r\n\
Content-type: application/octet-stream;\r\n\
  name=\"%s\"\r\n\
Content-Transfer-Encoding: basp64\r\n\
Content-Disposition: attachment;\r\n\
  filename=\"%s\"\r\n\r\n"

