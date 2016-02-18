#if !defined(AFX_DIREXPORTPAGE_H__E7444432_50C5_4238_81F4_AA3081D55A0C__INCLUDED_)
#define AFX_DIREXPORTPAGE_H__E7444432_50C5_4238_81F4_AA3081D55A0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DirExportPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirExportPage dialog
#include "SuperGridCtrl/MySuperGrid.h"
class CDirExportPage : public CDialog
{
// Construction
public:
	CDirExportPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDirExportPage)
	enum { IDD = IDD_DIALOG_DIR_PAGE_EXPORT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirExportPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirExportPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMySuperGrid m_List;
public:
	void InitGridColumn(CMySuperGrid& m_ListGrid);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIREXPORTPAGE_H__E7444432_50C5_4238_81F4_AA3081D55A0C__INCLUDED_)
