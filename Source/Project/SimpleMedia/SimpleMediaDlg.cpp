// SimpleMediaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleMedia.h"
#include "SimpleMediaDlg.h"
#include "MediaUtil.h"

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
// CSimpleMediaDlg dialog

CSimpleMediaDlg::CSimpleMediaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleMediaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleMediaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL;
	m_pListBox = NULL;
}

CSimpleMediaDlg::~CSimpleMediaDlg()
{
	if(m_pListBox)
	{
		delete m_pListBox;
		m_pListBox = NULL;
	}
}

void CSimpleMediaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleMediaDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleMediaDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleMediaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMediaDlg message handlers

BOOL CSimpleMediaDlg::OnInitDialog()
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
	if(m_hThread)
	{
		return FALSE;
	}
	if(m_pListBox == NULL)
	{
		CRect rect;
		GetDlgItem(IDC_LIST1)->GetClientRect(&rect);
		m_pListBox = new CListBox();
		m_pListBox->Create(0, rect, this, WM_USER+1);
	}

	char buffer[256] = {0};
	sprintf(buffer, "SDL_WINDOWID=0x%lx", m_pListBox->GetSafeHwnd());
	char *myvalue = SDL_getenv("SDL_WINDOWID");
	int iRet;
	if(myvalue == NULL)
	{
		iRet = SDL_setenv("SDL_WINDOWID", buffer, 1);	
	}
	myvalue = SDL_getenv("SDL_WINDOWID");

	m_hThread = CreateThread(NULL, 0, Thread_, this, 0, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleMediaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimpleMediaDlg::OnPaint() 
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
HCURSOR CSimpleMediaDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


DWORD WINAPI CSimpleMediaDlg::Thread_(LPVOID lparam)
{
	CSimpleMediaDlg* _this = (CSimpleMediaDlg*)lparam;
	if(_this)
	{
		_this->Thread();
	}

	return 0;
}
DWORD WINAPI CSimpleMediaDlg::Thread()
{
	SDL_Window * pWindow = SDL_CreateWindowFrom( (void *)( m_pListBox->GetSafeHwnd() ) );
//	PlayVedio("http://10.10.1.67/CyberX/amano.asf", m_pListBox->GetSafeHwnd());
	m_hThread = NULL;
	return  0;
}