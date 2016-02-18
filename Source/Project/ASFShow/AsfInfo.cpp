//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   AsfInfo.cpp
//* Author   :   liujiquan
//* DateTime :   11/6/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "AsfInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -----------------------------------------------------------//
// Function :   DWTOSTR
// Param    :   DWORD dwValue
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString DWTOSTR(DWORD dwValue)
{
	CString str;
	str.Format("%08X", dwValue);

	return str;
}

// -----------------------------------------------------------//
// Function :   FILETIMETOSTRING
// Param    :   FILETIME fileTime
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString FILETIMETOSTRING(FILETIME fileTime)
{
	SYSTEMTIME systime;	
	CString str;

	::FileTimeToSystemTime(&fileTime, &systime);
	str.Format("%04d/%02d/%02d %02d:%02d:%02d", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
	
	return str;
}

// -----------------------------------------------------------//
// Function :   DWORD128TOGUID
// Param    :   DWORD128 value
// Return   :   CString
// Comment  :   
// -----------------------------------------------------------//
CString DWORD128TOGUID(DWORD128 value)
{
	//	"2B445C5F8000FDA811CF 5B4D F8699E40"	// F8699E40-5B4D-11CF-A8FD-00805F5C442B	
	CString strTemp;
	DWORD d1 = LODWORD(value.dwwValueLow);
	WORD  w1 = (WORD)(value.dwwValueLow>>32);
	WORD  w2 = (WORD)(value.dwwValueLow>>48);
	WORD  w3 = (WORD)(value.dwwValueHi);
	DWORD64 d2 = value.dwwValueHi>>16;
	
	strTemp.Format("%08X-%04X-%04X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X", d1, w1, w2, (BYTE)w3, (BYTE)(w3>>8), 
		(BYTE)d2, (BYTE)(d2>>8), (BYTE)(d2>>16), (BYTE)(d2>>24), (BYTE)(d2>>32));

	return strTemp;						
}

// -----------------------------------------------------------//
// Function :   CString	INDEX
// Param    :   DWORD dwIndex
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CString	INDEX(DWORD dwIndex)
{	
	CString str; 
	str.Format("[%d]", dwIndex);	
	return str;
}

// -----------------------------------------------------------//
// Function :   ASCIITOUNICODE
// Param    :   TCHAR* pszAsciiData
//              WCHAR* wszUTFData
//              DWORD dwLen/* = 0 */
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL ASCIITOUNICODE(TCHAR* pszAsciiData, WCHAR* wszUTFData, DWORD dwLen/* = 0 */)
{	
	if(pszAsciiData == 0 || wszUTFData == NULL)			return FALSE;
	if(dwLen == 0)			dwLen = strlen(pszAsciiData);
	
	int wsclen=2 * MultiByteToWideChar(CP_ACP, 0, pszAsciiData, dwLen, (WORD*)wszUTFData, dwLen*2);
	
	return wsclen == dwLen*2;
}

// -----------------------------------------------------------//
// Function :   UNICODETOASCII
// Param    :   WCHAR* wszUTFData
//              TCHAR* pszAsciiData
//              DWORD dwLen/* = 0 */
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL UNICODETOASCII(WCHAR* wszUTFData,TCHAR* pszAsciiData, DWORD dwLen/* = 0 */)
{	
	if(pszAsciiData == 0 || wszUTFData == NULL)			return FALSE;
	if(dwLen == 0)			dwLen = wcslen(wszUTFData)*sizeof(WCHAR);
	
	int wsclen = WideCharToMultiByte(CP_ACP, 0, wszUTFData, dwLen*2, pszAsciiData, dwLen, NULL, NULL);
	
	return wsclen == dwLen/2;
}

// -----------------------------------------------------------//
// Function :   AddMainItem
// Param    :   LPCTSTR pszName
//              DWORD dwAddress
//              CMySuperGrid& m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* AddMainItem(LPCTSTR pszName, DWORD dwAddress, CMySuperGrid& m_ListGrid)
{
	CItemInfo* MainItem = new CItemInfo();
	MainItem->SetImage(4);	
	MainItem->SetItemText(pszName);
	MainItem->AddSubItemText(DWTOSTR(dwAddress));     
	MainItem->AddSubItemText(_T("-"));
	MainItem->AddSubItemText(_T("-"));  
	MainItem->AddSubItemText(_T("-"));  
	MainItem->AddSubItemText(_T("_"));  
	return m_ListGrid.InsertRootItem(MainItem);
}

// -----------------------------------------------------------//
// Function :   AddSubMainItem
// Param    :   LPCTSTR pszName
//              LPCTSTR pszDesc
//              DWORD dwAddress
//              CTreeItem_* parentItem
//              CMySuperGrid& m_ListGrid
// Return   :   CTreeItem_*
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_* AddSubMainItem(LPCTSTR pszName, LPCTSTR pszDesc, DWORD dwAddress, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid)
{
	CItemInfo* SubMainItem = new CItemInfo();
	SubMainItem->SetImage(1);	
	SubMainItem->SetItemText(pszName);
	SubMainItem->AddSubItemText(DWTOSTR(dwAddress));     
	SubMainItem->AddSubItemText(_T("-"));
	SubMainItem->AddSubItemText(_T("-"));  
	SubMainItem->AddSubItemText(_T("-"));  
	if(pszDesc)
	{
		SubMainItem->AddSubItemText(pszDesc); 
	}

	return m_ListGrid.InsertItem(parentItem, SubMainItem);
}

// -----------------------------------------------------------//
// Function :   AddSubItem
// Param    :   LPCTSTR strTitle
//              DWORD& dwAddress
//              ITEMVALUE itemvalue
//              LPCTSTR pszSpec
//              LPCTSTR pszDesc
//              CTreeItem_* parentItem
//              CMySuperGrid& m_ListGrid
// Return   :   CTreeItem_* 
// Comment  :   
// -----------------------------------------------------------//
CTreeItem_*  AddSubItem(LPCTSTR strTitle, DWORD& dwAddress,  ITEMVALUE& itemvalue, LPCTSTR pszSpec, LPCTSTR pszDesc, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid) 
{
	// _STRING
	if(strTitle == NULL || pszDesc == NULL)			return NULL;
	
	CString strTemp;
	CItemInfo* dosHeaderItem = new CItemInfo();
	dosHeaderItem->SetImage(2);
	// title
	dosHeaderItem->SetItemText(strTitle);
	// address
	dosHeaderItem->AddSubItemText(DWTOSTR(dwAddress));
	// data(HEX)
	switch(itemvalue.vt)
	{
	case _BYTE:
		dosHeaderItem->AddSubItemText("BYTE");
//		strTemp.Format("%02X", itemvalue.value.bValue);
		strTemp.Format("%d", itemvalue.value.bValue);
		dwAddress+= 1;	
		break;
	case _WORD:
		dosHeaderItem->AddSubItemText("WORD");
//		strTemp.Format("%04X", itemvalue.value.wValue);
		strTemp.Format("%d", itemvalue.value.wValue);
		dwAddress+= 2; 
		break;
	case _DWORD:
		dosHeaderItem->AddSubItemText("DWORD");
//		strTemp.Format("%08X", itemvalue.value.dwValue);
		strTemp.Format("%ld", itemvalue.value.dwValue);
		dwAddress+= 4;
		break;
	case _DWORD64:
		dosHeaderItem->AddSubItemText("DWORD64");
		strTemp.Format("%08X%08X", HIDWORD(itemvalue.value.dw64Value), LODWORD(itemvalue.value.dw64Value));
//		strTemp.Format("%d", itemvalue.value.dw64Value);
		dwAddress+= 8;
		break;
	case _DWORD128:
		dosHeaderItem->AddSubItemText("DWORD128");
		strTemp.Format("%08X%08X%08X%08X",	HIDWORD(itemvalue.value.dw128Value.dwwValueHi), 
											LODWORD(itemvalue.value.dw128Value.dwwValueHi),
											HIDWORD(itemvalue.value.dw128Value.dwwValueLow),
											LODWORD(itemvalue.value.dw128Value.dwwValueLow));
		dwAddress+= 16;break;
	case _BYTE_STR:
		dosHeaderItem->AddSubItemText("_BYTE_STR");
		strTemp.Format("%s", itemvalue.value.bszValue);
		dwAddress=dwAddress+strlen((char*)itemvalue.value.bszValue)+1;break;
	case _CHAR_STR:
		dosHeaderItem->AddSubItemText("_CHAR_STR");
		strTemp.Format("%s", itemvalue.value.szValue);
		dwAddress=dwAddress+strlen(itemvalue.value.szValue)+1;break;
	case _WCHAR_STR:
		{
			dosHeaderItem->AddSubItemText("_WCHAR_STR");
			int wlen = wcslen(itemvalue.value.wszValue)+1;
			CHAR* szBuffer = (char*)malloc(wlen);
			UNICODETOASCII(itemvalue.value.wszValue, szBuffer, wlen);
			strTemp.Format("%s", szBuffer);
			free(szBuffer);
			szBuffer = NULL;
			dwAddress=dwAddress+wlen;
		}
		break;
	case _NULL:
	default:
		dosHeaderItem->AddSubItemText("-");
		strTemp = _T("-");break;
	}
	dosHeaderItem->AddSubItemText(strTemp);
	// SPEC
	dosHeaderItem->AddSubItemText(pszSpec == NULL ? "-" : pszSpec);
	// DESC
	dosHeaderItem->AddSubItemText(pszDesc);

	return m_ListGrid.InsertItem(parentItem, dosHeaderItem);
}
