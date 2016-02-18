// SimpleEmailDoc.cpp : implementation of the CSimpleEmailDoc class
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "SimpleEmailDoc.h"
#include "MailUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int				g_AccountSize;			// account size
extern vector<Account>	g_AccountVector;		// account
/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailDoc
IMPLEMENT_DYNCREATE(CSimpleEmailDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleEmailDoc, CDocument)
	//{{AFX_MSG_MAP(CSimpleEmailDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailDoc construction/destruction

CSimpleEmailDoc::CSimpleEmailDoc()
{
	// TODO: add one-time construction code here

}

CSimpleEmailDoc::~CSimpleEmailDoc()
{
}

BOOL CSimpleEmailDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailDoc serialization

void CSimpleEmailDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailDoc diagnostics

#ifdef _DEBUG
void CSimpleEmailDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleEmailDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailDoc commands
// -----------------------------------------------------------//
// Function :   CSimpleEmailDoc::InitInstance
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailDoc::InitInstance()
{
	InitAccountInfo();	// InitAccountInfo
	GetRecivecUser();
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailDoc::InitAccountInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailDoc::InitAccountInfo()
{
	//m_AccountSize
	g_AccountSize = GetAccountSize();
	//AccountInfo
	for(int i = 0; i < g_AccountSize; i++)
	{
		Account data;
		if(GetAccountFromIniFile(&data, i))
		{
			g_AccountVector.push_back(data);
		}
	}
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailDoc::Update
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailDoc::Update()
{
	UpdateAccountInfo();	// UpdateAccountInfo
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailDoc::UpdateAccountInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailDoc::UpdateAccountInfo()
{
	int index = 0;
	SetAccountSize(g_AccountVector.size());
	for(vector<Account>::iterator it = g_AccountVector.begin(); it != g_AccountVector.end(); it++)
	{
		SetAccountFromIniFile(it, index);
		index++;
	}
}

void CSimpleEmailDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetRecivecUser();
	CDocument::OnCloseDocument();
}
