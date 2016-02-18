// InjectSimpleCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InjectSimpleCode.h"
#include "InjectSimpleCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning(disable:4305)
#pragma warning(disable:4309)
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
// CInjectSimpleCodeDlg dialog

CInjectSimpleCodeDlg::CInjectSimpleCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInjectSimpleCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInjectSimpleCodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInjectSimpleCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInjectSimpleCodeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInjectSimpleCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CInjectSimpleCodeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INJECT, OnButtonInject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectSimpleCodeDlg message handlers

BOOL CInjectSimpleCodeDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInjectSimpleCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInjectSimpleCodeDlg::OnPaint() 
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
HCURSOR CInjectSimpleCodeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/************************************************************************/
/* Global Member                                                        */
/************************************************************************/

TCHAR g_szInjectCode[] = 
{
0xE8,0x07,0x00,0x00,0x00,
0xB8,0x50,0x1F,0x40,0x00,
0xFF,0xE0,
0x55,
0x89,0xE5,
0x83,0xEC,0x0C,
0x53,
0x56,
0x57,
0x8D,0x7D,0xF4,
0xB9,0x03,0x00,0x00,0x00,
0xB8,0x00,0x00,0x00,0x00,
0xF3,0xAB,
0xB8,0x5F,0x00,0x00,0x00,
0x05,0x00,0x70,0x40,0x00,
0x50,
0xB8,0x7B,0x1D,0x80,0x7C,
0xFF,0xD0,
0x6A,0x00,
0xB8,0x6A,0x00,0x00,0x00,
0x05,0x00,0x70,0x40,0x00,
0x50,
0xB8,0x75,0x00,0x00,0x00,
0x05,0x00,0x70,0x40,0x00,
0x50,
0x6A,0x00,
0xB8,0xEA,0x07,0x45,0x7E,
0xFF,0xD0,
0x5F,
0x5E,
0x5B,
0x83,0xC4,0x0C,
0x5D,
0xC3,
0x75,0x73,0x65,0x72,0x33,0x32,0x2E,0x64,0x6C,
0x6C,0x00,
0x49,0x6E,0x66,0x6F,0x6D,0x61,0x74,0x69,0x6F,
0x6E,0x00,
0x54,0x68,0x69,0x73,0x20,0x65,0x78,0x65,0x20,
0x77,0x61,0x73,0x20,0x49,0x6E,0x6A,0x65,0x63,
0x74,0x65,0x64,0x20,0x43,0x6F,0x64,0x65,0x2E,
0x00
};
/************************************************************************/
/* Define                                                               */
/************************************************************************/
//  2014.09.24 Ver1.00[X64/X32 PE] Start
#define X64_PE	0x8664			// 62bits PE
#define X32_PE	0x014c			// 32bits PE
#define _X32_	 1
//  2014.09.24 Ver1.00[X64/X32 PE] End
DWORD g_PEVerson = X32_PE;
void GetPEVersion();
/************************************************************************/
/* Function																*/
/************************************************************************/
void ChangeAddr(int index, DWORD dwValue);
BOOL OpenFile(char* szFileName, DWORD& dwFileSize);
//  2014.09.23 Ver1.00[Inject Code To My Section] Start
BOOL AppendSection(char* szName, DWORD dwSize, DWORD& dwFileSize);
//  2014.09.23 Ver1.00[Inject Code To My Section] End
//  2014.09.24 Ver1.00[Inject Code To My Section] Start
BOOL JudgeMemoryNotUsed(char* szBuffer, DWORD dwSize);
BOOL RemoveInfoBetweenDosHeaderAndNTHeader();	// RemoveInfoBetweenDosHeaderAndNTHeader
//  2014.09.24 Ver1.00[Inject Code To My Section] Start
BOOL InjectCode(DWORD dwFileSize, char* szFileName);
//  2014.09.25Ver1.00[Privileges] Start
BOOL Privileges();
//  2014.09.25Ver1.00[Privileges] End
// -----------------------------------------------------------//
// Function :   CInjectSimpleCodeDlg::OnButtonInject
// Return   :   void
// Comment  :   InjectCode 
// -----------------------------------------------------------//
char* g_szBuffer = NULL;
void CInjectSimpleCodeDlg::OnButtonInject() 
{
	if(Privileges() == FALSE)
	{
		MessageBox("Privileges Failed.");
		return;
	}

	char szFileName[MAX_PATH] = "*.exe";
	DWORD dwFileSize = 0;
	
	BOOL bRet = OpenFile(szFileName, dwFileSize);
	if(bRet == FALSE)
	{
		goto END;
	}
	// X32/X64
	GetPEVersion();

	bRet = AppendSection(".Inser", sizeof(g_szInjectCode), dwFileSize);
	if(bRet == FALSE)
	{
		goto END;
	}
	::MessageBox(0, "AppendSection.", 0, 0);
	
	bRet = InjectCode(dwFileSize, szFileName);

END:	
	if(bRet)
	{
		MessageBox("Inject Code Success");
	}
	else
	{
		MessageBox("Inject Code Failed");
	}
	
	if(g_szBuffer)
	{
		free(g_szBuffer);
		g_szBuffer = NULL;
	}
}

// -----------------------------------------------------------//
// Function :   OpenFile
// Param    :   char* szFileName
//              DWORD& dwFileSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL OpenFile(char* szFileName, DWORD& dwFileSize)
{
	if(g_szBuffer != NULL)	{	return FALSE;}
	// Select File
	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(ofn));
	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Exe File(*.exe)\0*.exe\0All File(*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	{	return FALSE;}

	// Open File
	HANDLE handle = CreateFile(szFileName, 
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	if(handle == NULL)
	{
		return FALSE;
	}

	DWORD  dwFileSizeHi;
	dwFileSize = GetFileSize(handle, &dwFileSizeHi);
	if(dwFileSize == 0)	
	{
		CloseHandle(handle);
		return FALSE;
	}
	// Read File
	g_szBuffer = (TCHAR*)malloc(dwFileSize);
	if(g_szBuffer == NULL)
	{
		CloseHandle(handle);
		return FALSE;
	}

	DWORD dwReadSize;
	if(ReadFile(handle, g_szBuffer, dwFileSize, &dwReadSize, NULL) == FALSE)
	{
		CloseHandle(handle);
		return FALSE;
	}

	CloseHandle(handle);
	handle = NULL;

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   InjectCode
// Param    :   DWORD dwFileSize
//              char* szFileName
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL InjectCode(DWORD dwFileSize, char* szFileName)
{
	if(g_szBuffer == NULL || dwFileSize <= 0 || szFileName == NULL)	{	return FALSE;	}
	//1) Init PE Member
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
	IMAGE_SECTION_HEADER sectionHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	DWORD dwNtHeaderSize;
//  2014.09.24 Ver1.00[X64/X32 PE] Start+
	WORD wSectionNum;
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
		dwNtHeaderSize = sizeof(ntHeader64);
		wSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		dwNtHeaderSize = sizeof(ntHeader);
		wSectionNum = ntHeader.FileHeader.NumberOfSections;
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	
//  2014.09.23 Ver1.00[Inject Code To My Section] Start
//	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + 0*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+dwNtHeaderSize + (wSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
//  2014.09.23 Ver1.00[Inject Code To My Section] End	
	//2) InjectAddress (VA)
	DWORD dwSizeRawData = sectionHeader.SizeOfRawData;
	DWORD dwPointToRawData = sectionHeader.PointerToRawData;			// Point
	DWORD dwViturlSize = sectionHeader.Misc.VirtualSize;				// ViturlSize
	DWORD dwInjectAddress = dwPointToRawData + dwViturlSize;			// Point+ViturlSize = End : Inject Code at the end
	
	DWORD mod = dwInjectAddress % 16;										// 
	if(mod != 0)
	{
		mod = 16 - mod;
		dwInjectAddress = dwInjectAddress + mod;
	}
	//3) InjectSize
	DWORD dwInjectSize = sizeof(g_szInjectCode);
	if(dwSizeRawData-dwViturlSize < (dwInjectSize + mod))
	{
		MessageBox(NULL, "Info", "No Enough Size For Inject Code.", MB_OK);
		return FALSE;
	}
	//4)Modify Inject Data(modify the API Address)
	HMODULE hModule,hMessage;
	FARPROC pfLoadLibrary1,pfMessagebox;
	hModule = LoadLibrary("Kernel32.dll");
	hMessage  = LoadLibrary("user32.dll");
	if(g_PEVerson == X64_PE)
	{
		pfLoadLibrary1 = GetProcAddress(hModule,"LoadLibraryW");
		pfMessagebox =  GetProcAddress(hMessage ,"MessageBoxW");
	}
	else 
	{
		pfLoadLibrary1 = GetProcAddress(hModule,"LoadLibraryA");
		pfMessagebox =  GetProcAddress(hMessage ,"MessageBoxA");
	}
	FreeLibrary(hModule);
	FreeLibrary(hMessage);

	ChangeAddr(0x30, (DWORD)pfLoadLibrary1);
	ChangeAddr(0x51, (DWORD)pfMessagebox);
	DWORD dwOEP;
	if(g_PEVerson == X64_PE)
	{
		dwOEP = ntHeader64.OptionalHeader.ImageBase + ntHeader64.OptionalHeader.AddressOfEntryPoint;
	}
	else
	{
		dwOEP = ntHeader.OptionalHeader.ImageBase + ntHeader.OptionalHeader.AddressOfEntryPoint;
	}

	ChangeAddr(0x06, dwOEP);
	// String Address Begin
	DWORD dwNewOEP;
	if(g_PEVerson == X64_PE)
	{
		dwNewOEP = ntHeader64.OptionalHeader.ImageBase + sectionHeader.VirtualAddress;			// sectionHeader.VirtualAddress =  new AddressOfEntryPoint
	}
	else
	{
		dwNewOEP = ntHeader.OptionalHeader.ImageBase + sectionHeader.VirtualAddress;			// sectionHeader.VirtualAddress =  new AddressOfEntryPoint
	}
	ChangeAddr(0x2A, dwNewOEP);
	ChangeAddr(0x3E, dwNewOEP);
	ChangeAddr(0x49, dwNewOEP);
	
	// String Address End
	
//	__asm
//	{
//		lea esi,g_szInjectCode
//		jmp esi
//	} 

	//5)Set Inject Data
	memcpy(g_szBuffer+dwInjectAddress, g_szInjectCode, dwInjectSize);				// Inject Data
	//6)Modify PE Info
	sectionHeader.Misc.VirtualSize = dwViturlSize + dwInjectSize + mod;				// Modify VirtualSize
//  2014.09.23 Ver1.00[Inject Code To My Section] Start	
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		ntHeader64.OptionalHeader.AddressOfEntryPoint = sectionHeader.VirtualAddress;		// Modify AddressOfEntryPoint
	}
	else
	{
		ntHeader.OptionalHeader.AddressOfEntryPoint = sectionHeader.VirtualAddress;		// Modify AddressOfEntryPoint
	}
//	2014.09.24 Ver1.00[X64/X32 PE] End
//  2014.09.23 Ver1.00[Inject Code To My Section] End	
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader64, sizeof(ntHeader64));
	}
	else
	{
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, sizeof(ntHeader));
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
//  2014.09.23 Ver1.00[Inject Code To My Section] Start	
	memcpy(g_szBuffer+dosHeader.e_lfanew+dwNtHeaderSize+sizeof(IMAGE_SECTION_HEADER)*(wSectionNum-1), &sectionHeader, sizeof(sectionHeader));
//  2014.09.23 Ver1.00[Inject Code To My Section] End
	
	//7:
	CString newFileName(szFileName);
	int index = newFileName.ReverseFind('\\');
	if(index == -1)
	{
		index = newFileName.ReverseFind('/');
	}
	if(index != -1)
	{
		newFileName = newFileName.Left(index+1) + _T("Inject_") + newFileName.Right(newFileName.GetLength()-index-1);

		FILE* pFile;
		pFile = fopen(newFileName.GetBuffer(0), "wb");
		if(pFile)
		{
			fwrite(g_szBuffer, 1, dwFileSize, pFile);
			fclose(pFile);
		}
		
		return TRUE; 
	}
	
	return FALSE; 
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

// -----------------------------------------------------------//
// Function :   ChangeAddr
// Param    :   int index
//              DWORD dwValue
// Return   :   void
// Comment  :   Change Address
// -----------------------------------------------------------//
void ChangeAddr(int index, DWORD dwValue)
{
	tag_DWORDDATA data;
	data.u.dwValue = dwValue;
	
	g_szInjectCode[index] = data.u.s.c1;
	g_szInjectCode[index+1] = data.u.s.c2;
	g_szInjectCode[index+2] = data.u.s.c3;
	g_szInjectCode[index+3] = data.u.s.c4;
	
}

// -----------------------------------------------------------//
// Function :   PEAlign
// Param    :   DWORD dwAddress
//              DWORD dwAlignment
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD PEAlign(DWORD dwAddress, DWORD dwAlignment)
{
	return ((dwAddress+dwAlignment-1)/dwAlignment)*dwAlignment;
}

//  2014.09.23 Ver1.00[Inject Code To My Section] Start	
// -----------------------------------------------------------//
// Function :   AppendSection
// Param    :   char* szName
//              DWORD dwSize
//              DWORD& dwFileSize
// Return   :   BOOL
// Comment  :   Add a Section
// -----------------------------------------------------------//
BOOL AppendSection(char* szName, DWORD dwSize, DWORD& dwFileSize)
{
	if(g_szBuffer == NULL )	{	return FALSE;	}
	//1) Init PE Member
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;

	IMAGE_SECTION_HEADER EndSectionHeader;
	IMAGE_SECTION_HEADER newSection;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	DWORD dwNtHeaderSize = sizeof(ntHeader);
	if(g_PEVerson == X64_PE)
	{
		dwNtHeaderSize = sizeof(ntHeader64);
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
	}
	else
	{
		dwNtHeaderSize = sizeof(ntHeader);
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	WORD wSectionNum ;
	if(g_PEVerson == X64_PE)
	{
		wSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		wSectionNum = ntHeader.FileHeader.NumberOfSections;
	}
//	2014.09.24 Ver1.00[X64/X32 PE] End
	memcpy(&EndSectionHeader, g_szBuffer+dosHeader.e_lfanew+dwNtHeaderSize + (wSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(EndSectionHeader));
//  2014.09.24 Ver1.00[Inject Code To My Section] Start
	//0:Judge Memory Not Used
	DWORD dwNewSecAddress = dosHeader.e_lfanew+dwNtHeaderSize+sizeof(IMAGE_SECTION_HEADER)*wSectionNum;
	if(JudgeMemoryNotUsed(g_szBuffer+dwNewSecAddress, sizeof(IMAGE_SECTION_HEADER)) == FALSE)
	{
		//RemoveInfoBetweenDosHeaderAndNTHeader
		if(RemoveInfoBetweenDosHeaderAndNTHeader() == FALSE)	return FALSE;
		MessageBox(0, "RemoveInfoBetweenDosHeaderAndNTHeader", 0, 0);
		//
		memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
//  2014.09.24 Ver1.00[X64/X32 PE] Start
		if(g_PEVerson == X64_PE)
		{
			memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
			wSectionNum = ntHeader64.FileHeader.NumberOfSections;
		}
		else
		{
			memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
			wSectionNum = ntHeader.FileHeader.NumberOfSections;
		}
//  2014.09.24 Ver1.00[X64/X32 PE] End
		memcpy(&EndSectionHeader, g_szBuffer+dosHeader.e_lfanew+dwNtHeaderSize + (wSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(EndSectionHeader));
		dwNewSecAddress = dosHeader.e_lfanew+dwNtHeaderSize+sizeof(IMAGE_SECTION_HEADER)*wSectionNum;

		if(JudgeMemoryNotUsed(g_szBuffer+dwNewSecAddress, sizeof(IMAGE_SECTION_HEADER)) == FALSE)
		{
			return FALSE;
		}
	}	
//  2014.09.24 Ver1.00[Inject Code To My Section] End
	//1:NumberOfSections++
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		ntHeader64.FileHeader.NumberOfSections = wSectionNum + 1;
	}
	else
	{
		ntHeader.FileHeader.NumberOfSections = wSectionNum + 1;
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	
	//2:New Section Info(IMAGE_SECTION_HEADER)
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	DWORD dwSecAlignSize ;
	DWORD dwFileAlignSize;
	if(g_PEVerson == X64_PE)
	{
		dwSecAlignSize = ntHeader64.OptionalHeader.SectionAlignment;
		dwFileAlignSize = ntHeader64.OptionalHeader.FileAlignment;
	}
	else
	{
		dwSecAlignSize = ntHeader.OptionalHeader.SectionAlignment;
		dwFileAlignSize = ntHeader.OptionalHeader.FileAlignment;
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	DWORD dwSizeOfRawData = PEAlign(dwSize, dwFileAlignSize);				// 
	DWORD dwVirtualSize = PEAlign(dwSizeOfRawData, dwSecAlignSize);	//
	DWORD dwPointerToRawData = PEAlign(EndSectionHeader.PointerToRawData+EndSectionHeader.SizeOfRawData, dwFileAlignSize);
	DWORD dwVirtualAddress = PEAlign(EndSectionHeader.VirtualAddress+EndSectionHeader.Misc.VirtualSize, dwSecAlignSize);

	memset(&newSection, 0x00, sizeof(newSection));
	newSection.PointerToRawData = dwPointerToRawData;			//PointerToRawData 
	newSection.SizeOfRawData = dwSizeOfRawData;					//SizeOfRawData
	newSection.VirtualAddress = dwVirtualAddress;				//VirtualAddress
	newSection.Misc.VirtualSize = 0;							//VirtualSize=0
	newSection.Characteristics = 0xC0000040;					//Characteristics
	memcpy(newSection.Name, szName, IMAGE_SIZEOF_SHORT_NAME);	//name
	
	//3:Append new Section Header
	DWORD dw = dosHeader.e_lfanew+dwNtHeaderSize + (wSectionNum)*sizeof(IMAGE_SECTION_HEADER);
	memcpy(g_szBuffer+dw, &newSection, sizeof(newSection));
	//4:Modify NT Header Info: [ImageSize,NumberOfSections]
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		ntHeader64.OptionalHeader.SizeOfImage += dwSizeOfRawData;
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader64, dwNtHeaderSize);
	}
	else
	{
		ntHeader.OptionalHeader.SizeOfImage += dwSizeOfRawData;
		memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, dwNtHeaderSize);
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	
	//5:Modify PE File Size 
	char* szTemp = (char* )malloc(dwFileSize);
	memcpy(szTemp, g_szBuffer, dwFileSize);
	free(g_szBuffer);
	g_szBuffer = NULL;
	g_szBuffer = (char* )malloc(dwFileSize+dwSizeOfRawData);
	memset(g_szBuffer, 0x00, dwFileSize+dwSizeOfRawData);
	memcpy(g_szBuffer, szTemp, dwFileSize);
	free(szTemp);
	szTemp = NULL;
	dwFileSize += dwSizeOfRawData;

	return TRUE;
}
//  2014.09.23 Ver1.00[Inject Code To My Section] End

//  2014.09.24 Ver1.00[Inject Code To My Section] Start
// -----------------------------------------------------------//
// Function :   JudgeMemoryNotUsed
// Param    :   char* szBuffer
//              DWORD dwSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL JudgeMemoryNotUsed(char* szBuffer, DWORD dwSize)
{
	try
	{
		for(DWORD index = 0; index < dwSize; index++)
		{
			if(*(szBuffer+index) != 0)
			{
				return FALSE;
			}
		}
		return TRUE;
	}	
	catch (CException*)
	{
		return FALSE;
	}

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   RemoveInfoBetweenDosHeaderAndNTHeader
// Return   :   BOOL
// Comment  :   Remove Info Between DosHeader and NtHeader
// -----------------------------------------------------------//
BOOL RemoveInfoBetweenDosHeaderAndNTHeader()
{
	if(g_szBuffer == NULL)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;

	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
	DWORD dwNTHeaderSize = 0;
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		dwNTHeaderSize = sizeof(ntHeader64);
	}
	else
	{
		dwNTHeaderSize = sizeof(ntHeader);
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	DWORD dwSectionNum;
	if(g_PEVerson == X64_PE)
	{
		dwSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		dwSectionNum = ntHeader.FileHeader.NumberOfSections;
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	
	
	DWORD dwRemainSize = dosHeader.e_lfanew - dwDosHeaderSize;
	if(dwRemainSize <= 0)
	{
		MessageBox(0, "No Size Between Dos and NtHeader", 0, 0);
		return FALSE;
	}
	//3:Copy IMAGE_SECTION_HEADER
	DWORD dwSectionOldIndex = dosHeader.e_lfanew+dwNTHeaderSize;
	DWORD dwSectionNewIndex = dwSectionOldIndex - dwRemainSize;
	DWORD dwSectionSize = dwSectionHeaderSize * dwSectionNum;
	
	char* oldBuffer = (char* )malloc(dwSectionSize);
	memcpy(oldBuffer, g_szBuffer+dwSectionOldIndex, dwSectionSize);
//	memset(g_szBuffer+dwSectionOldIndex, 0x00, dwSectionSize);
	memset(g_szBuffer+dwSectionOldIndex-dwNTHeaderSize, 0x00, dwNTHeaderSize+dwSectionSize);
	memcpy(g_szBuffer+dwSectionNewIndex, oldBuffer, dwSectionSize);
	free(oldBuffer);
	oldBuffer = NULL;
	//2:Copy IMAGE_NT_HEADERS
//  2014.09.24 Ver1.00[X64/X32 PE] Start
	if(g_PEVerson == X64_PE)
	{
		memcpy(g_szBuffer+dwDosHeaderSize, &ntHeader64, dwNTHeaderSize);
	}
	else
	{
		memcpy(g_szBuffer+dwDosHeaderSize, &ntHeader, dwNTHeaderSize);
	}
//  2014.09.24 Ver1.00[X64/X32 PE] End
	//1:Mdoify IMAGE_DOS_HEADER
	dosHeader.e_lfanew = dwDosHeaderSize;
	memcpy(g_szBuffer, &dosHeader, dwDosHeaderSize);
	
	return TRUE;
}

//  2014.09.24 Ver1.00[X64/X32 PE] Start
// -----------------------------------------------------------//
// Function :   GetPEVersion
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void GetPEVersion()
{
	if(g_szBuffer == NULL)	return;

	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	if(ntHeader.FileHeader.Machine == X32_PE)
	{
		g_PEVerson = X32_PE;
	}
	else if(ntHeader.FileHeader.Machine == X64_PE)
	{
		g_PEVerson = X64_PE;
	}
}
//  2014.09.24 Ver1.00[X64/X32 PE] End

//  2014.09.24 Ver1.00[Inject Code To My Section] End


//  2014.09.25Ver1.00[Privileges] Start
BOOL Privileges()
{
    HANDLE Token;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Token))
    {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (AdjustTokenPrivileges(Token, 0, &tp, sizeof(tp), NULL, NULL) == 0)
		{
			CloseHandle(Token);
            return FALSE; //FAIL
        }
        else
		{
			CloseHandle(Token);
            return TRUE; //SUCCESS
        }
    }
    return FALSE;
}
//  2014.09.25 Ver1.00[Privileges] End