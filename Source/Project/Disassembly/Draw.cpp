//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Draw.cpp
//* Author   :   liujiquan
//* DateTime :   10/30/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "StdAfx.h"
#include "Draw.h"

//Global Member
list<ASSEMDATA>	g_AssemblyData;
COLORREF		g_TextColor = RGB(255,255,255);
// -----------------------------------------------------------//
// Function :   Disasmembly_OnDraw
// Param    :   CDC* pdc
// Return   :   BOOL
// Comment  :   Disasmembly_OnDraw
// -----------------------------------------------------------//
BOOL Disasmembly_OnDraw(CDC* pdc, CComboBox* pComBox, int width, int height)
{
	if(pdc == NULL && pComBox == NULL || width <= 0 || height <= 0)	return FALSE;
	//1:rect
	pdc->DrawEdge(CRect(0, COMBOX_HEIGHT, width, height), EDGE_SUNKEN, BF_RECT);
	//2:Data
	HPEN newPen = ::CreatePen(BS_SOLID, 1, g_TextColor);
	HPEN oldPen = (HPEN)pdc->SelectObject(newPen);
	
	for(list<ASSEMDATA>::iterator it = g_AssemblyData.begin(); it != g_AssemblyData.end(); it++)
	{
		TCHAR szBuffer[MAX_PATH] = {0};
		sprintf(szBuffer, "%d	%s	%s", it->dwAddress, it->wCodeDataArr, it->szAssemData);
		
		pdc->TextOut(0, COMBOX_HEIGHT, szBuffer, strlen(szBuffer));
	}
	pdc->SelectObject(oldPen);
	return TRUE;
}

BOOL Disasmembly_InitData(char* pszData)
{
	if(pszData == NULL)			return FALSE;

	TCHAR szData1[8+1] = {0};
	TCHAR szData2[CODEDATALEN+1] = {0};
	TCHAR szData3[ASSEMDATALEN+1] = {0};

	char* szData = pszData;

	// data1
	char* szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)		return FALSE;
	memcpy(szData1, szData, szDataTemp-szData);
	szData = trim(szDataTemp);
	
	// data2
	szDataTemp = strstr(szData, " ");
	if(szDataTemp == NULL)		return FALSE;
	memcpy(szData2, szData, szDataTemp-szData);
	szData = trim(szDataTemp);

	// data3
	memcpy(szData3, szData, strlen(szData));

	ASSEMDATA assemData;
	assemData.dwAddress = atoi((char*)szData1);
	memcpy(assemData.wCodeDataArr, (char*)szData2, strlen((char*)szData2));
	memcpy(assemData.szAssemData, (char*)szData3, strlen((char*)szData3));

	g_AssemblyData.push_back(assemData);
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   trim
// Param    :   char* pszData
// Return   :   char*
// Comment  :   trimLeft
// -----------------------------------------------------------//
char* trim(char* pszData)
{
	if(pszData == NULL)	return NULL;

	char* szData = pszData;
	while(*(szData) == ' ')	szData++;
	
	return szData;
}