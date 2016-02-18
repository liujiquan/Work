// NTHeader.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "NTHeader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNTHeader dialog


CNTHeader::CNTHeader(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CNTHeader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNTHeader::DoDataExchange(CDataExchange* pDX)
{
}


BEGIN_MESSAGE_MAP(CNTHeader, CDialogBar)
	//{{AFX_MSG_MAP(CNTHeader)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTHeader message handlers

BOOL CNTHeader::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		
	}
	CRect rect;
	GetClientRect(&rect);
	if(m_List.GetSafeHwnd())
			m_List.MoveWindow(rect);

	return TRUE;  
}

int CNTHeader::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_List.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(0,0,0,0),this,0x1001);	
	m_List.InitializeGrid();
	m_List.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	return 0;
}
