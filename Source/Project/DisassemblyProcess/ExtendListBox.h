#if !defined(AFX_EXTENDLISTBOX_H__70972311_A501_4D88_86D0_50BE8BB5EF29__INCLUDED_)
#define AFX_EXTENDLISTBOX_H__70972311_A501_4D88_86D0_50BE8BB5EF29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox window
#include <vector>
using namespace std;
class CExtendListBox : public CListBox
{
	DECLARE_DYNAMIC(CExtendListBox)
// Construction
public:
	CExtendListBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendListBox)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void Copy();
	void SelectAll();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDLISTBOX_H__70972311_A501_4D88_86D0_50BE8BB5EF29__INCLUDED_)
