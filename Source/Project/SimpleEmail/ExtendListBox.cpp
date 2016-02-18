//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendListBox.cpp
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   实现文件拖拽功能 
//*				 del删除功能
//*				 水平滚动条功能 
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "SimpleEmail.h"
#include "ExtendListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox

CExtendListBox::CExtendListBox()
{
}

CExtendListBox::~CExtendListBox()
{
}

BEGIN_MESSAGE_MAP(CExtendListBox, CListBox)
	//{{AFX_MSG_MAP(CExtendListBox)
	ON_MESSAGE(WM_DROPFILES, OnDragAcceptFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox message handlers
// -----------------------------------------------------------//
// Function :   CExtendListBox::AddString
// Param    :   LPCTSTR lpszItem
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CExtendListBox::AddString( LPCTSTR lpszItem )
{
	int nResult = CListBox::AddString( lpszItem );
	
	RefushHorizontalScrollBar();
	
	return nResult;
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::InsertString
// Param    :    int nIndex
//              LPCTSTR lpszItem
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CExtendListBox::InsertString( int nIndex, LPCTSTR lpszItem )
{
	int nResult = CListBox::InsertString( nIndex, lpszItem );
	
	RefushHorizontalScrollBar();
	
	return nResult;
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::RefushHorizontalScrollBar
// Param    :   void
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendListBox::RefushHorizontalScrollBar( void )
{
	CDC *pDC = this->GetDC();
	if ( NULL == pDC )
	{
		return;
	}

	int nCount = this->GetCount();
	if ( nCount < 1 )
	{
		this->SetHorizontalExtent( 0 );
		return;
	}

	int nMaxExtent = 0;
	CString szText;
	for ( int i = 0; i < nCount; ++i )
	{
		this->GetText( i, szText );
		CSize &cs = pDC->GetTextExtent( szText );
		if ( cs.cx > nMaxExtent )
		{
			nMaxExtent = cs.cx;
		}
	}

	nMaxExtent += 150;		// Add

	this->SetHorizontalExtent( nMaxExtent );
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::OnDragAcceptFiles
// Param    :   WPARAM wparam
//              LPARAM lparam
// Return   :   LRESULT
// Comment  :   
// -----------------------------------------------------------//
LRESULT CExtendListBox::OnDragAcceptFiles(WPARAM wparam,LPARAM lparam)
{	

	HDROP hdrop = (HDROP)wparam;
	if(hdrop == NULL)	return 0;
	CString strTemp = "";
	int nCount = ::DragQueryFile(hdrop, -1, NULL, 0);
	if(nCount > 0)
	{
		TCHAR szBuffer[MAX_PATH] = {0};
		for(int i = 0; i < nCount; i++)
		{
			::DragQueryFile(hdrop, i, szBuffer, MAX_PATH);
			m_strFileNameArr.Add(CString(szBuffer));	// Add
			AddString(szBuffer);						// AddString
			strTemp += szBuffer;
			strTemp += "\r\n";
		}
	}
	
	return 0;
}

// -----------------------------------------------------------//
// Function :   CExtendListBox::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CExtendListBox::PreTranslateMessage(MSG* pMsg) 
{
	HACCEL haccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_LISTBOX_DEL));
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(haccel && TranslateAccelerator(m_hWnd, haccel, pMsg))
		{
			if(pMsg->wParam == VK_DELETE)	
			{
				int index = this->GetCurSel();
				if(index != -1)
				{
					DeleteString(index);
					m_strFileNameArr.RemoveAt(index);
				}
			}
		}
	}

	return CListBox::PreTranslateMessage(pMsg);
}
