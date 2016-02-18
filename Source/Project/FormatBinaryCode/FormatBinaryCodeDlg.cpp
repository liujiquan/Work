// FormatBinaryCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FormatBinaryCode.h"
#include "FormatBinaryCodeDlg.h"

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
// CFormatBinaryCodeDlg dialog

CFormatBinaryCodeDlg::CFormatBinaryCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFormatBinaryCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormatBinaryCodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFormatBinaryCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormatBinaryCodeDlg)
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFormatBinaryCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CFormatBinaryCodeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_MESSAGE(WM_DROPFILES, OnDragAcceptFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatBinaryCodeDlg message handlers

BOOL CFormatBinaryCodeDlg::OnInitDialog()
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
	if(ReleaseNasmExe() == FALSE)
	{
		return FALSE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

CFormatBinaryCodeDlg::~CFormatBinaryCodeDlg()
{
	DeleteNasmExe();
}


void CFormatBinaryCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFormatBinaryCodeDlg::OnPaint() 
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
HCURSOR CFormatBinaryCodeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CString FormatBinary(CString strSource);
// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::OnButton1
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CFormatBinaryCodeDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString strSource;
	m_Edit1.GetWindowText(strSource);
	CString strDest = FormatBinary(strSource);
	m_Edit2.SetWindowText(strDest);
}

// -----------------------------------------------------------//
// Function :   FormatBinary
// Param    :   CString strSource
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString FormatBinary(CString strSource)
{
	CString strTemp = strSource;

	strTemp.Remove('-');
	strTemp.Remove('[');
	strTemp.Remove(']');
	strTemp.Remove(' ');
	strTemp.Remove('\t');
		
	char* szBuffer = strTemp.GetBuffer(0);
	int length = strTemp.GetLength();
	char* szDest = (char*)malloc(length*5);
	memset(szDest, 0x00, length*5);
	int nCount1 = 0;
	int nCount2 = 0;

	while(true)
	{
		if(szBuffer[nCount1] == '\0' || szBuffer[nCount1+1] == '\0')
		{
			break;
		}
		if(szBuffer[nCount1] != '\n' && szBuffer[nCount1] != '\r'
			  &&szBuffer[nCount1+1] != '\n' && szBuffer[nCount1+1] != '\r')
		{	
			szDest[nCount2++] = '0';	
			szDest[nCount2++] = 'x';	
			szDest[nCount2++] = szBuffer[nCount1++];	
			szDest[nCount2++] = szBuffer[nCount1++];
			szDest[nCount2++] = ',';
		}
		else
		{	
			szDest[nCount2++] = szBuffer[nCount1++];
		}
	}
	
	strTemp.Empty();
	strTemp.Format("%s", szDest);
	free(szDest);
	return strTemp;
}

// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::OnButton2
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CFormatBinaryCodeDlg::OnButton2() 
{
	CString strSource;
	m_Edit2.GetWindowText(strSource);
	strSource.Remove(',');
	strSource.Remove(' ');
	strSource.Replace("0x", "");
	m_Edit1.SetWindowText(strSource);		
}

// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::OnDragAcceptFiles
// Param    :   WPARAM wparam
//              LPARAM lparam
// Return   :   LRESULT
// Comment  :   
// -----------------------------------------------------------//
#define BINARY_FILE_NAME	_T("7A43A012-B913-435d-A6D7-4281190EBB37.txt")
#define	NASM_EXE_NAME		_T("_nasm.exe")
LRESULT CFormatBinaryCodeDlg::OnDragAcceptFiles(WPARAM wparam,LPARAM lparam)
{
	HDROP hdrop = (HDROP)wparam;
	if(hdrop == NULL)	return 0;
	
	int nCount = ::DragQueryFile(hdrop, -1, NULL, 0);
	if(nCount == 1)
	{
		m_strFileName.Empty();
		TCHAR szBuffer[MAX_PATH] = {0};
		::DragQueryFile(hdrop, 0, szBuffer, MAX_PATH);
		m_strFileName = (CString)(szBuffer);

		DoSomeThing();
	}
	return 0;
}

// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::DoSomeThing
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CFormatBinaryCodeDlg::DoSomeThing()
{
	// Output binary file
	CString strCmd;
	CString strFileName = BINARY_FILE_NAME;
	strCmd.Format("%s \"%s\" -l %s",NASM_EXE_NAME, m_strFileName, strFileName);
	system(strCmd.GetBuffer(0));
	//
	FILE *pFile = fopen(strFileName, "rb");
	if(pFile == NULL)		return ;
	DWORD dwLength;
	fseek(pFile, 0, SEEK_SET);
	fseek(pFile, 0, SEEK_END);
	dwLength = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	TCHAR * szBuffer = (TCHAR*)malloc(dwLength* sizeof(TCHAR));	
	memset(szBuffer, 0x00, dwLength);
	fread(szBuffer,  dwLength,sizeof(TCHAR), pFile);
	//buffer
	CString strSource(szBuffer);
	free(szBuffer);
	fclose(pFile);
	DeleteFile(strFileName);

	//strSource
	int oldIndex = -1;
	int newIndex = 0;
	CString strDest;
	while(true)
	{
		newIndex = strSource.Find('\r', oldIndex+1);
		if(newIndex == -1)
		{
			break;
		}
		CString strTemp;
		strTemp = strSource.Mid(oldIndex+1, newIndex - oldIndex - 1);	
		strTemp = strTemp.Right(strTemp.GetLength() - 17);
		CString str = strTemp.Left(1);
		if(strTemp.Left(1) != " ")
		{
			int nIndex = strTemp.Find(' ', 0);
			if(nIndex == -1)
			{
				nIndex = strTemp.Find('-', 0);
				if(nIndex != -1)	nIndex += 1;
			}
			if(nIndex != -1)
			{
				strTemp = strTemp.Left(nIndex);
				strDest = strDest +  strTemp + '\r' + '\n';
			}
		}
		oldIndex = newIndex;
	}

	m_Edit1.SetWindowText(strDest);
}


// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::ReleaseNasmExe
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CFormatBinaryCodeDlg::ReleaseNasmExe()
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_NASM1), "nasm");
	if(hResource == NULL)	return FALSE;
	HGLOBAL hGobal = LoadResource(NULL, hResource);	
	if(hGobal == NULL)	return FALSE;
	LPVOID lBuffer = LockResource(hGobal);				// buffer
	DWORD dwLen = SizeofResource(NULL, hResource);		// len
	//New File
	FILE* pFile = fopen(NASM_EXE_NAME, "wb");
	if(pFile == NULL)	return FALSE;
	DWORD dwWriteLen = fwrite(lBuffer, 1, dwLen, pFile);	
	fclose(pFile);	
	FreeResource(hGobal);	

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CFormatBinaryCodeDlg::DeleteNasmExe
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CFormatBinaryCodeDlg::DeleteNasmExe()
{
	DeleteFile(NASM_EXE_NAME);
}	