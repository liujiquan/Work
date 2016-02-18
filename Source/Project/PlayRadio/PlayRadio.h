// PlayRadio.h : main header file for the PLAYRADIO application
//

#if !defined(AFX_PLAYRADIO_H__50E9D8C6_5DC9_4770_A9CF_55CA0BEDB6DE__INCLUDED_)
#define AFX_PLAYRADIO_H__50E9D8C6_5DC9_4770_A9CF_55CA0BEDB6DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlayRadioApp:
// See PlayRadio.cpp for the implementation of this class
//

class CPlayRadioApp : public CWinApp
{
public:
	CPlayRadioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayRadioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPlayRadioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYRADIO_H__50E9D8C6_5DC9_4770_A9CF_55CA0BEDB6DE__INCLUDED_)
