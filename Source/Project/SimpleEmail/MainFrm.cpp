// MainFrm.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"
#include "SimpleEmail.h"
#include "MainFrm.h"
#include "MailUtil.h"

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
	ON_WM_CREATE()
	ON_COMMAND(AFX_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))		return -1;     
	if (!m_wndStatusBar.Create(this))					return -1;   
//	m_SendMailDlg.Create(this, IDD_DIALOG_SENDMAIL		,
//		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
//	IDD_DIALOG_SENDMAIL);
//	CRect rect(0, 0, VIEW_WID, VIEW_HEI);
//	m_SendMailDlg.SetWindowPos(NULL, 0, 0, VIEW_WID, VIEW_HEI, SWP_NOMOVE|SWP_NOZORDER);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_SendMailDlg.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
//	DockControlBar(&m_SendMailDlg);
	
	return 0;
}

// -----------------------------------------------------------//
// Function :   CMainFrame::PreCreateWindow
// Param    :   CREATESTRUCT& cs
// Return   :   BOOL
// Comment  :   Set MainWnd Info
// -----------------------------------------------------------//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	//  the CREATESTRUCT cs
	cs.cx = VIEW_WID;			// MainWnd wid
	cs.cy = VIEW_HEI;			// MainWnd hei

	cs.style &= ~WS_THICKFRAME; // MainWnd Style
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style |= WS_DLGFRAME; 

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
	// TODO: Add your specialized code here and/or call the base class
//	if(m_SendMailDlg.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//	{
//		return TRUE;
//	}
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

// -----------------------------------------------------------//
// Function :   CMainFrame::OnHelp
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CMainFrame::OnHelp() 
{
	TCHAR tchPath[MAX_PATH];	
	GetModuleFileName(NULL,tchPath,MAX_PATH);	

	CString sPath(tchPath); 
	int index = sPath.ReverseFind('\\');
	sPath=sPath.Left(index);
	
	HINSTANCE hReturn=ShellExecute(m_hWnd, "open", _T("simplehelp.chm"), NULL, sPath.GetBuffer(0), SW_SHOWNORMAL);
	if ((int)hReturn<=32)
	{
		AfxMessageBox("The Help chm is not exist. please install it.");
	}
}
