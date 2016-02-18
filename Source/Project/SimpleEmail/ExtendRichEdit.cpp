//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendRichEdit.cpp
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
// ExtendRichEdit.cpp : implementation file
//
#include "stdafx.h"
#include "SimpleEmail.h"
#include "ExtendRichEdit.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendRichEdit
#pragma warning(default:4996)
IMPLEMENT_DYNCREATE(CExtendRichEdit, CRichEditCtrl)
CExtendRichEdit::CExtendRichEdit()
{
	m_ShowBorder =    TRUE;
    m_BorderColor = RGB(53, 104, 187);
    m_bBottom = true;
    m_bCreate = false;
    m_bFocus = true;
    AfxInitRichEdit();
}

CExtendRichEdit::~CExtendRichEdit()
{
}

BEGIN_MESSAGE_MAP(CExtendRichEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CExtendRichEdit)
    ON_WM_PAINT()
    ON_NOTIFY_REFLECT_EX(EN_LINK, OnLink)
    ON_WM_SETFOCUS()
	ON_WM_RBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CExtendRichEdit message handlers
#define CP_UNICODE		1200
#define CP_ASCII		CP_ACP

void CExtendRichEdit::Initlize()
{
    m_bBottom = true;
    m_bCreate = true;
    SetEventMask(GetEventMask() | ENM_LINK) ; 
    //SendMessage(EM_AUTOURLDETECT, TRUE, 0);
    SetOptions(ECOOP_OR, ECO_AUTOVSCROLL);
    LimitText(0xFFFFFFFF);
    SetBackgroundColor(FALSE,RGB(248,248,248));
    SetLeftOffset(150);
}

long CExtendRichEdit::GetTextLengthEx( DWORD dwFlags,  UINT uCodePage) const
{
	GETTEXTLENGTHEX getlenEx;
	memset(&getlenEx, 0x00, sizeof(GETTEXTLENGTHEX));
	getlenEx.codepage = uCodePage;		// unicode
	getlenEx.flags = dwFlags;			// default

	long lRet =  ::SendMessage(m_hWnd, EM_GETTEXTLENGTHEX, (WPARAM)&getlenEx, 0);

	return lRet;
}

void CExtendRichEdit::Append(LPCSTR text,bool newline,bool link,int nLinkBegin,int nLinkCount)
{
    int nPrvTotal = GetTextLengthEx( GTL_DEFAULT, 1200 );
//  SetSel(-1,-1);
    ReplaceSel((LPCTSTR)text);
    if (newline)
    {
        Append("\r\n");
    }
    if (link)
    {
        if (!newline)
        {
            Append("\r\n");
        }
        int nTotal = GetTextLengthEx( GTL_DEFAULT, 1200 ) - 1;
        if( nTotal > 0)
        {
            if (nLinkCount>nTotal-nPrvTotal)
            {
                nLinkCount = nTotal-nPrvTotal;
            }
            SetSel( nPrvTotal+nLinkBegin, nPrvTotal+nLinkBegin+nLinkCount );
            AddLink();
        }
    }
    // ??????????????????
    if (m_bBottom)
    {
        PostMessage(WM_VSCROLL, SB_BOTTOM,0);
    }
}
void CExtendRichEdit::GetText(int nBegin,int nEnd,CString& text)
{
    CHARRANGE CharRange;
    CharRange.cpMin = nBegin;
    CharRange.cpMax = nEnd;
    SetSel(CharRange);
    CHAR szTmp[1024] = {0};
    GetSelText(szTmp);
    text.Format("%s",szTmp);
}
void CExtendRichEdit::SetScrollBottom(bool bottom)
{
    m_bBottom = bottom;
}
void CExtendRichEdit::StopScroll()
{
    m_bBottom = !m_bBottom;
    if (m_bBottom)
    {
        PostMessage(WM_VSCROLL, SB_BOTTOM,0);
    }
}
void CExtendRichEdit::SetTextFont(int nBegin,int nEnd,bool bold,bool italic,bool underline,COLORREF color,int size)
{
    SetSel(nBegin,nEnd);
    CHARFORMAT2 cf,oldCf;
    GetSelectionCharFormat(oldCf);
    GetSelectionCharFormat(cf);
    if (bold)
    {
        cf.dwMask|=CFM_BOLD;
        cf.dwEffects|=CFE_BOLD;            //????,???cf.dwEffects&=~CFE_BOLD;
    }
    if (italic)
    {
        cf.dwMask|=CFM_ITALIC;
        cf.dwEffects|=CFE_ITALIC;			//????,???cf.dwEffects&=~CFE_ITALIC;
    }
    if (underline)
    {
        cf.dwMask|=CFM_UNDERLINE;
        cf.dwEffects|=CFE_UNDERLINE;		//?????,???cf.dwEffects&=~CFE_UNDERLINE;
    }
    if (color)
    {
        cf.dwEffects &= ~CFE_AUTOCOLOR;    //?????,??????????????,dwEffects?????CEF_AUTOCOLOR???
        cf.dwMask|=CFM_COLOR;
        cf.crTextColor = color;				//????
    }
    if (size)
    {
        cf.dwMask|=CFM_SIZE;
        cf.yHeight =200;					//????
    }
    cf.dwMask|=CFM_FACE;
    strcpy(cf.szFaceName ,_T("??"));//????
    SetSelectionCharFormat(cf);
    SetSel(-1,-1);
    SetSelectionCharFormat(oldCf);
}
void CExtendRichEdit::AddLink()
{
    CHARFORMAT2 cf2;
    ZeroMemory(&cf2, sizeof(CHARFORMAT2));
    cf2.cbSize = sizeof(CHARFORMAT2);
 
    cf2.dwMask |= CFM_LINK;
    cf2.dwEffects |= CFE_LINK;
 
    cf2.dwEffects &= ~CFE_AUTOCOLOR;    // no CEF_AUTOCOLOR
    cf2.dwMask |= CFM_COLOR;
    cf2.crTextColor = RGB( 255, 112, 5 );
 
    SetSelectionCharFormat(cf2);
    SetSel( -1, -1 );
}
 
void CExtendRichEdit::CancelLink()
{
    CHARFORMAT2 cf2;
    ZeroMemory(&cf2, sizeof(CHARFORMAT2));
    cf2.cbSize = sizeof(CHARFORMAT2);
    cf2.dwMask = CFM_LINK;
    cf2.dwEffects &= ~CFE_LINK;
 
    SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf2);
    SetSel( -1, -1 );
}
BOOL CExtendRichEdit::CheckURL(const CString &szUrl, CString &szMsg)
{
    DWORD dwService = 0;
    DWORD dwValid = AFX_INET_SERVICE_FTP|AFX_INET_SERVICE_HTTP|AFX_INET_SERVICE_HTTPS|AFX_INET_SERVICE_FILE;
    CString strServer;  
    CString strObject;  
    INTERNET_PORT port; 
 
    BOOL bValid = AfxParseURL(szUrl, dwService, strServer, strObject, port);  
    if (!bValid)
    { 
        szMsg = szUrl + "\rURL failed.";
        return FALSE;  
    }
    return TRUE;
}
BOOL CExtendRichEdit::OnLink(NMHDR *pNotifyHeader, LRESULT *pResult)
{
    ENLINK *pEnLink = reinterpret_cast<ENLINK *>(pNotifyHeader);
    CString      strURL;
    *pResult = 0;
    CHAR szTmpLink[512] = {0};
    switch (pNotifyHeader->code)
    {
    case EN_LINK:
        switch (pEnLink->msg)
        {
        case WM_LBUTTONUP:
            SetSel(pEnLink->chrg);
            GetSelText(szTmpLink);
            strURL.Format("%s",szTmpLink);
            CString strMsg;
            if (CheckURL(strURL,strMsg))
            {
                ShellExecute(GetSafeHwnd(), _T("open"), strURL, NULL, NULL, SW_SHOWNORMAL);
            }
            break;
        }
        break;
    }
    return *pResult;
}
 
//    We need to handle the OnSize message to ensure that the most recent
//    line of text is visible.
void CExtendRichEdit::OnSize(UINT nType, int cx, int cy)
{
    CRichEditCtrl::OnSize(nType, cx, cy);
}
void CExtendRichEdit::OnSize(CWnd* pParent)
{
    if (!m_bCreate)
    {
        return;
    }
    CRect parentRect;
    pParent->GetClientRect(parentRect);
    parentRect.bottom = parentRect.bottom - 5;
    parentRect.top = parentRect.top + 5;
    parentRect.left = parentRect.left + 5;
    parentRect.right = parentRect.right - 5;
    MoveWindow(parentRect,TRUE);
}
void CExtendRichEdit::OnSize(CRect& rect)
{
    if (!m_bCreate)
    {
        return;
    }
    rect.bottom = rect.bottom - 5;
    rect.top = rect.top + 5;
    rect.left = rect.left + 5;
    rect.right = rect.right - 5;
    MoveWindow(rect,TRUE);
}
void CExtendRichEdit::OnSpecifySize(CWnd* pParent)
{
    if (!m_bCreate)
    {
        return;
    }
    CRect parentRect;
    pParent->GetClientRect(parentRect);
    parentRect.left = 5;
    parentRect.top = 197;
    parentRect.right -= 5;
    parentRect.bottom -= 5;
    MoveWindow(parentRect,TRUE);
 
}
void CExtendRichEdit::OnPaint()
{
    if (!m_ShowBorder)
    {
        CRichEditCtrl::OnPaint();
        return;
    }
    CRichEditCtrl::OnPaint();
    CClientDC dc(this);
    if (!m_pParentWnd)
    {
        return;
    }
    CRect rect;
    GetWindowRect(rect);
    rect.left-=1;
    rect.top-=1;
    rect.right+=1;
    rect.bottom+=1;
    ScreenToClient(rect);
    dc.Draw3dRect(rect,m_BorderColor,m_BorderColor);
}
void CExtendRichEdit::OnSetFocus(CWnd* pOldWnd)
{
    if (!m_bFocus)
    {
        return;
    }
    CRichEditCtrl::OnSetFocus(pOldWnd);
}
 
bool CExtendRichEdit::IsCreate()
{
    return m_bCreate;
}
void CExtendRichEdit::Clear()
{
    if (GetWindowLong(this->m_hWnd,GWL_STYLE) & ES_READONLY)
    {
        SetReadOnly(FALSE);
        CRichEditCtrl::Clear();
        SetReadOnly();
    }
    else
    {
        CRichEditCtrl::Clear();
    }
}
void CExtendRichEdit::SetEditFocus(bool focus)
{
    m_bFocus = focus;
}
void CExtendRichEdit::ShowBorderLine(BOOL bShow,COLORREF nColor)
{
    m_ShowBorder = bShow;
}
void CExtendRichEdit::SetLeftOffset(int nOffset)
{
    PARAFORMAT2 PF_his;
    PF_his.dwMask = PFM_ALIGNMENT|PFM_STARTINDENT;
    PF_his.wAlignment = PFA_LEFT;
    PF_his.dxStartIndent = nOffset;
    SetParaFormat(PF_his);
}

void CExtendRichEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar >= 0x21 && nChar <= 0x2F)			// space [ " # $ % & ' ( ) * + , - . /
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x30 && nChar <= 0x39)		// 0-9 
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x3A && nChar <= 0x40)		// : ; < = > ? @
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x41 && nChar <= 0x5A)		// A-Z
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x5B && nChar <= 0x60)		// [ \ ] ^ _ `
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x61 && nChar <= 0x7A)		// a-z
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar >= 0x7B && nChar <= 0x7E)		// { | } ~ 
	{
		Append((LPCSTR)&nChar);
	}
	else if(nChar == 0x09)	// tab
	{
		Append((LPCSTR)&nChar);
	}
	else
	{
		CRichEditCtrl::OnChar(nChar, nRepCnt, nFlags);
	}
}

// -----------------------------------------------------------//
// Function :   CExtendRichEdit::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#define VK_A	0x41				// all select
#define VK_C	0x43				// copy
#define VK_V	0x41 + 'V' - 'A'	// paste
#define VK_Z	0x41 + 'Z' - 'A'	// back
#define VK_X	0x41 + 'X' - 'A'	// clear
BOOL CExtendRichEdit::PreTranslateMessage(MSG* pMsg) 
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
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}
