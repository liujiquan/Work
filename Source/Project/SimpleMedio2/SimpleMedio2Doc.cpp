// SimpleMedio2Doc.cpp : implementation of the CSimpleMedio2Doc class
//

#include "stdafx.h"
#include "SimpleMedio2.h"

#include "SimpleMedio2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2Doc

IMPLEMENT_DYNCREATE(CSimpleMedio2Doc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleMedio2Doc, CDocument)
	//{{AFX_MSG_MAP(CSimpleMedio2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2Doc construction/destruction

CSimpleMedio2Doc::CSimpleMedio2Doc()
{
	// TODO: add one-time construction code here

}

CSimpleMedio2Doc::~CSimpleMedio2Doc()
{
}

BOOL CSimpleMedio2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2Doc serialization

void CSimpleMedio2Doc::Serialize(CArchive& ar)
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
// CSimpleMedio2Doc diagnostics

#ifdef _DEBUG
void CSimpleMedio2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleMedio2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2Doc commands
