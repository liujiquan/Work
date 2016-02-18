// SendMailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SendMail.h"
#include "SendMailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg dialog

CSendMailDlg::CSendMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendMailDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata) !=0)  {   return;}
    server = INVALID_SOCKET;
}

void CSendMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMailDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX, IDC_EDIT_MAILSERVER, m_Server);
    DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
    DDX_Text(pDX, IDC_EDIT_FROM, m_From);
    DDX_Text(pDX, IDC_EDIT_TO, m_To);
    DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
    DDX_Text(pDX, IDC_EDIT_Pwd, m_Pwd);
    DDX_Text(pDX, IDC_EDIT_Title, m_Title);
    DDX_Text(pDX, IDC_EDIT_Data, m_Data);
    DDX_Control(pDX, IDC_LIST1, m_Info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSendMailDlg, CDialog)
	//{{AFX_MSG_MAP(CSendMailDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SENDMAIL, OnButtonSendmail)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMailDlg message handlers

BOOL CSendMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Server    = "10.10.1.9";
    m_From      = "liujiquan@ase.com.cn";
    m_To        = "liujiquan@ase.com.cn";
    m_Port      = 25;
    m_Data      = "Hello Word";
    m_Title     = "One Mail";
    m_Data      = "Our";
    m_UserName  = "Jiquan Liu/ASECN";
    m_Pwd       = "ase_123";
	
    UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSendMailDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSendMailDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSendMailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::OnButtonSendmail
// Return   :   void
// Comment  :   Sendmail
// -----------------------------------------------------------//
void CSendMailDlg::OnButtonSendmail() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    Init();
    Connect();
//    Login();
//    SendBegin();
//	SendText();
//	FindJpgFile("C:\\Work\\Pic\\", "*.txt");
//	SendFile();
//	SendFile();	
	
	SendPrepare();
	SendTextAndFile();
	SendEnd();
	
    UpdateData(FALSE);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::Init
// Return   :   void
// Comment  :   Init
// -----------------------------------------------------------//
void CSendMailDlg::Init()
{
    UpdateData(TRUE);
    if(server == INVALID_SOCKET)
    {
        server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 
        if(INVALID_SOCKET!=server)
            m_Info.AddString("server successful");
        else
            m_Info.AddString("server failure");

        struct hostent *pHostent = gethostbyname(m_Server);
        if(NULL!=pHostent)
            m_Info.AddString("pHostent successful");
        else
            m_Info.AddString("pHostent failure");

        ServerAddr.sin_family=AF_INET; 
        memcpy(&ServerAddr.sin_addr.S_un.S_addr,pHostent->h_addr_list[0],pHostent->h_length);
        ServerAddr.sin_port=htons((u_short )m_Port);
    }
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::Connect
// Return   :   void
// Comment  :   Connect
// -----------------------------------------------------------//
void CSendMailDlg::Connect()
{
    TCHAR szBuffer[MAX_PATH*10] = {0};
    int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
    if(nRet == -1)
    {
        m_Info.AddString("connect Failed");
        closesocket(server);
        return ;
    }
    nRet = GetStatus(server);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::Login
// Return   :   void
// Comment  :   Login
// -----------------------------------------------------------//
void CSendMailDlg::Login()
{
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //Hello
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "HELO %s\r\n", m_Server);
    SendData(server,szBuffer);
    int nRet = GetStatus(server);//250
    //auto login
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "AUTO LOGIN\r\n");
    SendData(server,szBuffer);
    nRet = GetStatus(server);//500
  /*  //4 Send UserName
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "%s\r\n", GetBasp64(m_UserName));
    SendData(server,szBuffer);
    nRet = GetStatus(server);//500
    //5 Send PassWord
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "%s\r\n", GetBasp64(m_Pwd));
    SendData(server,szBuffer);
    nRet = GetStatus(server);
*/
 }

// -----------------------------------------------------------//
// Function :   CSendMailDlg::SendBegin
// Return   :   void
// Comment  :   SendBegin
// -----------------------------------------------------------//
void CSendMailDlg::SendBegin()
{
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //1
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "MAIL FROM: <%s>\r\n", m_From);
    SendData(server,szBuffer);
    int nRet = GetStatus(server);//250
    //2
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "RCPT TO: <%s>\r\n", m_To);
    SendData(server,szBuffer);
    nRet = GetStatus(server);//250
    //3
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "DATA\r\n");
    SendData(server,szBuffer);
    nRet = GetStatus(server);//354
    //4
    memset(szBuffer, 0x0, MAX_PATH*10);
    CTime time = CTime::GetCurrentTime();
    CString str = time.Format("%Y/%m/%d %H:%M");
    sprintf(szBuffer, DATA, m_From, m_To, str, m_Title);
    SendData(server,szBuffer);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::SendText
// Return   :   void
// Comment  :   SendText
// -----------------------------------------------------------//
void CSendMailDlg::SendText()
{
    int nRet = 0;
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //1
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, DATA_TEXT, m_Data);
    SendData(server,szBuffer);
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::SendFile
// Return   :   void
// Comment  :   SendFile
// -----------------------------------------------------------//
void CSendMailDlg::SendFile()
{
    int nRet = 0;
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //1
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, DATA_FILE, "123.txt");
    SendData(server,szBuffer);
    SendData(server,"nihao");
	SendData(server,"nihao");
	SendData(server,"nihao");
	SendData(server,"nihao");
	SendData(server,"nihao");
	//End
	SendData(server,"\r\n");
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::SendEnd
// Return   :   void
// Comment  :   SendEnd
// -----------------------------------------------------------//
void CSendMailDlg::SendEnd()
{
    TCHAR szBuffer[MAX_PATH*10] = {0};
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, ".\r\nQUIT\r\n");
    SendData(server,szBuffer);
    int nRet = GetStatus(server);
}

void CSendMailDlg::SendPrepare()
{
	TCHAR szBuffer[MAX_PATH*10] = {0};
	//1
	memset(szBuffer, 0x0, MAX_PATH*10);
	sprintf(szBuffer, DATA_PREPARE);
	SendData(server,szBuffer);

}

void CSendMailDlg::SendTextAndFile()
{
	SendText();
	FindJpgFile("C:\\Work\\Pic\\", "*.txt");
}


//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------//
// Function :   SendData
// Param    :   SOCKET sock
//              LPCTSTR szBuffer
// Return   :   BOOL
// Comment  :   SendData
// -----------------------------------------------------------//
BOOL SendData(SOCKET sock, LPCTSTR szBuffer)
{
    if(sock == INVALID_SOCKET)  return FALSE;
    int nRet = send(sock, szBuffer, (int)strlen(szBuffer), 0);
    if(nRet <= 0)
    {
        closesocket(sock);
        return FALSE;
    }
    return TRUE;
}

// -----------------------------------------------------------//
// Function :   GetStatus
// Param    :   SOCKET sock
// Return   :   int
// Comment  :   GetStatus
// -----------------------------------------------------------//
int GetStatus(SOCKET sock)
{
   TCHAR szBuffer[MAX_PATH*10] = {0};
    if(sock == INVALID_SOCKET)  return FALSE;

    int nRet = recv(sock, szBuffer, MAX_PATH*10, 0);
    if(nRet <= 0)
    {
        closesocket(sock);
        return 0;
    } 
    TCHAR szStatus[3] = {0};
    memcpy(szStatus, szBuffer, 3);
    return atoi(szStatus);

	return 0;
}

// -----------------------------------------------------------//
// Function :   ToBase64
// Param    :   LPTSTR pszBase64
//              LPCTSTR pszSource
//              int len
// Return   :   void
// Comment  :   BASE64 
// -----------------------------------------------------------//
DWORD ToBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len)
{
    if(len <= 0 || pszSource == NULL)   return -1;
    int nCount = 0;
    static char BASE64CODE[] = 
    {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    };

    int nSize = len % 3 == 0 ? len/3 : len/3+1;
    for(int i = 0; i < nSize ; i++)
    {
        TCHAR cSrc0,cSrc1,cSrc2;
        TCHAR cDest0,cDest1,cDest2,cDest3;
        if(i*3+1 == len)
        {
            cSrc0 = pszSource[i*3];

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         //
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)];                 //
            cDest2 = '=';
            cDest3 = '=';
        }
        else if(i*3+2 == len)
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)];                   
            cDest3 = '=';
        }
        else
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
            cSrc2 = pszSource[i*3+2];   

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)|(cSrc2>>6)];        
            cDest3 = BASE64CODE[(cSrc2 & 0x3f)];                      
        } 

        pszBase64[nCount++] = cDest0;
        pszBase64[nCount++] = cDest1;
        pszBase64[nCount++] = cDest2;
        pszBase64[nCount++] = cDest3;
    }

	return nCount;
}

// -----------------------------------------------------------//
// Function :   GetBasp64
// Param    :   CString strSrc
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetBasp64(CString strSrc )
{
    TCHAR szBuffer[1024] = {0};
    ToBase64(szBuffer, strSrc.GetBuffer(0), strSrc.GetLength());
    
    CString str(szBuffer);
    return str;
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::OnButtonFind
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
#include <io.h>
void CSendMailDlg::OnButtonFind() 
{
	// TODO: Add your control notification handler code here
	char* szFile = "C:\\*.jpg";
	CString strPath = "C:\\Work\\Pic\\";
	CString strFilter = "*.jpg";
	FindJpgFile(strPath, strFilter);
}

void CSendMailDlg::FindJpgFile(CString strPath, CString  strFilter)
{
	if(strPath.IsEmpty() || strFilter.IsEmpty())
	{
		return;
	}
	
	BOOL bRet = TRUE;
	WIN32_FIND_DATA findData;
	//1:Find File
	long handle = (long)::FindFirstFile(strPath+strFilter, &findData);	
	if(handle != 0xFFFFFFFF)
	{
		while(bRet)
		{
			m_Info.AddString(strPath+findData.cFileName);
//			SendFile2(strPath+findData.cFileName);
			SendFile3(findData.cFileName, strPath+findData.cFileName);
			bRet = FindNextFile((HANDLE)handle, &findData);
		}
		FindClose((HANDLE)handle);
	}
	//2:Find Dir
	bRet = TRUE;
	CString AllFile = "*.*";
	handle = (long)::FindFirstFile(strPath+AllFile, &findData);
	if(handle != 0xFFFFFFFF)
	{
		while(bRet)
		{	
			if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY &&(findData.cFileName[0] != '.'))
			{
				FindJpgFile(strPath+findData.cFileName+"\\", strFilter);
			}
			bRet = FindNextFile((HANDLE)handle, &findData);
		}
		FindClose((HANDLE)handle);
	}
}

void CSendMailDlg::SendFile2(CString strFilePath)
{
	TCHAR szBuffer[MAX_PATH*10] = {0};

	//Send FileName
	sprintf(szBuffer, DATA_FILE3, strFilePath);
	SendData(server,szBuffer);
	//Send Context
	FILE *hFile = NULL;
	hFile = fopen(strFilePath, "rb");
	if(hFile)
	{
		memset(szBuffer, 0x0, MAX_PATH*10);
		int nRead = (int)fread(szBuffer, sizeof(TCHAR), MAX_PATH*10, hFile);
		while(nRead > 0)
		{	
			int nRet = send(server, szBuffer, nRead, 0);
			nRead = (int)fread(szBuffer, sizeof(TCHAR), MAX_PATH*10, hFile);
		}
		fclose(hFile);
	}
}

// -----------------------------------------------------------//
// Function :   CSendMailDlg::SendFile3
// Param    :   CString strFileName
//              CString strFilePath
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSendMailDlg::SendFile3(CString strFileName, CString strFilePath)
{
	TCHAR szBuffer[MAX_PATH*10] = {0};
	//Send FileName
	sprintf(szBuffer, DATA_FILE, strFileName);
	//1: Send Begin
	SendData(server,szBuffer);
	//Send Context
	//Send Data
	HANDLE handle = CreateFile(strFilePath, 
		GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(handle != INVALID_HANDLE_VALUE)
	{
		memset(szBuffer, 0x0, MAX_PATH*10);
		DWORD nRead = 0;
		BOOL bRet = ReadFile(handle, szBuffer, MAX_PATH*10, &nRead, NULL);
		while(bRet && nRead > 0)
		{
			int nRet = send(server, szBuffer, nRead, 0);
			bRet = ReadFile(handle, szBuffer, MAX_PATH*10, &nRead, NULL);
		}
		CloseHandle(handle);
	}	
	// Send End
	SendData(server,"\r\n");
}
