// SimpleMedio2Doc.h : interface of the CSimpleMedio2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEMEDIO2DOC_H__FE51998B_68DC_4529_BE50_534A71C0AFCD__INCLUDED_)
#define AFX_SIMPLEMEDIO2DOC_H__FE51998B_68DC_4529_BE50_534A71C0AFCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpleMedio2Doc : public CDocument
{
protected: // create from serialization only
	CSimpleMedio2Doc();
	DECLARE_DYNCREATE(CSimpleMedio2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleMedio2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleMedio2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleMedio2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMEDIO2DOC_H__FE51998B_68DC_4529_BE50_534A71C0AFCD__INCLUDED_)
