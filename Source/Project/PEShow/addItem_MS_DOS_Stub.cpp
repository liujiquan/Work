//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItem_MS_DOS_Stub.cpp
//* Author   :   liujiquan
//* DateTime :   9/5/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "PEShow.h"
#include "PEShowDoc.h"
#include "PEShowView.h"
#include "DosHeaderDlg.h"
#include "MainFrm.h"
#include "PEFileHeader.h"
#include "SuperGridCtrl\supergridctrl.h"
#include <tchar.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   Add_MS_DOS_Stub
// Param    :   CHAR*			pBuffer
//              CMySuperGrid&	m_ListGrid
//              CTreeItem_*		parentItem
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_MS_DOS_Stub(CHAR* pBuffer, DWORD dwAddressBase, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem)
{
	if(pBuffer == NULL || parentItem == NULL)
	{
		return NULL;
	}
	
	CItemInfo* dosStubItem = new CItemInfo();
	dosStubItem->SetImage(0);
	dosStubItem->SetItemText("MS_DOS_Stub");
	CString str;
	str.Format(_T("%08x"), dwAddressBase);
	dosStubItem->AddSubItemText(str);
	dosStubItem->AddSubItemText("-");
	dosStubItem->AddSubItemText("-");
	dosStubItem->AddSubItemText("-");
	dosStubItem->AddSubItemText("MS_DOS_Stub");
	
	CTreeItem_* pDosTreeItem =  m_ListGrid.InsertItem(parentItem, dosStubItem);
	if(pDosTreeItem == NULL)
	{
		return NULL;
	}

	return pDosTreeItem;
}
