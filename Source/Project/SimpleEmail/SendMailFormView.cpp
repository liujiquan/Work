// SendMailFormView.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "SendMailFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMailFormView

IMPLEMENT_DYNCREATE(CSendMailFormView, CFormView)

CSendMailFormView::CSendMailFormView()
	: CFormView(CSendMailFormView::IDD)
{
	//{{AFX_DATA_INIT(CSendMailFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSendMailFormView::~CSendMailFormView()
{
}

void CSendMailFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMailFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendMailFormView, CFormView)
	//{{AFX_MSG_MAP(CSendMailFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMailFormView diagnostics

#ifdef _DEBUG
void CSendMailFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSendMailFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSendMailFormView message handlers
