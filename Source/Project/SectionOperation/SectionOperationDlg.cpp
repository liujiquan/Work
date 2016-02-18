// SectionOperationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SectionOperation.h"
#include "SectionOperationDlg.h"
#include "_SectionUtil.h"
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
// CSectionOperationDlg dialog

extern char*	g_szBuffer;						// Buffer
extern char		g_szFileName[MAX_PATH];			// FileName
extern DWORD	g_dwFileSize;					// FileSize
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
extern DWORD	g_PEVerson;						// PE Version
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End

CSectionOperationDlg::CSectionOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectionOperationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSectionOperationDlg)
	m_FileSize = _T("");
	m_sectionAlignment = _T("");
	m_SecionData = _T("");
	m_ExtendedSize = _T("");
	m_SectionName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSectionOperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSectionOperationDlg)
	DDX_Control(pDX, IDC_LIST1, m_SectionList);
	DDX_Text(pDX, IDC_EDIT1, m_FileSize);
	DDX_Text(pDX, IDC_EDIT2, m_sectionAlignment);
	DDX_Text(pDX, IDC_RICHEDIT1, m_SecionData);
	DDX_Text(pDX, IDC_EDIT3, m_ExtendedSize);
	DDX_Text(pDX, IDC_EDIT4, m_SectionName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSectionOperationDlg, CDialog)
	//{{AFX_MSG_MAP(CSectionOperationDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OpenFIle, OnBUTTONOpenFIle)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEDOSNT, OnButtonRemovedosnt)
	ON_BN_CLICKED(IDC_BUTTON_CREATEFILE, OnButtonCreatefile)
	ON_BN_CLICKED(IDC_BUTTON_InsertSection, OnBUTTONInsertSection)
	ON_BN_CLICKED(IDC_BUTTON_EXTENEDSECSIZE, OnButtonExtenedsecsize)
	ON_BN_CLICKED(IDC_BUTTON_DELETESEC, OnButtonDeletesec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSectionOperationDlg message handlers
// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::~CSectionOperationDlg
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CSectionOperationDlg::~CSectionOperationDlg()
{
	Release();
}

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::OnInitDialog
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CSectionOperationDlg::OnInitDialog()
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

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::OnSysCommand
// Param    :   UINT nID
//              LPARAM lParam
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::OnPaint
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::OnPaint() 
{
	CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSectionOperationDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::InitListColumn
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::InitListColumn()
{
	CRect rect;
	GetClientRect(&rect);
	int wid = rect.Width();
	
	m_SectionList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_SectionList.InsertColumn(0, "ID", LVCFMT_LEFT, wid/6);
	m_SectionList.InsertColumn(1, "Name", LVCFMT_LEFT, wid/6);
	m_SectionList.InsertColumn(2, "RVA", LVCFMT_LEFT, wid/6);
	m_SectionList.InsertColumn(3, "PointerToRawData", LVCFMT_LEFT, wid/6);
	m_SectionList.InsertColumn(4, "Size", LVCFMT_LEFT, wid/6);
	m_SectionList.InsertColumn(5, "MaxSize", LVCFMT_LEFT, wid/6);
}

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::SetListInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::SetListInfo()
{
	if(g_szBuffer == NULL || g_dwFileSize <= 0 || g_szFileName == NULL)	{	return ;	}
	m_SectionList.DeleteAllItems();
	m_FileSize.Format("0x%X", g_dwFileSize);

	//1) Init PE Member
	IMAGE_DOS_HEADER dosHeader;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	IMAGE_NT_HEADERS32	ntHeader;
	IMAGE_NT_HEADERS64	ntHeader64;
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	IMAGE_SECTION_HEADER sectionHeader;
	WORD wSectionNum;							// Section Num

	memcpy(&dosHeader, g_szBuffer, sizeof(dosHeader));
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	DWORD dwSectionalignment = 0;
	if(g_PEVerson == X64_PE)
	{
		memcpy(&ntHeader64, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
		dwSectionalignment = ntHeader64.OptionalHeader.SectionAlignment;
	}
	else
	{
		memcpy(&ntHeader, g_szBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		dwSectionalignment = ntHeader.OptionalHeader.SectionAlignment;
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End	
	
	m_sectionAlignment.Format("0x%X", dwSectionalignment);
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(g_PEVerson == X64_PE)
	{
		wSectionNum = ntHeader64.FileHeader.NumberOfSections;
	}
	else
	{
		wSectionNum = ntHeader.FileHeader.NumberOfSections;	
	}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
	for(WORD i = 0; i < wSectionNum; i++)
	{
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
		if(g_PEVerson == X64_PE)
		{
			memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader64) + i*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));
		}
		else
		{
			memcpy(&sectionHeader, g_szBuffer+dosHeader.e_lfanew+sizeof(ntHeader) + i*sizeof(IMAGE_SECTION_HEADER), sizeof(sectionHeader));		
		}
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
		//
		CString strTemp;
		m_SectionList.InsertItem(i,"");
		//ID
		strTemp.Format("%02d", i);
		m_SectionList.SetItemText(i, 0, strTemp);
		//Name
		m_SectionList.SetItemText(i, 1, (char*)sectionHeader.Name);
		//RVA
		strTemp.Format("%08X", sectionHeader.VirtualAddress);
		m_SectionList.SetItemText(i, 2, strTemp);
		//PointToRawData
		strTemp.Format("%08X", sectionHeader.PointerToRawData);
		m_SectionList.SetItemText(i, 3, strTemp);
		//Size
		strTemp.Format("%08X", sectionHeader.Misc.VirtualSize);
		m_SectionList.SetItemText(i, 4, strTemp);
		//MaxSize
		strTemp.Format("%08X", sectionHeader.SizeOfRawData);
		m_SectionList.SetItemText(i, 5, strTemp);
	}
	
	UpdateData(FALSE);
}

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::OnBUTTONOpenFIle
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::OnBUTTONOpenFIle() 
{
	if(g_szBuffer)
	{
		Release();
		m_SectionList.DeleteAllItems();
		m_FileSize = "0";
		m_sectionAlignment = "0";
	}

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
// Function :   CSectionOperationDlg::OnButtonRemovedosnt
// Return   :   void
// Comment  :   Remvoe Info between DosHeader and Nt Header
// -----------------------------------------------------------//
void CSectionOperationDlg::OnButtonRemovedosnt() 
{
	if(RemoveInfoBetweenDosHeaderAndNTHeader())
	{
		MessageBox("Remvoe Info between DosHeader and Nt Header Succeed.");
	}
	else 
	{
		MessageBox("Remvoe Info between DosHeader and Nt Header Failed.");
	}

	SetListInfo();
}

// -----------------------------------------------------------//
// Function :   CSectionOperationDlg::OnButtonCreatefile
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSectionOperationDlg::OnButtonCreatefile() 
{
	if(CreateNewFile())
	{
		MessageBox("CreateNewFile Succeed.");
	}
	else 
	{
		MessageBox("CreateNewFile Failed.");
	}

}

void CSectionOperationDlg::OnBUTTONInsertSection() 
{
	UpdateData(TRUE);
	DWORD dwExtendSize = 0;
	::sscanf(m_ExtendedSize,"%x",&dwExtendSize);   
	if(m_SectionName.IsEmpty())	return;
	
	if(InserSection(dwExtendSize, m_SectionName.GetBuffer(0), m_SecionData.GetBuffer(0), m_SecionData.GetLength()))
	{
		MessageBox("InserSection Succeed.");
		m_FileSize.Format("%x", g_dwFileSize);
		UpdateData(FALSE);
	}
	else 
	{
		MessageBox("InserSection Failed.");
	}
	
	SetListInfo();	
}

void CSectionOperationDlg::OnButtonExtenedsecsize() 
{
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
//	UpdateData(TRUE);
//	DWORD dwExtendSize = 0;
//	::sscanf(m_ExtendedSize,"%x",&dwExtendSize);  
//	int nIndex = m_SectionList.GetSelectionMark();
//	if(nIndex == -1)
//	{
//		MessageBox("Select Section.");
//		return;
//	}
//		
//	if(ExtendSecionSize(nIndex, dwExtendSize))
//	{
//		MessageBox("ExtendSecionSize Succeed.");
//		g_dwFileSize += dwExtendSize;
//		m_FileSize.Format("%x", g_dwFileSize);
//		UpdateData(FALSE);
//	}
//	else 
//	{
//		MessageBox("ExtendSecionSize Failed.");
//	}
//	
//	SetListInfo();
// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] End
}

void CSectionOperationDlg::OnButtonDeletesec() 
{
	int nIndex = m_SectionList.GetSelectionMark();
	if(nIndex == -1)
	{
		MessageBox("Select Section.");
		return;
	}

	if(DeleteSection(nIndex))
	{
		MessageBox("DeleteSection Succeed.");
	}
	else 
	{
		MessageBox("DeleteSection Failed.");
	}

	SetListInfo();
}

