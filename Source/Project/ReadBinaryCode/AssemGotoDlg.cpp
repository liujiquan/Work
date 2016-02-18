// AssemGotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadBinaryCode.h"
#include "AssemGotoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssemGotoDlg dialog


CAssemGotoDlg::CAssemGotoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssemGotoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAssemGotoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAssemGotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssemGotoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssemGotoDlg, CDialog)
	//{{AFX_MSG_MAP(CAssemGotoDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssemGotoDlg message handlers
