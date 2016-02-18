// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PEShow.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	// Init Oher	
	InitDialog();

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndShowMemory);
/*	DockControlBar(&m_wndDosHeader);
	DockControlBar(&m_wndPEStruct);
*/	DockControlBar(&m_wndNTHeader);
	DockControlBar(&m_wndDirInfo);

	return 0;
}

// -----------------------------------------------------------//
// Function :   CMainFrame::InitDialog
// Return   :   void
// Comment  :   InitDialog
// -----------------------------------------------------------//
void CMainFrame::InitDialog()
{
	// SHOWMEMORY
	m_wndShowMemory.Create(this, IDD_DIALOG_SHOWMEMORY, 
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
		IDD_DIALOG_SHOWMEMORY);
	m_wndShowMemory.EnableDocking(CBRS_ALIGN_ANY);

/*	// DOSHEADER
	m_wndDosHeader.Create(this, IDD_DIALOG_DOS_HEADER,
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_RIGHT|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
		IDD_DIALOG_DOS_HEADER);
	m_wndDosHeader.EnableDocking(CBRS_ALIGN_ANY);

	// m_wndPEStruct
	m_wndPEStruct.Create(this, IDD_DIALOG_PE,
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_LEFT|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
		IDD_DIALOG_PE);
	m_wndPEStruct.EnableDocking(CBRS_ALIGN_ANY);
*/
	// m_wndNTHeader
	m_wndNTHeader.Create(this, IDD_DIALOG_NTHEADER,
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
		IDD_DIALOG_NTHEADER);
	m_wndNTHeader.EnableDocking(CBRS_ALIGN_ANY);

	// m_wndDirInfo
	m_wndDirInfo.Create(this, IDD_DIALOG_DIRECTORYINFO		,
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
		IDD_DIALOG_DIRECTORYINFO);
	m_wndDirInfo.EnableDocking(CBRS_ALIGN_ANY);

}	

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if(m_wndShowMemory.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	if(m_wndDosHeader.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	if(m_wndPEStruct.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	if(m_wndNTHeader.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	if(m_wndDirInfo.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
