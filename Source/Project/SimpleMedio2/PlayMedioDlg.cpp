// PlayMedioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleMedio2.h"
#include "PlayMedioDlg.h"
#include "MediaUtil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayMedioDlg dialog


CPlayMedioDlg::CPlayMedioDlg(CWnd* pParent /*=NULL*/)
{
	m_hThread = NULL;
}


void CPlayMedioDlg::DoDataExchange(CDataExchange* pDX)
{
}


BEGIN_MESSAGE_MAP(CPlayMedioDlg, CDialogBar)
	//{{AFX_MSG_MAP(CPlayMedioDlg)
		ON_MESSAGE(WM_INITDIALOG, OnInitDialog)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayMedioDlg message handlers
BOOL CPlayMedioDlg::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		
	}
	m_hThread = CreateThread(NULL, 0, Thread_, this, 0, 0);
	Sleep(1000);
	return TRUE;
}

DWORD WINAPI CPlayMedioDlg::Thread_(LPVOID lparam)
{
	CPlayMedioDlg* _this = (CPlayMedioDlg*)lparam;
	if(_this)
	{
		_this->Thread();
	}
	
	return 0;
}
DWORD WINAPI CPlayMedioDlg::Thread()
{
	PlayVedio("http://10.10.1.67/CyberX/amano.asf", GetSafeHwnd());
	
	m_hThread = NULL;
	return  0;
}