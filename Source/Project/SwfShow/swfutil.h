//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2015, liujiquan Company All rights reserved. )
//* FileName :   swfutil.h
//* Author   :   liujiquan
//* DateTime :   1/15/2015
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __SWFUTIL_H_2459134951B94A1895E650CFD52F4215__
#define __SWFUTIL_H_2459134951B94A1895E650CFD52F4215__
#pragma once

#include "SuperGridCtrl/MySuperGrid.h"
/************************************************************************/
/* Define                                                               */
/************************************************************************/
#define CTreeItem_ CSuperGridCtrl::CTreeItem
#define IDC_MYLISTCTRL WM_USER + 1
#define NO_VALUE -1

/************************************************************************/
/* Struct                                                                     */
/************************************************************************/
typedef struct tag_SWF_HeaderInfo{
	BYTE header[3];		// header
	BYTE version;		// Version
	BYTE filelen;		// FileLen
	BYTE rectByteCount;	// rectByteCount
}SWF_HeaderInfo;

// TagValue
struct TagValue
{
	BYTE	bValue;
	CHAR	szValue[64];
};
// TagInfo
extern TagValue g_tagInfoList[];
extern int  TAGSIZE ;
struct TagInfo
{		
	BOOL	boolShortTag;			// long short
	BYTE	type;					// type
	int		length;					// length
	CHAR	szTagName[64];			// name
	TagInfo()
	{	
		this->boolShortTag = TRUE;
		this->type = 0; 
		this->length = 0;
		memset(this->szTagName, 0x00, 64);
	}
	TagInfo(BYTE buffer[])	
	{  
		
	}
	void Anaylize(BYTE buffer[])
	{
		this->boolShortTag = TRUE;
		BYTE bHi = buffer[1];
		BYTE bLow = buffer[0];
		this->type = (bHi << 2) + (bLow >> 6);	
		this->length = bLow & 0x3F;
		if(this->length == 0x3F)
		{
			memcpy(&this->length, buffer + 2, 4);
			this->boolShortTag = FALSE;
		}
		for(int i = 0; i < TAGSIZE; i++)
		{
			if(g_tagInfoList[i].bValue == this->type)
			{
				memcpy(this->szTagName, g_tagInfoList[i].szValue, 64);
				break;
			}
		}
	}
};

/************************************************************************/
/* Function                                                             */
/************************************************************************/
CString DWTOHEX(DWORD dwValue);
CString DWTOSTR(DWORD dwValue);
CString DWTOINT(DWORD dwValue);
CTreeItem_*  AddMainItem(LPCTSTR pszName, DWORD dwIndex, CMySuperGrid& m_ListGrid);
CTreeItem_*  AddSubMainItem(LPCTSTR pszName, DWORD dwIndex, DWORD dwValue,CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
CTreeItem_*  AddSubItem(LPCTSTR strTitle, DWORD dwIndex, DWORD dwValue, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);
CTreeItem_*  AddSubItem(LPCTSTR strTitle, LPCTSTR pszValue, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid);

#endif//__SWFUTIL_H_2459134951B94A1895E650CFD52F4215__
