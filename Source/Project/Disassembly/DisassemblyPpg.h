#if !defined(AFX_DISASSEMBLYPPG_H__A89FFACA_4B6F_4541_826A_B8204F09A081__INCLUDED_)
#define AFX_DISASSEMBLYPPG_H__A89FFACA_4B6F_4541_826A_B8204F09A081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DisassemblyPpg.h : Declaration of the CDisassemblyPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CDisassemblyPropPage : See DisassemblyPpg.cpp.cpp for implementation.

class CDisassemblyPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDisassemblyPropPage)
	DECLARE_OLECREATE_EX(CDisassemblyPropPage)

// Constructor
public:
	CDisassemblyPropPage();

// Dialog Data
	//{{AFX_DATA(CDisassemblyPropPage)
	enum { IDD = IDD_PROPPAGE_DISASSEMBLY };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CDisassemblyPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISASSEMBLYPPG_H__A89FFACA_4B6F_4541_826A_B8204F09A081__INCLUDED)
