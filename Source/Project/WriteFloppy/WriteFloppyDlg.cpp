
// WriteFloppyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WriteFloppy.h"
#include "WriteFloppyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWriteFloppyDlg dialog

CWriteFloppyDlg::CWriteFloppyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteFloppyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteFloppyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriteFloppyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteFloppyDlg)
	DDX_Control(pDX, IDC_COMBO_DRIVER, m_FloppyCmb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWriteFloppyDlg, CDialog)
	//{{AFX_MSG_MAP(CWriteFloppyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_WriteFloppy, OnBUTTONWriteFloppy)
	ON_BN_CLICKED(IDC_BUTTON_WriteImage, OnBUTTONWriteImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void GetDevice(CStringArray& DeviceArr);
/////////////////////////////////////////////////////////////////////////////
// CWriteFloppyDlg message handlers

BOOL CWriteFloppyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	CStringArray arr;
	GetDevice(arr);
	for(int i = 0; i < arr.GetSize(); i++)
	{
		m_FloppyCmb.AddString(arr.GetAt(i));
	}
	if(m_FloppyCmb.GetCount() > 0)
	{
		m_FloppyCmb.SetCurSel(0);
	}
	//
//	m_bitmap.LoadBitmap(IDB_BITMAP1);
//	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON_WriteFloppy);
//	pButton->SetBitmap((HBITMAP)m_bitmap);
//	pButton = (CButton*)GetDlgItem(IDC_BUTTON_WriteImage);
//	pButton->SetBitmap((HBITMAP)m_bitmap);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWriteFloppyDlg::OnPaint() 
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
HCURSOR CWriteFloppyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// -----------------------------------------------------------//
// Function :   GetDevice
// Param    :   CStringArray& DeviceArr
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void GetDevice(CStringArray& DeviceArr)
{
	DWORD dwCount = 0;
	dwCount = ::GetLogicalDriveStrings(0, NULL);

	// Get All Diever String
	TCHAR *pszBuffer = new TCHAR[dwCount];
	::GetLogicalDriveStrings(dwCount, pszBuffer);
	// split
	TCHAR* point1= pszBuffer, *point2;
	point2 = strstr(point1, "\0");
	while(point2)
	{
		CString str;
		str.Format("%s", point1);
		str.Remove('\\');
		UINT nType = ::GetDriveType(str.GetBuffer(0));
		if(nType == DRIVE_REMOVABLE) 
		{
			DeviceArr.Add(str);
		}
		
		point1 =point1 +  strlen(point2) + 1 ;
		if(point1 == NULL)
			break;
		point2 = strstr(point1, "\0");
		if(strcmp(point2, "\0") == 0)
			break;
	}

	free(pszBuffer);
}

void CWriteFloppyDlg::OnBUTTONWriteFloppy() 
{
	
	//Open File
	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "Boot.bin";
	memset(&ofn, 0x00, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Bin File(*.bin)\0*.bin\0All File(*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	{	return;}

	HANDLE handle = CreateFile(szFile, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(handle == NULL)
	{
		return;
	}
	
	//ReadFile
	unsigned char pBootData[512] = {0};
	DWORD dwSize;
	DWORD dwFileSizeHigh = 0;
	DWORD dwFileSize = GetFileSize(handle, &dwFileSizeHigh);
	if(dwFileSize <= 0 )
	{
		CloseHandle(handle);
		MessageBox("File Size = 0");
		return;
	}

	BOOL bRet = ReadFile(handle, pBootData, dwFileSize, &dwSize, NULL);
	if(bRet == FALSE)
	{
		CloseHandle(handle);
		MessageBox("ReadFile Error.");
		return;
	}
	CloseHandle(handle);
	//Open Device
	CString szDevice ;
	m_FloppyCmb.GetLBText(m_FloppyCmb.GetCurSel(), szDevice);
	memset(szFile, 0x00, MAX_PATH);
	sprintf(szFile, "\\\\.\\%s", szDevice.GetBuffer(0));//\\\\.\\H:
	HANDLE hDevice = CreateFile(szFile, GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hDevice == NULL)
	{
		return;
	}
	SetFilePointer(hDevice, 0, NULL, FILE_BEGIN);
	bRet = WriteFile(hDevice, pBootData, 512, &dwSize, NULL);
	if(bRet == FALSE)
	{
		CloseHandle(hDevice);
		MessageBox("WriteFile Error.");
		return;
	}
	SetFilePointer(hDevice, 0, NULL, FILE_BEGIN);
	bRet = ReadFile(hDevice, pBootData, 512, &dwSize, NULL);
	if(bRet == FALSE)
	{
		CloseHandle(hDevice);
		MessageBox("ReadFile Error.");
		return;
	}
	
	CloseHandle(hDevice);
	MessageBox("WriteFloppy Success!");
}

void CWriteFloppyDlg::OnBUTTONWriteImage() 
{
	//Open File
	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "Boot.bin";
	memset(&ofn, 0x00, sizeof(ofn));
	
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Bin File(*.bin)\0*.bin\0All File(*.*)\0*.*\0\0";
	ofn.lpstrTitle = "Open File";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	if(GetOpenFileName(&ofn) == FALSE)	{	return;}
	
	HANDLE handle = CreateFile(szFile, GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(handle == NULL)
	{
		return;
	}
	
	//ReadFile
	unsigned char pBootData[512] = {0};
	DWORD dwSize;
	DWORD dwFileSizeHigh = 0;
	DWORD dwFileSize = GetFileSize(handle, &dwFileSizeHigh);
	if(dwFileSize <= 0 )
	{
		CloseHandle(handle);
		MessageBox("File Size = 0");
		return;
	}
	
	BOOL bRet = ReadFile(handle, pBootData, dwFileSize, &dwSize, NULL);
	if(bRet == FALSE)
	{
		CloseHandle(handle);
		MessageBox("ReadFile Error.");
		return;
	}
	CloseHandle(handle);
	//Open Device
	::strcpy(szFile, "tinix.img");
	ofn.lpstrFilter = "Image File(*.img)\0*.img\0All File(*.*)\0*.*\0\0";
	if(GetOpenFileName(&ofn) == FALSE)	{	return;}

	HANDLE hDevice = CreateFile(szFile, GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hDevice == NULL)
	{
		return;
	}
	SetFilePointer(hDevice, 0, NULL, FILE_BEGIN);
	bRet = WriteFile(hDevice, pBootData, 512, &dwSize, NULL);
	if(bRet == FALSE)
	{
		CloseHandle(hDevice);
		MessageBox("WriteFile Error.");
		return;
	}
	
	CloseHandle(hDevice);
	MessageBox("WriteImage Success!");
	
}
