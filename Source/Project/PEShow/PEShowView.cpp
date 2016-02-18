// PEShowView.cpp : implementation of the CPEShowView class
//

#include "stdafx.h"
#include "PEShow.h"
#include "PEShowDoc.h"
#include "PEShowView.h"
#include "DosHeaderDlg.h"
#include "MainFrm.h"
#include "SuperGridCtrl\supergridctrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPEShowView

IMPLEMENT_DYNCREATE(CPEShowView, CView)

BEGIN_MESSAGE_MAP(CPEShowView, CView)
	//{{AFX_MSG_MAP(CPEShowView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPEShowView construction/destruction

CPEShowView::CPEShowView()
{
	// TODO: add construction code here
//	m_listTree = NULL;
//	m_ListCtrl = NULL;
}

BOOL CPEShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPEShowView drawing

void CPEShowView::OnDraw(CDC* pDC)
{
	CPEShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPEShowView printing

BOOL CPEShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPEShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPEShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPEShowView diagnostics

#ifdef _DEBUG
void CPEShowView::AssertValid() const
{
	CView::AssertValid();
}

void CPEShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPEShowDoc* CPEShowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPEShowDoc)));
	return (CPEShowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPEShowView message handlers
// -----------------------------------------------------------//
// Function :   CPEShowView::OnInitialUpdate
// Return   :   void
// Comment  :   Init
// -----------------------------------------------------------//
CFont font;
void CPEShowView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect);

/*	if(m_listTree == NULL)
	{
		m_listTree = new CTreeCtrl;
		m_listTree->Create(TVS_HASLINES|TVS_FULLROWSELECT|TVS_LINESATROOT|TVS_HASBUTTONS, CRect(0, 0, rect.Width()/8, rect.Height()), this, TREEID);
		m_listTree->ShowWindow(SW_SHOW);
	}

	if(m_ListCtrl == NULL)
	{
		m_ListCtrl = new CListCtrl;
		m_ListCtrl->Create(LVS_LIST|WS_BORDER|WS_TABSTOP, CRect(rect.Width()/8, 0, rect.Width()/8*7, rect.Height()), this, LISTCTRL);
		m_ListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES);
		m_ListCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
		m_ListCtrl->ShowWindow(SW_SHOW);
	}
	if(m_ListBox == NULL)
	{
		m_ListBox = new CListBox;
		m_ListBox->Create(LBS_NOINTEGRALHEIGHT|WS_BORDER|WS_VSCROLL, CRect(rect.Width()/8, 0, rect.Width()/8*7, rect.Height()), this, LISTBOX);
		m_ListBox->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
		m_ListBox->ShowWindow(SW_SHOW);

		font.CreateFont(20,10,0,0,
			FW_BOLD,FALSE,FALSE,0, 1,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS,"MS Sans Serif"); 
 
		m_ListBox->SetFont(&font, TRUE);
	}
*/
}

// -----------------------------------------------------------//
// Function :   CPEShowView::~CPEShowView
// Return   :   
// Comment  :   destruction
// -----------------------------------------------------------//
CPEShowView::~CPEShowView()
{
	_Release();
//	if(m_listTree)
//	{
//		delete m_listTree;
//		m_listTree = NULL;
//	}
//	if(m_ListCtrl)
//	{
//		delete m_ListCtrl;
//		m_ListCtrl = NULL;
//	}
}
/************************************************************************/
/* Define                                                                     */
/************************************************************************/
TCHAR*	g_FileMemory = NULL;
DWORD	g_dwFileSize = 0;
DWORD   g_PEVerson = X32_PE;
// -----------------------------------------------------------//
// Function :   CPEShowDoc::OnFileOpen
// Return   :   void
// Comment  :   OpenFile
// -----------------------------------------------------------//
void CPEShowView::OnFileOpen() 
{
	TCHAR szFileName[MAX_PATH] = {0};
	
	// Select A File
	OPENFILENAME info;
	memset(&info, 0x00, sizeof(info));
	
	info.lStructSize = sizeof(info);
	info.hwndOwner = m_hWnd;
	info.lpstrFile = szFileName;
	info.nMaxFile = MAX_PATH;
	info.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	info.lpstrFilter = "exe file(*.exe)\0*.exe\0All Files(*.*)\0*.*\0\0";
	info.lpstrTitle = "Open File";
	info.nMaxFileTitle = MAX_PATH;
	
	if(GetOpenFileName(&info) == FALSE)
	{
		return;
	}
	
	// Open FIle
	if(_OpenFile(szFileName) == FALSE)
	{
		return;
	}
	CMainFrame* pMainFram = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(!pMainFram)
	{
		return;
	}
	// InitMemoryInfo
	pMainFram->m_wndShowMemory.InitMemoryInfo(g_FileMemory, g_dwFileSize);

	// IMAGE_DOS_HEADER
	IMAGE_DOS_HEADER* pDosHeader = _GetMSDosHeader();
/*	if(pDosHeader)
	{
		pMainFram->m_wndPEStruct.InsertItem("IMAGE_DOS_HEADER");
		pMainFram->m_wndDosHeader.SetImageDosHeadeData(pDosHeader);
		pMainFram->m_wndDosHeader.InitListCtrl();
	}
	// MS_DOS STUB
	LONG nOffset = pDosHeader->e_lfanew;
	pMainFram->m_wndPEStruct.InsertItem("MS_DOS STUB");
	// IMAGE_NT_HEADERS
	IMAGE_NT_HEADERS* pNTHeaders = _GetNTHeaders(nOffset);;
	HTREEITEM hItem = pMainFram->m_wndPEStruct.InsertItem("IMAGE_NT_HEADERS");
	// 1)Signature
	// 2)IMAGE_FILE_HEADER
	// 3)IMAGE_OPTIONAL_HEADER32
	HTREEITEM hItem0 = pMainFram->m_wndPEStruct.InsertItem("Signature", hItem);
	HTREEITEM hItem1 = pMainFram->m_wndPEStruct.InsertItem("IMAGE_FILE_HEADER", hItem, hItem0);
	HTREEITEM hItem2 = pMainFram->m_wndPEStruct.InsertItem("IMAGE_OPTIONAL_HEADER32", hItem, hItem1);
*/
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	// Column
	InitGridColumn(pMainFram->m_wndNTHeader.m_List);
	// MainItem
	CTreeItem_ *bootItem = AddMainItem(pMainFram->m_wndNTHeader.m_List);
	// IMAGE_DOS_HEADER
	Add_IMAGE_DOS_HEADER(pDosHeader, pMainFram->m_wndNTHeader.m_List, bootItem);
	//Add_MS_DOS_Stub
	CHAR* buffer = _GetDosStubBuffer();
	Add_MS_DOS_Stub(buffer, sizeof(IMAGE_DOS_HEADER), pMainFram->m_wndNTHeader.m_List, bootItem);
	//  IMAGE_NT_HEADERS
	Add_IMAGE_NT_HEADERS(_GetNTHeaders(), pDosHeader->e_lfanew, pMainFram->m_wndNTHeader.m_List, bootItem);
	// IMAGE_SECTION_INFO
	Add_IMAGE_SECTION_HEADER(_GetSECTION_INFO(), pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS), _GetNTHeaders()->FileHeader.NumberOfSections, 
		pMainFram->m_wndNTHeader.m_List, bootItem);
}

// -----------------------------------------------------------//
// Function :   CPEShowView::InitGridColumn
// Param    :   CMySuperGrid m_ListGrid
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CPEShowView::InitGridColumn(CMySuperGrid& m_ListGrid)
{
	LPTSTR lpszCols[] = {_T("Tree Thing"),_T("Offset"), _T("TYPE"), _T("Data(HEX)"),_T("Data(ASCII)"),_T("DESC"), 0};
	LV_COLUMN   lvColumn;
	// 1)initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for(int x = 0; lpszCols[x]!=NULL; x++)
    {
		//make the secondary columns smaller
		if(x == 0 || x == 5)	lvColumn.cx = 200;
		else 
			lvColumn.cx = 100;
		lvColumn.pszText = lpszCols[x];
		m_ListGrid.InsertColumn(x,&lvColumn);
    }
}

// -----------------------------------------------------------//
// Function :   CPEShowView::AddMainItem
// Param    :   CMySuperGrid& m_ListGrid
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//

CTreeItem_* CPEShowView::AddMainItem(CMySuperGrid& m_ListGrid)
{
	CItemInfo* MainItem = new CItemInfo();
	MainItem->SetImage(4);	
	MainItem->SetItemText(_T("PE"));
	MainItem->AddSubItemText(_T("00000000"));     
	MainItem->AddSubItemText(_T("EXE"));
	MainItem->AddSubItemText(_T("-"));  
	MainItem->AddSubItemText(_T("-"));  
	MainItem->AddSubItemText(_T("_"));  
	return m_ListGrid.InsertRootItem(MainItem);
}

	
// -----------------------------------------------------------//
// Function :   _OpenFile
// Param    :   LPCTSTR pszFileName
// Return   :   BOOL
// Comment  :   Open A File
// -----------------------------------------------------------//
BOOL _OpenFile(LPCTSTR pszFileName)
{
	// Open File
	HANDLE hFile = ::CreateFile(pszFileName, 
		GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	DWORD dwFileSize = GetFileSize(hFile, 0);
	if(dwFileSize == 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	
	// AllocMemory
	if(g_FileMemory)
	{
		::GlobalFree(g_FileMemory);
		g_FileMemory = NULL;
	}
	g_dwFileSize = dwFileSize;
	g_FileMemory = (TCHAR*)::GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, dwFileSize);
	if(g_FileMemory == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	// ReadFile
	DWORD nReadSize;
	if(::ReadFile(hFile, g_FileMemory, dwFileSize, &nReadSize, NULL) )
	{
		if(nReadSize == dwFileSize)
		{
			CloseHandle(hFile);
			return TRUE;
		}
	}
	CloseHandle(hFile);
	
	// X32/X64
	GetPEVersion();

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   _GetMSDosHeader
// Return   :   IMAGE_DOS_HEADER*
// Comment  :   
// -----------------------------------------------------------//
IMAGE_DOS_HEADER* _GetMSDosHeader()
{
	if(g_FileMemory)
	{
		return (IMAGE_DOS_HEADER*)g_FileMemory;
	}

	return NULL;
}

// -----------------------------------------------------------//
// Function :   _GetDosStubBuffer
// Return   :   TCHAR*
// Comment  :   
// -----------------------------------------------------------//
TCHAR* _GetDosStubBuffer()
{
	if(g_FileMemory)
	{
		return (g_FileMemory+sizeof(IMAGE_DOS_HEADER));
	}
	
	return NULL;
}

// -----------------------------------------------------------//
// Function :   _Release
// Return   :   BOOL
// Comment  :   Release
// -----------------------------------------------------------//
BOOL _Release()
{
	if(g_FileMemory)
	{
		GlobalFree(g_FileMemory);
		g_FileMemory = NULL;
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   _GetNTHeaders
// Return   :   IMAGE_NT_HEADERS*
// Comment  :   
// -----------------------------------------------------------//
IMAGE_NT_HEADERS* _GetNTHeaders()
{
	if(g_FileMemory)
	{
		IMAGE_DOS_HEADER* pDosHeader =  _GetMSDosHeader();
		if(pDosHeader)
		{
			LONG lOffset = pDosHeader->e_lfanew;
			return (IMAGE_NT_HEADERS*)(g_FileMemory+lOffset);
		}
		
	}
	
	return NULL;
}

// -----------------------------------------------------------//
// Function :   _GetSECTION_INFO
// Return   :   CHAR*
// Comment  :   
// -----------------------------------------------------------//
CHAR* _GetSECTION_INFO()
{
	IMAGE_NT_HEADERS* pNTHeader = _GetNTHeaders();
	if(pNTHeader)
	{
		return (CHAR*)((CHAR*)pNTHeader+sizeof(IMAGE_NT_HEADERS));
	}

	return NULL;
}

// -----------------------------------------------------------//
// Function :   GetData
// Return   :   CHAR*
// Comment  :   
// -----------------------------------------------------------//
CHAR* GetData()
{
	return g_FileMemory;
}

// -----------------------------------------------------------//
// Function :   GetMaxSize
// Return   :   DWORD
// Comment  :   
// -----------------------------------------------------------//
DWORD GetMaxSize()
{
	return g_dwFileSize;
}

// -----------------------------------------------------------//
// Function :   FormatTime
// Param    :   DWORD TimeDateStamp
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString FormatTime(DWORD TimeDateStamp)
{
	CTime t(TimeDateStamp);
	
	CString str;
	str.Format("%04d/%02d/%02d %02d:%02d:%04d", t.GetYear(), t.GetMonth(), t.GetDay(), t.GetHour(), t.GetMinute(), t.GetSecond());
	
	return str;
}

//  2014.09.24 Ver1.00[X64/X32 PE] Start
// -----------------------------------------------------------//
// Function :   GetPEVersion
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void GetPEVersion()
{
	if(g_FileMemory == NULL)	return;
	
	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS ntHeader;
	
	memcpy(&dosHeader, g_FileMemory, sizeof(dosHeader));
	memcpy(&ntHeader, g_FileMemory+dosHeader.e_lfanew, sizeof(ntHeader));
	
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