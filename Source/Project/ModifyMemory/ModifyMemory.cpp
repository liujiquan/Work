// ModifyMemory.cpp : アプリケーションのクラス動作を定義します。
//

#include "stdafx.h"
#include "ModifyMemory.h"
#include "ModifyMemoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CModifyMemoryApp

BEGIN_MESSAGE_MAP(CModifyMemoryApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CModifyMemoryApp コンストラクション

CModifyMemoryApp::CModifyMemoryApp()
{
	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CModifyMemoryApp オブジェクトです。

CModifyMemoryApp theApp;


// CModifyMemoryApp 初期化

BOOL CModifyMemoryApp::InitInstance()
{
	CWinApp::InitInstance();

	// 標準初期化
	// これらの機能を使わずに、最終的な実行可能ファイルのサイズを縮小したい場合は、
	// 以下から、不要な初期化ルーチンを
	// 削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: この文字列を、会社名または組織名などの、
	// 適切な文字列に変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	CModifyMemoryDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//       記述してください。
	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
