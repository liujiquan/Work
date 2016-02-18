#if !defined(AFX_EXTENDLISTCTRL_H__171DD3EE_8E47_4315_A757_950C2157DAB6__INCLUDED_)
#define AFX_EXTENDLISTCTRL_H__171DD3EE_8E47_4315_A757_950C2157DAB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendListCtrl window

class CExtendListCtrl : public CListCtrl
{
// Construction
public:
	CExtendListCtrl();

// Attributes
public:

// Operations
public:
// Implementation
public:
	virtual ~CExtendListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendListCtrl)
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpMeasureItemStruct); 
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDLISTCTRL_H__171DD3EE_8E47_4315_A757_950C2157DAB6__INCLUDED_)
