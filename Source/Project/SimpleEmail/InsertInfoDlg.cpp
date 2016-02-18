// InsertInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "InsertInfoDlg.h"
#include "MailUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertInfoDlg dialog


CInsertInfoDlg::CInsertInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertInfoDlg)
	m_InserInfo = _T("");
	//}}AFX_DATA_INIT
}


void CInsertInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertInfoDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertInfoDlg message handlers

BOOL CInsertInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(m_nFlags)
	{
	case 0:		SetWindowText("Insert Href");	break;
	case 1:		SetWindowText("Insert Img");	break;
	case 2:		SetWindowText("Insert Audio");	break;
	case 3:		SetWindowText("Insert Vedio");	break;
// 2015.03.03 Ver10.9.0.2 [Remember User] Start
	case 10:	SetWindowText("Insert User");	break;
// 2015.03.03 Ver10.9.0.2 [Remember User] End
	}

	return TRUE; 
}

BOOL CInsertInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->wParam == VK_ESCAPE)			// esc
	{
		m_InserInfo = "";
		OnClose();
	}
	else if(pMsg->wParam == VK_RETURN)		// enter
	{
		GetDlgItem(IDC_EDIT1)->GetWindowText(m_InserInfo);
		if(m_InserInfo != "")
		{
			switch(m_nFlags)
			{
				case 0:		m_InserInfo = HREF_LEFT + m_InserInfo + HREF_RIGHT;	break;
				case 1:		m_InserInfo = IMG_LEFT + m_InserInfo + IMG_RIGHT;	break;
				case 2:		m_InserInfo = AUDIO_LEFT + m_InserInfo + AUDIO_RIGHT;	break;
				case 3:		m_InserInfo = VEDIO_LEFT + m_InserInfo + VEDIO_RIGHT;	break;
// 2015.03.03 Ver10.9.0.2 [Remember User] Start
				case 10:	break;
// 2015.03.03 Ver10.9.0.2 [Remember User] End
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
