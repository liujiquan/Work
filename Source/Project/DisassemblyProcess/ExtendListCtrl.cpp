// ExtendListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DisassemblyProcess.h"
#include "ExtendListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendListCtrl

CExtendListCtrl::CExtendListCtrl()
{
}

CExtendListCtrl::~CExtendListCtrl()
{
}


BEGIN_MESSAGE_MAP(CExtendListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CExtendListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendListCtrl message handlers


void CExtendListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CExtendListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 15;
}

void CExtendListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CExtendListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType & ODT_LISTBOX);
	CString str;
	LPCTSTR pszText = (LPCTSTR)lpDrawItemStruct->itemData;
	ASSERT(pszText != NULL);
	
	CDC cdc;
	cdc.Attach(lpDrawItemStruct->hDC);
	
	COLORREF oldTextColor = cdc.GetTextColor();
	COLORREF oldBkColor = cdc.GetBkColor();
	
	// Draw back
	if( (lpDrawItemStruct->itemAction | ODA_SELECT)
		&&(lpDrawItemStruct->itemState & ODS_SELECTED)
		)
	{
		if( (lpDrawItemStruct->itemAction | ODA_FOCUS) &&
			(lpDrawItemStruct->itemState & ODS_FOCUS)
			)
		{
			cdc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));	// focus
			cdc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			cdc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255, 0, 0));
		}
		else
		{
			cdc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));	// selected
			cdc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			cdc.FillSolidRect(&lpDrawItemStruct->rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
		}	
	}
	else
	{
		cdc.FillSolidRect(&lpDrawItemStruct->rcItem, oldBkColor);
	}
	// Draw Text
	cdc.DrawText(pszText, strlen(pszText), &lpDrawItemStruct->rcItem, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	
	cdc.SetTextColor(oldTextColor);
	cdc.SetBkColor(oldBkColor);
	cdc.Detach();
}