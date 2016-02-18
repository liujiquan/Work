// PEShow.h : main header file for the PESHOW application
//

#if !defined(AFX_PESHOW_H__BBEE5767_8FA7_4F1B_AD80_11285DF515BC__INCLUDED_)
#define AFX_PESHOW_H__BBEE5767_8FA7_4F1B_AD80_11285DF515BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPEShowApp:
// See PEShow.cpp for the implementation of this class
//

class CPEShowApp : public CWinApp
{
public:
	CPEShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPEShowApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PESHOW_H__BBEE5767_8FA7_4F1B_AD80_11285DF515BC__INCLUDED_)
