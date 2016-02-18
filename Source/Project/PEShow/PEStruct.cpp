// PEStruct.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "PEStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPEStruct dialog


CPEStruct::CPEStruct(CWnd* pParent /*=NULL*/)
{

}


void CPEStruct::DoDataExchange(CDataExchange* pDX)
{

}

BEGIN_MESSAGE_MAP(CPEStruct, CDialogBar)
	//{{AFX_MSG_MAP(CPEStruct)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPEStruct message handlers

BOOL CPEStruct::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	HandleInitDialog(wparam, lparam);
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CPEStruct::InsertItem
// Param    :   LPCTSTR		lpszItem
//              HTREEITEM	hParent = TVI_ROOT 
//              HTREEITEM	hInsertAfter  = TVI_LAST 
// Return   :   HTREEITEM
// Comment  :   
// -----------------------------------------------------------//
HTREEITEM CPEStruct::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent /* = TVI_ROOT */,HTREEITEM hInsertAfter /* = TVI_LAST */)
{
	CTreeCtrl* pListView = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	if(pListView)
	{
		return pListView->InsertItem(lpszItem, hParent, hInsertAfter);
	}

	return NULL;
}
