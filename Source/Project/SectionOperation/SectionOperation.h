// SectionOperation.h : main header file for the SECTIONOPERATION application
//

#if !defined(AFX_SECTIONOPERATION_H__BFE80D73_068F_47D8_BFB7_8029F90FEF34__INCLUDED_)
#define AFX_SECTIONOPERATION_H__BFE80D73_068F_47D8_BFB7_8029F90FEF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSectionOperationApp:
// See SectionOperation.cpp for the implementation of this class
//

class CSectionOperationApp : public CWinApp
{
public:
	CSectionOperationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSectionOperationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSectionOperationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECTIONOPERATION_H__BFE80D73_068F_47D8_BFB7_8029F90FEF34__INCLUDED_)
