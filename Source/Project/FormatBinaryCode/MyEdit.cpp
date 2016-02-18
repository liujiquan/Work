//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   MyEdit.cpp
//* Author   :   liujiquan
//* DateTime :   10/9/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "StdAfx.h"
#include "MyEdit.h"

#define CTRL_C		10001
#define CTRL_V		10002
#define CTRL_X		10003


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CFormatBinaryCodeDlg)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// -----------------------------------------------------------//
// Function :   CMyEdit::CMyEdit
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CMyEdit::CMyEdit()
{
	
}

// -----------------------------------------------------------//
// Function :   CMyEdit::~CMyEdit
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CMyEdit::~CMyEdit()
{
//	::UnregisterHotKey(m_hWnd, CTRL_C);
//	::UnregisterHotKey(m_hWnd, CTRL_V);
//	::UnregisterHotKey(m_hWnd, CTRL_X);
}

void CMyEdit::InitHotKey()
{
//	BOOL b = ::RegisterHotKey(m_hWnd, CTRL_C, MOD_CONTROL, 0x41 + 'C' - 'A');
//	b = ::RegisterHotKey(m_hWnd, CTRL_V, MOD_CONTROL, 0x41 + 'V' - 'A');
//	b = ::RegisterHotKey(m_hWnd, CTRL_X, MOD_CONTROL, 0x41 + 'X' - 'A');
}

// -----------------------------------------------------------//
// Function :   CMyEdit::OnHotKey
// Param    :   LPARAM lprarm
//              WPARAM wparam
// Return   :   LRESULT
// Comment  :   
// -----------------------------------------------------------//
LRESULT CMyEdit::OnHotKey(LPARAM lprarm, WPARAM wparam)
{
	WORD w1 = LOWORD(wparam);
	WORD w2 = HIWORD(wparam);
	
	if(w1 ==  MOD_CONTROL && w2 == (0x41 + 'C' - 'A'))
	{
		Copy();
	}
	else if(w1 ==  MOD_CONTROL && w2 == (0x41 + 'V' - 'A'))
	{
		Paste();
	}
	else if(w1 ==  MOD_CONTROL && w2 == (0x41 + 'X' - 'A'))
	{
		Cut();
	}

	return 0;
}

void CMyEdit::OnKeyDown(UINT  nChar, UINT nRepCnt, UINT nFlags)
{
	SHORT sState = GetKeyState(VK_CONTROL);
	if(sState == 0)
	{
		return;
	}

	if(nChar == (0x41 + 'C' - 'A'))
	{
		Copy();
	}
	else if(nChar == (0x41 + 'V' - 'A'))
	{
	//	Paste();
	}
	else if(nChar == (0x41 + 'X' - 'A'))
	{
		Cut();
	}
	else if(nChar == (0x41 + 'A' - 'A'))
	{
		SetSel(0, -1);
	}
}