#if !defined(AFX_DIRRESOURCEPAGE_H__EB615070_89CE_4562_95D6_23D39906BC56__INCLUDED_)
#define AFX_DIRRESOURCEPAGE_H__EB615070_89CE_4562_95D6_23D39906BC56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirResourcePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirResourcePage dialog
#include "SuperGridCtrl/MySuperGrid.h"
class CDirResourcePage : public CDialog
{
// Construction
public:
	CDirResourcePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirResourcePage)
	enum { IDD = IDD_DIALOG_DIR_PAGE_RESOURCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirResourcePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirResourcePage)
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

#endif // !defined(AFX_DIRRESOURCEPAGE_H__EB615070_89CE_4562_95D6_23D39906BC56__INCLUDED_)
