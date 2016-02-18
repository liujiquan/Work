// ReadBinaryCode.h : main header file for the READBINARYCODE application
//

#if !defined(AFX_READBINARYCODE_H__7573BCBF_73D6_4BD4_9FC4_4FD0DF3B2378__INCLUDED_)
#define AFX_READBINARYCODE_H__7573BCBF_73D6_4BD4_9FC4_4FD0DF3B2378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReadBinaryCodeApp:
// See ReadBinaryCode.cpp for the implementation of this class
//

class CReadBinaryCodeApp : public CWinApp
{
public:
	CReadBinaryCodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadBinaryCodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReadBinaryCodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READBINARYCODE_H__7573BCBF_73D6_4BD4_9FC4_4FD0DF3B2378__INCLUDED_)
