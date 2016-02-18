#if !defined(AFX_ASSEMBLYDLG_H__7CDB6278_2F9F_4AC1_9307_50011951349F__INCLUDED_)
#define AFX_ASSEMBLYDLG_H__7CDB6278_2F9F_4AC1_9307_50011951349F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssemblyDlg.h : header file
//
#include "PEUtil.h"
#include "AccembFindDlg.h"
#include "AssemGotoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg dialog

class CAssemblyDlg : public CDialog
{
// Construction
public:
	CAssemblyDlg(CWnd* pParent = NULL);   // standard constructor
	~CAssemblyDlg();
// Dialog Data
	//{{AFX_DATA(CAssemblyDlg)
	enum { IDD = IDD_DIALOG_ASSEMBLY };
	CEdit	m_Data;
	CRichEditCtrl	m_RichEdit;
	UINT			m_scrollLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssemblyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssemblyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetAssemblyData(CString szBuffer);
	BOOL InitData(TCHAR* szPEBuffer);
	BOOL FindData(DWORD dwFlag, CString strFindData);
public:
	CString m_strData;
	CMap<DWORD, DWORD, LPCTSTR, LPCTSTR> m_FuncMap; 

	CAccembFindDlg	m_Finddlg;
	CAssemGotoDlg	m_Gotodlg;
	CStringArray	m_findStrArr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSEMBLYDLG_H__7CDB6278_2F9F_4AC1_9307_50011951349F__INCLUDED_)
