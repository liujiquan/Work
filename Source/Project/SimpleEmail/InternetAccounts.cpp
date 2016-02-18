// InternetAccounts.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "InternetAccounts.h"
#include "AccountInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int				g_AccountSize;			// account size
extern vector<Account>	g_AccountVector;		// account
/////////////////////////////////////////////////////////////////////////////
// CInternetAccounts dialog
CInternetAccounts::CInternetAccounts(CWnd* pParent /*=NULL*/)
	: CDialog(CInternetAccounts::IDD, pParent)
{

}

void CInternetAccounts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInternetAccounts)
	DDX_Control(pDX, IDC_LIST2, m_AccountList);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CInternetAccounts, CDialog)
	//{{AFX_MSG_MAP(CInternetAccounts)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CInternetAccounts message handlers

BOOL CInternetAccounts::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//ListCtrl
	m_AccountList.InsertColumn(0, "Account", LVCFMT_LEFT, 200);
	m_AccountList.InsertColumn(1, "Type", LVCFMT_LEFT, 110);
	m_AccountList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	InitAccountListInfo();

	return TRUE;  
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::InitAccountListInfo
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::InitAccountListInfo()
{
	while(m_AccountList.GetItemCount() != 0)
	m_AccountList.DeleteItem(m_AccountList.GetItemCount() - 1);

	int index = 0;
	for(vector<Account>::iterator it = g_AccountVector.begin(); it != g_AccountVector.end(); it++)
	{
		m_AccountList.InsertItem(index, "");
		m_AccountList.SetItemText(index, 0, it->szSendServer);
		if(index == 0)	m_AccountList.SetItemText(index, 1, "Default");
		else			m_AccountList.SetItemText(index, 1, "Normal");

		index++;
	}
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::OnButtonAdd
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::OnButtonAdd() 
{
	CAccountInfo info(this);
	if(info.DoModal() == IDOK)
	{
		g_AccountVector.push_back(info.m_AccountInfo);
		g_AccountSize++;
	}

	InitAccountListInfo();
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::OnButtonModify
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	int index = m_AccountList.GetSelectionMark();
	if(index == -1)	
	{	
		MessageBox("Please Select One Acccount.");		
			return;
	}
	CAccountInfo info(this);
	info.SetAccountInfo(g_AccountVector.at(index), 1);
	if(info.DoModal() == IDOK)
	{
		g_AccountVector.at(index) = info.m_AccountInfo;
	}

	InitAccountListInfo();
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::OnDblclkList2
// Param    :   NMHDR* pNMHDR
//              LRESULT* pResult
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonModify();
	*pResult = 0;
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::OnButtonDelete
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::OnButtonDelete() 
{
	int index = m_AccountList.GetSelectionMark();
	if(index == -1)	
	{	
		MessageBox("Please Select One Acccount.");		
		return;
	}
	int i = 0;
	for(vector<Account>::iterator it = g_AccountVector.begin(); it != g_AccountVector.end(); it++)
	{
		if(i == index)
		{
			g_AccountVector.erase(it);
			g_AccountSize--;
			break;
		}
		i++;;
	}
	
	InitAccountListInfo();
}

// -----------------------------------------------------------//
// Function :   CInternetAccounts::OnClose
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CInternetAccounts::OnClose() 
{
	CDialog::OnClose();
}

