// TesWinBrowseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TesWinBrowse.h"
#include "TesWinBrowseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTesWinBrowseDlg dialog

CTesWinBrowseDlg::CTesWinBrowseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTesWinBrowseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTesWinBrowseDlg)
	m_strFilePath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTesWinBrowseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTesWinBrowseDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strFilePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTesWinBrowseDlg, CDialog)
	//{{AFX_MSG_MAP(CTesWinBrowseDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTesWinBrowseDlg message handlers
/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define DLL_NAME	"exe_WinBrowse.dll"
#define FUNC_NAME	"browse"
BOOL FormatResourceToDllFile(UINT nID, LPCTSTR dllName);

BOOL CTesWinBrowseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// Find
	BOOL bRet = FormatResourceToDllFile(IDR_DLL1, DLL_NAME);
	return bRet;  // return TRUE  unless you set the focus to a control
}

// -----------------------------------------------------------//
// Function :   CTesWinBrowseDlg::~CTesWinBrowseDlg
// Return   :   
// Comment  :   DeleteFile
// -----------------------------------------------------------//
CTesWinBrowseDlg::~CTesWinBrowseDlg()
{
	::DeleteFile(DLL_NAME);
}

// -----------------------------------------------------------//
// Function :   FormatResourceToDllFile
// Param    :   UINT		nID
//              LPCTSTR		dllName
// Return   :   BOOL
// Comment  :   ResourceToDllFile
// -----------------------------------------------------------//
BOOL FormatResourceToDllFile(UINT nID, LPCTSTR dllName)
{
	// Find
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(nID), TEXT("dll"));
	if(hResource == NULL)
	{
		return FALSE;
	}
	DWORD dwResSize = SizeofResource(NULL, hResource);
	if(dwResSize == 0)
	{
		return FALSE;
	}
	// Load
	HGDIOBJ hGobal = LoadResource(NULL, hResource);
	if(hGobal == NULL)
	{
		return FALSE;
	}
	// Lockmemory
	LPVOID pBuffer = LockResource(hGobal);
	if(pBuffer == NULL)
	{
		FreeResource(hGobal);
		return FALSE;
	}
	// export Dll File
	FILE* pFile = fopen(dllName, "wb");
	if(pFile != NULL)
	{
		DWORD dwWriteSize = fwrite(pBuffer, sizeof(char), dwResSize, pFile);
		fclose(pFile);
		if(dwWriteSize == dwResSize)
		{
			FreeResource(hGobal);
			return TRUE;
		}
	}
	
	FreeResource(hGobal);
	return FALSE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTesWinBrowseDlg::OnPaint() 
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
HCURSOR CTesWinBrowseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CTesWinBrowseDlg::OnButtonOpen
// Return   :   void
// Comment  :   Open File
// -----------------------------------------------------------//
extern "C"  bool browse(const char* pszFilePath);		// Method1
typedef  bool (*browseFunc)(const char* pszFilePath);	// Method2
void CTesWinBrowseDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
/*	
	// Method1
	bool b = browse(m_strFilePath);
	if(b)
	{
		MessageBox("Open File Succeed");
	}
	else
	{
		MessageBox("Open File Failed");
	}
*/
	// Method2
	HMODULE hDll = LoadLibrary(DLL_NAME);
	if(hDll)
	{
		browseFunc func = (browseFunc)GetProcAddress(hDll, FUNC_NAME);
		if(func)
		{
			bool b = func(m_strFilePath);
			if(b)
			{
				MessageBox("Open File Succeed");
			}
			else
			{
				MessageBox("Open File Failed");
			}
		}
		FreeLibrary(hDll);
	}
}
