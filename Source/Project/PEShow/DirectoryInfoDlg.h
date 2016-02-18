#if !defined(AFX_DIRECTORYINFODLG_H__F9D3EFF3_B6F2_44B8_AD64_A4A4F5143EE4__INCLUDED_)
#define AFX_DIRECTORYINFODLG_H__F9D3EFF3_B6F2_44B8_AD64_A4A4F5143EE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirectoryInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirectoryInfoDlg dialog
#include "DirImportPage.h"
#include "DirExportPage.h"
#include "DirResourcePage.h"
#include "DirBoundImportPage.h"
class CDirectoryInfoDlg : public CDialogBar
{
// Construction
public:
	CDirectoryInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirectoryInfoDlg)
	enum { IDD = IDD_DIALOG_DIRECTORYINFO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirectoryInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirectoryInfoDlg)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CDirImportPage		m_Page0;
	CDirExportPage		m_Page1;
	CDirResourcePage	m_Page2;
	CDirBoundImportPage	m_Page3;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRECTORYINFODLG_H__F9D3EFF3_B6F2_44B8_AD64_A4A4F5143EE4__INCLUDED_)
