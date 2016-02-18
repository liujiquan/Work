// ShowMemory.cpp : implementation file
//

#include "stdafx.h"
#include "PEShow.h"
#include "ShowMemory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowMemory dialog


CShowMemory::CShowMemory(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CShowMemory)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShowMemory::DoDataExchange(CDataExchange* pDX)
{
}


BEGIN_MESSAGE_MAP(CShowMemory, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowMemory message handlers

BOOL CShowMemory::OnInitDialog(UINT wparam, long lparam) 
{	
	BOOL bRet = HandleInitDialog(wparam, lparam);
	if(!UpdateData(FALSE))
	{
		TRACE("InitCDataStatus FailedI");
	}

	

	return TRUE;
}


// -----------------------------------------------------------//
// Function :   CShowMemory::InitMemoryInfo
// Param    :   LPCTSTR pBuffer
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
#define LINE_SZIE	8
void CShowMemory::InitMemoryInfo(LPCTSTR pBuffer, DWORD nSize)
{
	if(pBuffer == NULL || nSize == 0)
	{
		return;
	}
	
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST1);
	if(pListBox == NULL)
	{
		return ;
	}

	while(pListBox->GetCount())
		pListBox->DeleteString(pListBox->GetCount()-1);
	
	DWORD dwAddress = 0x00000000;
	CString strData1,strData2;
	DWORD nMaxLine = nSize % LINE_SZIE == 0 ? nSize / LINE_SZIE : nSize / LINE_SZIE + 1;
	
	for(DWORD nLine = 0; nLine < nMaxLine; nLine++)
	{
		strData1.Format(_T("%02X %02X %02X %02X %02X %02X %02X %02X"), 
			UCHAR(pBuffer[nLine*LINE_SZIE]), UCHAR(pBuffer[nLine*LINE_SZIE+1]),
			UCHAR(pBuffer[nLine*LINE_SZIE+2]), UCHAR(pBuffer[nLine*LINE_SZIE+3]), 
			UCHAR(pBuffer[nLine*LINE_SZIE+4]), UCHAR(pBuffer[nLine*LINE_SZIE+5]), 
			UCHAR(pBuffer[nLine*LINE_SZIE+6]), UCHAR(pBuffer[nLine*LINE_SZIE+7]));
		
		strData2.Format(_T("%c%c%c%c%c%c%c%c"), 
			ToChar(pBuffer[nLine*LINE_SZIE]), ToChar(pBuffer[nLine*LINE_SZIE+1]), 
			ToChar(pBuffer[nLine*LINE_SZIE+2]), ToChar(pBuffer[nLine*LINE_SZIE+3]), 
			ToChar(pBuffer[nLine*LINE_SZIE+4]), ToChar(pBuffer[nLine*LINE_SZIE+5]), 
			ToChar(pBuffer[nLine*LINE_SZIE+6]), ToChar(pBuffer[nLine*LINE_SZIE+7]));
		
		CString strTemp;
		strTemp.Format("%08X:        %s        %s", dwAddress, strData1.GetBuffer(0), strData2.GetBuffer(0));

		dwAddress += LINE_SZIE;
		pListBox->AddString(strTemp);
	}
	
}

TCHAR ToChar(CHAR c)
{
	if(c == 0)
	{
		return '.';
	}
	return c;
}
