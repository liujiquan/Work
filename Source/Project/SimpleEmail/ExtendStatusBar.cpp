//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendStatusBar.cpp
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "SimpleEmail.h"
#include "ExtendStatusBar.h"
#include "MailUtil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendStatusBar

CExtendStatusBar::CExtendStatusBar()
{
}

CExtendStatusBar::~CExtendStatusBar()
{
}

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_TIME,
};

BEGIN_MESSAGE_MAP(CExtendStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CExtendStatusBar)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendStatusBar message handlers
#define TIMEEVENT			WM_USER+1000
int CExtendStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	CRect rect ;
	GetWindowRect(&rect);

	SetPaneInfo(0, ID_SEPARATOR,		SBPS_NORMAL, VIEW_WID*8/10);
	SetPaneInfo(1, ID_INDICATOR_TIME,	SBPS_NORMAL, VIEW_WID*2/10);
	SetPaneText(1, GetCurrentTimeStr(), TRUE);

	SetTimer(TIMEEVENT, 1000, NULL);

	return 0;
}

void CExtendStatusBar::OnDestroy() 
{
	CStatusBar::OnDestroy();
	KillTimer(TIMEEVENT);
}

void CExtendStatusBar::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMEEVENT)
	{
		SetPaneText(1, GetCurrentTimeStr(), TRUE);
	}
	CStatusBar::OnTimer(nIDEvent);
}

// -----------------------------------------------------------//
// Function :   CExtendStatusBar::SetInfo
// Param    :   LPCTSTR pszBufferInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendStatusBar::SetInfo(LPCTSTR pszBufferInfo)
{
	if(pszBufferInfo)
		SetPaneText(0, pszBufferInfo, TRUE);
}


