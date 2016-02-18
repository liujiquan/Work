//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   AddItemIMAGE_NT_HEADER.cpp
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
// Function :   Add_IMAGE_NT_HEADERS
// Param    :   IMAGE_NT_HEADERS*	pBuffer
//              CMySuperGrid&		m_ListGrid
//              CTreeItem_*			parentItem
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* CPEShowView::Add_IMAGE_NT_HEADERS(IMAGE_NT_HEADERS* pBuffer, DWORD dwAddressBase, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem)
{
	if(pBuffer == NULL || parentItem == NULL)
	{
		return NULL;
	}
	CMainFrame* pMainFram = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(!pMainFram)
	{
		return NULL;					
	}
	
	CItemInfo* ntHeaderItem = new CItemInfo();
	CString strTemp;
	DWORD dwBase = dwAddressBase;
	ntHeaderItem->SetImage(0);
	ntHeaderItem->SetItemText("IMAGE_NT_HEADERS");
	strTemp.Format("%08x", dwBase);
	ntHeaderItem->AddSubItemText(strTemp);
	ntHeaderItem->AddSubItemText("-");
	ntHeaderItem->AddSubItemText("-");
	ntHeaderItem->AddSubItemText("-");
	ntHeaderItem->AddSubItemText("IMAGE_NT_HEADERS");

	CTreeItem_* pDosTreeItem =  m_ListGrid.InsertItem(parentItem, ntHeaderItem);
	if(pDosTreeItem == NULL)
	{
		return NULL;
	}
	// Signature
	AddItenm(_T("Signature"), dwBase, _DWORD, pBuffer->Signature, _T("Signature"), pDosTreeItem, m_ListGrid);
	// IMAGE_FILE_HEADER
	IMAGE_FILE_HEADER FileHeader = pBuffer->FileHeader;
	CTreeItem_* pFileHeaderItem = AddItenm(_T("IMAGE_FILE_HEADER"), dwBase, _NULL, _NULL, _T("IMAGE_FILE_HEADER"), pDosTreeItem, m_ListGrid);
	if(pFileHeaderItem)
	{
		// Machine
		AddItenm(_T("Machine"), dwBase, _WORD, FileHeader.Machine, _T("The architecture type of the computer"), pFileHeaderItem, m_ListGrid);
		// NumberOfSections
		AddItenm(_T("NumberOfSections"), dwBase, _WORD, FileHeader.NumberOfSections, _T("The number of sections"), pFileHeaderItem, m_ListGrid);
		// TimeDateStamp
		AddItenm(_T("TimeDateStamp"), dwBase, _DWORD, FileHeader.TimeDateStamp, _T("TimeDate : 1970.1.1"), pFileHeaderItem, m_ListGrid);
		// PointerToSymbolTable
		AddItenm(_T("PointerToSymbolTable"), dwBase, _DWORD, FileHeader.PointerToSymbolTable, _T("The offset of the symbol table, in bytes, or zero if no COFF symbol table exists."), pFileHeaderItem, m_ListGrid);
		// NumberOfSymbols
		AddItenm(_T("NumberOfSymbols"), dwBase, _DWORD, FileHeader.NumberOfSymbols, _T("The number of symbols in the symbol table"), pFileHeaderItem, m_ListGrid);
		// PointerToSymbolTable
		AddItenm(_T("SizeOfOptionalHeader"), dwBase, _WORD, FileHeader.SizeOfOptionalHeader, _T("The size of the optional header, in bytes. This value should be 0 for object files"), pFileHeaderItem, m_ListGrid);
		// PointerToSymbolTable
		AddItenm(_T("Characteristics"), dwBase, _WORD, FileHeader.Characteristics, _T("The characteristics of the image"), pFileHeaderItem, m_ListGrid);
	}
	// IMAGE_OPTIONAL_HEADER
	IMAGE_OPTIONAL_HEADER OptionalHeader = pBuffer->OptionalHeader;
	CTreeItem_* pOptionalHeaderItem = AddItenm(_T("IMAGE_OPTIONAL_HEADER"), dwBase, _NULL, _NULL, _T("IMAGE_OPTIONAL_HEADER"), pDosTreeItem, m_ListGrid);
	if(pOptionalHeaderItem)
	{
		// Magic
		AddItenm(_T("Magic"), dwBase, _WORD, OptionalHeader.Magic, _T("The state of the image file"), pOptionalHeaderItem, m_ListGrid);
		// MajorLinkerVersion
		AddItenm(_T("MajorLinkerVersion"), dwBase, _BYTE, OptionalHeader.MajorLinkerVersion, _T("The major version number of the linker"), pOptionalHeaderItem, m_ListGrid);
		// MinorLinkerVersion
		AddItenm(_T("MinorLinkerVersion"), dwBase, _BYTE, OptionalHeader.MinorLinkerVersion, _T("The minor version number of the linker"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfCode
		AddItenm(_T("SizeOfCode"), dwBase, _DWORD, OptionalHeader.SizeOfCode, _T("The size of the code section"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfInitializedData
		AddItenm(_T("SizeOfInitializedData"), dwBase, _DWORD, OptionalHeader.SizeOfInitializedData, _T("The size of the initialized data section"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfUninitializedData
		AddItenm(_T("SizeOfUninitializedData"), dwBase, _DWORD, OptionalHeader.SizeOfUninitializedData, _T("The size of the uninitialized data section"), pOptionalHeaderItem, m_ListGrid);
		// AddressOfEntryPoint
		AddItenm(_T("AddressOfEntryPoint"), dwBase, _DWORD, OptionalHeader.AddressOfEntryPoint, _T("A pointer to the entry point function"), pOptionalHeaderItem, m_ListGrid);
		// BaseOfCode
		AddItenm(_T("BaseOfCode"), dwBase, _DWORD, OptionalHeader.BaseOfCode, _T("A pointer to the beginning of the code section"), pOptionalHeaderItem, m_ListGrid);
		// BaseOfData
		AddItenm(_T("BaseOfData"), dwBase, _DWORD, OptionalHeader.BaseOfData, _T("A pointer to the beginning of the data section"), pOptionalHeaderItem, m_ListGrid);
		// ImageBase
		AddItenm(_T("ImageBase"), dwBase, _DWORD, OptionalHeader.ImageBase, _T("The preferred address of the first byte of the image when it is loaded in memory"), pOptionalHeaderItem, m_ListGrid);
		// SectionAlignment
		AddItenm(_T("SectionAlignment"), dwBase, _DWORD, OptionalHeader.SectionAlignment, _T("The alignment of sections loaded in memory"), pOptionalHeaderItem, m_ListGrid);
		// FileAlignment
		AddItenm(_T("FileAlignment"), dwBase, _DWORD, OptionalHeader.FileAlignment, _T("The alignment of the raw data of sections in the image file"), pOptionalHeaderItem, m_ListGrid);
		// MajorOperatingSystemVersion
		AddItenm(_T("MajorOperatingSystemVersion"), dwBase, _WORD, OptionalHeader.MajorOperatingSystemVersion, _T("The major version number of the required operating system"), pOptionalHeaderItem, m_ListGrid);
		// MinorOperatingSystemVersion
		AddItenm(_T("MinorOperatingSystemVersion"), dwBase, _WORD, OptionalHeader.MinorOperatingSystemVersion, _T("The minor version number of the required operating system"), pOptionalHeaderItem, m_ListGrid);
		// MajorImageVersion
		AddItenm(_T("MajorImageVersion"), dwBase, _WORD, OptionalHeader.MajorImageVersion, _T("The major version number of the subsystem"), pOptionalHeaderItem, m_ListGrid);
		// MinorImageVersion
		AddItenm(_T("MinorImageVersion"), dwBase, _WORD, OptionalHeader.MinorImageVersion, _T("The minor version number of the image"), pOptionalHeaderItem, m_ListGrid);
		// MajorSubsystemVersionBaseOfData
		AddItenm(_T("MajorSubsystemVersion"), dwBase, _WORD, OptionalHeader.MajorSubsystemVersion, _T("The major version number of the subsystem"), pOptionalHeaderItem, m_ListGrid);
		// MinorSubsystemVersion
		AddItenm(_T("MinorSubsystemVersion"), dwBase, _WORD, OptionalHeader.MinorSubsystemVersion, _T("The minor version number of the subsystem"), pOptionalHeaderItem, m_ListGrid);
		// Win32VersionValue
		AddItenm(_T("Win32VersionValue"), dwBase, _DWORD, OptionalHeader.Win32VersionValue, _T("This member is reserved and must be 0"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfImage
		AddItenm(_T("SizeOfImage"), dwBase, _DWORD, OptionalHeader.SizeOfImage, _T("The size of the image, in bytes, including all headers"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfHeaders
		AddItenm(_T("SizeOfHeaders"), dwBase, _DWORD, OptionalHeader.SizeOfHeaders, _T("The combined size of the following items:IMAGE_DOS_HEADER:e_lfanew+•4 byte signature+sizeof(IMAGE_FILE_HEADER)+•size of optional header+•size of all section headers"), pOptionalHeaderItem, m_ListGrid);
		// CheckSum
		AddItenm(_T("CheckSum"), dwBase, _DWORD, OptionalHeader.CheckSum, _T("The image file checksum"), pOptionalHeaderItem, m_ListGrid);
		// Subsystem
		AddItenm(_T("Subsystem"), dwBase, _WORD, OptionalHeader.Subsystem, _T("The subsystem required to run this image"), pOptionalHeaderItem, m_ListGrid);
		// DllCharacteristics
		AddItenm(_T("DllCharacteristics"), dwBase, _WORD, OptionalHeader.DllCharacteristics, _T("The DLL characteristics of the image"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfStackReserve
		AddItenm(_T("SizeOfStackReserve"), dwBase, _DWORD, OptionalHeader.SizeOfStackReserve, _T("The number of bytes to reserve for the stack"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfStackCommit
		AddItenm(_T("SizeOfStackCommit"), dwBase, _DWORD, OptionalHeader.SizeOfStackCommit, _T("The number of bytes to commit for the stack"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfHeapReserve
		AddItenm(_T("SizeOfHeapReserve"), dwBase, _DWORD, OptionalHeader.SizeOfHeapReserve, _T("The number of bytes to reserve for the local heap"), pOptionalHeaderItem, m_ListGrid);
		// SizeOfHeapCommit
		AddItenm(_T("SizeOfHeapCommit"), dwBase, _DWORD, OptionalHeader.SizeOfHeapCommit, _T("The number of bytes to commit for the local heap"), pOptionalHeaderItem, m_ListGrid);
		// LoaderFlags
		AddItenm(_T("LoaderFlags"), dwBase, _DWORD, OptionalHeader.LoaderFlags, _T("This member is obsolete"), pOptionalHeaderItem, m_ListGrid);
		// NumberOfRvaAndSizes
		AddItenm(_T("NumberOfRvaAndSizes"), dwBase, _DWORD, OptionalHeader.NumberOfRvaAndSizes, _T("The number of directory entries in the remainder of the optional header"), pOptionalHeaderItem, m_ListGrid);
		// IMAGE_DATA_DIRECTORY 
		CTreeItem_* pMainDataDirItem = AddItenm(_T("IMAGE_DATA_DIRECTORY "), dwBase, _NULL, _NULL, _T("A pointer to the first IMAGE_DATA_DIRECTORY structure in the data directory"), pOptionalHeaderItem, m_ListGrid);
		if(pMainDataDirItem)
		{
			for(int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
			{
				CString strID, strInfo;

				strID.Format("%02d", i);
				switch(i)
				{
				case 0:		strInfo = _T("Export Table");			break;
				case 1:		strInfo = _T("Import Table");			break;
				case 2:		strInfo = _T("Resource Table");			break;
				case 3:		strInfo = _T("Exception Table");		break;
				case 4:		strInfo = _T("Certificate Table");		break;
				case 5:		strInfo = _T("Relocation  Table");		break;
				case 6:		strInfo = _T("Debug  Table");			break;
				case 7:		strInfo = _T("Architecture Table");		break;
				case 8:		strInfo = _T("Global Table");			break;
				case 9:		strInfo = _T("TLS  Table");				break;
				case 10:	strInfo = _T("Load Config Table");		break;
				case 11:	strInfo = _T("Bound Import Table");		break;
				case 12:	strInfo = _T("Import Address Table");	break;
				case 13:	strInfo = _T("Delay Import Descriptor");break;
				case 14:	strInfo = _T("COM+ Runtime Header");	break;
				case 15:	strInfo = _T("Reserved");				break;
				}
				CTreeItem_* pSubDataDirItem = AddItenm(strID, dwBase, _NULL, _NULL, strInfo, pMainDataDirItem, m_ListGrid);
				if(pSubDataDirItem)
				{
					IMAGE_DATA_DIRECTORY dataDir = OptionalHeader.DataDirectory[i];
					
					// VirtualAddress
					AddItenm(_T("VirtualAddress"), dwBase, _DWORD, dataDir.VirtualAddress, _T("The relative virtual address of the table"), pSubDataDirItem, m_ListGrid);
					// Size
					AddItenm(_T("Size"), dwBase, _DWORD, dataDir.Size, _T("The size of the table"), pSubDataDirItem, m_ListGrid);	
					
					// 

					if(i == IMAGE_DIRECTORY_ENTRY_IMPORT)
					{	
						if(dataDir.VirtualAddress + dataDir.Size <= GetMaxSize())
						{
							Add_Directory_ImportSymbols(dataDir.VirtualAddress, dataDir.Size, pMainFram->m_wndDirInfo.m_Page0.m_List);
						}
					}
					else if(i== IMAGE_DIRECTORY_ENTRY_EXPORT)
					{
						if(dataDir.VirtualAddress + dataDir.Size <= GetMaxSize())
						{
							Add_Directory_ExportSymbols(dataDir.VirtualAddress, dataDir.Size, pMainFram->m_wndDirInfo.m_Page1.m_List);
						}
					}
					else if(i== IMAGE_DIRECTORY_ENTRY_RESOURCE)
					{
						if(dataDir.VirtualAddress + dataDir.Size <= GetMaxSize())
						{
							Add_Directory_ResourceTable(dataDir.VirtualAddress, dataDir.Size, pMainFram->m_wndDirInfo.m_Page2.m_List);
						}
					}
					else if(i == IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT)
					{
						if(dataDir.VirtualAddress + dataDir.Size <= GetMaxSize())
						{
							Add_Directory_BoundImportSymbols(dataDir.VirtualAddress, dataDir.Size, pMainFram->m_wndDirInfo.m_Page3.m_List);
						}
					}
				}
				
			}
		}
	}

	return pDosTreeItem;
}
