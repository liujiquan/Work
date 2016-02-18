// DisassemblyProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DisassemblyProcess.h"
#include "DisassemblyProcessDlg.h"
#include "ProcessInfo.h"
#include "PeUti.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisassemblyProcessDlg dialog

CDisassemblyProcessDlg::CDisassemblyProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisassemblyProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisassemblyProcessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset(&m_ExeInfo, 0x00, sizeof(m_ExeInfo));
	m_strProcessFullPath = _T("");
	m_strProcessName = _T("");
	m_dwThreadID = 0;
	m_FileSize = 0;
	m_AssemblyData.clear();
	m_bRunning = FALSE;
	m_hThread = NULL;
	m_szProcessData = NULL;
}

void CDisassemblyProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisassemblyProcessDlg)
	DDX_Control(pDX, IDC_LIST1, m_assemListBox);
	//}}AFX_DATA_MAP
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::~CDisassemblyProcessDlg
// Return   :   
// Comment  :   
// -----------------------------------------------------------//
CDisassemblyProcessDlg::~CDisassemblyProcessDlg()
{
	if(m_szProcessData)
	{
		GlobalFree(m_szProcessData);
		m_szProcessData = NULL;
	}
	DeleteNasmExe();
}

BEGIN_MESSAGE_MAP(CDisassemblyProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CDisassemblyProcessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisassemblyProcessDlg message handlers

BOOL CDisassemblyProcessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if(LoadDlls() == FALSE)
	{
		return FALSE;
	}
	
	if(ReleaseNasmExe() == FALSE)
	{
		return FALSE;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDisassemblyProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDisassemblyProcessDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDisassemblyProcessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::ReleaseNasmExe
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CDisassemblyProcessDlg::ReleaseNasmExe()
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_NDISASM1), "ndisasm");
	if(hResource == NULL)				return FALSE;
	HGLOBAL hGobal = LoadResource(NULL, hResource);	
	if(hGobal == NULL)					return FALSE;
	LPVOID lBuffer = LockResource(hGobal);				// buffer
	DWORD dwLen = SizeofResource(NULL, hResource);		// len
	//New File
	FILE* pFile = fopen(NDISASM_EXE_NAME, "wb");
	if(pFile == NULL)					return FALSE;
	DWORD dwWriteLen = fwrite(lBuffer, 1, dwLen, pFile);	
	fclose(pFile);	
	FreeResource(hGobal);	
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::DeleteNasmExe
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDisassemblyProcessDlg::DeleteNasmExe()
{
	DeleteFile(NDISASM_EXE_NAME);
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::OnButtonOpen
// Return   :   void
// Comment  :   Open Process
// -----------------------------------------------------------//
void CDisassemblyProcessDlg::OnButtonOpen() 
{
	if(m_bRunning)
	{
		MessageBox("One Process Running Now.");
		return;
	}

	ResetData();

	CProcessInfo dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		m_strProcessFullPath = dlg.m_strProcessPath;
		m_strProcessName = dlg.m_strProcessName;
		m_dwThreadID = dlg.m_dwThreadID;
		
		m_hThread = CreateThread(NULL, 0, _ThreadFunc, this, 0, NULL);
		if(m_hThread == NULL)
		{
			CloseHandle(m_hThread);
			m_hThread = NULL;
		}
	}
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::_ThreadFunc
// Param    :   LPVOID lparam
// Return   :   DWORDWINAPI 
// Comment  :   
// -----------------------------------------------------------//
DWORD WINAPI CDisassemblyProcessDlg::_ThreadFunc(LPVOID lparam)
{
	CDisassemblyProcessDlg* _this = (CDisassemblyProcessDlg*)lparam;
	if(_this)
	{
		_this->ThreadFunc();
	}

	return 0;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::ThreadFunc
// Return   :   DWORDWINAPI 
// Comment  :   
// -----------------------------------------------------------//
DWORD WINAPI CDisassemblyProcessDlg::ThreadFunc()
{	
	m_bRunning = TRUE;
	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(FALSE);

	if(GetExeInfo(m_strProcessFullPath, &m_ExeInfo) == FALSE)				return 0;
	CString str;
	if(m_ExeInfo.dwPEVersion == X32_PE)
	{   
        str.Format("%s X32_PE/%s", m_strProcessName, g_WindowsVersion == X86 ? "X86" : "X64");  
		SetWindowText(str);
	}
	else
	{
		str.Format("%s X64_PE%s", m_strProcessName, g_WindowsVersion == X86 ? "X86" : "X64");
		SetWindowText(str);
	}
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwThreadID);
	if(hProcess == INVALID_HANDLE_VALUE)									return 0;
	
	if(m_ExeInfo.dwPEVersion == X32_PE)
	{
		m_szProcessData = ReadProcessAllMemory (hProcess, m_ExeInfo.dwSizeofImage, FALSE, m_ExeInfo.dwImageBase64); 
	}
	else
	{
		m_szProcessData = ReadProcessAllMemory(hProcess, m_ExeInfo.dwSizeofImage, TRUE, m_ExeInfo.dwImageBase64); 
	}
	m_FileSize = m_ExeInfo.dwSizeofImage;
	// InitImportFunction
    if(m_ExeInfo.dwPEVersion == X64_PE)
    { 
        if(InitImportFunction64(m_szProcessData, &m_ExeInfo, m_FuncRvaMap64) == FALSE)	return 0;
    }
    else
    {
        if(InitImportFunction(m_szProcessData, &m_ExeInfo, m_FuncRvaMap) == FALSE)	    return 0;
    }
	
	// DisassemblyData AnalysisAssemblyData FlushListBoxData
	if(DisassemblyData() && AnalysisAssemblyData() && FlushListBoxData())
	{
		
	}
	
	CloseHandle(hProcess);
	m_bRunning = FALSE;
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(TRUE);
	MessageBox("Success.");

	return 0;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::DisassemblyData
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CDisassemblyProcessDlg::DisassemblyData()
{	
	if(m_szProcessData == NULL || m_FileSize == 0)			return FALSE;
	// 1: Make Binary File
	FILE *pBinaryFile = fopen(BINARY_FILE_NAME, "wb");
	if(!pBinaryFile)										return FALSE;
	fwrite(m_szProcessData, m_FileSize, 1, pBinaryFile);
	fclose(pBinaryFile);

	// 2: Disassembly Binary File
	CString strCmd;
	if(m_ExeInfo.dwPEVersion == X64_PE)
	{
		strCmd.Format("%s -b 64   \"%s\">>%s",NDISASM_EXE_NAME, BINARY_FILE_NAME, ASSEMBLY_FILENAME);
	}
	else
	{
		strCmd.Format("%s -b 32   \"%s\">>%s",NDISASM_EXE_NAME, BINARY_FILE_NAME, ASSEMBLY_FILENAME);
	}
	int intRet = system(strCmd.GetBuffer(0));
	if(intRet == -1)										return FALSE;
	// 3: Remove Binary File
	DeleteFile(BINARY_FILE_NAME);
	// 4: Free Process Data
	if(m_szProcessData)
	{
		::GlobalFree(m_szProcessData);
		m_szProcessData = NULL;
	}

	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::AnalysisAssemblyData
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CDisassemblyProcessDlg::AnalysisAssemblyData()
{
	g_FirstTime = GetTickCount();

	CStdioFile file;
	// 1:Open Assembly File
	BOOL bRet = file.Open(ASSEMBLY_FILENAME, CFile::shareDenyRead);
	if(bRet == FALSE)									return FALSE;
	// 2:Read
	CString strLineData;
	ASSEMDATA data;
	bRet = file.ReadString(strLineData);
	while(bRet)
	{
		Sleep_();

		memset(&data, 0x00, sizeof(ASSEMDATA));
		if(m_ExeInfo.dwPEVersion == X64_PE)
		{
			bRet = Disasmembly_InitData64(strLineData.GetBuffer(0), &data, m_ExeInfo.dwImageBase64);
		}
		else
		{
			bRet = Disasmembly_InitData(strLineData.GetBuffer(0), &data, m_ExeInfo.dwImageBase);
		}
		
		if(bRet == FALSE)
		{
			break;
		}
		if( ((CButton*)GetDlgItem(IDC_CHECK_FUNC_RVA))->GetCheck() )
		{
			CString strAssemData(data.szAssemData);
			if(!strAssemData.IsEmpty())
			{
				if(m_ExeInfo.dwPEVersion == X64_PE)
				{
					for(map<DWORD64, CString>::iterator it = m_FuncRvaMap64.begin(); it != m_FuncRvaMap64.end(); it++)
					{
						TCHAR szRva[MAX_PATH] = {0};
						TCHAR szFuncName[MAX_PATH] = {0};
						//                  sprintf(szRva, "%I64x", it->first);
						sprintf(szRva, "[rel 0x%I64x]", it->first);
						sprintf(szFuncName, "%s:%s", szRva, it->second); 
						strAssemData.Replace(szRva, szFuncName);
					}
				}
				else
				{
					for(map<DWORD, CString>::iterator it = m_FuncRvaMap.begin(); it != m_FuncRvaMap.end(); it++)
					{
						TCHAR szRva[MAX_PATH] = {0};
						TCHAR szFuncName[MAX_PATH] = {0};
						sprintf(szRva, "0x%x]", it->first);
						sprintf(szFuncName, "%s:%s", szRva, it->second); 
						strAssemData.Replace(szRva, szFuncName);
					}
				}
				
			}
			memcpy(data.szAssemData, strAssemData, strAssemData.GetLength() > ASSEMDATALEN ? ASSEMDATALEN : strAssemData.GetLength());

		}	
		m_AssemblyData.push_back(data);
		
		bRet = file.ReadString(strLineData);
	}
	// 3:Remove  Assembly File
	file.Close();
	DeleteFile(ASSEMBLY_FILENAME);
	
	g_LastTime = GetTickCount();
	TRACE1("%d\n", g_LastTime - g_FirstTime);
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::FlushListBoxData
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CDisassemblyProcessDlg::FlushListBoxData()
{
	g_FirstTime = GetTickCount();

	m_assemListBox.SetRedraw(FALSE);
	// Clear
	for(int i = m_assemListBox.GetCount() - 1; i >= 0; i--)
		m_assemListBox.DeleteString(i);
	// Add
	TCHAR szLineData[MAX_PATH] = {0};
	TCHAR szCodeData[MAX_PATH] = {0};
//	int nCount = 0; 
	for(list<ASSEMDATA>::iterator it = m_AssemblyData.begin(); it != m_AssemblyData.end(); it++)
	{
		if(it == NULL)	continue;
		Sleep_();

		memset(szLineData, 0x00, MAX_PATH);
		memset(szCodeData, 0x00, MAX_PATH);
		int len = strlen(it->szCodeData);

		for(int i = len; i < CODEDATAWIDTH; i++)
		{
			szCodeData[i-len] = ' ';
		}
        if(m_ExeInfo.dwPEVersion == X64_PE)
        {
            if(it->dwAddress64 == 0x0000000000000000)
            {
				sprintf(szLineData, _T("                        %s%s%s"), it->szCodeData, szCodeData, it->szAssemData);	
			}
            else
            {
//              DWORD64 value = 0x0000ABCD1234DEFA;
//              TRACE1("%I64d\n", value);       // 188897262100218
//              TRACE1("%I64u\n", value);       // 188897262100218
//              TRACE1("%I64X\n", value);       // ABCD1234DEFA
//              TRACE1("%016I64X\n", value);    // 0000ABCD1234DEFA
//			    strLineData.Format("%016I64X        %s%s%s", it->dwAddress64, it->szCodeData, strCodeData, it->szAssemData);
				sprintf(szLineData, _T("%016I64X        %s%s%s"), it->dwAddress64, it->szCodeData, szCodeData, it->szAssemData);
			}
        }
        else
        {
            if(it->dwAddress == 0x00000000)
            {
				sprintf(szLineData, _T("                %s%s%s"), it->szCodeData, szCodeData, it->szAssemData);	
			}
            else
            {
				sprintf(szLineData, _T("%08X        %s%s%s"), it->dwAddress, it->szCodeData, szCodeData, it->szAssemData);
			}
        }

		m_assemListBox.AddString(szLineData);
//		nCount++;
//		if(nCount == 10)
//		{
//			break;
//		}
	}
	m_assemListBox.SetRedraw(TRUE);
	g_LastTime = GetTickCount();
	TRACE1("%d\n", g_LastTime - g_FirstTime);
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CDisassemblyProcessDlg::ResetData
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CDisassemblyProcessDlg::ResetData()
{
	if(m_szProcessData)
	{
		::GlobalFree(m_szProcessData);
		m_szProcessData = NULL;
	}

	if(m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	memset(&m_ExeInfo, 0x00, sizeof(m_ExeInfo));
	m_strProcessFullPath = _T("");
	m_strProcessName = _T("");
	m_dwThreadID = 0;
	m_FileSize = 0;
	m_AssemblyData.clear();
	m_bRunning = FALSE;
}
