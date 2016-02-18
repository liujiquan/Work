// CMailDemo3.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CCMailDemo3App:
// このクラスの実装については、CMailDemo3.cpp を参照してください。
//

class CCMailDemo3App : public CWinApp
{
public:
	CCMailDemo3App();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCMailDemo3App theApp;
