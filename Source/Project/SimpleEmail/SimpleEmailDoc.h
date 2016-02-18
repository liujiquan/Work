// SimpleEmailDoc.h : interface of the CSimpleEmailDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEEMAILDOC_H__1D18979E_8156_4873_BC74_31B6631CA38C__INCLUDED_)
#define AFX_SIMPLEEMAILDOC_H__1D18979E_8156_4873_BC74_31B6631CA38C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpleEmailDoc : public CDocument
{
protected: // create from serialization only
	CSimpleEmailDoc();
	DECLARE_DYNCREATE(CSimpleEmailDoc)

// Attributes
public:
	
// Operations
public:
	void InitInstance();
	void InitAccountInfo();
	void Update();
	void UpdateAccountInfo();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleEmailDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleEmailDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleEmailDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEEMAILDOC_H__1D18979E_8156_4873_BC74_31B6631CA38C__INCLUDED_)
