// SimpleMedio2View.cpp : implementation of the CSimpleMedio2View class
//

#include "stdafx.h"
#include "SimpleMedio2.h"

#include "SimpleMedio2Doc.h"
#include "SimpleMedio2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View

IMPLEMENT_DYNCREATE(CSimpleMedio2View, CView)

BEGIN_MESSAGE_MAP(CSimpleMedio2View, CView)
	//{{AFX_MSG_MAP(CSimpleMedio2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View construction/destruction

CSimpleMedio2View::CSimpleMedio2View()
{
	// TODO: add construction code here

}

CSimpleMedio2View::~CSimpleMedio2View()
{
}

BOOL CSimpleMedio2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View drawing

void CSimpleMedio2View::OnDraw(CDC* pDC)
{
	CSimpleMedio2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View printing

BOOL CSimpleMedio2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimpleMedio2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimpleMedio2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View diagnostics

#ifdef _DEBUG
void CSimpleMedio2View::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleMedio2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleMedio2Doc* CSimpleMedio2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleMedio2Doc)));
	return (CSimpleMedio2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2View message handlers
