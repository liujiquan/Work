#if !defined(AFX_DISASSEMBLYCTL_H__930B6E14_03CD_4134_9061_7B717C9C660B__INCLUDED_)
#define AFX_DISASSEMBLYCTL_H__930B6E14_03CD_4134_9061_7B717C9C660B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DisassemblyCtl.h : Declaration of the CDisassemblyCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl : See DisassemblyCtl.cpp for implementation.

class CDisassemblyCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDisassemblyCtrl)

// Constructor
public:
	CDisassemblyCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisassemblyCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CDisassemblyCtrl();

	DECLARE_OLECREATE_EX(CDisassemblyCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDisassemblyCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDisassemblyCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDisassemblyCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDisassemblyCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDisassemblyCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDisassemblyCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDisassemblyCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
private:
	CComboBox*	m_pComBox;
	BOOL		m_bDrawRefresh;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISASSEMBLYCTL_H__930B6E14_03CD_4134_9061_7B717C9C660B__INCLUDED)
