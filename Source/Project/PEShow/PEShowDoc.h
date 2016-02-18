// PEShowDoc.h : interface of the CPEShowDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PESHOWDOC_H__25805EDA_037B_443F_B2D9_6963F2B19410__INCLUDED_)
#define AFX_PESHOWDOC_H__25805EDA_037B_443F_B2D9_6963F2B19410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPEShowDoc : public CDocument
{
protected: // create from serialization only
	CPEShowDoc();
	DECLARE_DYNCREATE(CPEShowDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEShowDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPEShowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPEShowDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PESHOWDOC_H__25805EDA_037B_443F_B2D9_6963F2B19410__INCLUDED_)
