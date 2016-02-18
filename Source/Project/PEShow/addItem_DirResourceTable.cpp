//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItem_DirResourceTable.cpp
//* Author   :   liujiquan
//* DateTime :   9/16/2014
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

//////////////////////////////////////////////////////////////////////////
typedef struct tag_IMAGE_RESOURCE_DIRECTORY_ENTRY {
    union {
        struct {
            DWORD NameOffset:31;
            DWORD NameIsString:1;
        }u1;
        DWORD   Name;
        WORD    Id;
    };
    union {
        DWORD   OffsetToData;
        struct {
            DWORD   OffsetToDirectory:31;
            DWORD   DataIsDirectory:1;
        }u2;
    };
} IMAGE_RESOURCE_DIRECTORY_ENTRY_, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_;

void _W2T(WCHAR* wszData, char *destValue, WORD len);
void  AddResourceTableItem(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem);
void AddChildItem(char* szData, DWORD dwTableOffset, PIMAGE_RESOURCE_DIRECTORY_ENTRY_ pMainDirEntry, int nDep, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem);
// -----------------------------------------------------------//
// Function :   CPEShowView::Add_Directory_ResourceTable
// Param    :   DWORD dwVirtualAddress
//              DWORD dwSize
//              CMySuperGrid& m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_Directory_ResourceTable(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid)
{
	if(dwVirtualAddress == 0 || dwSize == 0)
	{
		return NULL;
	}

	CItemInfo* pResMainItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwVirtualAddress;
	pResMainItem->SetImage(0);
	pResMainItem->SetItemText("Resource Symbols");
	strTemp.Format("%08x", dwBase);
	pResMainItem->AddSubItemText(strTemp);
	pResMainItem->AddSubItemText("-");
	pResMainItem->AddSubItemText("-");
	pResMainItem->AddSubItemText("-");
	
	CTreeItem_* pResMainTreeItem =  m_ListGrid.InsertRootItem(pResMainItem);
	if(pResMainTreeItem == NULL)
	{
		return NULL;
	}

	// Insert Item
	AddResourceTableItem(dwVirtualAddress, dwSize, m_ListGrid, pResMainTreeItem);

	return pResMainTreeItem;
}

// -----------------------------------------------------------//
// Function :   AddResourceTableItem
// Param    :   DWORD dwVirtualAddress
//              DWORD dwSize
//              CMySuperGrid& m_ListGrid
//              CTreeItem_* pParentTreeItem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void AddResourceTableItem(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem)
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
	PIMAGE_RESOURCE_DIRECTORY	 pResourceDir;			// main resource
	PIMAGE_RESOURCE_DIRECTORY_ENTRY_ pMainDirEntry;		// main entry
	// 1)IMAGE_RESOURCE_DIRECTORY
	pResourceDir = (PIMAGE_RESOURCE_DIRECTORY)(szData + dwVirtualAddress);
	if(pResourceDir == NULL)
	{
		return;
	}

	WORD wIDEntrySize = pResourceDir->NumberOfIdEntries;			// ID size
	WORD wNameEntrySize = pResourceDir->NumberOfNamedEntries;		// Name size
	DWORD dwTableOffset = dwVirtualAddress;
	
	// 2) Main Resource
	pMainDirEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY_)(szData + dwTableOffset + sizeof(IMAGE_RESOURCE_DIRECTORY));
	for(WORD i = 0; i < wIDEntrySize + wNameEntrySize; i++)
	{
		AddChildItem(szData, dwTableOffset, pMainDirEntry + i, 0, m_ListGrid, pParentTreeItem);
	}
}


// -----------------------------------------------------------//
// Function :   AddChildItem
// Param    :   char* szData
//              DWORD dwTableOffset
//              PIMAGE_RESOURCE_DIRECTORY_ENTRY_ pMainDirEntry
//              int nDep
//              CMySuperGrid& m_ListGrid
//              CTreeItem_* pParentTreeItem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void AddChildItem(char* szData, DWORD dwTableOffset, PIMAGE_RESOURCE_DIRECTORY_ENTRY_ pMainDirEntry, int nDep, CMySuperGrid& m_ListGrid, CTreeItem_* pParentTreeItem)
{

	if(szData == NULL)			return;
	char* szTableData = szData + dwTableOffset;
	if(szTableData == NULL)		return;
	// Question 1
	if(pMainDirEntry->OffsetToData > GetMaxSize())	return;

	// 1)
	TCHAR szMainName[MAX_PATH] = {0};
	if(pMainDirEntry->u1.NameIsString)		// Self Define Name
	{	
		if(pMainDirEntry->u1.NameOffset > GetMaxSize())
		{
			return;
		}
		PIMAGE_RESOURCE_DIR_STRING_U pNameStr = (PIMAGE_RESOURCE_DIR_STRING_U)(szTableData + pMainDirEntry->u1.NameOffset);
		_W2T(pNameStr->NameString, szMainName, pNameStr->Length);
	}
	else									// ID
	{
		if(nDep == 0)
		{
			switch(pMainDirEntry->Id)
			{
				case 1:		sprintf(szMainName, _T("Cursor"));			break;
				case 2:		sprintf(szMainName, _T("Bitmap"));			break;
				case 3:		sprintf(szMainName, _T("Icon"));			break;
				case 4:		sprintf(szMainName, _T("Menu"));			break;
				case 5:		sprintf(szMainName, _T("Dialog"));			break;
				case 6:		sprintf(szMainName, _T("String"));			break;
				case 7:		sprintf(szMainName, _T("FontDir"));			break;
				case 8:		sprintf(szMainName, _T("Font"));			break;
				case 9:		sprintf(szMainName, _T("Accelerator"));		break;
				case 10:	sprintf(szMainName, _T("RCDATA"));			break;
				case 11:	sprintf(szMainName, _T("MessageTable"));	break;
				case 12:	sprintf(szMainName, _T("GroupCursor"));		break;
				case 14:	sprintf(szMainName, _T("GroupIcon"));		break;
				case 16:	sprintf(szMainName, _T("Version"));			break;
				case 17:	sprintf(szMainName, _T("DlgInclude"));		break;
				case 19:	sprintf(szMainName, _T("PlugPlay"));		break;
				case 20:	sprintf(szMainName, _T("VXD"));				break;
				case 21:	sprintf(szMainName, _T("ANICursor"));		break;
				case 22:	sprintf(szMainName, _T("ANIIcon"));			break;
				case 23:	sprintf(szMainName, _T("HTML"));			break;
				case 241:	sprintf(szMainName, _T("Toolbar"));			break;
				default:	sprintf(szMainName, _T("ID: %ld"), pMainDirEntry->Id); break;
			}
				
		}
		else
		{
			sprintf(szMainName, _T("[%d]ID: %ld"), nDep, pMainDirEntry->Id); 
		}
	}

	CItemInfo* pResSubItem = new CItemInfo();
	pResSubItem->SetImage(0);
	pResSubItem->SetItemText(szMainName);
	CTreeItem_* pResSubTreeItem =  m_ListGrid.InsertItem(pParentTreeItem, pResSubItem);
	
	// 2)
	if(pMainDirEntry->u2.DataIsDirectory)
	{
		DWORD dwSubOffset = pMainDirEntry->u2.OffsetToDirectory;		// RVA-Resource Table
		PIMAGE_RESOURCE_DIRECTORY pSubResorceDir = (PIMAGE_RESOURCE_DIRECTORY)(szTableData + dwSubOffset);
		PIMAGE_RESOURCE_DIRECTORY_ENTRY_ pSubEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY_)(szTableData + dwSubOffset + sizeof(IMAGE_RESOURCE_DIRECTORY));
		DWORD dwSize = pSubResorceDir->NumberOfNamedEntries + pSubResorceDir->NumberOfIdEntries;
		for(DWORD j = 0; j < dwSize; j++)
		{
			AddChildItem(szData, dwTableOffset, pSubEntry + j, nDep + 1, m_ListGrid, pResSubTreeItem);
		}
	}
	else
	{
		TCHAR szFileInfo[MAX_PATH] = {0};
		PIMAGE_RESOURCE_DATA_ENTRY pDataEntry = (PIMAGE_RESOURCE_DATA_ENTRY)(szTableData + pMainDirEntry->OffsetToData);
		char* szResData = szData+pDataEntry->OffsetToData;
		
		CItemInfo* pResSubItem2 = new CItemInfo();
		pResSubItem2->SetImage(0);
		pResSubItem2->SetItemText("");
		sprintf(szFileInfo, _T("0x%08X"), szResData);
		pResSubItem2->AddSubItemText(szFileInfo);
		sprintf(szFileInfo, _T("0x%08X"),pDataEntry->OffsetToData);
		pResSubItem2->AddSubItemText(szFileInfo);
		sprintf(szFileInfo, _T("%ld Bytes"),  pDataEntry->Size);
		pResSubItem2->AddSubItemText(szFileInfo);

		m_ListGrid.InsertItem(pResSubTreeItem, pResSubItem2);
	}
}

typedef struct tag_CHAR2
{
	union
	{
		struct{
			char c0;
			char c1;
		}charValue;
		WCHAR wcharValue;
	};	
}CHAR2;
// -----------------------------------------------------------//
// Function :   W2T
// Param    :   WCHAR* wszData
//              char *destValue
// Return   :   void
// Comment  :   WCHAR -> CHAR
// -----------------------------------------------------------//
void _W2T(WCHAR* wszData, char *destValue, WORD len)
{
	if(wszData == NULL)
	{
		return;
	}

	int nCount = 0;
	CHAR2 data;
	while(len--)
	{
		data.wcharValue = *(wszData+nCount);
		if(data.charValue.c0 == '\0' && data.charValue.c1 == '\0')
		{
			break;
		}
		destValue[nCount] = data.charValue.c0;
		nCount++;	
	}
}

