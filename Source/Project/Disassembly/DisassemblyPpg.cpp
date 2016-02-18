// DisassemblyPpg.cpp : Implementation of the CDisassemblyPropPage property page class.

#include "stdafx.h"
#include "Disassembly.h"
#include "DisassemblyPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CDisassemblyPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CDisassemblyPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CDisassemblyPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CDisassemblyPropPage, "DISASSEMBLY.DisassemblyPropPage.1",
	0x7f352257, 0xfa21, 0x422e, 0x9a, 0x2, 0x22, 0xe, 0xac, 0x75, 0x7f, 0x2c)


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyPropPage::CDisassemblyPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CDisassemblyPropPage

BOOL CDisassemblyPropPage::CDisassemblyPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_DISASSEMBLY_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyPropPage::CDisassemblyPropPage - Constructor

CDisassemblyPropPage::CDisassemblyPropPage() :
	COlePropertyPage(IDD, IDS_DISASSEMBLY_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CDisassemblyPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyPropPage::DoDataExchange - Moves data between page and properties

void CDisassemblyPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CDisassemblyPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CDisassemblyPropPage message handlers
