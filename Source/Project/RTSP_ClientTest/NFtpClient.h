// NFtpClient.h : main header file for the NFTPCLIENT application
//

#if !defined(AFX_NFTPCLIENT_H__9F01C14C_6621_44C9_9165_EDF03A295980__INCLUDED_)
#define AFX_NFTPCLIENT_H__9F01C14C_6621_44C9_9165_EDF03A295980__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNFtpClientApp:
// See NFtpClient.cpp for the implementation of this class
//

class CNFtpClientApp : public CWinApp
{
public:
	CNFtpClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNFtpClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNFtpClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NFTPCLIENT_H__9F01C14C_6621_44C9_9165_EDF03A295980__INCLUDED_)
