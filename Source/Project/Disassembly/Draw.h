//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Draw.h
//* Author   :   liujiquan
//* DateTime :   10/30/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifndef __DRAW_H_2459134951B94A1895E650CFD52F4215__
#define __DRAW_H_2459134951B94A1895E650CFD52F4215__
#pragma once
#include <list>
using namespace std;
/************************************************************************/
/* Macro                                                                */
/************************************************************************/
#define		MAX_WIDTH		600
#define		MAX_HEIGHT		400
#define		COMBOX_HEIGHT	20
#define		COMBOX_ID		WM_USER+1
#define		CODEDATALEN		32
#define		ASSEMDATALEN	32
/************************************************************************/
/* Struct                                                                     */
/************************************************************************/
typedef struct tag_ASSEMDATA
{
	DWORD	dwAddress;					// address
	TCHAR	wCodeDataArr[CODEDATALEN];	// Codedata
	TCHAR	szAssemData[ASSEMDATALEN];	// assemData
	// constructor
	tag_ASSEMDATA()
	{
		memset(this, 0x00, sizeof(tag_ASSEMDATA));
	}
	// operator=
	tag_ASSEMDATA& operator= (tag_ASSEMDATA& entry)
	{
		memcpy(this, &entry, sizeof(tag_ASSEMDATA));
		return *this;
	}
}ASSEMDATA, *PASSEMDATA;
/************************************************************************/
/* Global Member                                                        */
/************************************************************************/
extern list<ASSEMDATA>	g_AssemblyData;
extern COLORREF			g_TextColor;
/************************************************************************/
/* Function                                                                /
/************************************************************************/
BOOL Disasmembly_OnDraw(CDC* pdc, CComboBox* pComBox, int width, int height);
BOOL Disasmembly_InitData(char* pszData);
char* trim(char* pszData);
#endif//__DRAW_H_2459134951B94A1895E650CFD52F4215__
