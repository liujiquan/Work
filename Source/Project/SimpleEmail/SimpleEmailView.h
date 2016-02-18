// SimpleEmailView.h : interface of the CSimpleEmailView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLEEMAILVIEW_H__8E4B62E6_4CB6_4963_942E_41D3A5E34F6E__INCLUDED_)
#define AFX_SIMPLEEMAILVIEW_H__8E4B62E6_4CB6_4963_942E_41D3A5E34F6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SendMailDlg.h"
class CSimpleEmailView : public CView
{
protected: // create from serialization only
	CSimpleEmailView();
	DECLARE_DYNCREATE(CSimpleEmailView)

// Attributes
public:
	CSimpleEmailDoc* GetDocument();
	
// Operations
private:
	CSendMailDlg	m_SendMailDlg;
public:
	void InitInstance();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleEmailView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSimpleEmailView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleEmailView)
	afx_msg void OnMenuitemAccount();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SimpleEmailView.cpp
inline CSimpleEmailDoc* CSimpleEmailView::GetDocument()
   { return (CSimpleEmailDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEEMAILVIEW_H__8E4B62E6_4CB6_4963_942E_41D3A5E34F6E__INCLUDED_)
