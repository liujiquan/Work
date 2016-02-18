// DosHeaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "DosHeaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDosHeaderDlg dialog


CDosHeaderDlg::CDosHeaderDlg(CWnd* pParent /*=NULL*/)
{
}


void CDosHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
}


BEGIN_MESSAGE_MAP(CDosHeaderDlg, CDialogBar)
	//{{AFX_MSG_MAP(CDosHeaderDlg)
//	ON_WM_SIZE()
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDosHeaderDlg message handlers
#define SCROLL_WIDTH 20
BOOL CDosHeaderDlg::OnInitDialog(WPARAM wparam, LONG lparam) 
{
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		
	}
	
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width() - SCROLL_WIDTH;
	CListCtrl* pListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	if(pListCtrl == NULL)
	{
		return FALSE;
	}

	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	pListCtrl->InsertColumn(0, "Add", LVCFMT_LEFT, width/5);
	pListCtrl->InsertColumn(1, "ITEM", LVCFMT_LEFT, width/5);
	pListCtrl->InsertColumn(2, "DATA", LVCFMT_LEFT, width/5);
	pListCtrl->InsertColumn(4, "DATA", LVCFMT_LEFT, width/5);
	pListCtrl->InsertColumn(4, "DES", LVCFMT_LEFT, width/5);
	
	InitListCtrl();

	return TRUE;  
}

// -----------------------------------------------------------//
// Function :   CDosHeaderDlg::SetImageDosHeadeData
// Param    :   IMAGE_DOS_HEADER* pData
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDosHeaderDlg::SetImageDosHeadeData(IMAGE_DOS_HEADER* pData)
{
	if(pData)
	{
		memcpy(&m_DosheaderData, pData, sizeof(IMAGE_DOS_HEADER));
	}
}

// -----------------------------------------------------------//
// Function :   CDosHeaderDlg::InitListCtrl
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDosHeaderDlg::InitListCtrl()
{
	DWORD dwAddress = 0x00000000;
	CString strTemp;
	UINT nCount = 0;

	CListCtrl* m_m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	if(m_m_ListCtrl == NULL)
	{
		return;
	}
	m_m_ListCtrl->DeleteAllItems();
	
	// e_magic
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_magic");
	strTemp.Format("%04X", m_DosheaderData.e_magic);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_magic);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Magic number");	
	nCount++;

	// e_cblp
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_cblp");
	strTemp.Format("%04X", m_DosheaderData.e_cblp);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_cblp);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Bytes on last page of file");
	nCount++;

	// e_cp
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_cp");
	strTemp.Format("%04X", m_DosheaderData.e_cp);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_cp);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Pages in file");
	nCount++;

	// e_crlc
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_crlc");
	strTemp.Format("%04X", m_DosheaderData.e_crlc);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_crlc);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Relocations");
	nCount++;

	// e_cparhdr
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_cparhdr");
	strTemp.Format("%04X", m_DosheaderData.e_cparhdr);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_cparhdr);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Size of header in paragraphs");
	nCount++;

	// e_minalloc
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_minalloc");
	strTemp.Format("%04X", m_DosheaderData.e_minalloc);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_minalloc);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Minimum extra paragraphs needed");
	nCount++;

	// e_maxalloc
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_maxalloc");
	strTemp.Format("%04X", m_DosheaderData.e_maxalloc);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_maxalloc);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Maximum extra paragraphs needed");
	nCount++;

	// e_ss
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_ss");
	strTemp.Format("%04X", m_DosheaderData.e_ss);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_ss);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Initial (relative) SS value");
	nCount++;

	// e_sp
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_sp");
	strTemp.Format("%04X", m_DosheaderData.e_sp);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_sp);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Initial SP value");
	nCount++;

	// e_csum
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_csume_cblp");
	strTemp.Format("%04X", m_DosheaderData.e_csum);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_csum);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Checksum");
	nCount++;

	// e_ip
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_ip");
	strTemp.Format("%04X", m_DosheaderData.e_ip);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_ip);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Initial IP value");
	nCount++;

	// e_cs
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_cs");
	strTemp.Format("%04X", m_DosheaderData.e_cs);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_cs);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Initial (relative) CS value");
	nCount++;

	// e_lfarlc
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_lfarlc");
	strTemp.Format("%04X", m_DosheaderData.e_lfarlc);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_lfarlc);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "File address of relocation table");
	nCount++;

	// e_ovno
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_ovno");
	strTemp.Format("%04X", m_DosheaderData.e_ovno);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_ovno);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "Overlay number");
	nCount++;

	// e_res[0]
	for(int i = 0; i < 4; i++)
	{
		m_m_ListCtrl->InsertItem(nCount, "0");
		strTemp.Format("%08X", dwAddress+nCount*2);
		m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
		strTemp.Format("e_res[%d]", i);
		m_m_ListCtrl->SetItemText(nCount, 1, strTemp);
		strTemp.Format("%04X", m_DosheaderData.e_res[i]);
		m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
		strTemp.Format("%s", &m_DosheaderData.e_res[i]);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
		m_m_ListCtrl->SetItemText(nCount, 4, "Reserved words");
		nCount++;
	}	

	// e_oemid
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_oemid");
	strTemp.Format("%04X", m_DosheaderData.e_oemid);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_oemid);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "OEM identifier (for e_oeminfo)");
	nCount++;

	// e_oeminfo
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_oeminfo");
	strTemp.Format("%04X", m_DosheaderData.e_oeminfo);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_oeminfo);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "OEM information; e_oemid specific");
	nCount++;

	// e_res2[10]
	for(i = 0; i < 10; i++)
	{
		m_m_ListCtrl->InsertItem(nCount, "0");
		strTemp.Format("%08X", dwAddress+nCount*2);
		m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
		strTemp.Format("e_res2[%d]", i);
		m_m_ListCtrl->SetItemText(nCount, 1, strTemp);
		strTemp.Format("%04X", m_DosheaderData.e_res2[i]);
		m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
		strTemp.Format("%s", &m_DosheaderData.e_res2[i]);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
		m_m_ListCtrl->SetItemText(nCount, 4, "Reserved words");
		nCount++;
	}
	
	// e_lfanew
	m_m_ListCtrl->InsertItem(nCount, "0");
	strTemp.Format("%08X", dwAddress+nCount*2);
	m_m_ListCtrl->SetItemText(nCount, 0, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 1, "e_lfanew");
	strTemp.Format("%04X", m_DosheaderData.e_lfanew);
	m_m_ListCtrl->SetItemText(nCount, 2, strTemp);
	strTemp.Format("%s", &m_DosheaderData.e_lfanew);
	m_m_ListCtrl->SetItemText(nCount, 3, strTemp);
	m_m_ListCtrl->SetItemText(nCount, 4, "File address of new exe header");
}

/*
void CDosHeaderDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	cx -= SCROLL_WIDTH;

	CListCtrl* m_m_ListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1);
	if(m_m_ListCtrl == NULL)
	{
		return ;
	}
	if(m_m_ListCtrl->m_hWnd)
	{
		m_m_ListCtrl->MoveWindow(0, 0, cx, cy);
		m_m_ListCtrl->SetColumnWidth(0, cx/5);
		m_m_ListCtrl->SetColumnWidth(1, cx/5);
		m_m_ListCtrl->SetColumnWidth(2, cx/5);
		m_m_ListCtrl->SetColumnWidth(4, cx/5);
		m_m_ListCtrl->SetColumnWidth(4, cx/5);
	}
}*/
