// SimpleMedio2View.h : interface of the CSimpleMedio2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEMEDIO2VIEW_H__F59BCD44_6D75_4FF0_AABC_2BF9FB203615__INCLUDED_)
#define AFX_SIMPLEMEDIO2VIEW_H__F59BCD44_6D75_4FF0_AABC_2BF9FB203615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpleMedio2View : public CView
{
protected: // create from serialization only
	CSimpleMedio2View();
	DECLARE_DYNCREATE(CSimpleMedio2View)

// Attributes
public:
	CSimpleMedio2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleMedio2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleMedio2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleMedio2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SimpleMedio2View.cpp
inline CSimpleMedio2Doc* CSimpleMedio2View::GetDocument()
   { return (CSimpleMedio2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMEDIO2VIEW_H__F59BCD44_6D75_4FF0_AABC_2BF9FB203615__INCLUDED_)
