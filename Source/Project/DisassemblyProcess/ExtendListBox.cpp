// ExtendListBox.cpp : implementation file
//

#include "stdafx.h"
#include "DisassemblyProcess.h"
#include "ExtendListBox.h"
#include <afxtempl.h>
#include "PeUti.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox
IMPLEMENT_DYNAMIC(CExtendListBox, CListBox)
CExtendListBox::CExtendListBox()
{
}

CExtendListBox::~CExtendListBox()
{
}


BEGIN_MESSAGE_MAP(CExtendListBox, CListBox)
	//{{AFX_MSG_MAP(CExtendListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox message handlers
void CExtendListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTBOX);
	CString strData;
	GetText(lpDrawItemStruct->itemID, strData);

	CDC cdc;
	cdc.Attach(lpDrawItemStruct->hDC);

	COLORREF oldTextColor = cdc.GetTextColor();
	COLORREF oldBkColor = cdc.GetBkColor();
	
	// Draw back
	if( (lpDrawItemStruct->itemAction | ODA_SELECT)
		&&(lpDrawItemStruct->itemState & ODS_SELECTED))
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
	cdc.DrawText(strData, strData.GetLength(), &lpDrawItemStruct->rcItem, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	
	cdc.SetTextColor(oldTextColor);
	cdc.SetBkColor(oldBkColor);
	cdc.Detach();
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::OnChildNotify
// Param    :   UINT message
//              WPARAM wParam
//              LPARAM lParam
//              LRESULT* pResult
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CExtendListBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	switch (message)
	{
	case WM_DRAWITEM:
		ASSERT(pResult == NULL);       // no return value expected
		DrawItem((LPDRAWITEMSTRUCT)lParam);
		break;
	case WM_MEASUREITEM:
		ASSERT(pResult == NULL);       // no return value expected
		MeasureItem((LPMEASUREITEMSTRUCT)lParam);
		break;
	case WM_COMPAREITEM:
		ASSERT(pResult != NULL);       // return value expected
		*pResult = CompareItem((LPCOMPAREITEMSTRUCT)lParam);
		break;
	case WM_DELETEITEM:
		ASSERT(pResult == NULL);       // no return value expected
		DeleteItem((LPDELETEITEMSTRUCT)lParam);
		break;
	case WM_VKEYTOITEM:
		*pResult = VKeyToItem(LOWORD(wParam), HIWORD(wParam));
		break;
	case WM_CHARTOITEM:
		*pResult = CharToItem(LOWORD(wParam), HIWORD(wParam));
		break;
	default:
		return CWnd::OnChildNotify(message, wParam, lParam, pResult);
	}
	return TRUE;	
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::MeasureItem
// Param    :   LPMEASUREITEMSTRUCT lpMeasureItemStruct
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 15;
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::CompareItem
// Param    :   LPCOMPAREITEMSTRUCT lpCompareItemStruct
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CExtendListBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// TODO: Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2
	return 0;
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#define VK_C	0x43
#define VK_A	0x41
BOOL CExtendListBox::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HACCEL hAccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
		{
			if(pMsg->wParam == VK_A)
			{
				SelectAll();
			}
			else if(pMsg->wParam == VK_C)
			{
				Copy();
			}
		}
	}
	return CListBox::PreTranslateMessage(pMsg);
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::Copy
// Return   :   void
// Comment  :   Copy
// -----------------------------------------------------------//
void CExtendListBox::Copy()
{
	int nSelCount = GetSelCount();
	
	CArray<int, int> selIndenArr;
	selIndenArr.SetSize(nSelCount);
	GetSelItems(nSelCount, selIndenArr.GetData());
	
	CString strSelData = _T("");
	CString strData = _T("");
	
	DWORD lineCount = 16 + 8 + CODEDATAWIDTH + ASSEMDATALEN;
	DWORD nLen = nSelCount * lineCount;
	DWORD nCurIndex = 0;
	HGLOBAL hAddress = ::GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT, (nLen+1)*sizeof(TCHAR));
	LPVOID pBuffer = ::GlobalLock(hAddress);
	for(int i = 0; i < selIndenArr.GetSize(); i++)
	{
		GetText(selIndenArr.GetAt(i), strData);
		DWORD n = strData.GetLength();
		if(n > 0)
		{
			memcpy((TCHAR*)pBuffer + nCurIndex, strData.GetBuffer(0), n);
			*((TCHAR*)pBuffer+nCurIndex + n) = '\n';
			nCurIndex += n + 1;
		}	
	}
	*((TCHAR*)pBuffer+nCurIndex) = '\0';
	::GlobalUnlock(hAddress);
	if(::OpenClipboard(NULL) && ::EmptyClipboard())
	{
		if(::SetClipboardData(CF_TEXT, hAddress) == NULL)
		{
			::GlobalFree(hAddress);
		}
		::CloseClipboard();
	}	
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::SelectAll
// Return   :   void
// Comment  :   SelectAll
// -----------------------------------------------------------//
void CExtendListBox::SelectAll()
{
	SetRedraw(FALSE);
	for(int i = GetCount() - 1; i >= 0 ; i--)
	{
		SetSel(i, TRUE);
	}
	SetRedraw(TRUE);
}