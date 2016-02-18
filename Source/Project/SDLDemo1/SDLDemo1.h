// SDLDemo1.h : main header file for the SDLDEMO1 application
//

#if !defined(AFX_SDLDEMO1_H__DE6831FF_78A1_44BE_90B5_947897D98385__INCLUDED_)
#define AFX_SDLDEMO1_H__DE6831FF_78A1_44BE_90B5_947897D98385__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDLDemo1App:
// See SDLDemo1.cpp for the implementation of this class
//

class CSDLDemo1App : public CWinApp
{
public:
	CSDLDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDLDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSDLDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDLDEMO1_H__DE6831FF_78A1_44BE_90B5_947897D98385__INCLUDED_)
