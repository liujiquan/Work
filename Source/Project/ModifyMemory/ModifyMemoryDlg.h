// ModifyMemoryDlg.h :
//
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <afxtempl.h>

class CModifyMemoryDlg : public CDialog
{
public:
    CModifyMemoryDlg(CWnd* pParent = NULL);	
    ~CModifyMemoryDlg()
    {
        if(m_Process)
        {
            CloseHandle(m_Process);
            m_Process = NULL;
        }
    }
	enum { IDD = IDD_MODIFYMEMORY_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    void InitInfo();                        // 初始化信息
    void GetProcessInfo();                  // 獲取線程信息
public:
    CListCtrl m_ProcessList;
    CListBox m_MemAddrList;
    CComboBox m_CmbDataType;

    CArray<DWORD, DWORD>    m_AddressArr;   // 内存地址集合
    BOOL                    m_bRun;         // 第一次搜索Flag
    HANDLE                  m_Process;      // 進程句柄
public:
    afx_msg void OnBnClickedBtnRestart();
    afx_msg void OnBnClickedBtnRefresh();
    afx_msg void OnBnClickedBtnRun();
    afx_msg void OnBnClickedBtnModify();
    LRESULT OnSearchFinish(WPARAM wparam, LPARAM lparam);
};