// DisassemblyCtl.cpp : Implementation of the CDisassemblyCtrl ActiveX Control class.

#include "stdafx.h"
#include "Disassembly.h"
#include "DisassemblyCtl.h"
#include "DisassemblyPpg.h"
#include "Draw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDisassemblyCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDisassemblyCtrl, COleControl)
	//{{AFX_MSG_MAP(CDisassemblyCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CDisassemblyCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CDisassemblyCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CDisassemblyCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CDisassemblyCtrl, COleControl)
	//{{AFX_EVENT_MAP(CDisassemblyCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CDisassemblyCtrl, 1)
	PROPPAGEID(CDisassemblyPropPage::guid)
END_PROPPAGEIDS(CDisassemblyCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDisassemblyCtrl, "DISASSEMBLY.DisassemblyCtrl.1",
	0x89a7cc2f, 0x7a81, 0x4039, 0xa5, 0x4b, 0x36, 0xf2, 0x79, 0xc2, 0x90, 0x95)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CDisassemblyCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DDisassembly =
		{ 0x5b75efa2, 0x8995, 0x43e2, { 0xb6, 0xf8, 0xdf, 0x15, 0xa4, 0xf9, 0x6d, 0x1a } };
const IID BASED_CODE IID_DDisassemblyEvents =
		{ 0xf26223ed, 0x15c8, 0x4420, { 0xb8, 0x96, 0x6, 0xb5, 0xae, 0xfb, 0x3f, 0x4 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwDisassemblyOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CDisassemblyCtrl, IDS_DISASSEMBLY, _dwDisassemblyOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::CDisassemblyCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CDisassemblyCtrl

BOOL CDisassemblyCtrl::CDisassemblyCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_DISASSEMBLY,
			IDB_DISASSEMBLY,
			afxRegApartmentThreading,
			_dwDisassemblyOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::CDisassemblyCtrl - Constructor

CDisassemblyCtrl::CDisassemblyCtrl()
{
	InitializeIIDs(&IID_DDisassembly, &IID_DDisassemblyEvents);
	SetInitialSize(MAX_WIDTH, MAX_HEIGHT);
	// TODO: Initialize your control's instance data here.

	m_pComBox = NULL;
	char* szData = "00000026  0000              add [eax],al";
	Disasmembly_InitData(szData);
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::~CDisassemblyCtrl - Destructor

CDisassemblyCtrl::~CDisassemblyCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::OnDraw - Drawing function

void CDisassemblyCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{	
	if(m_pComBox == NULL)
	{
		m_pComBox = new CComboBox;
		if(m_pComBox == NULL)	return;
		BOOL bRet = m_pComBox->Create(CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | WS_TABSTOP | WS_VISIBLE, CRect(0,0,MAX_WIDTH,COMBOX_HEIGHT*6), this, COMBOX_ID);
		m_pComBox->ShowWindow(SW_SHOW);
	}
	Disasmembly_OnDraw(pdc, m_pComBox, MAX_WIDTH, MAX_HEIGHT);
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::DoPropExchange - Persistence support

void CDisassemblyCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::OnResetState - Reset control to default state

void CDisassemblyCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl::AboutBox - Display an "About" box to the user

void CDisassemblyCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_DISASSEMBLY);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyCtrl message handlers
