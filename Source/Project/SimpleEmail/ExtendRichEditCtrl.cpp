//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendRichEditCtrl.cpp
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "SimpleEmail.h"
#include "ExtendRichEditCtrl.h"
#include "InsertInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendRichEditCtrl
#define TEXT_COLOR	RGB(255, 255, 255)			// nomarl color
#define LINK_TEXT_COLOR	RGB(255, 112, 5)		// link color
CExtendRichEditCtrl::CExtendRichEditCtrl()
{
	AfxInitRichEdit();
}

CExtendRichEditCtrl::~CExtendRichEditCtrl()
{
}
BEGIN_MESSAGE_MAP(CExtendRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CExtendRichEditCtrl)
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_COMMAND(ID_MENUITEM_INSERTHREF, OnMenuitemInserthref)
	ON_COMMAND(ID_MENUITEM_INSERTIMG, OnMenuitemInsertimg)
	ON_COMMAND(ID_MENUITEM_INSERTVEDIO, OnMenuitemInsertvedio)
	ON_COMMAND(ID_MENUITEM_INSERTAUDIO, OnMenuitemInsertaudio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CExtendRichEditCtrl message handlers
BOOL CExtendRichEditCtrl::Initlize()
{
	SetEventMask(GetEventMask() | EN_LINK); 

	GetDefaultCharFormat(m_Defaultcf);
	m_LinkCf = m_Defaultcf;
//	m_LinkCf.dwMask |= CFM_LINK |CFM_UNDERLINE;		// link bold underline
//	m_LinkCf.dwMask &= ~CFM_COLOR;
	m_LinkCf.dwEffects =  CFE_LINK |CFE_UNDERLINE;	// link bold underline
	m_LinkCf.dwEffects &= ~CFE_AUTOCOLOR;
	m_LinkCf.crTextColor = LINK_TEXT_COLOR;

	return TRUE;
}

int CExtendRichEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}

void CExtendRichEditCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CRichEditCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#define VK_L	0x41 + 'L' - 'A'	// link
#define VK_A	0x41				// all select
#define VK_C	0x43				// copy
#define VK_V	0x41 + 'V' - 'A'	// paste
#define VK_Z	0x41 + 'Z' - 'A'	// back
#define VK_X	0x41 + 'X' - 'A'	// clear
BOOL CExtendRichEditCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HACCEL haccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_RICKEDITCTRL));
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(haccel && TranslateAccelerator(m_hWnd, haccel, pMsg))
		{
//			if(pMsg->wParam == VK_L)	
//			{
//				AddSelLink();
//			}
//			else 
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
				Cut();
			}
		}
		
	}
	else if(pMsg->message == WM_RBUTTONDOWN)
	{
		POINT pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU_RICHEDIT);
		CMenu* pSubMenu = menu.GetSubMenu(0);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}
//	if(pMsg->message == WM_KEYDOWN)
//	{
//		UINT nVirKey = (UINT)pMsg->wParam;
//		if(nVirKey == VK_BACK)
//		{			
//			if(DelLink() == TRUE)
//			{
//				return TRUE;
//			}
//		}
//	}
	return CRichEditCtrl::PreTranslateMessage(pMsg);
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::AddSelLink
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendRichEditCtrl::AddSelLink()
{
	CHARRANGE cr;
	GetSel(cr);
	if(cr.cpMin >= cr.cpMax)		return;
	
	SetSelectionCharFormat(m_LinkCf);			// setting
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::DelLink
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CExtendRichEditCtrl::DelLink()	
{
	int nIndexMax = 0;	
	int nIndexMin = 0;
	CHARRANGE Oldcr;
	CHARRANGE cr;
	CHARFORMAT cf;
	DWORD dwCFFlags = 0;

	GetSel(Oldcr);						// current sel
	cr = Oldcr;
	if(cr.cpMin > cr.cpMax)		return FALSE;
	nIndexMin = cr.cpMin;
	nIndexMax = cr.cpMax;
	nIndexMin--;
	cr.cpMax = cr.cpMin = nIndexMin;
	SetSel(cr);

	GetSelectionCharFormat(cf);
	if((cf.dwEffects & CFE_LINK) != CFE_LINK && (cf.dwEffects & CFE_UNDERLINE) != CFE_UNDERLINE )	// no link
	{
		SetSel(Oldcr);
		return FALSE;
	}

	while(true)
	{
		nIndexMin--;
		cr.cpMax = cr.cpMin = nIndexMin;
		SetSel(cr);

		GetSelectionCharFormat(cf);
		if((cf.dwEffects & CFE_LINK) != CFE_LINK && (cf.dwEffects & CFE_UNDERLINE) != CFE_UNDERLINE )	// no link
			break;
		if(nIndexMin == 0)	
			break;
	}
	SetSel(nIndexMin, nIndexMax);
	SetSelectionCharFormat(m_Defaultcf);
	SetSel(Oldcr);

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::OnChange
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
#define MAX_URL_SIZE		MAX_PATH
void CExtendRichEditCtrl::OnChange()
{
	CString strText;
	GetWindowText(strText);
	
	CHARRANGE cr,crold;
	GetSel(crold);
	cr = crold;
	
	cr.cpMax = -1;
	cr.cpMin = 0;
	SetSel(cr);
	SetSelectionCharFormat(m_Defaultcf);

	long nBeginIndex = 0;
	TEXTTYPE findType;
	long lFindDataStart = 0;
	long lFindDataEnd = 0;
	CString strRightData = "";

	lFindDataEnd = FindNextData(nBeginIndex, lFindDataStart, findType, strRightData);
	while(lFindDataEnd != -1)
	{
		SetSel(lFindDataStart, lFindDataEnd + strRightData.GetLength());
		SetSelectionCharFormat(m_LinkCf);

		nBeginIndex = lFindDataEnd + strRightData.GetLength();
		lFindDataEnd = FindNextData(nBeginIndex, lFindDataStart, findType, strRightData);
	}
	
	SetSel(crold);
}


long CExtendRichEditCtrl::FindNextData(long nBeginIndex, long& lFindDataStart, TEXTTYPE& findType, CString& strRightData)
{
	if(nBeginIndex < 0)				return -1;

	FINDTEXTEX hrefFindText;		// href
	FINDTEXTEX imgFindText;			// ime
	FINDTEXTEX audioFindText;		// audio
	FINDTEXTEX vedioFindText;		// vedio

	hrefFindText.chrg.cpMin = hrefFindText.chrgText.cpMin = nBeginIndex;
	hrefFindText.chrg.cpMax = hrefFindText.chrgText.cpMax = -1;
	memcpy(&imgFindText, &hrefFindText, sizeof(FINDTEXTEX));
	memcpy(&audioFindText, &hrefFindText, sizeof(FINDTEXTEX));
	memcpy(&vedioFindText, &hrefFindText, sizeof(FINDTEXTEX));

	hrefFindText.lpstrText = HREF_LEFT;			//  1:href
	imgFindText.lpstrText = IMG_LEFT;			//  1:img
	audioFindText.lpstrText = AUDIO_LEFT;		//  1:audio
	vedioFindText.lpstrText = VEDIO_LEFT;		//  1:vedio
	
	long nHrefBegin	= FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &hrefFindText);			// find href
	long nImgBegin	= FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &imgFindText);				// find img
	long nAudioBegin = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &audioFindText);			// find audio
	long nVedioBegin = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &vedioFindText);			// find vedio
	long nEndIndex = -1;

	SortData sortDataArr[4];
	if(SortFindIndex(nHrefBegin, nImgBegin, nAudioBegin, nVedioBegin, sortDataArr) == FALSE)	return -1;
	
	for(int i = 0; i < 4; i++)
	{
		TEXTTYPE type = sortDataArr[i].type;
		long nStartIndex = sortDataArr[i].nStartIndex;
		if(nStartIndex == -1)	continue;
		lFindDataStart = nStartIndex;
		switch(type)
		{
		case TEXT_HREF:
			hrefFindText.lpstrText = HREF_RIGHT;
			nEndIndex = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &hrefFindText);
			if(nEndIndex != -1)	
			{
				strRightData = HREF_RIGHT;
				findType = TEXT_HREF;
				return		nEndIndex;
			}
			break;
		case TEXT_IMG:
			imgFindText.lpstrText = IMG_RIGHT;
			nEndIndex = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &imgFindText);
			if(nEndIndex != -1)	
			{
				strRightData = IMG_RIGHT;
				findType = TEXT_IMG;
				return		nEndIndex;
			}
			break;
		case TEXT_AUDIO:
			audioFindText.lpstrText = AUDIO_RIGHT;
			nEndIndex = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &audioFindText);
			if(nEndIndex != -1)	
			{
				strRightData = AUDIO_RIGHT;
				findType = TEXT_AUDIO;
				return		nEndIndex;
			}
			break;
		case TEXT_VEDIO:
			vedioFindText.lpstrText = VEDIO_RIGHT;
			nEndIndex = FindText(FR_DOWN|FR_MATCHCASE|FR_FINDNEXT, &vedioFindText);
			if(nEndIndex != -1)	
			{
				strRightData = VEDIO_RIGHT;
				findType = TEXT_VEDIO;
				return		nEndIndex;
			}
			break;
		}
	}

	return -1;
}

BOOL CExtendRichEditCtrl::SortFindIndex(long a, long b, long c, long d, SortData findDataArr[])
{
	if(a == -1 && b == -1 && c == -1 && d == -1)		return FALSE;

	findDataArr[0].type = TEXT_HREF;
	findDataArr[0].nStartIndex = a;
	findDataArr[1].type = TEXT_IMG;
	findDataArr[1].nStartIndex = b;
	findDataArr[2].type = TEXT_AUDIO;
	findDataArr[2].nStartIndex = c;
	findDataArr[3].type = TEXT_VEDIO;
	findDataArr[3].nStartIndex = d;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = i+1; j < 4; j++)
		{
			if(findDataArr[j].nStartIndex < findDataArr[i].nStartIndex)
			{
				SortData temp = findDataArr[i];
				findDataArr[i] = findDataArr[j];
				findDataArr[j] = temp;
			}
		}
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::Split
// Param    :   CArray<TEXTINFO
//              TEXTINFO>& textArr
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendRichEditCtrl::Split(CArray<TEXTINFO, TEXTINFO>& textArr)
{
	CString strText;
	GetWindowText(strText);
	
	CHARRANGE cr,crold;
	GetSel(crold);
	cr = crold;
	
	long nBeginIndex = 0;
	TEXTTYPE findType;
	long lFindDataStart = 0;
	long lFindDataEnd = 0;
	CString strRightData = "";
	TEXTINFO info;

	lFindDataEnd = FindNextData(nBeginIndex, lFindDataStart, findType, strRightData);
	while(lFindDataEnd != -1)
	{
		CString strNormalText1 = strText.Mid(nBeginIndex, lFindDataStart - nBeginIndex);
		if(strNormalText1 != "")
		{
			info.nFlag = TEXT_TEXT;
			info.strText = strNormalText1;
			textArr.Add(info);
		}
		CString strDataText = strText.Mid(lFindDataStart, lFindDataEnd + strRightData.GetLength() - lFindDataStart);
		info.nFlag = findType;
		info.strText = strDataText.Mid(strRightData.GetLength(), strDataText.GetLength() - 2 * strRightData.GetLength());
		if(info.strText != "")
		{
			textArr.Add(info);
		}

		nBeginIndex = lFindDataEnd + strRightData.GetLength();
		lFindDataEnd = FindNextData(nBeginIndex, lFindDataStart, findType, strRightData);
	}
	info.nFlag = TEXT_TEXT;
	info.strText = strText.Right(strText.GetLength() - nBeginIndex);
	if(info.strText != "")
	{
		textArr.Add(info);
	}

	SetSel(crold);
}


void CExtendRichEditCtrl::OnMenuitemInserthref() 
{
	InsertInfo(0);	
}

void CExtendRichEditCtrl::OnMenuitemInsertimg() 
{
	InsertInfo(1);
}

void CExtendRichEditCtrl::OnMenuitemInsertaudio() 
{
	InsertInfo(2);
}

void CExtendRichEditCtrl::OnMenuitemInsertvedio() 
{
	InsertInfo(3);
}

// -----------------------------------------------------------//
// Function :   CExtendRichEditCtrl::InsertInfo
// Param    :   int nFlag /* = 0 */
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CExtendRichEditCtrl::InsertInfo(int nFlag /* = 0 */)
{
	CHARRANGE cr, crold;
	GetSel(cr);
	crold = cr;
	
	CString strText = GetSelText();
	CInsertInfoDlg insertDlg;
	insertDlg.SetInsertFlag(nFlag);
	insertDlg.DoModal();
	ReplaceSel(insertDlg.m_InserInfo);
}