// ffmpegDemo1.h : main header file for the FFMPEGDEMO1 application
//

#if !defined(AFX_FFMPEGDEMO1_H__33351163_0EBB_4EB4_95F9_C3A2F7B860B0__INCLUDED_)
#define AFX_FFMPEGDEMO1_H__33351163_0EBB_4EB4_95F9_C3A2F7B860B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFfmpegDemo1App:
// See ffmpegDemo1.cpp for the implementation of this class
//

class CFfmpegDemo1App : public CWinApp
{
public:
	CFfmpegDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFfmpegDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFfmpegDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFMPEGDEMO1_H__33351163_0EBB_4EB4_95F9_C3A2F7B860B0__INCLUDED_)
