// PEInjectDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PEInjectDemo.h"
#include "PEInjectDemoDlg.h"

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
// CPEInjectDemoDlg dialog

CPEInjectDemoDlg::CPEInjectDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPEInjectDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPEInjectDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEInjectDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPEInjectDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPEInjectDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CPEInjectDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPEInjectDemoDlg message handlers  66B8 00
void ChangeAddr(int index, DWORD dwValue);
TCHAR g_szInjectCode[] = 
//{
//	0xB8,0x50,0x1F,0x40,0x00,	// mov eax, 0x00401f50
//	0xFF,0xE0					// jmp eax
//};				
{
	0xE8,0x0B,0x00,0x00,0x00,								// call func0
	0x75,0x73,0x65,0x72,0x33,0x32,0x2E,0x64,0x6C,0x6C,0x00, // db 'user32.dll',0  
															// func0 :
	0xB8,0x7B,0x1D,0x80,0x7C,								// mov eax,7c801d7bH   ;LOADLIBRARYA
	0xFF,0xD0,												// CALL eax
	0x6A,0x00,												// push 0           
	0xE8,0x0B,0x00,0x00,0x00,								// call Func1
	0x49,0x6E,0x66,0x6F,0x6D,0x61,0x74,0x69,0x6F,0x6E,0x00, // db "Infomation",0   
															// Func1:
	0xE8,0x1C,0x00,0x00,0x00,								// call Func2
	0x54,0x68,0x69,0x73,0x20,0x65,0x78,0x65,0x20,			// db "This exe was Injected Code.",0
	0x77,0x61,0x73,0x20,0x49,0x6E,0x6A,0x65,0x63, 
	0x74,0x65,0x64,0x20,0x43,0x6F,0x64,0x65,0x2E,0x00,
															// Func2:
	0x6A,0x00,												// push 0  
	0xB8,0xEA,0x07,0x45,0x7E,								// mov eax,7e4507eaH  ; 7e4507eaH  MESSAGEBOXA 
	0xFF,0xD0,												// call eax
	0xB8,0x50,0x1F,0x40,0x00,								// mov eax,00401f50H  ;    
	0xFF,0xE0												// jmp eax
};

BOOL CPEInjectDemoDlg::OnInitDialog()
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
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader;


	//1) Read File Buffer
	HANDLE handle = CreateFile("C:\\Documents and Settings\\XPMUser\\Desktop\\WriteFloppy.exe",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(handle == NULL)
	{
		return;
	}
	
	DWORD dwFileSize, dwFileSizeHi;
	dwFileSize = GetFileSize(handle, &dwFileSizeHi);
	if(dwFileSize == 0)	
	{
		CloseHandle(handle);
		return;
	}
	TCHAR* szBuffer = (TCHAR*)malloc(dwFileSize);
	
	DWORD dwReadSize;
	ReadFile(handle, szBuffer, dwFileSize, &dwReadSize, NULL);
	//2:
	memcpy(&dosHeader, szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	memcpy(&sectionHeader, szBuffer+dosHeader.e_lfanew+sizeof(ntHeader), sizeof(sectionHeader));
	//3: 
	DWORD dwSizeRawData = sectionHeader.SizeOfRawData;
	DWORD dwPointToRawData = sectionHeader.PointerToRawData;	// Point
	DWORD dwSize = sectionHeader.Misc.VirtualSize;				// Size
	DWORD dwInjectAddress = dwPointToRawData + dwSize;			// Point+size = End

	DWORD mod = dwInjectAddress%16;
	if(mod != 0)
	{
		mod = 16 - mod;
		dwInjectAddress = dwInjectAddress + mod;
	}
	
	// InjectSize
	DWORD dwInjectSize = sizeof(g_szInjectCode);
	if(dwSizeRawData-dwSize < (dwInjectSize + mod))
	{
		MessageBox("No memory");
	}
	//4:Inject Data
	HMODULE hModule,hMessage;
	FARPROC pfLoadLibrary,pfMessagebox;
	hModule = GetModuleHandle("Kernel32.dll");
	pfLoadLibrary = GetProcAddress(hModule,"LoadLibraryA");
	hMessage  = LoadLibrary("user32.dll");
    pfMessagebox =  GetProcAddress(hMessage ,"MessageBoxA");
	ChangeAddr(0x11, (DWORD)pfLoadLibrary);
	ChangeAddr(0x4D, (DWORD)pfMessagebox);

	DWORD dwOEP = ntHeader.OptionalHeader.ImageBase + ntHeader.OptionalHeader.AddressOfEntryPoint;
	ChangeAddr(0x54, dwOEP);
	memcpy(szBuffer+dwInjectAddress, g_szInjectCode, dwInjectSize);		// Inject Data
	//5: Modify Buffer
	sectionHeader.Misc.VirtualSize = dwSize + dwInjectSize + mod;		// Inject Size
	
	ntHeader.OptionalHeader.AddressOfEntryPoint = ntHeader.OptionalHeader.BaseOfCode + dwInjectAddress - dwPointToRawData;
	//6:
	memcpy(szBuffer+dosHeader.e_lfanew, &ntHeader, sizeof(ntHeader));
	memcpy(szBuffer+dosHeader.e_lfanew+sizeof(ntHeader), &sectionHeader, sizeof(sectionHeader));
	//7:
	FILE* pFile;
	pFile = fopen("InjectExe.exe", "wb");
	if(pFile)
	{
		fwrite(szBuffer, 1, dwFileSize, pFile);
		fclose(pFile);
		MessageBox("Inject Ok");
	}
	free(szBuffer);
	CloseHandle(handle);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPEInjectDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPEInjectDemoDlg::OnPaint() 
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
HCURSOR CPEInjectDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPEInjectDemoDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	::MessageBox(NULL, "1","1",0);
	_asm
	{
		mov eax, 0x00001f50
		jmp eax
	}
}

struct tag_DWORDDATA
{
	union
	{
		DWORD dwValue;
		struct{
			CHAR c1;
			CHAR c2;
			CHAR c3;
			CHAR c4;
		}s;
	}u;
};
void ChangeAddr(int index, DWORD dwValue)
{
	tag_DWORDDATA data;
	data.u.dwValue = dwValue;

	g_szInjectCode[index] = data.u.s.c1;
	g_szInjectCode[index+1] = data.u.s.c2;
	g_szInjectCode[index+2] = data.u.s.c3;
	g_szInjectCode[index+3] = data.u.s.c4;

}