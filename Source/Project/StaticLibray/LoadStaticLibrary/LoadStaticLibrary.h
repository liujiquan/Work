// LoadStaticLibrary.h : main header file for the LOADSTATICLIBRARY application
//

#if !defined(AFX_LOADSTATICLIBRARY_H__38507934_4701_487E_A073_A76B30FF7BD8__INCLUDED_)
#define AFX_LOADSTATICLIBRARY_H__38507934_4701_487E_A073_A76B30FF7BD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadStaticLibraryApp:
// See LoadStaticLibrary.cpp for the implementation of this class
//

class CLoadStaticLibraryApp : public CWinApp
{
public:
	CLoadStaticLibraryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadStaticLibraryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoadStaticLibraryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADSTATICLIBRARY_H__38507934_4701_487E_A073_A76B30FF7BD8__INCLUDED_)
