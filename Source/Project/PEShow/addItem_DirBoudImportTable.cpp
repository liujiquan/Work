//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItem_DirBoudBoundImportTable.cpp
//* Author   :   liujiquan
//* DateTime :   9/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "PEShow.h"
#include "PEShowDoc.h"
#include "PEShowView.h"
#include "MainFrm.h"
#include "SuperGridCtrl\supergridctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef N_A
#define N_A  -1
#endif 

void InsertBoundImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem);
BOOL IsBoundImportSymbolaEnd(PIMAGE_BOUND_IMPORT_DESCRIPTOR pBoundImportDesc);
CTreeItem_*  AddBoundImportInfoItem(CHAR*  strName, DWORD dwOridinal,  DWORD dwHint, CHAR*  FuncName, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, BOOL bDLL = FALSE);
CTreeItem_*  AddImportInfoItem(DWORD& dwBaseAddress, CHAR*  strName, DWORD TimeDateStamp, DWORD dwRefs, int index,  CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, BOOL bDLL = FALSE);
// -----------------------------------------------------------//
// Function :   Add_Directory_BoundImportSymbols
// Param    :   DWORD			dwVirtualAddress
//              DWORD			dwSize
//              CMySuperGrid&	m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_Directory_BoundImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid)
{
	if(dwVirtualAddress == 0 || dwSize == 0 || (dwVirtualAddress + dwSize) > GetMaxSize())
	{
		return NULL;
	}
	
	CItemInfo* pBoundImportMainItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwVirtualAddress;
	pBoundImportMainItem->SetImage(0);
	pBoundImportMainItem->SetItemText("BoundImport Symbols");
	strTemp.Format("%08x", dwBase);
	pBoundImportMainItem->AddSubItemText(strTemp);
	pBoundImportMainItem->AddSubItemText("-");
	pBoundImportMainItem->AddSubItemText("-");
	pBoundImportMainItem->AddSubItemText("-");
	
	CTreeItem_* pBoundImportMainTreeItem =  m_ListGrid.InsertRootItem(pBoundImportMainItem);
	if(pBoundImportMainTreeItem == NULL)
	{
		return NULL;
	}
	
	// Insert Item(DLL/ Dll Function)
	InsertBoundImportSymbols(dwVirtualAddress, dwSize, m_ListGrid, pBoundImportMainTreeItem);
	
	return pBoundImportMainTreeItem;
}

// -----------------------------------------------------------//
// Function :   InsertBoundImportSymbols
// Param    :   DWORD dwVirtualAddress
//              DWORD dwSize
//              CMySuperGrid& m_ListGrid
//              CTreeItem_* pParentTreeItem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void InsertBoundImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem)
{
	if(dwVirtualAddress == 0 || dwSize == 0 || pParentTreeItem == NULL)
	{
		return;
	}
	
	// PE Data
	DWORD dwBaseAddress = dwVirtualAddress;
	CHAR* szData = GetData();
	if(szData == NULL)
	{
		return;
	}
	//
	PIMAGE_BOUND_IMPORT_DESCRIPTOR pBoundImportDes = NULL;
	PIMAGE_BOUND_FORWARDER_REF pBoundForwarderRef = NULL;
	CHAR* szDllName = NULL;					// dllName
	
	
	
	pBoundImportDes = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)(szData + dwVirtualAddress);
	while(!IsBoundImportSymbolaEnd(pBoundImportDes))
	{
		WORD wForwarderRefs = pBoundImportDes->NumberOfModuleForwarderRefs;
		szDllName = szData + dwVirtualAddress + pBoundImportDes->OffsetModuleName;
		CTreeItem_*  pMainDllItem = AddImportInfoItem(dwBaseAddress, szDllName, pBoundImportDes->TimeDateStamp, 
			wForwarderRefs, N_A, pParentTreeItem, m_ListGrid);


		for(int nIndex = 0; nIndex < wForwarderRefs; nIndex++)
		{
			pBoundForwarderRef = (PIMAGE_BOUND_FORWARDER_REF)(pBoundImportDes + nIndex);
			AddImportInfoItem(dwBaseAddress, szDllName, pBoundImportDes->TimeDateStamp, wForwarderRefs, nIndex, pMainDllItem, m_ListGrid);
		}
		if(wForwarderRefs == 0)
		{
			pBoundImportDes++;
		}
		else
		{
			pBoundImportDes = (PIMAGE_BOUND_IMPORT_DESCRIPTOR)(pBoundForwarderRef + 1);
		}
	}

}

// -----------------------------------------------------------//
// Function :   IsBoundImportSymbolaEnd
// Param    :   PIMAGE_BOUND_IMPORT_DESCRIPTOR pBoundImportDesc
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL IsBoundImportSymbolaEnd(PIMAGE_BOUND_IMPORT_DESCRIPTOR pBoundImportDesc)
{
	if(pBoundImportDesc->NumberOfModuleForwarderRefs == 0x00 &&
		pBoundImportDesc->OffsetModuleName == 0x00 &&
		pBoundImportDesc->TimeDateStamp == 0x00)
	{
		return TRUE;
	}

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   AddImportInfoItem
// Param    :   DWORD& dwBaseAddress
//              CHAR*  strName
//              DWORD TimeDateStamp
//              DWORD dwRefs
//				WORD index
//              CTreeItem_* parentItem
//              CMySuperGrid& m_ListGrid
//              BOOL bDLL /*= FALSE*/
// Return   :   CTreeItem_* 
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_*  AddImportInfoItem(DWORD& dwBaseAddress, CHAR*  strName, DWORD TimeDateStamp, DWORD dwRefs, int index, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, BOOL bDLL /*= FALSE*/)
{
	if(parentItem == NULL)
	{
		return NULL;
	}
	
	CString strTemp;
	CItemInfo* pBoundImportItem = new CItemInfo();
	pBoundImportItem->SetImage(0);
	//Index
	if(index == N_A)
	{
		pBoundImportItem->SetItemText("-");
	}
	else
	{
		strTemp.Format("%d", index);
		pBoundImportItem->SetItemText(strTemp);
	}
	//dwBaseAddress
	strTemp.Format("%08X", dwBaseAddress);
	pBoundImportItem->AddSubItemText(strTemp);
	//strName
	if(strName == NULL)
	{
		pBoundImportItem->AddSubItemText("-");
	}
	else
	{
		pBoundImportItem->AddSubItemText(strName);
	}
	//TimeDateStamp
	pBoundImportItem->AddSubItemText(FormatTime(TimeDateStamp));
	//dwRefs
	if(dwRefs == N_A)
	{
		pBoundImportItem->AddSubItemText("-");
	}
	else
	{
		strTemp.Format("%d", dwRefs);
		pBoundImportItem->AddSubItemText(strTemp);
	}
	dwBaseAddress += sizeof(IMAGE_BOUND_IMPORT_DESCRIPTOR);

	return m_ListGrid.InsertItem(parentItem, pBoundImportItem);
}

