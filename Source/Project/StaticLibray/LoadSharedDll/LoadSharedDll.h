// LoadSharedDll.h : main header file for the LOADSHAREDDLL application
//

#if !defined(AFX_LOADSHAREDDLL_H__2F96F6BE_ED9B_44D7_BA34_A1890E424430__INCLUDED_)
#define AFX_LOADSHAREDDLL_H__2F96F6BE_ED9B_44D7_BA34_A1890E424430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadSharedDllApp:
// See LoadSharedDll.cpp for the implementation of this class
//

class CLoadSharedDllApp : public CWinApp
{
public:
	CLoadSharedDllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadSharedDllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoadSharedDllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADSHAREDDLL_H__2F96F6BE_ED9B_44D7_BA34_A1890E424430__INCLUDED_)
