// ASFShow.h : main header file for the ASFSHOW application
//

#if !defined(AFX_ASFSHOW_H__36A34E7A_CB7D_42B9_A6BE_4A2EBD1A8081__INCLUDED_)
#define AFX_ASFSHOW_H__36A34E7A_CB7D_42B9_A6BE_4A2EBD1A8081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CASFShowApp:
// See ASFShow.cpp for the implementation of this class
//

class CASFShowApp : public CWinApp
{
public:
	CASFShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASFShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CASFShowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASFSHOW_H__36A34E7A_CB7D_42B9_A6BE_4A2EBD1A8081__INCLUDED_)
