#if !defined(AFX_DIRPAGE0_H__731ED7A0_4B8E_4E1D_A0AE_9D248BEB3932__INCLUDED_)
#define AFX_DIRPAGE0_H__731ED7A0_4B8E_4E1D_A0AE_9D248BEB3932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirPage0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirImportPage dialog
#include "SuperGridCtrl/MySuperGrid.h"
class CDirImportPage : public CDialog
{
// Construction
public:
	CDirImportPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirImportPage)
	enum { IDD = IDD_DIALOG_DIR_PAGE_IMPORT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirImportPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirImportPage)
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

#endif // !defined(AFX_DIRPAGE0_H__731ED7A0_4B8E_4E1D_A0AE_9D248BEB3932__INCLUDED_)
