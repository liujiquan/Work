#if !defined(AFX_DISASSEMBLY_H__E77A6E1B_BA83_4B22_B6C7_4D51760DE5CA__INCLUDED_)
#define AFX_DISASSEMBLY_H__E77A6E1B_BA83_4B22_B6C7_4D51760DE5CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Disassembly.h : main header file for DISASSEMBLY.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDisassemblyApp : See Disassembly.cpp for implementation.

class CDisassemblyApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISASSEMBLY_H__E77A6E1B_BA83_4B22_B6C7_4D51760DE5CA__INCLUDED)
