#if !defined(AFX_NTHEADER_H__6434E8ED_64ED_473B_8464_C5AD9F9837C1__INCLUDED_)
#define AFX_NTHEADER_H__6434E8ED_64ED_473B_8464_C5AD9F9837C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NTHeader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNTHeader dialog
#include "SuperGridCtrl/MySuperGrid.h"
class CNTHeader : public CDialogBar
{
// Construction
public:
	CNTHeader(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNTHeader)
	enum { IDD = IDD_DIALOG_NTHEADER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNTHeader)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNTHeader)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMySuperGrid m_List;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTHEADER_H__6434E8ED_64ED_473B_8464_C5AD9F9837C1__INCLUDED_)
