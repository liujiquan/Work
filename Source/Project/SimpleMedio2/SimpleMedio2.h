// SimpleMedio2.h : main header file for the SIMPLEMEDIO2 application
//

#if !defined(AFX_SIMPLEMEDIO2_H__D3A4CFCD_1E6E_49B4_B0ED_BF28F4126701__INCLUDED_)
#define AFX_SIMPLEMEDIO2_H__D3A4CFCD_1E6E_49B4_B0ED_BF28F4126701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleMedio2App:
// See SimpleMedio2.cpp for the implementation of this class
//

class CSimpleMedio2App : public CWinApp
{
public:
	CSimpleMedio2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleMedio2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSimpleMedio2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMEDIO2_H__D3A4CFCD_1E6E_49B4_B0ED_BF28F4126701__INCLUDED_)
