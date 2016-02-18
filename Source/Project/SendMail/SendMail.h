// SendMail.h : main header file for the SENDMAIL application
//

#if !defined(AFX_SENDMAIL_H__5AE792D7_02EC_461B_BB44_7055BCC7EF44__INCLUDED_)
#define AFX_SENDMAIL_H__5AE792D7_02EC_461B_BB44_7055BCC7EF44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSendMailApp:
// See SendMail.cpp for the implementation of this class
//

class CSendMailApp : public CWinApp
{
public:
	CSendMailApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSendMailApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMAIL_H__5AE792D7_02EC_461B_BB44_7055BCC7EF44__INCLUDED_)
