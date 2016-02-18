//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendEdit.cpp
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   CExtendEdit: 复制 粘贴 全选 剪切 回滚功能 
//*				 CExtendDropFileEdit: 继承CExtendEdit 文件拖拽功能
//*				 CExtendSuspensionEdit:CExtendEdit 双击弹出提示栏 选择数据填充
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "ExtendEdit.h"
#include "resource.h"
#include "MailUtil.h"
#include "SuspensionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit

CExtendEdit::CExtendEdit()
{
}

CExtendEdit::~CExtendEdit()
{
}


BEGIN_MESSAGE_MAP(CExtendEdit, CEdit)
	//{{AFX_MSG_MAP(CExtendEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit message handlers
// -----------------------------------------------------------//
// Function :   CExtendEdit::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#define VK_A	0x41				// all select
#define VK_C	0x43				// copy
#define VK_V	0x41 + 'V' - 'A'	// paste
#define VK_Z	0x41 + 'Z' - 'A'	// back
#define VK_X	0x41 + 'X' - 'A'	// clear
BOOL CExtendEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HACCEL haccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_EDIT));
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(haccel && TranslateAccelerator(m_hWnd, haccel, pMsg))
		{
			if(pMsg->wParam == VK_A)	
			{
				SetSel(0, -1);	
			}
			else if((pMsg->wParam == VK_C))
			{
				Copy();	
			}
			else if((pMsg->wParam == VK_V))
			{
				Paste();
			}
			else if((pMsg->wParam == VK_Z))
			{
				Undo();
			}
			else if((pMsg->wParam == VK_X))
			{
				Clear();
			}
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CExtendEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnLButtonDown(nFlags, point);
//	SetSel(0, -1);
//	Copy();
}

void CExtendEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
//	SetSel(0, 0);
}

// CExtendDropFileEdit
CExtendDropFileEdit::CExtendDropFileEdit()
{

}
CExtendDropFileEdit::~CExtendDropFileEdit()
{
}
BEGIN_MESSAGE_MAP(CExtendDropFileEdit, CExtendEdit)
	//{{AFX_MSG_MAP(CExtendEdit)
	ON_MESSAGE(WM_DROPFILES, OnDragAcceptFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// -----------------------------------------------------------//
// Function :   CExtendDropFileEdit::OnDragAcceptFiles
// Param    :   WPARAM wparam
//              LPARAM lparam
// Return   :   LRESULT
// Comment  :   
// -----------------------------------------------------------//
LRESULT CExtendDropFileEdit::OnDragAcceptFiles(WPARAM wparam,LPARAM lparam)
{	
	HDROP hdrop = (HDROP)wparam;
	if(hdrop == NULL)	return 0;
	CString strTemp = "";
	int nCount = ::DragQueryFile(hdrop, -1, NULL, 0);
	if(nCount > 0)
	{
		m_strFileNameArr.RemoveAll();
		TCHAR szBuffer[MAX_PATH] = {0};
		for(int i = 0; i < nCount; i++)
		{
			::DragQueryFile(hdrop, i, szBuffer, MAX_PATH);
			m_strFileNameArr.Add(CString(szBuffer));
			strTemp += szBuffer;
			strTemp += "\r\n";
		}
	}
	SetWindowText(strTemp);

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CExtendSuspensionEdit
CExtendSuspensionEdit::CExtendSuspensionEdit()
{
}

CExtendSuspensionEdit::~CExtendSuspensionEdit()
{
}

BEGIN_MESSAGE_MAP(CExtendSuspensionEdit, CExtendEdit)
//{{AFX_MSG_MAP(CExtendSuspensionEdit)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendSuspensionEdit message handlers
BOOL CExtendSuspensionEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_LBUTTONDBLCLK)
	{
		CSuspensionDlg dlg(this);
		CRect rect;
		GetWindowRect(rect);
		dlg.SetPos(rect);
		dlg.DoModal();
		if(dlg.m_InserUser != "")
		{
			CString strText;
			GetWindowText(strText);
			if(strText == "")
			{
				strText = dlg.m_InserUser;
			}
			else
			{
				strText = strText + SPLITCHAR + dlg.m_InserUser;
			}
			
			SetWindowText(strText);
		}
	
		return TRUE;
	}

	return CExtendEdit::PreTranslateMessage(pMsg);
}