// TesWinBrowse.h : main header file for the TESWINBROWSE application
//

#if !defined(AFX_TESWINBROWSE_H__0623DC1F_461F_4539_86EC_59AACE8965DF__INCLUDED_)
#define AFX_TESWINBROWSE_H__0623DC1F_461F_4539_86EC_59AACE8965DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTesWinBrowseApp:
// See TesWinBrowse.cpp for the implementation of this class
//

class CTesWinBrowseApp : public CWinApp
{
public:
	CTesWinBrowseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesWinBrowseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTesWinBrowseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESWINBROWSE_H__0623DC1F_461F_4539_86EC_59AACE8965DF__INCLUDED_)
