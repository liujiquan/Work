//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItem_DirExportSymbols.cpp
//* Author   :   liujiquan
//* DateTime :   9/9/2014
//* Version  :   1.0
//* Comment  :   Export
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

void InsertExportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem);
CTreeItem_*  AddExportInfoItem(CHAR*  strName, DWORD dwOridinal,  DWORD dwHint, CHAR* FuncName, DWORD dwEntryPoint, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
// -----------------------------------------------------------//
// Function :   Add_Directory_ImportSymbols
// Param    :   DWORD			dwVirtualAddress
//              DWORD			dwSize
//              CMySuperGrid&	m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_Directory_ExportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid)
{
	if(dwVirtualAddress == 0 || dwSize == 0)
	{
		return NULL;
	}

	CItemInfo* pImportMainItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwVirtualAddress;
	pImportMainItem->SetImage(0);
	pImportMainItem->SetItemText("Export Symbols");
	strTemp.Format("%08x", dwBase);
	pImportMainItem->AddSubItemText(strTemp);
	pImportMainItem->AddSubItemText("-");
	pImportMainItem->AddSubItemText("-");
	pImportMainItem->AddSubItemText("-");
	pImportMainItem->AddSubItemText("-");
	
	CTreeItem_* pImportMainTreeItem =  m_ListGrid.InsertRootItem(pImportMainItem);
	if(pImportMainTreeItem == NULL)
	{
		return NULL;
	}

	// Insert Item(DLL/ Dll Function)
	InsertExportSymbols(dwVirtualAddress, dwSize, m_ListGrid, pImportMainTreeItem);

	return pImportMainTreeItem;
}

// -----------------------------------------------------------//
// Function :   InsertExportSymbols
// Param    :   DWORD				dwVirtualAddress
//              DWORD				dwSize
//              CMySuperGrid&		m_ListGrid
//              CTreeItem_*			pParentTreeItem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
typedef struct tag_IMAGE_EXPORT_BY_ENTRYPOINT{
	DWORD entryPointRVA;							// The Real Virtual Address for Name
}IMAGE_EXPORT_BY_ENTRYPOINT, *PIMAGE_EXPORT_BY_ENTRYPOINT;

typedef struct tag_IMAGE_EXPORT_BY_NAME{
	DWORD nameRVA;							// The Real Virtual Address for Name
}IMAGE_EXPORT_BY_NAME, *PIMAGE_EXPORT_BY_NAME;

typedef struct tag_IMAGE_EXPORT_BY_ORDINAL{
	WORD ordinalRVA;							// The Real Virtual Address for ordinal
}IMAGE_EXPORT_BY_ORDINAL, *PIMAGE_EXPORT_BY_ORDINAL;

//IMAGE_THUNK_DATA
void InsertExportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem)
{
	if(dwVirtualAddress == 0 || dwSize == 0 || pParentTreeItem == NULL)
	{
		return;
	}

	// PE Data
	CHAR* szData = GetData();
	if(szData == NULL)
	{
		return;
	}
	//
	PIMAGE_EXPORT_DIRECTORY	 pExportDir;
	UINT nDllSize = 0;							// Sizeof Dll
	UINT nFunSize = 0;							// sizeof Dll Function
	CHAR* szModuleName = NULL;					// dllName
	CHAR* szFunName = NULL;

	// EntryPoint[nFuncSize(DWORD)]
	// Func Name RVA[nNameSize(DWORD)]		--NO Name NO This Memory
	// NameOrdinal[nNameSize](WORD)			--NO Name NO This Memory
	// DLL Name[1('\0'End)]					
	// Func name[nNameSize('\0'End)]		--NO Name NO This Memory
	pExportDir = (PIMAGE_EXPORT_DIRECTORY)(szData + dwVirtualAddress);
	if(pExportDir)
	{
		szModuleName = szData + pExportDir->Name;

		DWORD dwbase = pExportDir->Base;						// Base Ordinal
		DWORD nFuncSize = pExportDir->NumberOfFunctions;		// Func Count
		DWORD nNameSize = pExportDir->NumberOfNames;			// Name Count
		DWORD nOrdinals = nFuncSize - nNameSize;				// Ordinal Count
		DWORD dwAddFunc = pExportDir->AddressOfFunctions;		// RVA -> Func(EntryPoint)
		DWORD dwAddName = pExportDir->AddressOfNames;			// RVA -> Name
		DWORD dwAddOrdinals = pExportDir->AddressOfNameOrdinals;// RVA -> Ordinal
		
		
		DWORD dwEntryPoint;
		DWORD dwOrdinal;
		for(DWORD i = 0; i < nFuncSize; i++)
		{
			szFunName = NULL;
			dwEntryPoint = 0x00;
			dwOrdinal = 0x00;
			// EntryPoint
			DWORD  dwEntryPointRva = dwAddFunc + i * sizeof(DWORD);
			PIMAGE_EXPORT_BY_ENTRYPOINT exportByEntryPoint = (PIMAGE_EXPORT_BY_ENTRYPOINT)(szData + dwEntryPointRva);
			dwEntryPoint  = exportByEntryPoint->entryPointRVA;
			if(dwEntryPoint == 0x00)
			{
				continue;
			}
			// dwOrdinal
			dwOrdinal = i + dwbase;

			// Name/NameOrdinal
			for(DWORD j = 0; j < nNameSize; j++)
			{
				DWORD  dwOrdinalRva = dwAddOrdinals + j * sizeof(WORD);
				PIMAGE_EXPORT_BY_ORDINAL exportByOrdinal = (PIMAGE_EXPORT_BY_ORDINAL)(szData + dwOrdinalRva);
				WORD dwNameOrdinal = exportByOrdinal->ordinalRVA + (WORD)dwbase;
				if(dwOrdinal == dwNameOrdinal)
				{
					// Name
					DWORD  dwNameRva = dwAddName + j * sizeof(DWORD);
					PIMAGE_EXPORT_BY_NAME exportByName = (PIMAGE_EXPORT_BY_NAME)(szData + dwNameRva);
					szFunName = szData + exportByName->nameRVA;
				}
			}
			AddExportInfoItem(NULL, dwOrdinal, i, szFunName, dwEntryPoint, pParentTreeItem, m_ListGrid);	
		}
	}
}



// -----------------------------------------------------------//
// Function :   AddExportInfoItem
// Param    :   CHAR*			strName
//              DWORD			dwOridinal
//              DWORD			dwHint
//              CHAR*			FuncName
//              CTreeItem_*		parentItem
//              CMySuperGrid&	m_ListGrid
//              BOOL			bDLL /*= FALSE*/
// Return   :   CTreeItem_* 
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_*  AddExportInfoItem(CHAR*  strName, DWORD dwOridinal,  DWORD dwHint, CHAR* FuncName, DWORD dwEntryPoint, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid)
{
	if(parentItem == NULL)
	{
		return NULL;
	}

	
	CItemInfo* pFuncItem = new CItemInfo();
	pFuncItem->SetImage(0);
	CString strTemp;
	// Name
	if(strName == NULL)
	{
		pFuncItem->SetItemText("-");
	}
	else
	{
		pFuncItem->SetItemText(strName);
	}
	// Oridinal
	if(dwOridinal == N_A)
	{
		pFuncItem->AddSubItemText("N/A");
	}
	else
	{
		strTemp.Format("%d(0x%04x)", dwOridinal, dwOridinal);
		pFuncItem->AddSubItemText(strTemp);
	}

	// Fucntion 
	if(FuncName == NULL)
	{
		pFuncItem->AddSubItemText("N/A");
		pFuncItem->AddSubItemText("N/A");
	}
	else
	{
		strTemp.Format("%d(0x%04x)", dwHint, dwHint);
		pFuncItem->AddSubItemText(strTemp);
		pFuncItem->AddSubItemText(FuncName);
	}


	// Entry Point
	if(dwEntryPoint == N_A || dwEntryPoint == 0x00)
	{
		pFuncItem->AddSubItemText("N/A");
	}
	else
	{
		strTemp.Format("%d(0x%08x)", dwEntryPoint, dwEntryPoint);
		pFuncItem->AddSubItemText(strTemp);
	}
	
	return m_ListGrid.InsertItem(parentItem, pFuncItem);
	
}