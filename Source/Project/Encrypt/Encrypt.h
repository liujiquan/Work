// Encrypt.h : main header file for the ENCRYPT application
//

#if !defined(AFX_ENCRYPT_H__B942DFBF_2513_46A7_9A10_F90C4C3E827E__INCLUDED_)
#define AFX_ENCRYPT_H__B942DFBF_2513_46A7_9A10_F90C4C3E827E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEncryptApp:
// See Encrypt.cpp for the implementation of this class
//

class CEncryptApp : public CWinApp
{
public:
	CEncryptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncryptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEncryptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRYPT_H__B942DFBF_2513_46A7_9A10_F90C4C3E827E__INCLUDED_)
