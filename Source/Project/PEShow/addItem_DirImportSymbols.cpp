//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItem_DirImportSymbols.cpp
//* Author   :   liujiquan
//* DateTime :   9/9/2014
//* Version  :   1.0
//* Comment  :   Import
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

extern DWORD	g_dwFileSize ;

#ifndef N_A
#define N_A  -1
#endif 

void InsertImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem);
BOOL IsImportSymbolaEnd(IMAGE_IMPORT_DESCRIPTOR * pImportDesc);
CTreeItem_*  AddImportInfoItem(CHAR*  strName, DWORD dwOridinal,  DWORD dwHint, CHAR*  FuncName, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, BOOL bDLL = FALSE);
// -----------------------------------------------------------//
// Function :   Add_Directory_ImportSymbols
// Param    :   DWORD			dwVirtualAddress
//              DWORD			dwSize
//              CMySuperGrid&	m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_Directory_ImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid)
{
	if(dwVirtualAddress == 0 || dwSize == 0 || dwVirtualAddress > g_dwFileSize)
	{
		return NULL;
	}

	CItemInfo* pImportMainItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwVirtualAddress;
	pImportMainItem->SetImage(0);
	pImportMainItem->SetItemText("Import Symbols");
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
	InsertImportSymbols(dwVirtualAddress, dwSize, m_ListGrid, pImportMainTreeItem);

	return pImportMainTreeItem;
}

// -----------------------------------------------------------//
// Function :   InsertImportSymbols
// Param    :   DWORD				dwVirtualAddress
//              DWORD				dwSize
//              CMySuperGrid&		m_ListGrid
//              CTreeItem_*			pParentTreeItem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void InsertImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem)
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
	IMAGE_IMPORT_DESCRIPTOR* pImportDesc = NULL;
	PIMAGE_IMPORT_BY_NAME pImportByName = NULL;
	PIMAGE_THUNK_DATA pThunkData = NULL;
	UINT nDllSize = 0;						// Sizeof Dll
	UINT nFunSize = 0;						// sizeof Dll Function
	CHAR* szDllName = NULL;					// dllName
	CHAR* szFunName = NULL;


	pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(szData + dwVirtualAddress);
	//////////////////////////////////////////////////////////////////////////
	while(pImportDesc->FirstThunk)  
	{  
		char *pszDllName = (char *)((BYTE *)szData + pImportDesc->Name);  
		TRACE1("\nModule Name:%s\n", pszDllName);  
		IMAGE_THUNK_DATA *pThunk = (IMAGE_THUNK_DATA *)((BYTE *)szData + pImportDesc->OriginalFirstThunk);  
		int n = 0;  
		//MessageBox(NULL, "Test", "MESS", MB_OK);  
		char *pszFunName = NULL;  
		while(pThunk->u1.Function)  
		{  
			pszFunName = (char *)((BYTE *)szData + (DWORD)pThunk->u1.AddressOfData + 2);  
			PDWORD lpAddr = (DWORD *)((BYTE *)szData + pImportDesc->FirstThunk) +  n;  
			DWORD dwRVA = (DWORD)lpAddr - (DWORD)(szData);
			try  
			{  
				TRACE1("function name : %-25s	", (char *)pszFunName);  
			}  
			catch(...)  
			{  
				TRACE0("function name :unknown!	");  
			}  
			TRACE1("addr :%0X\n", lpAddr);  
			n++;  
			pThunk++;  
		}  
		pImportDesc++;  
	}  
	//////////////////////////////////////////////////////////////////////////
	pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(szData + dwVirtualAddress);
	while(!IsImportSymbolaEnd(pImportDesc))
	{
		nFunSize = 0;
		
		// dll name
		DWORD dwDllNameAdd = pImportDesc->Name;					
		szDllName = szData + dwDllNameAdd;				// dllName
		szFunName = NULL;
		// InsertItem(DLL)
		CTreeItem_* pDllItem = AddImportInfoItem(szDllName, 0, 0, "", pParentTreeItem, m_ListGrid, TRUE);

		// dll function base Address
		DWORD dwFunBaseAdd = pImportDesc->OriginalFirstThunk;	// RVA INT
		if(dwFunBaseAdd == 0x00 || dwFunBaseAdd && 0x8000000)
		{	
			dwFunBaseAdd = pImportDesc->FirstThunk;				// RVA IAT
			if(dwFunBaseAdd == 0x00 || dwFunBaseAdd > GetMaxSize())
			{
				goto _END;
			}
		}
		// dll ThunkData
		pThunkData = (PIMAGE_THUNK_DATA)(szData + dwFunBaseAdd);
		// Show All Function Name
		while(pThunkData && pThunkData->u1.Function != 0x00 && pThunkData->u1.Ordinal < GetMaxSize())
		{
			DWORD dwOrdinal = -1;								// Ordinal
			if(IMAGE_SNAP_BY_ORDINAL(pThunkData->u1.Ordinal))
			{
				dwOrdinal = IMAGE_ORDINAL(pThunkData->u1.Ordinal);
			}
			if(dwOrdinal != -1)
			{
				// InsertItem(DLL Func)	
				AddImportInfoItem(NULL, dwOrdinal, N_A, NULL, pDllItem, m_ListGrid, FALSE);
			}
			else
			{
				// InsertItem(DLL Func)
				DWORD dwFunAddr = pThunkData->u1.Ordinal;
		
				pImportByName = (PIMAGE_IMPORT_BY_NAME)(szData + dwFunAddr);
				if(pImportByName)
				{
					szFunName = (CHAR*)pImportByName->Name;
					AddImportInfoItem(NULL, N_A, pImportByName->Hint, szFunName, pDllItem, m_ListGrid, FALSE);
				}	
			}
			
			nFunSize++;
			pThunkData = (PIMAGE_THUNK_DATA)(szData + dwFunBaseAdd + sizeof(IMAGE_THUNK_DATA) * nFunSize);
		}
_END:
		nDllSize++;
		pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(szData + dwVirtualAddress + sizeof(IMAGE_IMPORT_DESCRIPTOR)*nDllSize);
	}
}

// -----------------------------------------------------------//
// Function :   IsImportSymbolaEnd
// Param    :   IMAGE_IMPORT_DESCRIPTOR * pImportDesc
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL IsImportSymbolaEnd(IMAGE_IMPORT_DESCRIPTOR * pImportDesc)
{
	if(pImportDesc)
	{
		if(pImportDesc->Characteristics == 0x00 &&
			pImportDesc->FirstThunk == 0x00 &&
			pImportDesc->ForwarderChain == 0x00 &&
			pImportDesc->Name == 0x00 &&
			pImportDesc->OriginalFirstThunk == 0x00 &&
			pImportDesc->TimeDateStamp == 0x00 ||
			pImportDesc->FirstThunk > GetMaxSize() ||
			pImportDesc->OriginalFirstThunk > GetMaxSize()
			)
		{
			return TRUE;
		}
		if(pImportDesc->Name == 0x00)
		{
			return TRUE;
		}
				
		return FALSE;
	}
	
	return TRUE;
}


// -----------------------------------------------------------//
// Function :   AddImportInfoItem
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
CTreeItem_*  AddImportInfoItem(CHAR*  strName, DWORD dwOridinal,  DWORD dwHint, CHAR* FuncName, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, BOOL bDLL /*= FALSE*/)
{
	if(parentItem == NULL)
	{
		return NULL;
	}

	if(bDLL)
	{
		CItemInfo* pDllItem = new CItemInfo();
		pDllItem->SetImage(0);
		if(strName == NULL)
		{
			pDllItem->SetItemText("-");
		}
		else
		{
			pDllItem->SetItemText(strName);
		}
		pDllItem->AddSubItemText("-");
		pDllItem->AddSubItemText("-");
		pDllItem->AddSubItemText("-");
		pDllItem->AddSubItemText("-");
		pDllItem->AddSubItemText("-");

		return m_ListGrid.InsertItem(parentItem, pDllItem);
	}
	else
	{	
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
		// dwHint
		if(dwHint == N_A)
		{
			pFuncItem->AddSubItemText("N/A");
		}
		else
		{
			strTemp.Format("%d(0x%04x)", dwHint, dwHint);
			pFuncItem->AddSubItemText(strTemp);
		}

		// Fucntion 
		if(FuncName == NULL)
		{
			pFuncItem->AddSubItemText("N/A");
		}
		else
		{
			pFuncItem->AddSubItemText(FuncName);
		}

		// Entry Point
		pFuncItem->AddSubItemText("Not Found");
		
		
		return m_ListGrid.InsertItem(parentItem, pFuncItem);
	}
		
	return NULL;
}