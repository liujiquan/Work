// SwfShow.h : main header file for the SWFSHOW application
//

#if !defined(AFX_SWFSHOW_H__F951C41C_5B90_4493_B363_B8850A5AFA9D__INCLUDED_)
#define AFX_SWFSHOW_H__F951C41C_5B90_4493_B363_B8850A5AFA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSwfShowApp:
// See SwfShow.cpp for the implementation of this class
//

class CSwfShowApp : public CWinApp
{
public:
	CSwfShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwfShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSwfShowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWFSHOW_H__F951C41C_5B90_4493_B363_B8850A5AFA9D__INCLUDED_)
