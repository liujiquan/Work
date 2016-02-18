//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   addItemIMAGE_DOS_HEADER.cpp
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

//CTreeItem_*  AddItenm(CString strTitle, DWORD& dwAddress,  ITEMTYPE type, DWORD data, CString strDesc, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
CTreeItem_* CPEShowView::Add_IMAGE_DOS_HEADER(IMAGE_DOS_HEADER* pHeader, CMySuperGrid& m_ListGrid, CTreeItem_* parentItem)
{
	if(pHeader == NULL || parentItem == NULL)
	{
		return NULL;
	}

	CItemInfo* dosHeaderItem = new CItemInfo();
	dosHeaderItem->SetImage(0);
	dosHeaderItem->SetItemText("IMAGE_DOS_HEADER");
	dosHeaderItem->AddSubItemText("00000000");
	dosHeaderItem->AddSubItemText("-");
	dosHeaderItem->AddSubItemText("-");
	dosHeaderItem->AddSubItemText("-");
	dosHeaderItem->AddSubItemText("DOS .EXE header");
	
	CTreeItem_* pDosTreeItem =  m_ListGrid.InsertItem(parentItem, dosHeaderItem);
	if(pDosTreeItem == NULL)
	{
		return NULL;
	}

	DWORD dwAddress = 0x00000000;
	// e_magic
	AddItenm(_T("e_magic"), dwAddress, _WORD, pHeader->e_magic, _T("Magic number"), pDosTreeItem, m_ListGrid);
	// e_cblp
	AddItenm(_T("e_cblp"), dwAddress, _WORD, pHeader->e_cblp, _T("Bytes on last page of file"), pDosTreeItem, m_ListGrid);
	// e_crlc
	AddItenm(_T("e_cp"), dwAddress, _WORD, pHeader->e_cp, _T("Pages in file"), pDosTreeItem, m_ListGrid);
	// e_crlc
	AddItenm(_T("e_crlc"), dwAddress, _WORD, pHeader->e_crlc, _T("Relocations"), pDosTreeItem, m_ListGrid);
	// e_cparhdr
	AddItenm(_T("e_cparhdr"), dwAddress, _WORD, pHeader->e_cparhdr, _T("Size of header in paragraphs"), pDosTreeItem, m_ListGrid);
	// e_minalloc
	AddItenm(_T("e_minalloc"), dwAddress, _WORD, pHeader->e_minalloc, _T("Minimum extra paragraphs needed"), pDosTreeItem, m_ListGrid);
	// e_maxalloc
	AddItenm(_T("e_maxalloc"), dwAddress, _WORD, pHeader->e_maxalloc, _T("Maximum extra paragraphs needed"), pDosTreeItem, m_ListGrid);
	// e_ss
	AddItenm(_T("e_ss"), dwAddress, _WORD, pHeader->e_ss, _T("Initial (relative) SS value"), pDosTreeItem, m_ListGrid);
	// e_sp
	AddItenm(_T("e_sp"), dwAddress, _WORD, pHeader->e_sp, _T("Initial SP value"), pDosTreeItem, m_ListGrid);
	// e_csum
	AddItenm(_T("e_csum"), dwAddress, _WORD, pHeader->e_csum, _T("Checksum"), pDosTreeItem, m_ListGrid);
	// e_ip
	AddItenm(_T("e_ip"), dwAddress, _WORD, pHeader->e_ip, _T("Initial IP value"), pDosTreeItem, m_ListGrid);
	// e_cs
	AddItenm(_T("e_cs"), dwAddress, _WORD, pHeader->e_cs, _T("Initial (relative) CS value"), pDosTreeItem, m_ListGrid);
	// e_lfarlc
	AddItenm(_T("e_lfarlc"), dwAddress, _WORD, pHeader->e_lfarlc, _T("File address of relocation table"), pDosTreeItem, m_ListGrid);
	// e_ovno
	AddItenm(_T("e_ovno"), dwAddress, _WORD, pHeader->e_ovno, _T("Overlay number"), pDosTreeItem, m_ListGrid);
	// e_res
	CTreeItem_*  p = AddItenm(_T("e_res"), dwAddress, _NULL, 0, _T("Reserved words"), pDosTreeItem, m_ListGrid);
	for(int i = 0; i < 4; i++)
	{
		CString str;
		str.Format("%d", i);
		AddItenm(str, dwAddress, _WORD, pHeader->e_res[i], _T("-"), p, m_ListGrid);
	}
	// e_oemid
	AddItenm(_T("e_oemid"), dwAddress, _WORD, pHeader->e_oemid, _T("OEM identifier (for e_oeminfo)"), pDosTreeItem, m_ListGrid);
	// e_oeminfo
	AddItenm(_T("e_oeminfo"), dwAddress, _WORD, pHeader->e_oeminfo, _T("OEM information; e_oemid specific"), pDosTreeItem, m_ListGrid);
	// e_res2
	CTreeItem_*  p2 = AddItenm(_T("e_res2"), dwAddress, _NULL, 0, _T("Reserved words"), pDosTreeItem, m_ListGrid);
	for(i = 0; i < 10; i++)
	{
		CString str;
		str.Format("%d", i);
		AddItenm(str, dwAddress, _WORD, pHeader->e_res2[i], _T("-"), p2, m_ListGrid);
	}
	// e_lfanew
	AddItenm(_T("e_lfanew"), dwAddress, _LONG, pHeader->e_lfanew, _T("File address of new exe header"), pDosTreeItem, m_ListGrid);
	return pDosTreeItem;
}

CTreeItem_*  AddItenm(CString strTitle, DWORD& dwAddress,  ITEMTYPE type, DWORD data, CString strDesc, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, UINT nSize/*= 0*/, LPCTSTR pStringData /*= NULL*/) 
{
	// _STRING
	if(_STRING == type && (nSize == 0 || pStringData == NULL))
	{
		return NULL;
	}
	
	CString strTemp;
	CItemInfo* dosHeaderItem = new CItemInfo();
	dosHeaderItem->SetImage(0);
	// title
	dosHeaderItem->SetItemText(strTitle);
	// address
	strTemp.Format("%08X", dwAddress);
	dosHeaderItem->AddSubItemText(strTemp);
	// data(HEX)
	switch(type)
	{
	case _BYTE:
		dosHeaderItem->AddSubItemText("BYTE");
		strTemp.Format("%02X", data);dwAddress+= 1;	break;
	case _CHAR:
		dosHeaderItem->AddSubItemText("CHAR");
		strTemp.Format("%02X", data);dwAddress+= 1;	break;
	case _WORD:
		dosHeaderItem->AddSubItemText("WORD");
		strTemp.Format("%04X", data);dwAddress+= 2; break;
	case _DWORD:
		dosHeaderItem->AddSubItemText("DWORD");
		strTemp.Format("%08X", data);dwAddress+= 4;break;
	case _LONG:
		dosHeaderItem->AddSubItemText("LONG");
		strTemp.Format("%08X", data);dwAddress+= 4;break;
	case _DOUBLE:
		dosHeaderItem->AddSubItemText("DOUBLE");
		strTemp.Format("%016X", data);dwAddress+= 8;break;
	case _STRING:
		{
			dosHeaderItem->AddSubItemText(pStringData);
			CString strStringvalue = _T("");
			for(UINT i = 0; i < nSize; i++)
			{
			strTemp.Format("%02X", pStringData[i]);
			strStringvalue += strTemp;
			}
			strTemp = strStringvalue;
		}
		dwAddress+= nSize;break;
	default:
		dosHeaderItem->AddSubItemText("-");
		strTemp = _T("-");break;
	}
	dosHeaderItem->AddSubItemText(strTemp);
	// data(ASCII)
	DATA dataTemp;
	dataTemp.dwValue.dw0 = 0;
	dataTemp.dwValue.dw1 = data;

	switch(type)
	{
	case _BYTE:
	case _CHAR:
		strTemp.Format("%c", dataTemp.bValue.b4);	break;
	case _WORD:
		strTemp.Format("%c%c", dataTemp.bValue.b4, dataTemp.bValue.b5); break;
	case _DWORD:
	case _LONG:
		strTemp.Format("%c%c%c%c", dataTemp.bValue.b4, dataTemp.bValue.b5, dataTemp.bValue.b6, dataTemp.bValue.b7);break;
	case _DOUBLE:
		strTemp.Format("%c%c%c%c%c%c%c%c", dataTemp.bValue.b0, dataTemp.bValue.b1, dataTemp.bValue.b2, dataTemp.bValue.b3,
										dataTemp.bValue.b4, dataTemp.bValue.b5, dataTemp.bValue.b6, dataTemp.bValue.b7);break;
	case _STRING:
		{
			CString strStringvalue = _T("");
			for(UINT i = 0; i < nSize; i++)
			{
				strTemp.Format("%c", pStringData[i]);
				strStringvalue += strTemp;
			}
			strTemp = strStringvalue;
		}
		break;
	default:
		strTemp = _T("-");break;
	}
	dosHeaderItem->AddSubItemText(strTemp);
	// DESC
	dosHeaderItem->AddSubItemText(strDesc);
	
	return m_ListGrid.InsertItem(parentItem, dosHeaderItem);
}
