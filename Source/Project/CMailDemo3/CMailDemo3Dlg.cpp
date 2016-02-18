// CMailDemo3Dlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CMailDemo3.h"
#include "CMailDemo3Dlg.h"
#include ".\cmaildemo3dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMailDemo3Dlg ダイアログ



CCMailDemo3Dlg::CCMailDemo3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCMailDemo3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata) !=0)  {   return;}
    server = INVALID_SOCKET;
}

void CCMailDemo3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MAILSERVER, m_Server);
    DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
    DDX_Text(pDX, IDC_EDIT_FROM, m_From);
    DDX_Text(pDX, IDC_EDIT_TO, m_To);
    DDX_Text(pDX, IDC_EDIT_UserName, m_UserName);
    DDX_Text(pDX, IDC_EDIT_Pwd, m_Pwd);
    DDX_Text(pDX, IDC_EDIT_Title, m_Title);
    DDX_Text(pDX, IDC_EDIT_Data, m_Data);
    DDX_Control(pDX, IDC_LIST1, m_Info);
}

BEGIN_MESSAGE_MAP(CCMailDemo3Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CCMailDemo3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);		

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
	return TRUE;
}

void CCMailDemo3Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCMailDemo3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// -----------------------------------------------------------//
// Function:    CCMailDemo3Dlg::Init
// Param                
// Return  :    void 
// meaning :    
// -----------------------------------------------------------//
void CCMailDemo3Dlg::Init()
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
// Function:    CCMailDemo3Dlg::Connect
// Param                
// Return  :    void 
// meaning :    
// -----------------------------------------------------------//
void CCMailDemo3Dlg::Connect()
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

void CCMailDemo3Dlg::Login()
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
    //4 Send UserName
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "%s\r\n", GetBasp64(m_UserName));
    SendData(server,szBuffer);
    nRet = GetStatus(server);//500
    //5 Send PassWord
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "%s\r\n", GetBasp64(m_Pwd));
    SendData(server,szBuffer);
    nRet = GetStatus(server);
}

void CCMailDemo3Dlg::SendBegin()
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

void CCMailDemo3Dlg::SendText()
{
    int nRet = 0;
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //1
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, DATA_TEXT, m_Data);
    SendData(server,szBuffer);
}

void CCMailDemo3Dlg::SendFile()
{
    int nRet = 0;
    TCHAR szBuffer[MAX_PATH*10] = {0};
    //1
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, DATA_FILE, "123.txt","234.txt");
//    sprintf(szBuffer, "", "123.txt","234.txt");
    SendData(server,szBuffer);
    SendData(server,"nihao\r\n");
}

void CCMailDemo3Dlg::SendEnd()
{
    TCHAR szBuffer[MAX_PATH*10] = {0};
    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "--INVT--\r\n.\r\n");
    SendData(server,szBuffer);

    memset(szBuffer, 0x0, MAX_PATH*10);
    sprintf(szBuffer, "QUIT\r\n");
    SendData(server,szBuffer);
    int nRet = GetStatus(server);
}

void CCMailDemo3Dlg::OnBnClickedButton1()
{
    UpdateData(TRUE);
    Init();
    Connect();
    Login();
    SendBegin();
    SendText();
    SendFile();
    SendFile();
    SendEnd();

    UpdateData(FALSE);
}
//////////////////////////////////////////////////////////////////////////
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
}

void ToBase64(LPTSTR pszBase64, LPCTSTR pszSource, int len)
{
    if(len <= 0 || pszSource == NULL)   return;
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

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         // 取高6位 
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)];                 // 取第一個字符低2位
            cDest2 = '=';
            cDest3 = '=';
        }
        else if(i*3+2 == len)
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         // 取高6位 
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      // 取第一個字符低2位
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)];                   // 取第一個字符低4位+第二個字符高2位
            cDest3 = '=';
        }
        else
        {
            cSrc0 = pszSource[i*3];
            cSrc1 = pszSource[i*3+1];
            cSrc2 = pszSource[i*3+2];   

            cDest0 = BASE64CODE[cSrc0 >> 2] ;                         // 取高6位 
            cDest1 = BASE64CODE[((cSrc0 & 0x03)<<4)|(cSrc1>>4)];      // 取第一個字符低2位+第二個字符高4位
            cDest2 = BASE64CODE[((cSrc1&0x0F)<<2)|(cSrc2>>6)];        // 取第一個字符低4位+第二個字符高2位
            cDest3 = BASE64CODE[(cSrc2 & 0x3f)];                      // 取第三個字符低6位
        } 

        pszBase64[nCount++] = cDest0;
        pszBase64[nCount++] = cDest1;
        pszBase64[nCount++] = cDest2;
        pszBase64[nCount++] = cDest3;
    }
}

CString GetBasp64(CString strSrc )
{
    TCHAR szBuffer[1024] = {0};
    ToBase64(szBuffer, strSrc.GetBuffer(0), strSrc.GetLength());
    
    CString str(szBuffer);
    return str;
}