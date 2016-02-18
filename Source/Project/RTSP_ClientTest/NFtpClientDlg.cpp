// NFtpClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NFtpClient.h"
#include "NFtpClientDlg.h"
#include "NFTPFrameDef.h"
#include "NFtpParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FILE  *fdown;
FILE  *fdlog;
FILE  *fplog;
bool   IsDataDown = FALSE;
bool   IsDlogDown = FALSE;
bool   IsPlogDown = FALSE;
bool   isConnect = FALSE;

SOCKET *m_socket = NULL;  
static unsigned char buffer[1024];

DWORD WINAPI recvthread(LPVOID lpparam);

HWND hDialog_g;
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
// CNFtpClientDlg dialog

CNFtpClientDlg::CNFtpClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNFtpClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNFtpClientDlg)
	m_strUser = _T("");
	m_strPass = _T("");
	m_strIP = _T("");
	m_strDownPara = _T("");
	m_strGetdPara = _T("");
	m_strGetpPara = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSocket = NULL;
	
}

void CNFtpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNFtpClientDlg)
	DDX_Text(pDX, IDC_USERNAME, m_strUser);
	DDX_Text(pDX, IDC_PASSWORD, m_strPass);
	DDX_Text(pDX, IDC_IP, m_strIP);
	DDX_Text(pDX, IDC_DOWNPARA, m_strDownPara);
	DDX_Text(pDX, IDC_GETDPARA, m_strGetdPara);
	DDX_Text(pDX, IDC_GETPPARA, m_strGetpPara);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNFtpClientDlg, CDialog)
	//{{AFX_MSG_MAP(CNFtpClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_GETD, OnGetd)
	ON_BN_CLICKED(IDC_GETP, OnGetp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_SEND_DATA, OnSendData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNFtpClientDlg message handlers

BOOL CNFtpClientDlg::OnInitDialog()
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
	hDialog_g = this->m_hWnd; 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNFtpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNFtpClientDlg::OnPaint() 
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
HCURSOR CNFtpClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNFtpClientDlg::StartUp() 
{
	WSADATA wsaData;
	WORD	version = MAKEWORD(2,0);
	int		ret = WSAStartup(version,&wsaData);
	if (ret != 0)
	{
		AfxMessageBox("Winsock startup fail!");
	}
}

void CNFtpClientDlg::CleanUp()
{
	if (WSACleanup() != 0)
	{
		AfxMessageBox("UnInitialize Error!");
	}
}

unsigned char streamdata[1024*5];
DWORD WINAPI streamrecvthread(LPVOID lpparam)
{
	int ret;
	SOCKET mySocket = (SOCKET)lpparam;
	
	while (1)
	{
		ret = recv(mySocket, (char *)streamdata, 1024*5, 0);
		if(ret > 0)
		{
			
		}
		else
		{
			AfxMessageBox("流连接断开，请重新连接!");
			return 0;
		}
	}
	
} 

unsigned char stream_data_buffer[1024*1024];
void ReceiveStreamThread(void)
{
	SOCKADDR_IN local; 
	SOCKET monitor, m_hSocket; 
	unsigned char *pbuffer = stream_data_buffer;
	unsigned int len = 1024*1024;
	unsigned int ret;
	
	local.sin_family=AF_INET;				//Address family
	local.sin_addr.s_addr=INADDR_ANY;		//Wild card IP address
	local.sin_port=htons(9200);	//port to use	
	
	monitor = socket(AF_INET,SOCK_STREAM,0);
	if (monitor == INVALID_SOCKET)
	{
		AfxMessageBox("创建socket错误!");
		return;
	}
	
	if(bind(monitor,(sockaddr*)&local,sizeof(local)) != 0)
	{
		AfxMessageBox("bind error!");
		return;
	}
	
	if(listen(monitor,1)!=0)
	{
		AfxMessageBox("listen Error!");
		return;
	}
	
	sockaddr_in remote;
	int remotelen = sizeof(remote);

	while(1)
	{	
		m_hSocket = accept(monitor, (struct sockaddr*)&remote, &remotelen);
		if(m_hSocket == INVALID_SOCKET )
		{
			AfxMessageBox("accept error!");	
		}

 		AfxMessageBox("accept ok!");
		DWORD dwthread;
		::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)streamrecvthread,(LPVOID)m_hSocket,0,&dwthread); 
	}

#if 0
	ret = send(m_hSocket, "RTSP Client receive ok!", 24, 0);

	FILE *fp;
	fp = fopen("stream_down","ab");


	while (1)
	{
		ret = recv(m_hSocket, (char *)pbuffer, 1024*8, 0);
		if(ret > 0)
		{
			fwrite(pbuffer, sizeof(char), ret, fp);
		}
		else
		{
			fclose(fp);
			AfxMessageBox("连接失去，请重新连接!");
			return ;
		}
	} 
#endif 

}

void CNFtpClientDlg::OnConnect() 
{
	UpdateData(TRUE);

	char buff[256];
	StartUp();
	SOCKADDR_IN m_addr;
	if (isConnect)
	{
		AfxMessageBox("已经连接，请勿再连!");		
		return;
	}
	
	m_hSocket = socket(AF_INET,SOCK_STREAM,0);
	if (m_hSocket == INVALID_SOCKET)
	{
		AfxMessageBox("Socket创建失败!");
		return;
	}
	
	m_addr.sin_family = AF_INET;
	memset(buff, 0, 256);
	GetDlgItemText(IDC_IP, buff, 256);	
	m_addr.sin_addr.S_un.S_addr = inet_addr(buff);
	
	m_addr.sin_port = htons(554);
//	rtsp://218.204.223.237:554/live/1/6D1E43167B3A7BDA/oby9efo80duh9bjf.sdp
//	struct hostent* pHost = gethostbyname(buff);
//	memcpy(&m_addr.sin_addr.S_un.S_addr , pHost->h_addr_list[0], 4);
	int ret = connect(m_hSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr));
	if (ret == SOCKET_ERROR)
	{
		DWORD dwError = GetLastError(); 
		AfxMessageBox("连接失败!");
		return;
	}
	
	m_socket = &m_hSocket;
	isConnect = TRUE;
	DWORD dwthread;
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)recvthread,(LPVOID)m_hSocket,0,&dwthread); 
	::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReceiveStreamThread,0,0,&dwthread); 
	
	
}

void CNFtpClientDlg::OnGetd() 
{

}

void CNFtpClientDlg::OnGetp() 
{

}

void CNFtpClientDlg::OnDown() 
{

}

bool recv_data_parser(char *buff,int len)
{

	return TRUE;
}

void CNFtpClientDlg::OnAbort() 
{
	
}

void CNFtpClientDlg::OnQuit() 
{
	
}

void CNFtpClientDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

static char show_text[1024*64]; 
static char receive_text[1024*64]; 

DWORD WINAPI recvthread(LPVOID lpparam)
{
	int ret;
	SOCKET mySocket = (SOCKET)lpparam;

	CString str_receive, str_show;

	while (1)
	{
		ret = recv(mySocket,(char *)receive_text,1024*64,0);
		if(ret > 0)
		{
			receive_text[ret] = '\0';
			str_receive = (CString)receive_text;
			GetDlgItemText(hDialog_g, IDC_EDIT2, show_text, 1024*64);
			str_show = (CString)show_text;
			SetDlgItemText(hDialog_g, IDC_EDIT2, str_show+str_receive);
		}
		else
		{
			isConnect = false;
			AfxMessageBox("连接失去，请重新连接!");
			return 0;
		}
	}
		
}


void CNFtpClientDlg::OnSendData() 
{
	CString str;
	int len;
	char buff[1024];
	
	GetDlgItemText(IDC_EDIT1, buff, 1024);
	SetDlgItemText(IDC_EDIT1, "");

	str = (CString)buff;
	if (str.IsEmpty())
	{
		AfxMessageBox("请输入请求命令!");
		return;
	}
	
	len = str.GetLength();

	int ret;
	ret = send(m_hSocket, buff, len, 0);
	if (ret != len)
	{
		AfxMessageBox("发送失败!");
		return;
	} 
	
}










































