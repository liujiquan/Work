//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendStatusBar.h
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#if !defined(AFX_EXTENDSTATUSBAR_H__38438E81_A27A_44FF_8266_CC78BCCB4922__INCLUDED_)
#define AFX_EXTENDSTATUSBAR_H__38438E81_A27A_44FF_8266_CC78BCCB4922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendStatusBar window

class CExtendStatusBar : public CStatusBar
{
// Construction
public:
	CExtendStatusBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendStatusBar();
	void SetInfo(LPCTSTR pszBufferInfo);
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDSTATUSBAR_H__38438E81_A27A_44FF_8266_CC78BCCB4922__INCLUDED_)
