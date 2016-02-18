// PEShowDoc.cpp : implementation of the CPEShowDoc class
//

#include "stdafx.h"
#include "PEShow.h"

#include "PEShowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPEShowDoc

IMPLEMENT_DYNCREATE(CPEShowDoc, CDocument)

BEGIN_MESSAGE_MAP(CPEShowDoc, CDocument)
	//{{AFX_MSG_MAP(CPEShowDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPEShowDoc construction/destruction

CPEShowDoc::CPEShowDoc()
{
	// TODO: add one-time construction code here

}

CPEShowDoc::~CPEShowDoc()
{
}

BOOL CPEShowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPEShowDoc serialization

void CPEShowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPEShowDoc diagnostics

#ifdef _DEBUG
void CPEShowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPEShowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPEShowDoc commands

