// DisassemblyProcessDlg.h : header file
//

#if !defined(AFX_DISASSEMBLYPROCESSDLG_H__CA9557AB_A34E_4948_ACDE_04E5ECAC86CC__INCLUDED_)
#define AFX_DISASSEMBLYPROCESSDLG_H__CA9557AB_A34E_4948_ACDE_04E5ECAC86CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDisassemblyProcessDlg dialog
#include "PeUti.h"
#include "ExtendListBox.h"
#include "ExtendListCtrl.h"
#include <map>
using namespace std;
class CDisassemblyProcessDlg : public CDialog
{
// Construction
public:
	CDisassemblyProcessDlg(CWnd* pParent = NULL);	// standard constructor
	~CDisassemblyProcessDlg();
// Dialog Data
	//{{AFX_DATA(CDisassemblyProcessDlg)
	enum { IDD = IDD_DISASSEMBLYPROCESS_DIALOG };
	CExtendListCtrl	m_ListCtrlData;
	CExtendListBox	m_assemListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisassemblyProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDisassemblyProcessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnSelchangeList1();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString		m_strProcessName;
	CString		m_strProcessFullPath;
	DWORD		m_dwThreadID;
	ExeMemInfo	m_ExeInfo;
	TCHAR*		m_szProcessData;
	DWORD		m_FileSize;
	list<ASSEMDATA>	m_AssemblyData;
	map<DWORD, CString>		m_FuncRvaMap;
    map<DWORD64, CString>	m_FuncRvaMap64;		
public:
	BOOL ReleaseNasmExe();
	void DeleteNasmExe();
	void ResetData();
	BOOL DisassemblyData();
	BOOL AnalysisAssemblyData();
	BOOL FlushListBoxData();
public:
	BOOL		m_bRunning;
	HANDLE		m_hThread;
	static DWORD WINAPI _ThreadFunc(LPVOID lparam);
	DWORD WINAPI ThreadFunc();	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISASSEMBLYPROCESSDLG_H__CA9557AB_A34E_4948_ACDE_04E5ECAC86CC__INCLUDED_)
