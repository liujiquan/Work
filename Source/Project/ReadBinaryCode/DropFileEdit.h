#if !defined(AFX_DROPFILEEDIT_H__777E1927_96DB_44EE_8376_ECD2DE2FB6E3__INCLUDED_)
#define AFX_DROPFILEEDIT_H__777E1927_96DB_44EE_8376_ECD2DE2FB6E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DropFileEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropFileEdit window

class CDropFileEdit : public CEdit
{
// Construction
public:
	CDropFileEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropFileEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDropFileEdit();
private:
	CString m_strFileName;
	// Generated message map functions
protected:
	//{{AFX_MSG(CDropFileEdit)
		// NOTE - the ClassWizard will add and remove member functions here.
	LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};	
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPFILEEDIT_H__777E1927_96DB_44EE_8376_ECD2DE2FB6E3__INCLUDED_)
