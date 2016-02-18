// SwfShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include "SwfShow.h"
#include "SwfShowDlg.h"
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
// CSwfShowDlg dialog

CSwfShowDlg::CSwfShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSwfShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSwfShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_szBuffer = NULL;
}

// -----------------------------------------------------------//
// Function :   CSwfShowDlg::~CSwfShowDlg
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CSwfShowDlg::~CSwfShowDlg()
{
	if(m_szBuffer)
	{
		free(m_szBuffer);
		m_szBuffer = NULL;
	}
}

void CSwfShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSwfShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSwfShowDlg, CDialog)
	//{{AFX_MSG_MAP(CSwfShowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OpenFile, OnBUTTONOpenFile)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSwfShowDlg message handlers

BOOL CSwfShowDlg::OnInitDialog()
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
	InitGridColumn();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSwfShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSwfShowDlg::OnPaint() 
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
HCURSOR CSwfShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CSwfShowDlg::InitGridColumn()
{
	m_SuperGrid.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(0,0,0,0),this,IDC_MYLISTCTRL);	
	CRect rect;
	GetClientRect(&rect);
	rect.top += 30;
	if(m_SuperGrid.GetSafeHwnd())		m_SuperGrid.MoveWindow(rect);
	
	m_SuperGrid.InitializeGrid();
	m_SuperGrid.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	
	LPTSTR lpszCols[] = {_T("FILED"),_T("INDEX"), _T("HEX"), _T("VALUE"), _T("STR"), 0};
	LV_COLUMN   lvColumn;
	// 1)initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for(int x = 0; lpszCols[x]!=NULL; x++)
    {
		//make the secondary columns smaller
		lvColumn.pszText = lpszCols[x];
		int nRet = m_SuperGrid.InsertColumn(x,&lvColumn);
    }
}

void CSwfShowDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	rect.right  = rect.left + cx;
	rect.top += 30;
	rect.bottom = rect.top + cy;
	if(m_SuperGrid.GetSafeHwnd())		m_SuperGrid.MoveWindow(rect);
	if(m_SuperGrid.b_InitializeGrid && m_SuperGrid.GetNumCol())
	{
		m_SuperGrid.SetColumnWidth(0,  2 * rect.Width() / 6);
		m_SuperGrid.SetColumnWidth(1,  rect.Width() / 6);
		m_SuperGrid.SetColumnWidth(2,  rect.Width() / 6);
		m_SuperGrid.SetColumnWidth(3, rect.Width() / 6);
		m_SuperGrid.SetColumnWidth(4,  rect.Width() / 6);
	}
}


// -----------------------------------------------------------//
// Function :   CSwfShowDlg::OnBUTTONOpenFile
// Return   :   void
// Comment  :   Open .Swf File
// -----------------------------------------------------------//
void CSwfShowDlg::OnBUTTONOpenFile() 
{
	if(m_szBuffer != NULL)
	{
		free(m_szBuffer);
		m_szBuffer = NULL;
	}
	m_SuperGrid.DeleteAll();		
	// Select File
	OPENFILENAME ofn;
	memset(&ofn, 0x00, sizeof(ofn));
	memset(m_szFileName, 0x00, MAX_PATH);
	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = m_szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Exe File(*.swf)\0*.swf\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	
	{	
		DWORD dwError = GetLastError();
		return;
	}
	
	// Open File
	HANDLE handle = CreateFile(m_szFileName, 
		GENERIC_READ,
		FILE_SHARE_READ, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	if(handle == NULL)
	{
		MessageBox("CreateFile Failed.");
		return;
	}
	
	DWORD  dwFileSizeHi;
	m_dwFileSize = GetFileSize(handle, &dwFileSizeHi);
	if(m_dwFileSize == 0)	
	{
		CloseHandle(handle);
		MessageBox("GetFileSize Failed.");
		return;
	}
	// Read File
	m_szBuffer = (BYTE*)malloc(m_dwFileSize);
	if(m_szBuffer == NULL)
	{
		CloseHandle(handle);
		MessageBox("malloc Failed.");
		return;
	}
	
	DWORD dwReadSize;
	if(ReadFile(handle, m_szBuffer, m_dwFileSize, &dwReadSize, NULL) == FALSE)
	{
		CloseHandle(handle);
		MessageBox("ReadFile Failed.");
		return;
	}
	
	CloseHandle(handle);
	handle = NULL;

	AnalyzeSwf();
}

// -----------------------------------------------------------//
// Function :   CSwfShowDlg::AnalyzeSwf
// Return   :   void
// Comment  :   AnalyzeSwf
// -----------------------------------------------------------//
void CSwfShowDlg::AnalyzeSwf()
{
	if(m_szBuffer == NULL || m_dwFileSize == 0)	return;
	int headerSize = ReadHeader(m_szBuffer);
	int tagSize = ReadTagInfo(m_szBuffer, headerSize);
}

// -----------------------------------------------------------//
// Function :   CSwfShowDlg::UnCompressFile
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
/*BOOL CSwfShowDlg::UnCompressFile()
{
	ULONG nUnCompRessSize = m_dwFileSize;
//	BYTE* szDest = (BYTE*)malloc(nUnCompRessSize);
//	memset(szDest, 0x00, nUnCompRessSize);

//	if(szDest == NULL)	
//	{
//		return FALSE;
//	}
//	BYTE szDest[200] = {0};
//	int nRet = uncompress(szDest, &nUnCompRessSize, m_szBuffer, m_dwFileSize);
//	
//	free(szDest);
//	szDest = NULL;
	BYTE szDest[2000] = {0};
	BYTE szSource[2000] = {0};
	uLong nLen = m_dwFileSize;
	uLong nCompressLen = compressBound(m_dwFileSize);

	int nRet = compress(szDest, &nCompressLen, m_szBuffer, nLen);
	if(nRet == Z_OK)
	{
		nRet = uncompress(szSource, &nLen, szDest, nCompressLen);
	}

	return TRUE;
}*/


// -----------------------------------------------------------//
// Function :   CSwfShowDlg::ReadHeader
// Param    :   BYTE buffer[]
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CSwfShowDlg::ReadHeader(BYTE buffer[])
{
	CTreeItem_* pHeaderObjItem = AddMainItem("HeaderInfo", 0,  m_SuperGrid);

	DWORD nIndex= 0;				// address
	BYTE* szBuffer = buffer;		// buffer
	// Header.
	BYTE szHeader[4] = {0};
	memcpy(szHeader, szBuffer, 3);
	nIndex += 3;
	if(CString(szHeader) == "FWS")
	{
		
	}
	else if(CString(szHeader) == "CWS")
	{
//		if(UnCompressFile() == FALSE)
//		{
			return nIndex;
//		}
//		AnalyzeSwf();
	}
	else
	{
		return nIndex;
	}
	AddSubItem("header", nIndex, (DWORD)(*(DWORD*)(szHeader)), pHeaderObjItem, m_SuperGrid);
	// Version
	BYTE bVersion;
	bVersion = szBuffer[nIndex];
	nIndex += 1;
	AddSubItem("version", nIndex, (DWORD)bVersion, pHeaderObjItem, m_SuperGrid);
	// FileLen
	DWORD dwFileLen ;
	memcpy(&dwFileLen, szBuffer + nIndex, 4);
	nIndex += 4;
	AddSubItem("filelen", nIndex, dwFileLen, pHeaderObjItem, m_SuperGrid);
	// RectInfo
	int nBytes = (int)ceil((5 + (double)4 * (szBuffer[nIndex] >> 3)) / 8) ;

	DWORD dwXmin, dwXMax, dwYmin, dwYmax;

	BYTE* byteArr = (BYTE*)malloc(nBytes*sizeof(byte));
	memcpy(byteArr, szBuffer + nIndex, nBytes);
	nIndex += nBytes;

	dwXmin = ( ((byteArr[0] & 0x07) << 11) +	((byteArr[1]) << 3) +	(byteArr[2] >> 5) ) / 20;
	dwXMax = ( ((byteArr[2] & 0x1F) << 9) +	((byteArr[3]) << 1) +	(byteArr[4] >> 7) ) / 20;
	dwYmin = ( ((byteArr[4] & 0x7F) << 7) +	((byteArr[5]) >> 1) ) / 20;
	dwYmax = ( ((byteArr[5] & 0x01) << 13 )+	((byteArr[6]) << 5) +	(byteArr[7] >> 3) ) / 20;
	AddSubItem("Xmin", nIndex, dwXmin, pHeaderObjItem, m_SuperGrid);
	AddSubItem("Xmax", nIndex, dwXMax, pHeaderObjItem, m_SuperGrid);
	AddSubItem("Ymin", nIndex, dwYmin, pHeaderObjItem, m_SuperGrid);
	AddSubItem("Ymax", nIndex, dwYmax, pHeaderObjItem, m_SuperGrid);
	free(byteArr);
	byteArr = NULL;
	// Frame
	USHORT uFrameRate, uFrameSize;
	uFrameRate = (szBuffer[nIndex] >> 8) + szBuffer[nIndex + 1];
	nIndex += 2;
	AddSubItem("framerate", nIndex, uFrameRate, pHeaderObjItem, m_SuperGrid);

	memcpy(&uFrameSize, szBuffer + nIndex, 2);
	nIndex += 2;
	AddSubItem("framesize", nIndex, uFrameSize, pHeaderObjItem, m_SuperGrid);

	return nIndex;
}

// -----------------------------------------------------------//
// Function :   CSwfShowDlg::ReadTagInfo
// Param    :   BYTE buffer[]
//              int nHeaderSize
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CSwfShowDlg::ReadTagInfo(BYTE buffer[], int nHeaderSize)
{
	DWORD nIndex= nHeaderSize;						// address
	BYTE* szBuffer = buffer;						// buffer
	TagInfo info;
	DWORD dwI = 0;

	CTreeItem_* pTagMainItem = AddMainItem("TagInfo", nIndex,  m_SuperGrid);
	info.Anaylize(szBuffer + nIndex);
	while(info.type != 0)
	{
		CString strTemp;
		strTemp.Format(_T("[%02d]_%s_[%02d]"), dwI, info.szTagName, info.type);
		CTreeItem_* pSubMainItem = AddSubMainItem(strTemp.GetBuffer(0), nIndex, 0, pTagMainItem, m_SuperGrid);
		AddSubItem("type", info.boolShortTag ? "short" : "long", pSubMainItem, m_SuperGrid);
		AddSubItem("Name", info.szTagName, pSubMainItem, m_SuperGrid);
		AddSubItem("nLen", DWTOINT(info.length), pSubMainItem, m_SuperGrid);

		if(info.boolShortTag)
		{
			nIndex = nIndex + 2 + info.length;
		}
		else
		{
			nIndex = nIndex + 6 + info.length;
		}
		dwI++;
		info.Anaylize(szBuffer + nIndex);
	}

	return nIndex - nHeaderSize;
}
