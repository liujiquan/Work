// DropFileEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ReadBinaryCode.h"
#include "DropFileEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropFileEdit

CDropFileEdit::CDropFileEdit()
{
}

CDropFileEdit::~CDropFileEdit()
{
}


BEGIN_MESSAGE_MAP(CDropFileEdit, CEdit)
	//{{AFX_MSG_MAP(CDropFileEdit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(WM_DROPFILES, OnDragAcceptFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropFileEdit message handlers
LRESULT CDropFileEdit::OnDragAcceptFiles(WPARAM wparam,LPARAM lparam)
{
	HDROP hdrop = (HDROP)wparam;
	if(hdrop == NULL)	return 0;
	
	int nCount = ::DragQueryFile(hdrop, -1, NULL, 0);
	if(nCount == 1)
	{
		m_strFileName.Empty();
		TCHAR szBuffer[MAX_PATH] = {0};
		::DragQueryFile(hdrop, 0, szBuffer, MAX_PATH);
		m_strFileName = (CString)(szBuffer);
		SetWindowText(m_strFileName);
	}

	return 0;
}