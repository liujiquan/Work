// DirPage0.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "DirImportPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirImportPage dialog


CDirImportPage::CDirImportPage(CWnd* pParent /*=NULL*/)
	: CDialog(CDirImportPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirImportPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDirImportPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirImportPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirImportPage, CDialog)
	//{{AFX_MSG_MAP(CDirImportPage)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirImportPage message handlers

BOOL CDirImportPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(&rect);
	rect.top += 20;
	rect.bottom -= 20;
	if(m_List.GetSafeHwnd())
	{
		m_List.MoveWindow(rect);
	}

	InitGridColumn(m_List);
	return TRUE;  
}

int CDirImportPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_List.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(0,0,0,0),this,0x1002);	
	m_List.InitializeGrid();
	m_List.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	return 0;
}

// -----------------------------------------------------------//
// Function :   CDirImportPage::InitGridColumn
// Param    :   CMySuperGrid& m_ListGrid
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDirImportPage::InitGridColumn(CMySuperGrid& m_ListGrid)
{
	LPTSTR lpszCols[] = {_T("Tree Thing"), _T("Oridinal"), _T("Hint"),_T("Function"), _T("Entry Point"), 0};
	LV_COLUMN   lvColumn;
	// 1)initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for(int x = 0; lpszCols[x]!=NULL; x++)
    {
		//make the secondary columns smaller
		if(x == 0 || x == 3)	lvColumn.cx = 200;
		else 
			lvColumn.cx = 100;
		lvColumn.pszText = lpszCols[x];
		m_ListGrid.InsertColumn(x,&lvColumn);
    }
}
