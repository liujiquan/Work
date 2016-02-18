// WriteFloppy.h : main header file for the WRITEFLOPPY application
//

#if !defined(AFX_WRITEFLOPPY_H__FA65FBB1_8CBD_4688_AD59_D70D01DDFC90__INCLUDED_)
#define AFX_WRITEFLOPPY_H__FA65FBB1_8CBD_4688_AD59_D70D01DDFC90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWriteFloppyApp:
// See WriteFloppy.cpp for the implementation of this class
//

class CWriteFloppyApp : public CWinApp
{
public:
	CWriteFloppyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteFloppyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWriteFloppyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEFLOPPY_H__FA65FBB1_8CBD_4688_AD59_D70D01DDFC90__INCLUDED_)
