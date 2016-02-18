// FormatBinaryCode.h : main header file for the FORMATBINARYCODE application
//

#if !defined(AFX_FORMATBINARYCODE_H__962BFEB7_28F0_4BAC_8EF6_6022C625FD73__INCLUDED_)
#define AFX_FORMATBINARYCODE_H__962BFEB7_28F0_4BAC_8EF6_6022C625FD73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFormatBinaryCodeApp:
// See FormatBinaryCode.cpp for the implementation of this class
//

class CFormatBinaryCodeApp : public CWinApp
{
public:
	CFormatBinaryCodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatBinaryCodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFormatBinaryCodeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATBINARYCODE_H__962BFEB7_28F0_4BAC_8EF6_6022C625FD73__INCLUDED_)
