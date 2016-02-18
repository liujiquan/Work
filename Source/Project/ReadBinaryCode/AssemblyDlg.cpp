// AssemblyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadBinaryCode.h"
#include "AssemblyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg dialog


CAssemblyDlg::CAssemblyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAssemblyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAssemblyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CAssemblyDlg::~CAssemblyDlg()
{
}

void CAssemblyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssemblyDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Data);
	DDX_Control(pDX, IDC_RICHEDIT1, m_RichEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssemblyDlg, CDialog)
	//{{AFX_MSG_MAP(CAssemblyDlg)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssemblyDlg message handlers

BOOL CAssemblyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetAssemblyData(m_strData);
	return TRUE;  
}

void CAssemblyDlg::SetAssemblyData(CString strBuffer)
{
	m_RichEdit.SetWindowText(strBuffer);

	CHARFORMAT cf;
	cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_BOLD;
	cf.crTextColor=RGB(0,0,255);
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	m_RichEdit.SetSelectionCharFormat(cf);
	m_RichEdit.SetSel(0, 0);

	UpdateData(FALSE);
}

// -----------------------------------------------------------//
// Function :   CAssemblyDlg::InitData
// Param    :   TCHAR* szPEBuffer
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
#include "PEUtil.h"
BOOL CAssemblyDlg::InitData(TCHAR* szPEBuffer)
{
	if(szPEBuffer == NULL)	return FALSE;

	DWORD peVersion = GetPEVersion(szPEBuffer);
	if(peVersion == NO_PE)	return FALSE;
	DWORD dwImageBase = GetImageBase(szPEBuffer);

	IMAGE_DOS_HEADER dosHeader;
	IMAGE_NT_HEADERS32 ntHeader;
	IMAGE_NT_HEADERS64 ntHeader64;
	
	DWORD dwImportAddr;
	DWORD dwImportSize;
	memcpy(&dosHeader, szPEBuffer, sizeof(dosHeader));
	// 2014.10.15 Ver1.00[SEctionOperator 64Bits Conrresponding] Start
	if(peVersion == X64_PE)
	{
		memcpy(&ntHeader64, szPEBuffer+dosHeader.e_lfanew, sizeof(ntHeader64));
		dwImportAddr = ntHeader64.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		dwImportSize = ntHeader64.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
	}
	else
	{
		memcpy(&ntHeader, szPEBuffer+dosHeader.e_lfanew, sizeof(ntHeader));
		dwImportAddr = ntHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		dwImportSize = ntHeader.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
	}
	IMAGE_IMPORT_DESCRIPTOR* pImportDesc = NULL;
	pImportDesc = (IMAGE_IMPORT_DESCRIPTOR*)(szPEBuffer + dwImportAddr);
	// FuncName <-----> FuncAddr
	m_FuncMap.RemoveAll();
	while(pImportDesc->FirstThunk)  
	{  
		char *pszDllName = (char *)((BYTE *)szPEBuffer + pImportDesc->Name);  
		IMAGE_THUNK_DATA *pThunk = (IMAGE_THUNK_DATA *)((BYTE *)szPEBuffer + pImportDesc->OriginalFirstThunk);  
		int n = 0;  

		char *pszFunName = NULL;  
		while(pThunk->u1.Function)  
		{  
			pszFunName = (char *)((BYTE *)szPEBuffer + (DWORD)pThunk->u1.AddressOfData + 2);  
			PDWORD lpAddr = (DWORD *)((BYTE *)szPEBuffer + pImportDesc->FirstThunk) +  n;  
			DWORD dwRVA = (DWORD)lpAddr - (DWORD)(szPEBuffer);
			try  
			{  
				if(pszFunName)
				{
					m_FuncMap.SetAt(dwRVA, pszFunName);		// FuncName <-----> FuncAddr
					
					TCHAR szRva[MAX_PATH] = {0};
					TCHAR szFuncName[MAX_PATH] = {0};
					sprintf(szRva, "0x%x]", dwRVA+dwImageBase);
					sprintf(szFuncName, "%s:%s", szRva, pszFunName);
					m_strData.Replace(szRva, szFuncName);
				}
			}  
			catch(...)  
			{  
			}  
			n++;  
			pThunk++;  
		}  
		pImportDesc++;  
	}

	return TRUE;
}

#define VK_F	0x46
#define VK_G	0x47
BOOL CAssemblyDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HACCEL hAccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	
	if(WM_KEYFIRST <= pMsg->message && pMsg ->message <= WM_KEYLAST)
	{
		if(hAccel && ::TranslateAccelerator(m_hWnd, hAccel, pMsg))
		{
			switch(pMsg->wParam)
			{
				case VK_F:
					{
						m_Finddlg.m_strFindText = m_RichEdit.GetSelText();
						m_Finddlg.m_findStrArr.Copy(m_findStrArr);
						m_Finddlg.DoModal();
					}break;
				case VK_G:
					{
						m_Gotodlg.DoModal();
					}
					break;
			}
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

// -----------------------------------------------------------//
// Function :   CAssemblyDlg::FindData
// Param    :   DWORD dwFlag
//              CString strFindData
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CAssemblyDlg::FindData(DWORD dwFlag, CString strFindData)
{
	if(strFindData.IsEmpty())
	{
		MessageBox("Find Data Is Empty");
		return FALSE;
	}
	//
	m_findStrArr.Add(strFindData);

	FINDTEXTEX findText;
	memset(&findText, 0x00, sizeof(findText));
	CHARRANGE cr;
	m_RichEdit.GetSel(cr);
	if(dwFlag & FR_DOWN)
	{
		findText.chrg.cpMin = cr.cpMax;
		findText.chrg.cpMax = -1;
	}
	else
	{
		findText.chrg.cpMin = cr.cpMin;
		findText.chrg.cpMax = 0;
	}
	
	findText.lpstrText = strFindData.GetBuffer(0);

	DWORD dwRet = m_RichEdit.FindText(dwFlag, &findText);
	if(dwRet == -1)
	{
//		m_RichEdit.SendMessage(EM_SETSEL, 0, 0);
		MessageBox("canot find ", "MessageBox", MB_ICONWARNING);
		return FALSE;
	}
	else
	{
		dwRet = m_RichEdit.LineFromChar(dwRet);				// nInde  -> nLine
//		int nLineCount = m_RichEdit.GetLineCount();
//		INT nMinPos, nMaxPos;
//		m_RichEdit.GetScrollRange(SB_HORZ, &nMinPos, &nMaxPos);
//		float fValue = ((float)dwRet/(float)nLineCount);
//		int nPos = (nMaxPos - nMinPos)*fValue;
//		nPos = 100;
//		m_RichEdit.SetScrollPos(SB_HORZ, nPos);
//		m_RichEdit.LineScroll(dwRet-m_scrollLine);
		DWORD dwOldLine = m_RichEdit.LineFromChar(cr.cpMin);
		::SendMessage(m_RichEdit.m_hWnd, EM_LINESCROLL, 0, dwRet - dwOldLine);
		m_scrollLine = dwRet;
		m_RichEdit.SetSel(findText.chrgText);				// SetSel

		return TRUE;
	}

	return FALSE;
}

void CAssemblyDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
