#if !defined(AFX_SENDMAILFORMVIEW_H__6E93807C_E756_421C_9EEF_E22E142C8D3D__INCLUDED_)
#define AFX_SENDMAILFORMVIEW_H__6E93807C_E756_421C_9EEF_E22E142C8D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendMailFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendMailFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSendMailFormView : public CFormView
{
public:
	CSendMailFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSendMailFormView)

// Form Data
public:
	//{{AFX_DATA(CSendMailFormView)
	enum { IDD = IDD_DIALOG_SENDMAILFORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMailFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSendMailFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSendMailFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMAILFORMVIEW_H__6E93807C_E756_421C_9EEF_E22E142C8D3D__INCLUDED_)
