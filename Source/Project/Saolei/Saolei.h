// Saolei.h : main header file for the SAOLEI application
//

#if !defined(AFX_SAOLEI_H__F35024DB_824B_4939_A7CB_152860D6FE95__INCLUDED_)
#define AFX_SAOLEI_H__F35024DB_824B_4939_A7CB_152860D6FE95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSaoleiApp:
// See Saolei.cpp for the implementation of this class
//

class CSaoleiApp : public CWinApp
{
public:
	CSaoleiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaoleiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSaoleiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAOLEI_H__F35024DB_824B_4939_A7CB_152860D6FE95__INCLUDED_)
