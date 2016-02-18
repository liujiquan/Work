// SimpleEmail.h : main header file for the SIMPLEEMAIL application
//

#if !defined(AFX_SIMPLEEMAIL_H__DC2D4F5B_563E_42D2_B07B_2C98F73FC1D2__INCLUDED_)
#define AFX_SIMPLEEMAIL_H__DC2D4F5B_563E_42D2_B07B_2C98F73FC1D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailApp:
// See SimpleEmail.cpp for the implementation of this class
//

class CSimpleEmailApp : public CWinApp
{
public:
	CSimpleEmailApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleEmailApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSimpleEmailApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEEMAIL_H__DC2D4F5B_563E_42D2_B07B_2C98F73FC1D2__INCLUDED_)
