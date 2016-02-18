//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2015, liujiquan Company All rights reserved. )
//* FileName :   swfutil.cpp
//* Author   :   liujiquan
//* DateTime :   1/15/2015
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "swfutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************************************************/
/* TagInfo                                                                     */
/************************************************************************/
TagValue g_tagInfoList[] = {
		0,	"End",	
		1,	"ShowFrame",	
		2,	"DefineShape",	
		4,	"PlaceObject",	
		5,	"RemoveObject",	
		6,	"DefineBits",	
		7,	"DefineButton",	
		8,	"JPEGTables",	
		9,	"SetBackgroundColor",	
		10,	"DefineFont",	
		11,	"DefineText",	
		12,	"DoAction",	
		13,	"DefineFontInfo",	
		14,	"DefineSound",	
		15,	"StartSound",
		17,	"DefineButtonSound",	
		18,	"SoundStreamHead",	
		19,	"SoundStreamBlock",	
		20,	"DefineBitsLossless",	
		21,	"DefineBitsJPEG2",	
		22,	"DefineShape2",	
		23,	"DefineButtonCxform",	
		24,	"Protect",	
		26,	"PlaceObject2",	
		28,	"RemoveObject2",	
		32,	"DefineShape3",	
		33,	"DefineText2",	
		34,	"DefineButton2",	
		35,	"DefineBitsJPEG3",	
		36,	"DefineBitsLossless2",	
		37,	"DefineEditText",	
		39,	"DefineSprite",	
		43,	"FrameLabel",	
		45,	"SoundStreamHead2",	
		46,	"DefineMorphShape",	
		48,	"DefineFont2",	
		56,	"ExportAssets",	
		57,	"ImportAssets",	
		58,	"EnableDebugger",	
		59,	"DoInitAction",	
		60,	"DefineVideoStream",	
		61,	"VideoFrame",	
		62,	"DefineFontInfo2",	
		64,	"EnableDebugger2",	
		65,	"ScriptLimits",	
		66,	"SetTabIndex",	
		69,	"FileAttributes",	
		70,	"PlaceObject3",	
		71,	"ImportAssets2",	
		73,	"DefineFontAlignZones",	
		74,	"CSMTextSettings",	
		75,	"DefineFont3",	
		76,	"SymbolClass",	
		77,	"Metadata",	
		78,	"DefineScalingGrid",	
		82,	"DoABC",	
		83,	"DefineShape4",	
		84,	"DefineMorphShape2",	
		86,	"DefineSceneAndFrameLabelData",	
		87,	"DefineBinaryData",	
		88,	"DefineFontName",	
		89,	"StartSound2",	
		90,	"DefineBitsJPEG4",	
		91,	"DefineFont4"
};
int  TAGSIZE = 	(sizeof(g_tagInfoList)/sizeof(TagValue));


CTreeItem_*  AddMainItem(LPCTSTR pszName, DWORD dwIndex,  CMySuperGrid& m_ListGrid)
{
	CItemInfo* MainItem = new CItemInfo();
	MainItem->SetImage(4);	
	MainItem->SetItemText(pszName);   
	MainItem->AddSubItemText(DWTOHEX(dwIndex));

	return m_ListGrid.InsertRootItem(MainItem);
}

CTreeItem_*  AddSubMainItem(LPCTSTR pszName, DWORD dwIndex, DWORD dwValue,CTreeItem_* parentItem, CMySuperGrid& m_ListGrid)
{
	CItemInfo* SubMainItem = new CItemInfo();
	SubMainItem->SetImage(1);	
	SubMainItem->SetItemText(pszName);
	SubMainItem->AddSubItemText(DWTOHEX(dwIndex));    
	
	return m_ListGrid.InsertItem(parentItem, SubMainItem);
}

CTreeItem_*  AddSubItem(LPCTSTR strTitle, DWORD dwIndex, DWORD dwValue, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid)
{
	CString strTemp;
	CItemInfo* SubItem = new CItemInfo();
	SubItem->SetImage(2);
	SubItem->SetItemText(strTitle);
	SubItem->AddSubItemText(DWTOHEX(dwIndex));

	SubItem->AddSubItemText(DWTOHEX(dwValue));
	SubItem->AddSubItemText(DWTOINT(dwValue));
	SubItem->AddSubItemText(DWTOSTR(dwValue));

	return m_ListGrid.InsertItem(parentItem, SubItem);
}

CTreeItem_*  AddSubItem(LPCTSTR strTitle, LPCTSTR pszValue, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid)
{
	CString strTemp;
	CItemInfo* SubItem = new CItemInfo();
	SubItem->SetImage(2);
	SubItem->SetItemText(strTitle);
	SubItem->AddSubItemText(pszValue);
	
	return m_ListGrid.InsertItem(parentItem, SubItem);
}

CString DWTOSTR(DWORD dwValue)
{
	CString str;
	str.Format("%s", &dwValue);
	
	return str;
}

CString DWTOHEX(DWORD dwValue)
{
	CString str;
	str.Format("%08X", dwValue);
	
	return str;
}

CString DWTOINT(DWORD dwValue)
{
	CString str;
	str.Format("%d", dwValue);
	
	return str;
}
