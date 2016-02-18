// ExtendButton.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "ExtendButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendButton

CExtendButton::CExtendButton()
{
}

CExtendButton::~CExtendButton()
{
}


BEGIN_MESSAGE_MAP(CExtendButton, CButton)
	//{{AFX_MSG_MAP(CExtendButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendButton message handlers

int CExtendButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here

	return 0;
}

void CExtendButton::Initlize()
{
	ModifyStyle(0, BS_BITMAP|BS_OWNERDRAW, 0);
	m_Bitmap.LoadBitmap(IDB_BITMAP_BTN);
	m_BitmapFocus.LoadBitmap(IDB_BITMAP_FOCUS);
//	m_bitmap = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_BTN));
//	m_bitmap = (HBITMAP)bitmap.Detach();
//	SetBitmap(m_bitmap);
}

void CExtendButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_Bitmap.m_hObject != NULL);     // required
	
	// use the main bitmap for up, the selected bitmap for down
	CBitmap* pBitmap = &m_Bitmap;
	UINT state = lpDrawItemStruct->itemState;
	if (state & ODS_SELECTED)
		pBitmap = &m_BitmapFocus;
	else if (state & ODS_FOCUS)
		pBitmap = &m_BitmapFocus;		// third image for focused
	else if (state & ODS_DISABLED)
		pBitmap = &m_Bitmap;   // last image for disabled
	
	// draw the whole button
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOld = memDC.SelectObject(pBitmap);
	if (pOld == NULL)
		return;   
	
	CRect rect;
	rect.CopyRect(&lpDrawItemStruct->rcItem);
	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);
}
