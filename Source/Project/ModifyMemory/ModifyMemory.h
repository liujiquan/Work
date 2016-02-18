// ModifyMemory.h : 
//
#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif
#include "resource.h"	
class CModifyMemoryApp : public CWinApp
{
public:
	CModifyMemoryApp();
	public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
extern CModifyMemoryApp theApp;
