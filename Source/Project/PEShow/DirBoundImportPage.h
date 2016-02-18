#if !defined(AFX_DIRBOUNDIMPORTPAGE_H__E5DA6E2E_FADD_494E_807A_D9DF45BC5BAB__INCLUDED_)
#define AFX_DIRBOUNDIMPORTPAGE_H__E5DA6E2E_FADD_494E_807A_D9DF45BC5BAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirBoundImportPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirBoundImportPage dialog
#include "SuperGridCtrl/MySuperGrid.h"
class CDirBoundImportPage : public CDialog
{
// Construction
public:
	CDirBoundImportPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirBoundImportPage)
	enum { IDD = IDD_DIALOG_DIR_PAGE_BOUND_IMPORT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirBoundImportPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirBoundImportPage)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMySuperGrid m_List;
public:
	void InitGridColumn(CMySuperGrid& m_ListGrid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIRBOUNDIMPORTPAGE_H__E5DA6E2E_FADD_494E_807A_D9DF45BC5BAB__INCLUDED_)
