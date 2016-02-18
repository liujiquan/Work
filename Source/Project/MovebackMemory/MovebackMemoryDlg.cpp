//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   MovebackMemoryDlg.cpp
//* Author   :   liujiquan
//* DateTime :   9/22/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "MovebackMemory.h"
#include "MovebackMemoryDlg.h"

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
// CMovebackMemoryDlg dialog

CMovebackMemoryDlg::CMovebackMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMovebackMemoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMovebackMemoryDlg)
	m_SectionNum = 0;
	m_FileSize = _T("");
	m_offset = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMovebackMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMovebackMemoryDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT4, m_SectionNum);
	DDX_Text(pDX, IDC_EDIT3, m_FileSize);
	DDX_Text(pDX, IDC_EDIT1, m_offset);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMovebackMemoryDlg, CDialog)
	//{{AFX_MSG_MAP(CMovebackMemoryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Open, OnBUTTONOpen)
	ON_BN_CLICKED(IDC_BUTTON_MOVEBACK, OnButtonMoveback)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_ExtendedPeHeader, OnBUTTONExtendedPeHeader)
	ON_BN_CLICKED(IDC_BUTTON_InsertSection, OnBUTTONInsertSection)
	ON_BN_CLICKED(IDC_BUTTON_InsertSection2, OnBUTTONInsertSection2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovebackMemoryDlg message handlers

BOOL CMovebackMemoryDlg::OnInitDialog()
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
	InitListColumn();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMovebackMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMovebackMemoryDlg::OnPaint() 
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
HCURSOR CMovebackMemoryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/************************************************************************/
/* Struct                                                               */
/************************************************************************/
typedef struct tag_SECTIONINFO
{
	UINT	ID;
	BYTE	NAME[IMAGE_SIZEOF_SHORT_NAME];
	DWORD	RVA;
	DWORD	PointerToRawData;
	DWORD	Size;
	DWORD	MaxSize;
	DWORD	RemainSize;			// MaxSize - Size
}SECTIONINFO, *PSECTIONINFO;

/************************************************************************/
/* Gbloabl Member                                                       */
/************************************************************************/
char* g_szBuffer = NULL;				// Buffer
char g_szFileName[MAX_PATH];			// FileName
DWORD g_dwFileSize = 0;					// FileSize
SECTIONINFO	m_SectionInfo[15];			// Data
/************************************************************************/
/* Global Function                                                      */
/************************************************************************/
BOOL OpenFile();			// Open File
BOOL CreateNewFile();		// CreateFile
BOOL MoveBackFile(DWORD dwOffsetSize);
void Release();
BOOL RemoveInfoBetweenDosHeaderAndNTHeader();
BOOL ExtendPEHeader(DWORD dwSize);
bool MoveBuffer(char* szBuffer, DWORD dwRVA,  DWORD dwSize,  DWORD dwOffset);
bool MoveBuffer2(char* szBuffer, DWORD dwRVA,  DWORD dwSize,  DWORD dwOffset);
BOOL InserSectionHeader(DWORD dwSectionSize, char* sectionName);
BOOL ExtendedPESize(DWORD dwExtendSize);

CMovebackMemoryDlg::~CMovebackMemoryDlg()
{
	Release();
}
// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::OnBUTTONOpen
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMovebackMemoryDlg::OnBUTTONOpen() 
{

	// Open File
	BOOL bRet = OpenFile();
	if(bRet == FALSE)
	{
		return;
	}
	// Set Info
	SetListInfo();

}

// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::OnButtonMoveback
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMovebackMemoryDlg::OnButtonMoveback() 
{
	UpdateData(TRUE);	

	ExtendedPESize(0x1000);
	MoveBackFile(0x1000);

	SetListInfo();
}

// -----------------------------------------------------------//
// Function :   MoveBackFile
// Param    :   WORD nIndex
//              DWORD dwOffsetSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL MoveBackFile(DWORD dwOffsetSize)
{
	if(dwOffsetSize <= 0 )
	{
		return FALSE;
	}

	//
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader;

	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		
	DWORD dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;
	if(dwOffsetSize % dwSectionAlignment)
	{
		return FALSE;
	}
	WORD nSectionNum = ntHeader.FileHeader.NumberOfSections;
	//1:
	DWORD dwOldPointToRawData;
	DWORD dwUseSize;
	for(int index = nSectionNum - 1; index > 0; index--)
	{
		//1:Section Info
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		dwOldPointToRawData= sectionHeader.PointerToRawData;		// PointerToRawData
		dwUseSize = sectionHeader.Misc.VirtualSize;					// VirtualSize
		
		sectionHeader.PointerToRawData += dwOffsetSize;
		memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), &sectionHeader, sizeof(sectionHeader));
		
		//2 Section Data
		MoveBuffer(g_szBuffer, dwOldPointToRawData, dwUseSize, dwOffsetSize);
	}
		
	// .text Section
	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	dwOldPointToRawData= sectionHeader.PointerToRawData;		// PointerToRawData
	dwUseSize = sectionHeader.Misc.VirtualSize;				// VirtualSize

	sectionHeader.SizeOfRawData +=  dwOffsetSize;
	memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(IMAGE_NT_HEADERS) + index*sizeof(IMAGE_SECTION_HEADER), &sectionHeader, sizeof(sectionHeader));
	
	//7:
	CreateNewFile();
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CreateNewFile
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CreateNewFile()
{
	CString newFileName(g_szFileName);
	int index = newFileName.ReverseFind('\\');
	if(index == -1)
	{
		index = newFileName.ReverseFind('/');
	}
	if(index != -1)
	{
		newFileName = newFileName.Left(index+1) + _T("New") + newFileName.Right(newFileName.GetLength()-index-1);
		
		FILE* pFile;
		pFile = fopen(newFileName.GetBuffer(0), "wb");
		if(pFile)
		{
			fwrite(g_szBuffer, 1, g_dwFileSize, pFile);
			fclose(pFile);
		}
		
		return TRUE; 
	}
	
	return FALSE;
}

// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::InitListColumn
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMovebackMemoryDlg::InitListColumn()
{
	CRect rect;
	GetClientRect(&rect);
	int wid = rect.Width();

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "ID", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(1, "Name", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(2, "RVA", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(3, "PointerToRawData", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(4, "Size", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(5, "MaxSize", LVCFMT_LEFT, wid/7);
	m_list.InsertColumn(6, "RemainSize", LVCFMT_LEFT, wid/7);
}

// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::SetListInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMovebackMemoryDlg::SetListInfo()
{
	if(g_szBuffer == NULL || g_dwFileSize <= 0 || g_szFileName == NULL)	{	return ;	}
	m_list.DeleteAllItems();
	m_FileSize.Format("%X", g_dwFileSize);
	memset(m_SectionInfo, 0x00, sizeof(SECTIONINFO)*15);
	
	//1) Init PE Member
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader;
	WORD wSectionNum;							// Section Num

	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	wSectionNum = ntHeader.FileHeader.NumberOfSections;
	m_SectionNum = wSectionNum;
	for(WORD i = 0; i < wSectionNum; i++)
	{
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + i*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		//
		CString strTemp;
		m_list.InsertItem(i,"");
		//ID
		strTemp.Format("%02d", i);
		m_list.SetItemText(i, 0, strTemp);
		//Name
		m_list.SetItemText(i, 1, (char*)sectionHeader.Name);
		//RVA
		strTemp.Format("%08X", sectionHeader.VirtualAddress);
		m_list.SetItemText(i, 2, strTemp);
		//PointToRawData
		strTemp.Format("%08X", sectionHeader.PointerToRawData);
		m_list.SetItemText(i, 3, strTemp);
		//Size
		strTemp.Format("%08X", sectionHeader.Misc.VirtualSize);
		m_list.SetItemText(i, 4, strTemp);
		//MaxSize
		strTemp.Format("%08X", sectionHeader.SizeOfRawData);
		m_list.SetItemText(i, 5, strTemp);
		//RemainSize
		strTemp.Format("%08X", sectionHeader.SizeOfRawData-sectionHeader.Misc.VirtualSize);
		m_list.SetItemText(i, 6, strTemp);

		m_SectionInfo[i].ID = i;
		memcpy(m_SectionInfo[i].NAME, sectionHeader.Name,IMAGE_SIZEOF_SHORT_NAME);
		m_SectionInfo[i].RVA = sectionHeader.VirtualAddress;
		m_SectionInfo[i].PointerToRawData = sectionHeader.PointerToRawData;
		m_SectionInfo[i].Size = sectionHeader.Misc.VirtualSize;
		m_SectionInfo[i].MaxSize = sectionHeader.SizeOfRawData;
		m_SectionInfo[i].RemainSize = sectionHeader.SizeOfRawData-sectionHeader.Misc.VirtualSize;
	}

	UpdateData(FALSE);
}

// -----------------------------------------------------------//
// Function :   OpenFile
// Return   :   BOOL
// Comment  :   Open File
// -----------------------------------------------------------//
BOOL OpenFile()
{
	if(g_szBuffer != NULL)	{	return FALSE;}
	// Select File
	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(ofn));
	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = g_szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Exe File(*.exe)\0*.exe\0All File(*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	{	return FALSE;}
	
	// Open File
	HANDLE handle = CreateFile(g_szFileName, 
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
	g_dwFileSize = GetFileSize(handle, &dwFileSizeHi);
	if(g_dwFileSize == 0)	
	{
		CloseHandle(handle);
		return FALSE;
	}
	// Read File
	g_szBuffer = (TCHAR*)malloc(g_dwFileSize);
	if(g_szBuffer == NULL)
	{
		CloseHandle(handle);
		return FALSE;
	}
	
	DWORD dwReadSize;
	if(ReadFile(handle, g_szBuffer, g_dwFileSize, &dwReadSize, NULL) == FALSE)
	{
		CloseHandle(handle);
		free(g_szBuffer);
		g_szBuffer = NULL;
		return FALSE;
	}
	
	CloseHandle(handle);
	handle = NULL;
	
	return TRUE;
}


void Release()
{
	// Release
	if(g_szBuffer)
	{
		free(g_szBuffer);
		g_szBuffer = NULL;
	}
}

// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::OnButton2
// Return   :   void
// Comment  :   Remove Info Between DosHeader and NtHeader
// -----------------------------------------------------------//
void CMovebackMemoryDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	RemoveInfoBetweenDosHeaderAndNTHeader();
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
	IMAGE_NT_HEADERS ntHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
	DWORD dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS);
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
	DWORD dwSectionNum = ntHeader.FileHeader.NumberOfSections;

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
	memset(g_szBuffer+dwSectionOldIndex, 0x00, dwSectionSize);
	memcpy(g_szBuffer+dwSectionNewIndex, oldBuffer, dwSectionSize);
	free(oldBuffer);
	oldBuffer = NULL;
	//2:Copy IMAGE_NT_HEADERS
	memcpy(g_szBuffer+dwDosHeaderSize, &ntHeader, dwNTHeaderSize);
	//1:Mdoify IMAGE_DOS_HEADER
	dosHeader.e_lfanew = dwDosHeaderSize;
	memcpy(g_szBuffer, &dosHeader, dwDosHeaderSize);

	CreateNewFile();

	return TRUE;
}

void CMovebackMemoryDlg::OnBUTTONExtendedPeHeader() 
{
	// TODO: Add your control notification handler code here
	ExtendPEHeader(0x200);
}

BOOL ExtendPEHeader(DWORD dwSize)
{
	if(g_szBuffer == NULL)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
	DWORD dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS);
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
	DWORD dwSectionNum = ntHeader.FileHeader.NumberOfSections;

	DWORD dwSizeofHeader = ntHeader.OptionalHeader.SizeOfHeaders;	//dwDosHeaderSize+ zhongjian +  dwNTHeaderSize+ dwSectionHeaderSize*dwSectionNum;
	DWORD dwNewSizeofHeader	= dwSizeofHeader + dwSize;

	//Modify SizeOfHeader
	ntHeader.OptionalHeader.SizeOfHeaders = dwNewSizeofHeader;
	memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, dwNTHeaderSize);
	//Modify All Section PointerToRawData Data
	for(int i = dwSectionNum-1; i >= 0; i--)
	{
		memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + i*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		DWORD oldPointerToRawData = sectionHeader.PointerToRawData ;
		DWORD newPointerToRawData = sectionHeader.PointerToRawData + dwSize;
		sectionHeader.PointerToRawData = newPointerToRawData;
		//sectionHeader.VirtualAddress += dwSize;
		memcpy(g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + i*sizeof(IMAGE_SECTION_HEADER), &sectionHeader, sizeof(sectionHeader));
		DWORD dwVirtualSize = sectionHeader.Misc.VirtualSize;
		if(i == dwSectionNum - 1)
		{
			if(dwVirtualSize + dwSize > sectionHeader.SizeOfRawData)
			{
				int iii = dwVirtualSize + dwSize - sectionHeader.SizeOfRawData;
				dwVirtualSize -= iii;
			}
		}
		MoveBuffer(g_szBuffer, oldPointerToRawData, dwVirtualSize, dwSize);
	}
	//Move All Section Data dwSize
	
	CreateNewFile();

	return TRUE;
}

bool MoveBuffer(char* szBuffer, DWORD dwRVA,  DWORD dwSize,  DWORD dwOffset)
{
	char* szTemp = (char*)malloc(dwSize);
	if(szTemp == NULL)	return false;

	try
	{
		memcpy(szTemp, szBuffer+dwRVA, dwSize);
		memset(szBuffer+dwRVA, 0x00, dwSize);
		memcpy(szBuffer+dwRVA+dwOffset, szTemp, dwSize);

		free(szTemp);
		szTemp = NULL;
	}
	catch (CException* e)
	{
		return false;
	}
	
	return true;
}

bool MoveBuffer2(char* szBuffer, DWORD dwRVA, DWORD dwSize,  DWORD dwOffset)
{
	try
	{
		if(dwOffset > 0)
		{
			for(DWORD i = dwSize - 1; i >= 0; i--)
			{
				*(szBuffer+dwRVA+i+dwOffset) = *(szBuffer+dwRVA+i);
			}
		}
		else if(dwOffset < 0)
		{
			for(DWORD i = 0; i < dwSize; i++)
			{
				*(szBuffer+dwRVA+i+dwOffset) = *(szBuffer+dwRVA+i);
			}
		}
		else
		{
			return true;
		}
	}
	catch (CException* e)
	{
		return false;
	}
	
	return TRUE;
}



void CMovebackMemoryDlg::OnBUTTONInsertSection() 
{	
	InserSectionHeader(0x1000,".Insert");
}


BOOL InserSectionHeader(DWORD dwSectionSize, char* sectionName)
{
	if(g_szBuffer == NULL)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	IMAGE_SECTION_HEADER sectionHeader,newSectionHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	DWORD dwDosHeaderSize = sizeof(IMAGE_DOS_HEADER);
	DWORD dwNTHeaderSize = sizeof(IMAGE_NT_HEADERS);
	DWORD dwSectionHeaderSize = sizeof(IMAGE_SECTION_HEADER);
	DWORD dwSectionNum = ntHeader.FileHeader.NumberOfSections;
	DWORD dwInserAddress = dosHeader.e_lfanew + dwNTHeaderSize + dwSectionHeaderSize * dwSectionNum;
	memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + (dwSectionNum-1)*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
	
	//Set Section Count
	ntHeader.FileHeader.NumberOfSections += 1;
	memcpy(g_szBuffer+dosHeader.e_lfanew, &ntHeader, sizeof(ntHeader));
	// New Section
	memset(&newSectionHeader, 0x00, dwSectionHeaderSize);
	memcpy(&newSectionHeader, &sectionHeader, dwSectionHeaderSize);
	memcpy(newSectionHeader.Name, sectionName, IMAGE_SIZEOF_SHORT_NAME);
	newSectionHeader.Misc.VirtualSize = 0x100;
	newSectionHeader.PointerToRawData = sectionHeader.PointerToRawData + sectionHeader.SizeOfRawData;
	newSectionHeader.SizeOfRawData = dwSectionSize;
	newSectionHeader.VirtualAddress = newSectionHeader.PointerToRawData;
	// Insert New Section Info
	memcpy(g_szBuffer+dwInserAddress, &newSectionHeader, dwSectionHeaderSize);
	
	// Insert new Section Data
	char* szTemp = (char* )malloc(g_dwFileSize);
	memcpy(szTemp, g_szBuffer, g_dwFileSize);
	free(g_szBuffer);
	g_szBuffer = NULL;
	g_szBuffer = (char* )malloc(g_dwFileSize+dwSectionSize);
	memset(g_szBuffer, 0x00, g_dwFileSize+dwSectionSize);
	memcpy(g_szBuffer, szTemp, g_dwFileSize);
	memcpy(g_szBuffer+g_dwFileSize, "This is a section by liujiquan.", strlen("This is a section by liujiquan."));
	free(szTemp);
	szTemp = NULL;

	
	g_dwFileSize += dwSectionSize;

	CreateNewFile();

	return TRUE;
}


// -----------------------------------------------------------//
// Function :   CMovebackMemoryDlg::OnBUTTONInsertSection2
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMovebackMemoryDlg::OnBUTTONInsertSection2() 
{
	// TODO: Add your control notification handler code here
	ExtendedPESize(0x1000);
}

// -----------------------------------------------------------//
// Function :   ExtendedPESize
// Param    :   DWORD dwExtendSize
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL ExtendedPESize(DWORD dwExtendSize)
{
	if(g_szBuffer == NULL || dwExtendSize <= 0)	return FALSE;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	
	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
	memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
	
	DWORD dwSectionAlignment = ntHeader.OptionalHeader.SectionAlignment;

	if(dwExtendSize % dwSectionAlignment != 0)
	{
		return FALSE;
	}

	// Insert new Section Data
	char* szTemp = (char* )malloc(g_dwFileSize);
	memcpy(szTemp, g_szBuffer, g_dwFileSize);
	free(g_szBuffer);
	g_szBuffer = NULL;
	g_szBuffer = (char* )malloc(g_dwFileSize+dwExtendSize);
	memset(g_szBuffer, 0x00, g_dwFileSize+dwExtendSize);
	memcpy(g_szBuffer, szTemp, g_dwFileSize);
	free(szTemp);
	szTemp = NULL;
	
	
	g_dwFileSize += dwExtendSize;
	
	CreateNewFile();

	return TRUE;
}

