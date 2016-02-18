// EncryptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Encrypt.h"
#include "EncryptDlg.h"
#include "Base64.h"
#include "EncryptUtil.h"

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
// CEncryptDlg dialog

CEncryptDlg::CEncryptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncryptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEncryptDlg)
	m_source = _T("");
	m_Base64Source = _T("");
	m_DecrptyBase64Source = _T("");
	m_thunderSource = _T("");
	m_m_qqdlSource = _T("");
	m_FlashgetSource = _T("");
	m_Decode_Encode = _T("");
	m_UTF8 = 0;
	m_ed2k = _T("");
	m_MD5 = _T("");
	m_HashCodeIndex = 0;
	m_CyberXStr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncryptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEncryptDlg)
	DDX_Control(pDX, IDC_EDIT_CyberX, m_CyberXEdit);
	DDX_Control(pDX, IDC_EDIT9, m_m_ed2kedit);
	DDX_Control(pDX, IDC_EDIT8, m_Decode_EncodeEdit);
	DDX_Control(pDX, IDC_EDIT1, m_SourceEdit);
	DDX_Control(pDX, IDC_EDIT7, m_FlashgetSourceEdit);
	DDX_Control(pDX, IDC_EDIT6, m_qqdlSourceEdit);
	DDX_Control(pDX, IDC_EDIT5, m_thunderSourceEdit);
	DDX_Control(pDX, IDC_EDIT4, m_DecrptyBase64SourceEdit);
	DDX_Control(pDX, IDC_EDIT3, m_Base64SourceEdit);
	DDX_Text(pDX, IDC_EDIT1, m_source);
	DDX_Text(pDX, IDC_EDIT3, m_Base64Source);
	DDX_Text(pDX, IDC_EDIT4, m_DecrptyBase64Source);
	DDX_Text(pDX, IDC_EDIT5, m_thunderSource);
	DDX_Text(pDX, IDC_EDIT6, m_m_qqdlSource);
	DDX_Text(pDX, IDC_EDIT7, m_FlashgetSource);
	DDX_Text(pDX, IDC_EDIT8, m_Decode_Encode);
	DDX_Radio(pDX, IDC_RADIOUTF8, m_UTF8);
	DDX_Text(pDX, IDC_EDIT9, m_ed2k);
	DDX_Text(pDX, IDC_EDIT10, m_MD5);
	DDX_Control(pDX, IDC_EDIT10, m_m_MD5Edit);
	DDX_Radio(pDX, IDC_RADIO1, m_HashCodeIndex);
	DDX_Text(pDX, IDC_EDIT_CyberX, m_CyberXStr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEncryptDlg, CDialog)
	//{{AFX_MSG_MAP(CEncryptDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Encrypt, OnBUTTONEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_Decrypt, OnBUTTONDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_URLEncode, OnBUTTONURLEncode)
	ON_BN_CLICKED(IDC_BUTTON_URLDecode, OnBUTTONURLDecode)
	ON_BN_CLICKED(IDC_BUTTON_DecryptEd2k, OnBUTTONDecryptEd2k)
	ON_BN_CLICKED(IDC_BUTTON_EncryptEd2k, OnBUTTONEncryptEd2k)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIOUTF8, OnRadioutf8)
	ON_BN_CLICKED(IDC_RADIOUTFASCII, OnRadioutfascii)
	ON_BN_CLICKED(IDC_BUTTON_CyberX, OnBUTTONCyberX)
	ON_BN_CLICKED(IDC_BUTTON_CyberXDecrypt, OnBUTTONCyberXDecrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEncryptDlg message handlers

BOOL CEncryptDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEncryptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEncryptDlg::OnPaint() 
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
HCURSOR CEncryptDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CEncryptDlg::OnBUTTONEncrypt
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CEncryptDlg::OnBUTTONEncrypt() 
{
	UpdateData(TRUE);

	m_source.TrimRight();
	m_source.TrimLeft();
	// 1 Normal
	m_Base64Source = GetEncryptBase64(m_source);
	// 2 Thunder
	CString strTemp;
	BOOL bRet = FormatEncryptData(THUNDER_HEADER, m_source.GetBuffer(0), strTemp);
	m_thunderSource = THUNDER_HEADER_STR + GetEncryptBase64(strTemp);
	// 3:qqdl
	m_m_qqdlSource = QQDL_HEADER_STR +  m_Base64Source;
	// 4:Flashget
	bRet = FormatEncryptData(FLASHGET_HEADER, m_source.GetBuffer(0), strTemp);
	m_FlashgetSource = Flashget_HEADER_STR +  GetEncryptBase64(strTemp) + "&";
	UpdateData(FALSE);
}


// -----------------------------------------------------------//
// Function :   CEncryptDlg::OnBUTTONDecrypt
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CEncryptDlg::OnBUTTONDecrypt() 
{
	UpdateData(TRUE);
	
	CString strDest;
	HEADER header = GetHeader(m_source.GetBuffer(0), strDest);
	strDest.TrimLeft();
	strDest.TrimRight();

	//1
	if(header == HEADER_NULL)
	{	
		m_DecrptyBase64Source = GetDecryptBase64(m_source);
	}
	//2
	else if(header == THUNDER_HEADER)
	{
		m_DecrptyBase64Source = GetDecryptBase64(strDest);
		FormatDecryptData(THUNDER_HEADER, m_DecrptyBase64Source.GetBuffer(0), m_DecrptyBase64Source);
	}
	//3
	else if(header == QQDL_HEADER)
	{
		m_DecrptyBase64Source = GetDecryptBase64(strDest);
	}
	//4
	else if(header == FLASHGET_HEADER)
	{
		m_DecrptyBase64Source = GetDecryptBase64(strDest);
		FormatDecryptData(FLASHGET_HEADER, m_DecrptyBase64Source.GetBuffer(0), m_DecrptyBase64Source);
	}
	
	UpdateData(FALSE);
}

CString TOHEX(BYTE cValue);
CString UTF8TOASCII(LPCTSTR szUTF8Data);
void CEncryptDlg::OnBUTTONURLEncode() 
{
	UpdateData(TRUE);
	m_source.TrimRight();
	m_source.TrimLeft();

	LPCTSTR pszSource = m_source.GetBuffer(0);
	CString str;
	if(m_UTF8 == 0)
	{
		str = UTF8TOASCII(pszSource);
		pszSource = str.GetBuffer(0);
	}

	CString strDest = _T("");
	int index = 0;
	while(pszSource[index] != '\0')
	{
		BYTE bValue = (BYTE)pszSource[index];

        if (isalnum(bValue) ||   (bValue == '-') || (bValue == '_') ||  (bValue == '.') || (bValue == '~'))		// 0-9/A-Z/a-z/-/ _/./~
		{   
			strDest += bValue;  
		}
        else if (bValue == ' ')																					// ' ' -> +
        {
			strDest += "+"; 
		}
        else  
        {  
            strDest += TOHEX(bValue);    
        }  
        
		index++;
	}

	m_Decode_Encode = strDest;
	
	UpdateData(FALSE);
}

BYTE FROMHEX(BYTE bHi, BYTE bLow);
CString ASCIITOUTF8(LPCTSTR szAsciiData);
void CEncryptDlg::OnBUTTONURLDecode() 
{
	UpdateData(TRUE);
	m_source.TrimRight();
	m_source.TrimLeft();

	LPCTSTR pszSource = m_source.GetBuffer(0);
	BYTE bValue;
	CString strDest = _T("");
	int index = 0;
	while(pszSource[index] != '\0')
	{
		bValue = (BYTE)pszSource[index];
		if(bValue == '+')		
		{
			bValue = ' ';
			strDest += bValue;

			index++;
		}
		else if(bValue == '%')
		{	
			BYTE bValueLow = (BYTE)pszSource[index+2];
			BYTE bValueHi =  (BYTE)pszSource[index+1];
			if(bValueLow == '\0' || bValueHi == '\0')
			{
				strDest += bValue;
				strDest += bValueLow;
				strDest += bValueHi;
				break;
			}
			bValue = FROMHEX(bValueHi, bValueLow);
			strDest += bValue;
			
			index += 3;
		}
		else
		{
			strDest += bValue;
			index++;
		}
	}
	if(m_UTF8 == 0)
	{
		strDest = ASCIITOUTF8(strDest.GetBuffer(0));
	}

	m_Decode_Encode = strDest;
	
	UpdateData(FALSE);
}

CString TOHEX(BYTE cValue)
{
	CString strTemp;

	strTemp.Format("%%%02x", cValue);

	return strTemp;
}

BYTE FROMHEX(BYTE bHi, BYTE bLow)
{
	BYTE bValue;
	TCHAR szBuffer[3] = {0};

	sprintf(szBuffer,"%c%c", bHi, bLow);
	sscanf(szBuffer, "%02x", &bValue);

	return bValue;
}


CString UTF8TOASCII(LPCTSTR szUTF8Data)
{
	if(szUTF8Data == NULL)			return "";
	
	int nLen = strlen(szUTF8Data);
	//->WCHAR  
	WCHAR* pwchar = (WCHAR*)malloc(nLen*sizeof(WCHAR));
	memset(pwchar, 0x00, nLen*sizeof(WCHAR));
	int nUTF8Len = MultiByteToWideChar(CP_ACP, 0, szUTF8Data, nLen, pwchar, nLen*sizeof(WCHAR));

	TCHAR* szAscii = (TCHAR*)malloc(nUTF8Len * 4 + 1);
	memset(szAscii, 0x00, nUTF8Len * 4 + 1);
	int nAsciiLen = WideCharToMultiByte(CP_UTF8, 0, pwchar, nUTF8Len, szAscii, nUTF8Len * 4, 0, 0);
	if(nAsciiLen == 0)				return "";
	
	CString str(szAscii);
	free(pwchar);
	free(szAscii);
	pwchar = NULL;
	szAscii = NULL;

	return str;
}

CString ASCIITOUTF8(LPCTSTR szAsciiData)
{
	if(szAsciiData == NULL)			return "";
	
	int nLen = strlen(szAsciiData);


	WCHAR* pwchar = (WCHAR*)malloc(nLen*sizeof(WCHAR));
	int nUTF8Len = MultiByteToWideChar(CP_UTF8, 0, szAsciiData, nLen, pwchar, nLen*sizeof(WCHAR));

	TCHAR* szAscii = (TCHAR*)malloc(nUTF8Len * 2 + 1);
	memset(szAscii, 0x00, nUTF8Len * 2 + 1);
	int nAsciiLen = WideCharToMultiByte(CP_ACP, 0, pwchar, nUTF8Len, szAscii, nUTF8Len * 2, 0, 0);
	if(nAsciiLen == 0)				return "";

	CString str(szAscii);
	free(pwchar);
	free(szAscii);
	pwchar = NULL;
	szAscii = NULL;

	return str;
}

void CEncryptDlg::OnBUTTONEncryptEd2k() 
{
	UpdateData(TRUE);
	long lHashCode = GeneralHashFunctionLibrary::HashCode(m_source, m_HashCodeIndex);
	m_ed2k.Format("%X", lHashCode);
	UpdateData(FALSE);
}

void CEncryptDlg::OnBUTTONDecryptEd2k() 
{
	
}

void CEncryptDlg::OnButton1() 
{
	

}

void CEncryptDlg::OnRadioutf8() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_Decode_Encode = ASCIITOUTF8(m_Decode_Encode.GetBuffer(0));
	UpdateData(FALSE);
}

void CEncryptDlg::OnRadioutfascii() 
{
	UpdateData(TRUE);
	m_Decode_Encode = UTF8TOASCII(m_Decode_Encode.GetBuffer(0));
	UpdateData(FALSE);
}
extern unsigned char g_szKeyData[];
#include "CyberxEncrypt.h"
void CEncryptDlg::OnBUTTONCyberX() 
{
	UpdateData(TRUE);
	CString strTemp = m_source;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	m_CyberXStr = Encryption(strTemp.GetBuffer(0), (LPCTSTR)g_szKeyData);
	UpdateData(FALSE);
}

void CEncryptDlg::OnBUTTONCyberXDecrypt() 
{
	UpdateData(TRUE);
	CString strTemp = m_source;
	strTemp.TrimLeft();
	strTemp.TrimRight();
	m_CyberXStr = Decryption(strTemp.GetBuffer(0), (LPCTSTR)g_szKeyData);
	UpdateData(FALSE);
}
