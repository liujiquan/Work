// DownloadFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DownloadFile.h"
#include "DownloadFileDlg.h"
#include "SetDialog.h"
#include "EncryptUtil.h"
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
// CDownloadFileDlg dialog

CDownloadFileDlg::CDownloadFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownloadFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownloadFileDlg)
	m_Server = _T("");
	m_maxSize = _T("");
	m_curSize = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pHttpFile = NULL;
	m_bDownLoad = FALSE;
	m_bPause = FALSE;
	memset(m_handleArr, 0, sizeof(HANDLE)*1024);
	m_bClose = FALSE;
	InitializeCriticalSection(&m_criticalSection);
	m_ReadSize = MAX_PATH;
	m_nThreadCount = 1;
	m_szReadBuffer = NULL;
}

CDownloadFileDlg::~CDownloadFileDlg()
{
	DeleteCriticalSection(&m_criticalSection);
	m_session.Close();
}

void CDownloadFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownloadFileDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Text(pDX, IDC_EDIT1, m_Server);
	DDX_Text(pDX, IDC_STATIC_MAX, m_maxSize);
	DDX_Text(pDX, IDC_STATIC_CUR, m_curSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDownloadFileDlg, CDialog)
	//{{AFX_MSG_MAP(CDownloadFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnButtonDownload)
	ON_COMMAND(ID_MENUITEM_ABOUT, OnMenuitemAbout)
	ON_COMMAND(ID_MENUITEM_SET, OnMenuitemSet)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownloadFileDlg message handlers

BOOL CDownloadFileDlg::OnInitDialog()
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
	TCHAR szModulePath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szModulePath, MAX_PATH);
	m_strDownLoadFilePath = CString(szModulePath);
	int index = m_strDownLoadFilePath.ReverseFind('\\');
	if(index == -1)
	{
		index = m_strDownLoadFilePath.ReverseFind('/');
	}
	if(index == -1)
	{
		MessageBox("Path Error.");
		return FALSE;
	}
	m_strDownLoadFilePath = m_strDownLoadFilePath.Left(index+1);

	m_Progress.SetRange32(0, 100);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDownloadFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDownloadFileDlg::OnPaint() 
{
	CDialog::OnPaint();
	
	CWnd* pStaticWnd = GetDlgItem(IDC_STATIC_CUR);
	pStaticWnd->SetWindowText(m_curSize);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDownloadFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CDownloadFileDlg::OnButtonDownload
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
CString GetDownLoadFileName(CString strFileName, CString strDownLoadFilePath, UINT nCount);
BOOL FileExists(LPCTSTR szFilePath);
static DWORD dwFirst,dwLast;
#pragma comment(lib,"WININET.LIB")
typedef struct tag_DWORDDWORD
{
	DWORD dwValue1;
	DWORD dwValue2;
}DWORDDWORD;
void CDownloadFileDlg::OnButtonDownload() 
/*
{
	UpdateData(TRUE);
	m_Server.TrimLeft();
	m_Server.TrimRight();
	//INTERNETSESSION
	LPCTSTR pstrAgent = NULL;
	DWORD dwAccessType = PRE_CONFIG_INTERNET_ACCESS;
	LPCTSTR pstrProxyName = NULL;
	LPCTSTR pstrProxyBypass = NULL;
	DWORD dwFlags = 0;

	HINTERNET hSession = NULL;
	hSession = InternetOpen(pstrAgent, dwAccessType,pstrProxyName,pstrProxyBypass,dwFlags);
	if(hSession == NULL)
	{
		return;
	}

	LPCTSTR pstrURL = m_Server.GetBuffer(0);
	DWORD dwContext  = 0;
	dwFlags = INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD;
	DWORD dwHeadersLength= 0;

	DWORD dwServiceType;
	CString strServer;
	CString strObject;
	INTERNET_PORT nPort;
	LPCTSTR pstrHeaders = NULL;
	CStdioFile* pReturn;

	
	BOOL bParsed = AfxParseURL(pstrURL, dwServiceType, strServer, strObject, nPort);
	HINTERNET hOpener;
	hOpener = InternetOpenUrl(hSession, pstrURL, pstrHeaders,dwHeadersLength, dwFlags, dwContext);
	
	TCHAR szBuffer[MAX_PATH] = {0};
	DWORDDWORD dwFileSize;
	DWORD dwDWSize2 = MAX_PATH;
	DWORD dwDWSize = sizeof(dwFileSize);
	InternetQueryOption(hOpener, HTTP_QUERY_RAW_HEADERS, szBuffer, &dwDWSize2);
	InternetQueryOption(hOpener, HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, &dwFileSize, &dwDWSize);

	InternetCloseHandle(hSession);
	InternetCloseHandle(hOpener);
}*/
{	
	dwFirst = GetTickCount();
	if(m_bDownLoad == TRUE)
	{
		if(m_bPause)
		{
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("Pause");
			m_bPause = FALSE;
		}
		else
		{
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("Continue");
			m_bPause = TRUE;
		}
		return;
	}
	UpdateData(TRUE);
	if(m_pHttpFile != NULL)
	{
		m_pHttpFile->Close();
		delete m_pHttpFile;
		m_pHttpFile = NULL;
	}
	// Begin
	DWORD dwFlags = INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_TRANSFER_BINARY|INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RELOAD;
	
	// 1:OpenURL
	BOOL bRet = m_session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 1000);	// Connect TimeOut
	bRet = m_session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 1000);			// Send TimeOut
	bRet = m_session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 1000);		// Recieve TimeOut
	m_Server.TrimLeft();
	m_Server.TrimRight();
	try
	{
		m_pHttpFile = (CHttpFile*)m_session.OpenURL(m_Server, 1, dwFlags);
	}
	catch (CException* e)
	{
		DWORD dwError = GetLastError();
		if(dwError == 12006)
		{
			CString strTemp = DecryptData(m_Server);
			m_pHttpFile = (CHttpFile*)m_session.OpenURL(strTemp, 1, dwFlags);
			if(m_pHttpFile) 
			{
				m_Server = strTemp;
				UpdateData(FALSE);
			}
		}
	}
	
	// 2:
	if(m_pHttpFile == NULL)	return;
	
	m_strFileName = m_pHttpFile->GetFileName();										
	m_strFileName = GetDownLoadFileName(m_strFileName, m_strDownLoadFilePath, 0);	// FileName
	m_strFilePath = m_strDownLoadFilePath + m_strFileName;							// FilePath
	//3:FileSize
	
//	TCHAR szBuffer[MAX_PATH] = {0};
//	DWORD dwDWSize2 = MAX_PATH;
//	DWORD dwStatus;
//	DWORD dwSize3 = sizeof(dwStatus);
//	m_pHttpFile->QueryInfo(HTTP_QUERY_STATUS_CODE|HTTP_QUERY_FLAG_NUMBER, &dwStatus, &dwSize3, 0);
//	if(dwStatus != 200)
//	{
//		DWORD dwError = GetLastError();
//	}
	DWORD dwSize = sizeof(m_FileSize);
//	m_pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, &szBuffer, &dwDWSize2, 0);
	m_pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, &m_FileSize, &dwSize, 0);	
	m_Progress.SetPos(0);
	m_maxSize.Format(_T("%.2fkb"), ((float)m_FileSize)/1024);
	m_curSize = _T("0");
	GetDlgItem(IDC_STATIC_MAX)->SetWindowText(m_maxSize);
	//4:ReadFile
	m_pReadFile = NULL;
	m_dwReadMaxSize = 0;
	m_bDownLoad = TRUE;
	m_pReadFile = fopen(m_strFilePath,"wb");
	if(m_pReadFile == NULL)
	{
		m_pHttpFile->Close();
		delete m_pHttpFile;
		m_pHttpFile = NULL;
		MessageBox("fopen Failed");
		return;
	}
	for(int i = 0; i < m_nThreadCount; i++)
	{
		m_handleArr[i] = CreateThread(NULL, 0, _ThreadFunc, this, 0, NULL);
	}
	GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("Pause");
}

// -----------------------------------------------------------//
// Function :   CDownloadFileDlg::_ThreadFunc
// Param    :   LPARAM lparam
// Return   :   DWORDWINAPI 
// Comment  :   
// -----------------------------------------------------------//
DWORD WINAPI _ThreadFunc(LPVOID lparam)
{
	CDownloadFileDlg* _this = (CDownloadFileDlg*)lparam;
	if(_this)
	{
		_this->ThreadFunc();
	}

	return 0;
}
// -----------------------------------------------------------//
// Function :   CDownloadFileDlg::ThreadFunc
// Return   :   DWORDWINAPI 
// Comment  :   
// -----------------------------------------------------------//
#define READSIZE	MAX_PATH*10
DWORD WINAPI CDownloadFileDlg::ThreadFunc()
{
	DWORD dwReadLen = 0;
//	TCHAR* szFile = (TCHAR*)malloc(m_ReadSize);
	if(m_szReadBuffer == NULL)
	{
		m_szReadBuffer = (TCHAR*)malloc(m_ReadSize);
	}
	while(m_bDownLoad)
	{
		Sleep(1);
		while(m_bPause)		Sleep(1);
		
		EnterCriticalSection(&m_criticalSection);							// EnterCriticalSection
		if(m_pReadFile && m_pHttpFile)
		{
			memset(m_szReadBuffer, 0, m_ReadSize);	
			dwReadLen = m_pHttpFile->Read(m_szReadBuffer, m_ReadSize);
			if(dwReadLen <= 0)	
			{
				LeaveCriticalSection(&m_criticalSection);			
				break;
			}
			fwrite(m_szReadBuffer,  1, dwReadLen, m_pReadFile);
			m_dwReadMaxSize += dwReadLen;
			if(m_bClose == FALSE)
			{
				m_curSize.Format(_T("%d %.2f"), ::GetCurrentThreadId(), ((float)m_dwReadMaxSize)/1024);
				m_Progress.SetPos((double(m_dwReadMaxSize)/(double)m_FileSize)*100);
				CRect    rc;      
				GetDlgItem(IDC_STATIC_CUR)->GetWindowRect(&rc);   
				ScreenToClient(&rc);      
				InvalidateRect(rc);    
			}	
		}
		else
		{
			LeaveCriticalSection(&m_criticalSection);			
			break;
		}
		LeaveCriticalSection(&m_criticalSection);								// LeaveCriticalSection	
	}
	EnterCriticalSection(&m_criticalSection);									// EnterCriticalSection
	if(m_pReadFile && m_pHttpFile)
	{
		fclose(m_pReadFile);
		m_pReadFile = NULL;
		m_pHttpFile->Close();
		delete m_pHttpFile;
		m_pHttpFile = NULL;

		m_bDownLoad = FALSE;
		memset(m_handleArr, 0, sizeof(HANDLE)*1024);
	}
	LeaveCriticalSection(&m_criticalSection);							// LeaveCriticalSection

	EnterCriticalSection(&m_criticalSection);							// EnterCriticalSection
	if(m_szReadBuffer)
	{
		free(m_szReadBuffer);
		m_szReadBuffer = NULL;
		if(m_bClose == FALSE)
		{
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->SetWindowText("DownLoad");
			dwLast = GetTickCount();
			float value = ((dwLast-dwFirst)/1000);
			value = ((float)m_FileSize)/1024 / value;
			CString str;
			str.Format("%.4f kb/s", value);
			MessageBox(str);
		}
	}
	LeaveCriticalSection(&m_criticalSection);							// LeaveCriticalSection
	TRACE1("¡¾%d¡¿ Finish!\n", ::GetCurrentThreadId());
	return 0;
}

// -----------------------------------------------------------//
// Function :   CDownloadFileDlg::OnMenuitemAbout
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDownloadFileDlg::OnMenuitemAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}

void CDownloadFileDlg::OnMenuitemSet() 
{
	// TODO: Add your command handler code here
	CSetDialog dlg(this);
	dlg.m_ReadSize = m_ReadSize;
	dlg.m_ThreadCount = m_nThreadCount;
	if(dlg.DoModal() == IDOK)
	{
		m_ReadSize = dlg.m_ReadSize;
		m_nThreadCount = dlg.m_ThreadCount;
	}
}

// -----------------------------------------------------------//
// Function :   GetDownLoadFileName
// Param    :   CString strFileName
//              CString strDownLoadFilePath
//              UINT nCount
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString GetDownLoadFileName(CString strFileName, CString strDownLoadFilePath, UINT nCount)
{
	if(strDownLoadFilePath.IsEmpty() || strFileName.IsEmpty())	return _T("");

	CString strFileNameTemp = strFileName;
	if(nCount > 0)
	{
		strFileNameTemp.Format(_T("%s(%d)"), strFileName, nCount);						// FileName
	}
	CString strFilePath = strDownLoadFilePath + strFileNameTemp;						// FilePath
	if(FileExists(strFilePath.GetBuffer(0)))
	{
		nCount++;
		return GetDownLoadFileName(strFileName, strDownLoadFilePath, nCount);
	}
	
	return strFileNameTemp;
}

// -----------------------------------------------------------//
// Function :   FileExists
// Param    :   LPCTSTR szFilePath
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#include <io.h>
BOOL FileExists(LPCTSTR szFilePath)
{
	if(_access(szFilePath, 0) == -1)
	{
		return FALSE;	
	}
	return TRUE;
}

void CDownloadFileDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_bClose = TRUE;
	if(m_bDownLoad)
	{
		m_bPause = FALSE;
		m_bDownLoad = FALSE;
		WaitForMultipleObjects(m_nThreadCount, m_handleArr, TRUE, INFINITE);
//		MsgWaitForMultipleObjects(1, &m_handle, FALSE, INFINITE, QS_ALLINPUT);   
	}
	CDialog::OnClose();
}

void CDownloadFileDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	m_bClose = TRUE;
	if(m_bDownLoad)
	{
		m_bPause = FALSE;
		m_bDownLoad = FALSE;
		WaitForMultipleObjects(m_nThreadCount, m_handleArr, TRUE, INFINITE);
	}
}
