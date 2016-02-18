// InjectSimpleCode.h : main header file for the INJECTSIMPLECODE application
//

#if !defined(AFX_INJECTSIMPLECODE_H__D6454E52_D91D_47D0_9C4D_CA08D02E56A5__INCLUDED_)
#define AFX_INJECTSIMPLECODE_H__D6454E52_D91D_47D0_9C4D_CA08D02E56A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInjectSimpleCodeApp:
// See InjectSimpleCode.cpp for the implementation of this class
//

class CInjectSimpleCodeApp : public CWinApp
{
public:
	CInjectSimpleCodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectSimpleCodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInjectSimpleCodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTSIMPLECODE_H__D6454E52_D91D_47D0_9C4D_CA08D02E56A5__INCLUDED_)
