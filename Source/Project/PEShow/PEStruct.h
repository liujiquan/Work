#if !defined(AFX_PESTRUCT_H__282572B1_B5BA_45A5_8FFF_67FE14E2C076__INCLUDED_)
#define AFX_PESTRUCT_H__282572B1_B5BA_45A5_8FFF_67FE14E2C076__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PEStruct.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPEStruct dialog
class CPEStruct : public CDialogBar
{
// Construction
public:
	CPEStruct(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPEStruct)
	enum { IDD = IDD_DIALOG_PE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEStruct)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPEStruct)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT,HTREEITEM hInsertAfter = TVI_LAST);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PESTRUCT_H__282572B1_B5BA_45A5_8FFF_67FE14E2C076__INCLUDED_)
