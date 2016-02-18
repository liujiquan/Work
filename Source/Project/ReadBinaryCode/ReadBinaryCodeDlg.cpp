// ReadBinaryCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ReadBinaryCode.h"
#include "ReadBinaryCodeDlg.h"
#include "PEUtil.h"
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
	virtual void OnOK();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadBinaryCodeDlg dialog

CReadBinaryCodeDlg::CReadBinaryCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadBinaryCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadBinaryCodeDlg)
	m_BaseAddr = _T("");
	m_ReadSize = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_FileMemory = NULL;
	m_FileSize = 0;
	m_LineSize = LINE_SZIE;
	m_newFileName = "";
    m_bOpenProcess = FALSE;
}

CReadBinaryCodeDlg::~CReadBinaryCodeDlg()
{
	if(m_FileMemory)
	{
		::GlobalFree(m_FileMemory);
		m_FileMemory = NULL;
	}
	DeleteNasmExe();
}

void CReadBinaryCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadBinaryCodeDlg)
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_FilePath);
	DDX_Text(pDX, IDC_EDIT4, m_LineSize);
	DDX_Text(pDX, IDC_EDIT2, m_BaseAddr);
	DDX_Text(pDX, IDC_EDIT3, m_ReadSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReadBinaryCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CReadBinaryCodeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_FILEPATH, OnChangeEditFilepath)
	ON_BN_CLICKED(IDC_BUTTON_Flush, OnBUTTONFlush)
	ON_BN_CLICKED(IDC_BUTTON_CreateFile, OnBUTTONCreateFile)
	ON_BN_CLICKED(IDC_BUTTON_OpenFile, OnBUTTONOpenProcess)
	ON_BN_CLICKED(IDC_BUTTON_ASSEM, OnButtonAssem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadBinaryCodeDlg message handlers
BOOL CReadBinaryCodeDlg::OnInitDialog()
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
	if(ReleaseNasmExe() == FALSE)
	{
		return FALSE;
	}
	GetDlgItem(IDC_BUTTON_ASSEM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_Flush)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CreateFile)->EnableWindow(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadBinaryCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReadBinaryCodeDlg::OnPaint() 
{
	CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReadBinaryCodeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::ReleaseNasmExe
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CReadBinaryCodeDlg::ReleaseNasmExe()
{
	HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_NDISASM1), "ndisasm");
	if(hResource == NULL)	return FALSE;
	HGLOBAL hGobal = LoadResource(NULL, hResource);	
	if(hGobal == NULL)	return FALSE;
	LPVOID lBuffer = LockResource(hGobal);				// buffer
	DWORD dwLen = SizeofResource(NULL, hResource);		// len
	//New File
	FILE* pFile = fopen(NDISASM_EXE_NAME, "wb");
	if(pFile == NULL)	return FALSE;
	DWORD dwWriteLen = fwrite(lBuffer, 1, dwLen, pFile);	
	fclose(pFile);	
	FreeResource(hGobal);	
	
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::DeleteNasmExe
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CReadBinaryCodeDlg::DeleteNasmExe()
{
	DeleteFile(NDISASM_EXE_NAME);
}	

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::OnChangeEditFilepath
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CReadBinaryCodeDlg::OnChangeEditFilepath() 
{
    if(m_bOpenProcess)  return;
	UpdateData(TRUE);

	CString strFileFullPath;
	 m_FilePath.GetWindowText(strFileFullPath);

	 int index = strFileFullPath.ReverseFind('\\');
	 if(index == -1)
	 {
		 index = strFileFullPath.ReverseFind('/');
	 }
	 if(index != -1)
	 {	
		m_strFilePath = strFileFullPath.Left(index+1);
		m_strFileName = strFileFullPath.Right(strFileFullPath.GetLength()-index-1);
	 }

	 if(_OpenFile(m_strFilePath + m_strFileName) == FALSE)
	 {
		 MessageBox("Open File Failed.\nFile Not a PE File.");
		 return;
	 }
	 GetDlgItem(IDC_BUTTON_ASSEM)->EnableWindow(TRUE);
	 GetDlgItem(IDC_BUTTON_Flush)->EnableWindow(TRUE);
	 GetDlgItem(IDC_BUTTON_CreateFile)->EnableWindow(TRUE);
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::_OpenFile
// Param    :   LPCTSTR pszFileName
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CReadBinaryCodeDlg::_OpenFile(LPCTSTR pszFileName)
{
	// Open File
	HANDLE hFile = ::CreateFile(pszFileName, 
		GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	
	DWORD dwFileSize = GetFileSize(hFile, 0);
	if(dwFileSize == 0)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	
	// AllocMemory
	if(m_FileMemory)
	{
		::GlobalFree(m_FileMemory);
		m_FileMemory = NULL;
	}
	//
	UINT dwReadSize, dwBaseAddr;
	ExeMemInfo exeMemInfo;
	if(GetExeInfo(pszFileName, &exeMemInfo) == FALSE)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	dwBaseAddr = exeMemInfo.dwBaseOfCode;		// BaseOfCode
	dwReadSize = exeMemInfo.dwSizeOfCode;		// SizeOfCode
	m_BaseAddr.Format("0x%x", dwBaseAddr);
	m_ReadSize.Format("0x%x", dwReadSize);
	UpdateData(FALSE);
	
	if(dwReadSize != 0x00 && dwBaseAddr != 0x00)
	{
		m_FileSize = dwReadSize;
		SetFilePointer(hFile, dwBaseAddr, NULL, SEEK_SET);
	}
	else
	{
		m_FileSize = dwFileSize;
	}
	
	m_FileMemory = (TCHAR*)::GlobalAlloc(GMEM_FIXED|GMEM_ZEROINIT, m_FileSize);
	if(m_FileMemory == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	// ReadFile
	DWORD nReadSize;
	if(::ReadFile(hFile, m_FileMemory, m_FileSize, &nReadSize, NULL) )
	{
		if(nReadSize == m_FileSize)
		{
			CloseHandle(hFile);
		
			InitMemoryInfo(m_FileMemory, m_FileSize, dwBaseAddr);
			return TRUE;
		}
	}
	CloseHandle(hFile);

	return FALSE;
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::InitMemoryInfo
// Param    :   LPCTSTR pBuffer
//              DWORD nSize
//              DWORD dwBaseAddr
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CReadBinaryCodeDlg::InitMemoryInfo(LPCTSTR pBuffer, DWORD nSize, DWORD dwBaseAddr)
{
	if(pBuffer == NULL || nSize <= 0)
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

	CDC* pdc = pListBox->GetDC();
	if(pdc == NULL)	return;
	DWORD dwMaxExtend = 0;
	
	DWORD dwAddress = dwBaseAddr;
	CString strData1,strData2;
	CString strDataTemp1,strDataTemp2;
	DWORD nMaxLine = nSize % m_LineSize == 0 ? nSize / m_LineSize : nSize / m_LineSize + 1;
	
	for(DWORD nLine = 0; nLine < nMaxLine; nLine++)
	{	
		strData1 = _T("");
		strData2 = _T("");
		for(UINT i = 0; i < m_LineSize; i++)
		{
			strDataTemp1.Format("%02X ", UCHAR(pBuffer[nLine*m_LineSize+i]));
			strData1 += strDataTemp1;
			strDataTemp2.Format("%c", ToChar(pBuffer[nLine*m_LineSize+i]));
			strData2 += strDataTemp2;
		}	
		CString strTemp;
		strTemp.Format("%08X:    %s    %s", dwAddress, strData1.GetBuffer(0), strData2.GetBuffer(0));
		
		dwAddress += m_LineSize;
		pListBox->AddString(strTemp);
		// HorizontalExtent
		CSize &cs = pdc->GetTextExtent(strTemp);
		if(cs.cx > dwMaxExtend)
		{
			dwMaxExtend = cs.cx;
		}
	}
	// HorizontalExtent
	pListBox->SetHorizontalExtent(dwMaxExtend+100);
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::OnBUTTONFlush
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CReadBinaryCodeDlg::OnBUTTONFlush() 
{
	UpdateData(TRUE);
	InitMemoryInfo(m_FileMemory, m_FileSize);
}



// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::OnBUTTONCreateFile
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CReadBinaryCodeDlg::OnBUTTONCreateFile() 
{
	CString strFileFullpath = m_strFilePath + m_strFileName;
	if(CreateNewFile(m_FileMemory, m_FileSize, strFileFullpath))
	{
		MessageBox("Create File OK");
		m_newFileName = strFileFullpath;
		m_FilePath.SetWindowText(m_newFileName);
	}
	else 
	{
		MessageBox("Create File Failed");
	}
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::OnBUTTONOpenFile
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
#include "ProcessInfo.h"
void CReadBinaryCodeDlg::OnBUTTONOpenProcess() 
{
	CProcessInfo dlg(this);
	if(dlg.DoModal() == IDOK)
	{
		CString strProcessName = dlg.m_strProcessName;
		CString strProcessPath = dlg.m_strProcessPath;
		DWORD dwThreadID = dlg.m_dwThreadID;

		ExeMemInfo exeMemInfo;
		if(GetExeInfo(strProcessPath, &exeMemInfo) == FALSE)
		{
			MessageBox("Get Exe Info error.");
			return;
		}
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwThreadID);
		if(hProcess)
		{
			if(m_FileMemory)
			{
				::GlobalFree(m_FileMemory);
				m_FileMemory = NULL;
			}
			// strFileName strFilePath
			int index = strProcessPath.ReverseFind('\\');
			if(index == -1)
			{
				index = strProcessPath.ReverseFind('/');
			}
			if(index != -1)
			{	
				m_strFilePath = strProcessPath.Left(index+1);
				m_strFileName = strProcessPath.Right(strProcessPath.GetLength()-index-1);
                m_bOpenProcess = TRUE;
				m_FilePath.SetWindowText(m_strFilePath+m_strFileName);
                m_bOpenProcess = FALSE;
				GetDlgItem(IDC_BUTTON_ASSEM)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_Flush)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_CreateFile)->EnableWindow(TRUE);
			}
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] Start
            if(exeMemInfo.dwPEVersion == X32_PE)
            {
                m_FileMemory = ReadProcessAllMemory32_64 (hProcess, exeMemInfo.dwSizeofImage, FALSE); 
//              m_FileMemory = ReadProcessAllMemory(hProcess, exeMemInfo.dwImageBase, exeMemInfo.dwAddressOfEntryPoint, exeMemInfo.dwSizeofImage);
            }
            else
            {
                m_FileMemory = ReadProcessAllMemory32_64 (hProcess, exeMemInfo.dwSizeofImage, TRUE); 
//              m_FileMemory = ReadProcessAllMemory64(hProcess, exeMemInfo.dwImageBase64, exeMemInfo.dwAddressOfEntryPoint, exeMemInfo.dwSizeofImage);  
                
            }
//  2014.10.29 Ver2.00[Windows 7 X64  corresponding] End
            m_FileSize = exeMemInfo.dwSizeofImage;

			InitMemoryInfo(m_FileMemory, m_FileSize, exeMemInfo.dwImageBase);
			CloseHandle(hProcess);
		}
	}
}

// -----------------------------------------------------------//
// Function :   CReadBinaryCodeDlg::OnButtonAssem
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
#include "AssemblyDlg.h"
void CReadBinaryCodeDlg::OnButtonAssem() 
{
//  2014.10.30 Ver2.10[Windows 7 X64  Disassembly] Start
	ExeMemInfo exeMemInfo;
	if(GetExeInfo(m_strFilePath+m_strFileName, &exeMemInfo) == FALSE)
	{
		MessageBox("Get Exe Info error.");
		return;
	}
//  2014.10.30 Ver2.10[Windows 7 X64  Disassembly] End
	// buffer -> binary code file
	FILE *pBinaryFile = fopen(BINARY_FILE_NAME, "wb");
	if(!pBinaryFile)	{	return;	}
	fwrite(m_FileMemory, m_FileSize, 1, pBinaryFile);
	fclose(pBinaryFile);
	// binary code file -> assembly code file
	CString strCmd;
	CString strBinaryFileName = ASSEMBLY_FILENAME;
//  2014.10.30 Ver2.10[Windows 7 X64  Disassembly] Start
	if(exeMemInfo.dwPEVersion == X64_PE)
	{
		strCmd.Format("%s -b 64   \"%s\">>%s",NDISASM_EXE_NAME, BINARY_FILE_NAME, strBinaryFileName);
	}
	else
	{	
		strCmd.Format("%s -b 32   \"%s\">>%s",NDISASM_EXE_NAME, BINARY_FILE_NAME, strBinaryFileName);
	}
//  2014.10.30 Ver2.10[Windows 7 X64  Disassembly] End
	system(strCmd.GetBuffer(0));
	DeleteFile(BINARY_FILE_NAME);
	//
	FILE *pFile = fopen(strBinaryFileName, "rb");
	if(pFile == NULL)		return ;
	DWORD dwLength;
	fseek(pFile, 0, SEEK_SET);
	fseek(pFile, 0, SEEK_END);
	dwLength = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	TCHAR * szBuffer = (TCHAR*)malloc(dwLength* sizeof(TCHAR));	
	memset(szBuffer, 0x00, dwLength);
	fread(szBuffer,  dwLength,sizeof(TCHAR), pFile);
	//buffer
	CString strData(szBuffer);
	free(szBuffer);
	fclose(pFile);
	DeleteFile(strBinaryFileName);

	CAssemblyDlg dlg(this);
	dlg.m_strData = strData;
	dlg.InitData(m_FileMemory);
	ShowWindow(SW_HIDE);		// Hide 
	dlg.DoModal();
	ShowWindow(SW_SHOW);		// Show
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
