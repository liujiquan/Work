// AccountInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "AccountInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountInfo dialog


CAccountInfo::CAccountInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountInfo)
	m_DisplayName = _T("");
	m_EmaiAddr = _T("");
	m_SendServer = _T("");
	m_RecvServer = _T("");
	m_sendPort = 0;
	m_recvPort = 0;
	m_UserName = _T("");
	m_Pwd = _T("");
	m_nFlag = 0;
	//}}AFX_DATA_INIT

	memset(&m_AccountInfo, 0x00, sizeof(m_AccountInfo));
}


void CAccountInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountInfo)
	DDX_Text(pDX, IDC_EDIT1, m_DisplayName);
	DDX_Text(pDX, IDC_EDIT2, m_EmaiAddr);
	DDX_Text(pDX, IDC_EDIT3, m_SendServer);
	DDX_Text(pDX, IDC_EDIT4, m_RecvServer);
	DDX_Text(pDX, IDC_EDIT5, m_sendPort);
	DDX_Text(pDX, IDC_EDIT6, m_recvPort);
	DDX_Text(pDX, IDC_EDIT7, m_UserName);
	DDX_Text(pDX, IDC_EDIT8, m_Pwd);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CAccountInfo, CDialog)
	//{{AFX_MSG_MAP(CAccountInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CAccountInfo message handlers
// -----------------------------------------------------------//
// Function :   CAccountInfo::OnInitDialog
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CAccountInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(m_nFlag == 0)	// add
	{
		m_DisplayName = _T("For example: Zhangsan.");
		m_EmaiAddr = _T("For example: someone@gmail.com");
		m_SendServer = _T("For example: smtp.qq.com");
		m_RecvServer = _T("For example: pop.qq.com");
//		GetDlgItem(IDC_EDIT5)->SetWindowText("For example: 25");
		m_sendPort = 25;
//		GetDlgItem(IDC_EDIT6)->SetWindowText("For example: 110");
		m_recvPort = 110;
		m_UserName = _T("For example: Zhangsan123");
		m_Pwd = _T("For example: kkkk1234");

		GetDlgItem(IDOK)->SetWindowText("Add");
	}
	else if(m_nFlag == 1)
	{
		m_DisplayName.Format("%s", m_AccountInfo.szDisplayName);
		m_EmaiAddr.Format("%s", m_AccountInfo.szE_mailAddress);
		m_SendServer.Format("%s", m_AccountInfo.szSendServer);
		m_RecvServer.Format("%s", m_AccountInfo.szRecvServer);
		m_sendPort = m_AccountInfo.nSendPort;
		m_recvPort = m_AccountInfo.nRecvPort;
		m_UserName.Format("%s", m_AccountInfo.szUserName);
		m_Pwd.Format("%s", m_AccountInfo.szPwd);

		GetDlgItem(IDOK)->SetWindowText("Modify");
	}				// Modify
	else
		return FALSE;

	UpdateData(FALSE);

	return TRUE;  
}

// -----------------------------------------------------------//
// Function :   CAccountInfo::SetAccountInfo
// Param    :   Account& account
//              int nFlag
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CAccountInfo::SetAccountInfo(Account& account, int nFlag)
{
	memcpy(&m_AccountInfo, &account, sizeof(Account));
	m_nFlag = nFlag;
}

void CAccountInfo::OnOK() 
{
	UpdateData(TRUE);
	if(m_sendPort == 0 || m_recvPort == 0)	
	{
		MessageBox("Port is 0.");
		return;
	}
	memset(&m_AccountInfo, 0x00, sizeof(Account));
	//displayName
	memcpy(m_AccountInfo.szDisplayName, m_DisplayName, strlen(m_DisplayName) > DISPLAYNAMELEN ? DISPLAYNAMELEN : strlen(m_DisplayName));
	// emailaddress
	memcpy(m_AccountInfo.szE_mailAddress, m_EmaiAddr, strlen(m_EmaiAddr) > EMAILADDRESSLEN ? EMAILADDRESSLEN : strlen(m_EmaiAddr));
	// sendserver
	memcpy(m_AccountInfo.szSendServer, m_SendServer, strlen(m_SendServer) > SERVERLEN ? SERVERLEN : strlen(m_SendServer));
	// recvserver
	memcpy(m_AccountInfo.szRecvServer, m_RecvServer, strlen(m_RecvServer) > SERVERLEN ? SERVERLEN : strlen(m_RecvServer));
	// sendport
	m_AccountInfo.nSendPort = m_sendPort;
	// recvport
	m_AccountInfo.nRecvPort = m_recvPort;
	// username
	memcpy(m_AccountInfo.szUserName, m_UserName, strlen(m_UserName) > NAMEPWDLEN ? NAMEPWDLEN : strlen(m_UserName));
	// pwd
	memcpy(m_AccountInfo.szPwd, m_Pwd, strlen(m_Pwd) > NAMEPWDLEN ? NAMEPWDLEN : strlen(m_Pwd));

	CDialog::OnOK();
}
