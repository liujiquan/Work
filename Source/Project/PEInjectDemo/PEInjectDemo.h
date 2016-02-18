// PEInjectDemo.h : main header file for the PEINJECTDEMO application
//

#if !defined(AFX_PEINJECTDEMO_H__5433B5FB_F5F6_4BD8_A70F_DC4285D79165__INCLUDED_)
#define AFX_PEINJECTDEMO_H__5433B5FB_F5F6_4BD8_A70F_DC4285D79165__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPEInjectDemoApp:
// See PEInjectDemo.cpp for the implementation of this class
//

class CPEInjectDemoApp : public CWinApp
{
public:
	CPEInjectDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEInjectDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPEInjectDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEINJECTDEMO_H__5433B5FB_F5F6_4BD8_A70F_DC4285D79165__INCLUDED_)
