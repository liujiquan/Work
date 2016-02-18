//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItemIMAGE_SECTION_HEADER.cpp
//* Author   :   liujiquan
//* DateTime :   9/9/2014
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

// -----------------------------------------------------------//
// Function :   CPEShowView::Add_IMAGE_SECTION_HEADER
// Param    :   CHAR* pBuffer
//              DWORD dwAddressBase
//              UINT nSectionNum
//              CMySuperGrid& m_ListGrid
//              CTreeItem_* parentItem
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_IMAGE_SECTION_HEADER(CHAR* pBuffer, DWORD dwAddressBase, UINT nSectionNum, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem)
{
	if(pBuffer == NULL || parentItem == NULL || nSectionNum == 0)
	{
		return NULL;
	}

	// SECTION_INFO
	CItemInfo* sectionInfoItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwAddressBase;
	sectionInfoItem->SetImage(0);
	sectionInfoItem->SetItemText("SECTION_INFO");
	strTemp.Format("%08x", dwBase);
	sectionInfoItem->AddSubItemText(strTemp);
	sectionInfoItem->AddSubItemText("-");
	sectionInfoItem->AddSubItemText("-");
	sectionInfoItem->AddSubItemText("-");
	sectionInfoItem->AddSubItemText("SECTION_INFO");
	
	CTreeItem_* pSectionInfoTreeItem =  m_ListGrid.InsertItem(parentItem, sectionInfoItem);
	if(pSectionInfoTreeItem == NULL)
	{
		return NULL;
	}
	
	// 1)IMAGE_SECTION_HEADER
	CItemInfo* sectionHeaderItem = new CItemInfo();
	sectionHeaderItem->SetImage(0);
	sectionHeaderItem->SetItemText("IMAGE_SECTION_HEADER");
	strTemp.Format("%08x", dwBase);
	sectionHeaderItem->AddSubItemText(strTemp);
	sectionHeaderItem->AddSubItemText("-");
	sectionHeaderItem->AddSubItemText("-");
	sectionHeaderItem->AddSubItemText("-");
	sectionHeaderItem->AddSubItemText("IMAGE_SECTION_HEADER");
	
	CTreeItem_* pSectionHeaderTreeItem =  m_ListGrid.InsertItem(pSectionInfoTreeItem, sectionHeaderItem);
	if(pSectionHeaderTreeItem == NULL)
	{
		return NULL;
	}

	// IMAGE_SECTION_HEADER 
	for(UINT i = 0; i < nSectionNum; i++)
	{
		IMAGE_SECTION_HEADER* pSectionHeader = (IMAGE_SECTION_HEADER*)(pBuffer + sizeof(IMAGE_SECTION_HEADER)*i);
		if(pSectionHeader)
		{
			CString strID;
			strID.Format("%02d", i);

			CTreeItem_* pSubSectionHeader = AddItenm(strID, dwBase, _NULL, _NULL, _T("-"), pSectionHeaderTreeItem, m_ListGrid);
			if(pSubSectionHeader)
			{	
				// Name
				AddItenm(_T("Name"), dwBase, _STRING, _NULL, _T("section name."), pSubSectionHeader, m_ListGrid, IMAGE_SIZEOF_SHORT_NAME, (LPCTSTR)pSectionHeader->Name);
				// Misc{PhysicalAddress/VirtualSize}
				AddItenm(_T("Misc"), dwBase, _DWORD, pSectionHeader->Misc.PhysicalAddress, _T("The file address/The total size of the section when loaded into memory"), pSubSectionHeader, m_ListGrid);	
				// VirtualAddress
				AddItenm(_T("VirtualAddress"), dwBase, _DWORD, pSectionHeader->VirtualAddress, _T("The address of the first byte of the section when loaded into memory"), pSubSectionHeader, m_ListGrid);	
				// SizeOfRawData
				AddItenm(_T("SizeOfRawData"), dwBase, _DWORD, pSectionHeader->SizeOfRawData, _T("The size of the initialized data on disk, in bytes"), pSubSectionHeader, m_ListGrid);	
				// PointerToRawData
				AddItenm(_T("PointerToRawData"), dwBase, _DWORD, pSectionHeader->PointerToRawData, _T("A file pointer to the first page within the COFF file"), pSubSectionHeader, m_ListGrid);	
				// PointerToRelocations
				AddItenm(_T("PointerToRelocations"), dwBase, _DWORD, pSectionHeader->PointerToRelocations, _T("A file pointer to the beginning of the relocation entries for the section"), pSubSectionHeader, m_ListGrid);	
				// PointerToLinenumbers
				AddItenm(_T("PointerToLinenumbers"), dwBase, _DWORD, pSectionHeader->PointerToLinenumbers, _T("A file pointer to the beginning of the line-number entries for the section"), pSubSectionHeader, m_ListGrid);	
				// NumberOfRelocations
				AddItenm(_T("NumberOfRelocations"), dwBase, _WORD, pSectionHeader->NumberOfRelocations, _T("The number of relocation entries for the section"), pSubSectionHeader, m_ListGrid);	
				// NumberOfLinenumbers
				AddItenm(_T("NumberOfLinenumbers"), dwBase, _WORD, pSectionHeader->NumberOfLinenumbers, _T("The number of line-number entries for the section"), pSubSectionHeader, m_ListGrid);	
				// Characteristics
				AddItenm(_T("Characteristics"), dwBase, _DWORD, pSectionHeader->Characteristics, _T("The characteristics of the image"), pSubSectionHeader, m_ListGrid);	
			}
		}
	}
	
	// 2)SECTION
	CItemInfo* sectionItem = new CItemInfo();
	sectionItem->SetImage(0);
	sectionItem->SetItemText("SECTION");
	strTemp.Format("%08x", dwBase);
	sectionItem->AddSubItemText(strTemp);
	sectionItem->AddSubItemText("-");
	sectionItem->AddSubItemText("-");
	sectionItem->AddSubItemText("-");
	sectionItem->AddSubItemText("SECTION");
	
	CTreeItem_* pSectionTreeItem =  m_ListGrid.InsertItem(pSectionInfoTreeItem, sectionItem);
	if(pSectionTreeItem == NULL)
	{
		return NULL;
	}
	
	// IMAGE_SECTION_HEADER 
	for(i = 0; i < nSectionNum; i++)
	{
/*		IMAGE_SECTION_HEADER* pSectionHeader = (IMAGE_SECTION_HEADER*)(pBuffer + sizeof(IMAGE_SECTION_HEADER)*i);
		if(pSectionHeader)
		{
			CString strID;
			strID.Format("%02d", i);
			
			CTreeItem_* pSubSectionHeader = AddItenm(strID, dwBase, _NULL, _NULL, _T("-"), pSectionHeaderTreeItem, m_ListGrid);
			if(pSubSectionHeader)
			{	
				// Name
				AddItenm(_T("Name"), dwBase, _STRING, _NULL, _T("section name."), pSubSectionHeader, m_ListGrid, IMAGE_SIZEOF_SHORT_NAME, (LPCTSTR)pSectionHeader->Name);
				// Misc{PhysicalAddress/VirtualSize}
				AddItenm(_T("Misc"), dwBase, _DWORD, pSectionHeader->Misc.PhysicalAddress, _T("The file address/The total size of the section when loaded into memory"), pSubSectionHeader, m_ListGrid);	
				// VirtualAddress
				AddItenm(_T("VirtualAddress"), dwBase, _DWORD, pSectionHeader->VirtualAddress, _T("The address of the first byte of the section when loaded into memory"), pSubSectionHeader, m_ListGrid);	
				// SizeOfRawData
				AddItenm(_T("SizeOfRawData"), dwBase, _DWORD, pSectionHeader->SizeOfRawData, _T("The size of the initialized data on disk, in bytes"), pSubSectionHeader, m_ListGrid);	
				// PointerToRawData
				AddItenm(_T("PointerToRawData"), dwBase, _DWORD, pSectionHeader->PointerToRawData, _T("A file pointer to the first page within the COFF file"), pSubSectionHeader, m_ListGrid);	
				// PointerToRelocations
				AddItenm(_T("PointerToRelocations"), dwBase, _DWORD, pSectionHeader->PointerToRelocations, _T("A file pointer to the beginning of the relocation entries for the section"), pSubSectionHeader, m_ListGrid);	
				// PointerToLinenumbers
				AddItenm(_T("PointerToLinenumbers"), dwBase, _DWORD, pSectionHeader->PointerToLinenumbers, _T("A file pointer to the beginning of the line-number entries for the section"), pSubSectionHeader, m_ListGrid);	
				// NumberOfRelocations
				AddItenm(_T("NumberOfRelocations"), dwBase, _WORD, pSectionHeader->NumberOfRelocations, _T("The number of relocation entries for the section"), pSubSectionHeader, m_ListGrid);	
				// NumberOfLinenumbers
				AddItenm(_T("NumberOfLinenumbers"), dwBase, _WORD, pSectionHeader->NumberOfLinenumbers, _T("The number of line-number entries for the section"), pSubSectionHeader, m_ListGrid);	
				// Characteristics
				AddItenm(_T("Characteristics"), dwBase, _DWORD, pSectionHeader->Characteristics, _T("The characteristics of the image"), pSubSectionHeader, m_ListGrid);	
			}
		}
	*/
	}
	
	return pSectionInfoTreeItem;
}
