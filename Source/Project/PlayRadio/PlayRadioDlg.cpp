// PlayRadioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PlayRadio.h"
#include "PlayRadioDlg.h"
#include "PlayeRadioUti.h"
#include "Gfxsock.h"


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
// CPlayRadioDlg dialog

CPlayRadioDlg::CPlayRadioDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPlayRadioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPlayRadioDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	WSAInitialize();
	m_bRunning = FALSE;
	m_bDownloading = FALSE;
}

CPlayRadioDlg::~CPlayRadioDlg()
{
	WSAUninitialize();
}

void CPlayRadioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlayRadioDlg)
	DDX_Control(pDX, IDC_OCX1, m_PlayCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPlayRadioDlg, CDialog)
	//{{AFX_MSG_MAP(CPlayRadioDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_Download, OnButton_Download)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayRadioDlg message handlers
#define RADIO_NAME		_T("http://10.10.1.67/CyberX/123.avi")
#define RADIO_NAME2		_T("http://10.10.1.67/CyberX/amano.asf")
#define RADIO_NAME3		_T("http://liujiquan/CyberX/123.avi")
//#define RADIO_NAME  _T("mms://222.122.12.214/empas_wmv_high_060206/0025/002508.wmv")
BOOL CPlayRadioDlg::OnInitDialog()
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
//	m_PlayCtrl.SetUrl(RADIO_NAME);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayRadioDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPlayRadioDlg::OnPaint() 
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
HCURSOR CPlayRadioDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

DWORD MakeCmd_0x01(BYTE data[]);
DWORD MakeCmd_0x01_(BYTE* pData);
void GetAddr(SOCKET server, TCHAR* szDotAddr);
void CPlayRadioDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
/*	WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata) !=0)  {   return;}
	struct hostent *pHostent = gethostbyname(RADIO_NAME); 
	if(pHostent == NULL)
	{
		WSACleanup();
		return;
	}

	struct sockaddr_in ServerAddr;
	SOCKET server=socket(AF_INET,SOCK_STREAM,IPPROTO_IP); 

	DWORD dwError = GetLastError();

	TCHAR szAddr[MAX_PATH] = {0};
	GetAddr(server, szAddr);
	ServerAddr.sin_family=AF_INET; 
//	ServerAddr.sin_addr.S_un.S_addr = inet_addr("10.10.1.67");//180.168.41.175
	memcpy(&ServerAddr.sin_addr.S_un.S_addr,pHostent->h_addr_list[0],pHostent->h_length);
    ServerAddr.sin_port=htons((u_short )DEFAULT_PORT);
	
	u_long mode = 1;
	ioctlsocket(server,FIONBIO,&mode);
	int nRet = connect(server, (sockaddr*)&ServerAddr, sizeof(ServerAddr));
	dwError = GetLastError();
	BYTE szBuffer[MAX_PATH*10] = {0};
	
	DWORD dwSize = MakeCmd_0x01_(szBuffer);
	nRet = send(server, (CHAR*)szBuffer, dwSize, 0);
	nRet = recv(server, (CHAR*)szBuffer, MAX_PATH*10, 0);

	closesocket(server);

	WSACleanup();
*/
	WSAInitialize();

	SOCKADDR serverAddr;
	SOCKET server = INVALID_SOCKET;
	if(InitSockInfo(DEFAULT_PORT, GetIP(RADIO_NAME), server, serverAddr))
//	if(InitSockInfo(DEFAULT_PORT, "222.122.12.214", server, serverAddr))
	{
		int intRet = Connect(server, &serverAddr);
		if(intRet == 0)
		{
			BYTE szBuffer[MAX_PATH*10] = {0};
			DWORD dwSize = MakeCmd_0x01(szBuffer);

			int nCount = 0;
			if(SendData(server, (CHAR*)szBuffer, dwSize,  nCount, 0) == SEND_OK)
			{
				SetRecvTimeo(server, RECV_TIMEO);				// Set sock recv timeo
//				SetRecvTimeo(server, 0);						// Set sock block 
				if(RecvData(server, (CHAR*)szBuffer, MAX_PATH*10, nCount, 0) == RECV_OK)
				{
					TRACE1("%s\n", szBuffer);
				}
				else
				{
					TRACE1("%d\n", GetLastError());
				}
			}	
		}
	}
	
	ReleaseSock(server);
	WSAUninitialize();
}

typedef struct PACKET_01
{
	DWORD dwReserver;		// 0x00000001
	DWORD dwBoobFace;		// 0xB00BFACE
	DWORD dwDataLen;		// 协议类型后面数据的长度 Data+param(6*sizeof(DWORD) + sizeof(DWORD64))
	DWORD dwProtocolType;	// "MMS "  0x20534D4D
	DWORD dwAssginSize;		// 
	DWORD dwPacketSize;		// m_SeqNum
	DWORD64 dwTimeSpan;		// 0
	DWORD dwAssginSize2;	// 0
	DWORD dwCmd;			// 0x00030001
	DWORD dwProtocolFlag;	// 0xF0F0F0F0
	DWORD dwUnkonw;			// 0x0004000B 
	DWORD dwVersion;		// 0x0003001C "/x1C/x03NSPlayer/9.0.0.4503; ";
}PACKET_01, *PPACKET_01;
DWORD MakeCmd_0x01(BYTE* pData)
{
	int m_SeqNum = 0;
	DWORD dwSize = 0;
	
	LPCTSTR pszPlayerVersion = "NSPlayer/9.0.0.4503; \0";
	int playerVerLen = (strlen(pszPlayerVersion)+1) * 2 + 8;
	int playerVerAssginLen = (playerVerLen + 7)/8;
	

	PACKET_01 packet01;
	memset(&packet01, 0x00, sizeof(packet01));
	packet01.dwReserver = 0x00000001;
	packet01.dwBoobFace = 0XB00BFACE;
	packet01.dwDataLen = playerVerLen + sizeof(DWORD) * 7 + sizeof(DWORD64);
	packet01.dwProtocolType = 0X20534D4D;		// "MMS "
	packet01.dwAssginSize = playerVerAssginLen + 4;	// 4?
	packet01.dwPacketSize = m_SeqNum;
	packet01.dwTimeSpan = 0;
	packet01.dwAssginSize2 = playerVerAssginLen + 2;
	packet01.dwCmd = 0x00030001;
	packet01.dwProtocolFlag = 0XF0F0F0F0;
	packet01.dwUnkonw = 0X0004000B;
	packet01.dwVersion = 0x0003001C;
	
	int PACKETSIZE = sizeof(PACKET_01);
	memcpy(pData, &packet01, PACKETSIZE);

	BYTE wpszPlayerVersion[MAX_PATH*2];
	int len = 2*MultiByteToWideChar(CP_ACP,0,pszPlayerVersion,-1,(WORD*)wpszPlayerVersion,MAX_PATH*2);
	memcpy(pData + PACKETSIZE, wpszPlayerVersion, len);

	dwSize = playerVerLen + PACKETSIZE;
	return dwSize;	
}

void GetAddr(SOCKET server, TCHAR* szDotAddr)
{
	struct sockaddr_in sockAddr;
	
    TCHAR num[20]={0};
	
    int cbLen=sizeof(sockAddr);
	
    getsockname(server,(struct sockaddr*)&sockAddr,&cbLen);
	
    LPCTSTR pServAddr=inet_ntoa(sockAddr.sin_addr);
    lstrcpy(szDotAddr,"////");
    lstrcat(szDotAddr,pServAddr);
    lstrcat(szDotAddr,"//TCP//");
    int port=ntohs(sockAddr.sin_port);
    sprintf(num,"%d",port);
    lstrcat(szDotAddr,num);
    lstrcat(szDotAddr,"//0");
    int tail=20-lstrlen(pServAddr)-lstrlen(num);
    for(int i=0;i<tail;++i)	
    {
		lstrcat(szDotAddr,"0");	
    }
}

DWORD MakeCmd_0x01_(BYTE* data)
{
	int m_SeqNum = 1;
	LPCTSTR pPlayerVer="/x1C/x03NSPlayer/9.0.0.3372; ";
	int length=lstrlen(pPlayerVer)*2+8;
	int len8=(length+7)/8;
	LPBYTE pData=data;
	DWORD size=0;
	*(DWORD*)(pData+size)=1;
	size+=4;
	*(DWORD*)(pData+size)=0xB00BFACE;
	size+=4;
	*(DWORD*)(pData+size)=length+32;
	size+=4;
	*(DWORD*)(pData+size)=0x20534D4D;
	size+=4;
	*(DWORD*)(pData+size)=len8+4;
	size+=4;
	*(DWORD*)(pData+size)=m_SeqNum++;
	size+=4;
	*(DWORD*)(pData+size)=0;
	size+=4;
	*(DWORD*)(pData+size)=0;
	size+=4;
	*(DWORD*)(pData+size)=len8+2;
	size+=4;
	*(DWORD*)(pData+size)=0x00030001;
	size+=4;
	*(DWORD*)(pData+size)=0xF0F0F0F0;
	size+=4;
	*(DWORD*)(pData+size)=0x0004000B;
	size+=4;
	BYTE wPlayerVer[MAX_PATH*2];
	int len=2*MultiByteToWideChar(CP_ACP,0,pPlayerVer,-1,(WORD*)wPlayerVer,MAX_PATH*2);
	
	CopyMemory(pData+size,wPlayerVer,len);
	size+=len;
	size=length+48;	
	

	return size;
}
#include "asfrecorder.h"
void CPlayRadioDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	char *agrvs[2];
	char* szBuffer = (char*)malloc(strlen(RADIO_NAME)+1);
	memset(szBuffer, 0, strlen(RADIO_NAME)+1);
	memcpy(szBuffer, RADIO_NAME, strlen(RADIO_NAME));
	agrvs[1] = szBuffer;
	agrvs[0] = szBuffer;
	main(2, (char**)agrvs);
	free(szBuffer);
}
#define FILENAME	"123.avi"
void CPlayRadioDlg::OnButton_Download() 
{
	if(m_bDownloading )	return;

	m_hDownloadThread = CreateThread(NULL, 0, _DownloadThreadFunc, this, 0, NULL);
	if(m_hDownloadThread == NULL)
	{
		CloseHandle(m_hDownloadThread);
		m_hDownloadThread = NULL;
	}
}


DWORD WINAPI CPlayRadioDlg::_DownloadThreadFunc(LPVOID lparam)
{
	CPlayRadioDlg* _this = (CPlayRadioDlg*)lparam;
	if(_this)
	{
		_this->DownloadThreadFunc();
	}
	
	return 0;
}

DWORD WINAPI CPlayRadioDlg::DownloadThreadFunc()
{
	m_bDownloading = TRUE;
	DeleteFile(FILENAME);
	FILE* pFile = fopen(FILENAME, "wb");
	if(pFile == NULL)	return 0;
	
	TCHAR* szUrl = RADIO_NAME2;
	
	TCHAR szServerName[MAX_PATH] = {0};
	TCHAR szFile[MAX_PATH] = {0};
	u_short nPort;
	
	BOOL bRet = AnalyzeUrl(szUrl, szServerName, szFile, nPort);
	
	SOCKADDR serverAddr;
	m_ServerSock = INVALID_SOCKET;
	struct hostent* pHost = NULL;
	
	if(!isalpha(szServerName[0]))	// 10.10.1.67
	{
		unsigned long lAddr = inet_addr(szServerName);
		pHost = gethostbyaddr((char*)&lAddr, 4, AF_INET);
		if(pHost)	memcpy(szServerName, pHost->h_name, strlen(pHost->h_name));
	}
	else							// Other
	{
		pHost = gethostbyname(szServerName);
	}
	if(pHost == NULL)							return 0;	
	//////////////////////////////////////////////////////////////////////////
	TCHAR szBuffer[MAX_PATH*10] = {0};
	TCHAR* pszBuffer = (TCHAR*)szBuffer;

	pszBuffer += sprintf(pszBuffer, "GET %s HTTP/1.0\r\n", szFile);
	pszBuffer += sprintf(pszBuffer, "Accept: */*\r\n");
	pszBuffer += sprintf(pszBuffer, "User-Agent: NSPlayer/9.0.0.4503\r\n");
	pszBuffer += sprintf(pszBuffer, "Host: %s\r\n", pHost->h_name);
	pszBuffer += sprintf(pszBuffer, "Pragma: no-cache,rate=1.000000,stream-time=0,stream-offset=0:0,request-context=1,max-duration=0\r\n");
	pszBuffer += sprintf(pszBuffer, "Pragma: xClientGUID=%s\r\n", randomizeGuid());
	pszBuffer += sprintf(pszBuffer, "Connection: Close\r\n\r\n");

	m_ServerSock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if(m_ServerSock == INVALID_SOCKET)				return 0;	
	memset(&serverAddr, 0x00, sizeof(serverAddr));
	SOCKADDR_IN* pAddr_in = (SOCKADDR_IN*)&serverAddr;
	pAddr_in->sin_family = AF_INET;
	pAddr_in->sin_port = htons(nPort);
	memcpy(&pAddr_in->sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);

	int intRet = connect(m_ServerSock, &serverAddr, sizeof(serverAddr));
	if(intRet == 0)
	{
		int dwCount = 0;
		if(SendData(m_ServerSock, (CHAR*)szBuffer, pszBuffer - szBuffer,  dwCount, 0) == SEND_OK)
		{
			SetRecvTimeo(m_ServerSock, RECV_TIMEO);	
			if(RecvData(m_ServerSock, (CHAR*)szBuffer, MAX_PATH*10, dwCount, 0) == RECV_OK)
			{
				REQUESTINFO info;
				if(AnalyzePacket(szBuffer, &info))
				{
					TRACE2("%d	%s\n", info.dwHeaderLen, szBuffer);
					fwrite(szBuffer + info.dwHeaderLen, dwCount - info.dwHeaderLen, 1, pFile);

					m_dwRecvMaxCount = dwCount - info.dwHeaderLen;
					while(m_bDownloading)
					{
						Sleep(10);
						if(RecvData(m_ServerSock, (CHAR*)szBuffer, MAX_PATH*10, dwCount, 0) != RECV_OK)
						{
							break;
						}
						m_dwRecvMaxCount += dwCount;
						fwrite(szBuffer, dwCount, 1, pFile);
						TRACE2("%d / %d\n", m_dwRecvMaxCount, info.Content_Length);
					}
				}
			}
			else
			{
				TRACE1("%d\n", GetLastError());
			}
		}	
	}
	else
	{
		TRACE1("%d", GetLastError());
	}

	ReleaseSock(m_ServerSock);
	m_bDownloading = FALSE;

	return 0;
}

#include "wmpplayer4.h"
#include "wmpcontrols.h"
#include "wmpsettings.h"
#include "wmpnetwork.h"
#include "wmpmedia.h"
void CPlayRadioDlg::OnButton4() 
{
	if(m_bRunning)
	{
		return;
	}
	// TODO: Add your control notification handler code here
//	CWMPPlayer4 player;
//	m_PlayCtrl.launchURL(RADIO_NAME);						// 直接播放
	m_PlayCtrl.SetUrl(FILENAME);							// 本函数执行完菜播放
//	CWMPMedia wmpMedia = m_PlayCtrl.newMedia(RADIO_NAME);	// 不播放
	
	m_hThread = CreateThread(NULL, 0, _ThreadFunc, this, 0, NULL);
	if(m_hThread == NULL)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

DWORD WINAPI CPlayRadioDlg::_ThreadFunc(LPVOID lparam)
{
	CPlayRadioDlg* _this = (CPlayRadioDlg*)lparam;
	if(_this)
	{
		_this->ThreadFunc();
	}
	
	return 0;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::ThreadFunc
// Return   :   DWORDWINAPI 
// Comment  :   
// -----------------------------------------------------------//
DWORD WINAPI CPlayRadioDlg::ThreadFunc()
{	
	m_bRunning = TRUE;
	while(m_bRunning)
	{
		Sleep(1000);

		CWMPControls controls = m_PlayCtrl.GetControls();
		CWMPSettings settings = m_PlayCtrl.GetSettings();
		CWMPNetwork  network = m_PlayCtrl.GetNetwork();
		
		long lRet1 = network.GetBandWidth();
		long lRet2 = network.GetBitRate();
		long lRet3 = network.GetBufferingCount();
		long lRet4 = network.GetBufferingTime();//5000
		long lRet5 = network.GetDownloadProgress();//100
		long lRet6 = network.GetMaxBandwidth();//0
		long lRet7 = network.GetMaxBitRate();
		long lRet8 = network.GetLostPackets();
		long lRet9 = network.GetReceivedPackets();
		
		TRACE3("network %d %d %d ", lRet1, lRet2, lRet3);
		TRACE3("%d %d %d ", lRet4, lRet5, lRet6);
		TRACE3("%d %d %d \n", lRet7, lRet8, lRet9);

		long lRet11 = settings.GetRate();
		TCHAR szModue[MAX_PATH] = {0};
		long lRet12 = settings.getMode(szModue);
		TRACE3("settings %d [%s] %d \n", lRet11, szModue, lRet12);

		double dValue = controls.GetCurrentPosition();
		CString str = controls.GetCurrentPositionString();
		TRACE2("controls %.4f [%s]\n", dValue, str.GetBuffer(0));
	}

	m_bRunning = FALSE;

	return 0;
}

void CPlayRadioDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	m_bRunning = FALSE;
	Sleep(1000);
}
