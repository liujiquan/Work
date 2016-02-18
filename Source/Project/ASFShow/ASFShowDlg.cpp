// ASFShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ASFShow.h"
#include "ASFShowDlg.h"
#include "AsfInfo.h"

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
// CASFShowDlg dialog

CASFShowDlg::CASFShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CASFShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CASFShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CASFShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CASFShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CASFShowDlg, CDialog)
	//{{AFX_MSG_MAP(CASFShowDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CASFShowDlg message handlers

BOOL CASFShowDlg::OnInitDialog()
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
	ShowWindow(SW_SHOWMAXIMIZED); 
	InitGridColumn();
	ReadAsfFile(ASFFILENAME);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CASFShowDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CASFShowDlg::OnPaint() 
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
HCURSOR CASFShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::OnSize
// Param    :   UINT nType
//              int cx
//              int cy
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CASFShowDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	rect.right  = rect.left + cx;
	rect.bottom = rect.top + cy;
	if(m_SuperGrid.GetSafeHwnd())		m_SuperGrid.MoveWindow(rect);
	
	if(m_SuperGrid.m_InitializeGrid && m_SuperGrid.GetNumCol())
	{
		m_SuperGrid.SetColumnWidth(0, 6 * rect.Width() / 30);
		m_SuperGrid.SetColumnWidth(1, 2 * rect.Width() / 30);
		m_SuperGrid.SetColumnWidth(2, 2 * rect.Width() / 30);
		m_SuperGrid.SetColumnWidth(3, 5 * rect.Width() / 30);
		m_SuperGrid.SetColumnWidth(4, 4 * rect.Width() / 30);
		m_SuperGrid.SetColumnWidth(5, 20 * rect.Width() / 30);
	}
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InitGridColumn
// Param    :   CMySuperGrid& m_ListGrid
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CASFShowDlg::InitGridColumn()
{
	m_SuperGrid.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP, CRect(0,0,0,0),this,IDC_MYLISTCTRL);	
	CRect rect;
	GetClientRect(&rect);
	if(m_SuperGrid.GetSafeHwnd())		m_SuperGrid.MoveWindow(rect);
	m_SuperGrid.InitializeGrid();
	m_SuperGrid.ModifyStyleEx(0,WS_EX_CLIENTEDGE);

	LPTSTR lpszCols[] = {_T("Filed"),_T("Offset"), _T("TYPE"), _T("Data(HEX)"),_T("Data(SEPC)"),_T("DESC"), 0};
	LV_COLUMN   lvColumn;
	// 1)initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 100;
	for(int x = 0; lpszCols[x]!=NULL; x++)
    {
		//make the secondary columns smaller
		switch(x)
		{
		case 0:			lvColumn.cx = 6 * rect.Width() / 30; break;
		case 1:			lvColumn.cx = 2 * rect.Width() / 30; break;
		case 2:			lvColumn.cx = 2 * rect.Width() / 30; break;
		case 3:			lvColumn.cx = 5 * rect.Width() / 30; break;
		case 4:			lvColumn.cx = 4 * rect.Width() / 30; break;
		case 5:			lvColumn.cx = 30 * rect.Width() / 30; break;
		}
						
		lvColumn.pszText = lpszCols[x];
		m_SuperGrid.InsertColumn(x,&lvColumn);
    }
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::ReadAsfFile
// Param    :   LPCTSTR pszFileName
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL CASFShowDlg::ReadAsfFile(LPCTSTR pszFileName)
{
	if(pszFileName == NULL)		return FALSE;
	
	FILE *pFile = fopen(pszFileName, "rb");
	if(pFile == NULL)			return FALSE;
	
	DWORD dwReadCount = 0;
	DWORD dwAddress = 0x00000000;
	// 1:HeaderObject
	ASF_HeaderObject headeObject;
	memset(&headeObject, 0x00, sizeof(ASF_HeaderObject));
	dwReadCount = fread(&headeObject, 1, sizeof(ASF_HeaderObject), pFile);
	InsertHeaderObject(&headeObject, dwAddress);						// InsertHeaderObject

	// 2:Properties Object
	ASF_PropertiesObject propertiesObject;
	memset(&propertiesObject, 0x00, sizeof(ASF_PropertiesObject));
	dwReadCount = fread(&propertiesObject, 1, sizeof(ASF_PropertiesObject), pFile);
	InsertPropertiesObject(&propertiesObject, dwAddress);				// InsertPropertiesObject

	// 3:Clock Object
	ASF_ClockObject clockObj;
	memset(&clockObj, 0x00, sizeof(ASF_ClockObject));
	dwReadCount = fread(&clockObj, 1, sizeof(ASF_ClockObject), pFile);
	InsertClockObject(&clockObj, dwAddress);

	// 4:streamProperties Object
	for(int i = 0; i < 2; i++)
	{
		ASF_StreamPropertiesObject streamPropertiesObj;
		memset(&streamPropertiesObj, 0x00, sizeof(ASF_StreamPropertiesObject));
		dwReadCount = fread(&streamPropertiesObj, 1, sizeof(ASF_StreamPropertiesObject), pFile);
		CTreeItem_* pStreamProObjItem = InsertStreamPropertiesObject(&streamPropertiesObj, dwAddress);		// InsertStreamPropertiesObject
		// 4.1 TypeSpecificData/Audiomediatype
		DWORD128 streamType = streamPropertiesObj.StreamType;
		DWORD TypeSpecificDataLength = streamPropertiesObj.TypeSpecificDataLength;
		if(streamType == ASF_Audio_Media)
		{
			Audiomediatype audiomediatype;
			memset(&audiomediatype, 0x00, sizeof(Audiomediatype));
			dwReadCount = fread(&audiomediatype, 1, TypeSpecificDataLength, pFile);
			InsertAudiomediatype(&audiomediatype, dwAddress, pStreamProObjItem);
		}
		else if(streamType == ASF_Video_Media)
		{
			Videomediatype videomediatype;
			memset(&videomediatype, 0x00, sizeof(Videomediatype));
			dwReadCount = fread(&videomediatype, 1, TypeSpecificDataLength, pFile);
			InsertVideomediatype(&videomediatype, dwAddress, pStreamProObjItem);
		}
		else if(streamType == ASF_Command_Media)
		{
			if(TypeSpecificDataLength != 0 )	return FALSE;
		}
		else if(streamType == ASF_JFIF_Media)
		{	
			JFIF_JPEGmediatype jfif_jpegmediatype;
			memset(&jfif_jpegmediatype, 0x00, sizeof(JFIF_JPEGmediatype));
			dwReadCount = fread(&jfif_jpegmediatype, 1, TypeSpecificDataLength, pFile);
			InsertJFIF_JPEGmediatype(&jfif_jpegmediatype, dwAddress, pStreamProObjItem);
		}
		else if(streamType == ASF_Degradable_JPEG_Media)
		{	
			DegradableJPEGmediatype degradablejpegmediatype;
			memset(&degradablejpegmediatype, 0x00, sizeof(DegradableJPEGmediatype));
			dwReadCount = fread(&degradablejpegmediatype, 1, TypeSpecificDataLength, pFile);
			InsertDegradableJPEGmediatype(&degradablejpegmediatype, dwAddress, pStreamProObjItem);
		}
		else if(streamType == ASF_File_Transfer_Media)
		{	
			Filetransferandbinarymediatypes filetransferandbinarymediatypes;
			memset(&filetransferandbinarymediatypes, 0x00, sizeof(Filetransferandbinarymediatypes));
			dwReadCount = fread(&filetransferandbinarymediatypes, 1, sizeof(Filetransferandbinarymediatypes), pFile);
			CTreeItem_* pFiletransItem = InsertFiletransferandbinarymediatypes(&filetransferandbinarymediatypes, dwAddress, pStreamProObjItem);
			
			// Webstreams
			Webstreams webstreams;
			memset(&webstreams, 0x00, sizeof(Webstreams));
			dwReadCount = fread(&webstreams, 1, TypeSpecificDataLength - sizeof(Filetransferandbinarymediatypes), pFile);
			InsertWebstreams(&webstreams, dwAddress, pFiletransItem);
		}
		else if(streamType == ASF_Binary_Media)
		{	
			Filetransferandbinarymediatypes filetransferandbinarymediatypes;
			memset(&filetransferandbinarymediatypes, 0x00, sizeof(Filetransferandbinarymediatypes));
			dwReadCount = fread(&filetransferandbinarymediatypes, 1, TypeSpecificDataLength, pFile);
			InsertFiletransferandbinarymediatypes(&filetransferandbinarymediatypes, dwAddress, pStreamProObjItem);
		}
		else
		{
			fseek(pFile, TypeSpecificDataLength, SEEK_CUR);	// MoveForward
		}
		// 4.2 ErrorCorrectionType/	Spread audio
		DWORD128 ErrorCorrectionType = streamPropertiesObj.ErrorCorrectionType;
		DWORD ErrorCorrectionDataLength = streamPropertiesObj.ErrorCorrectionDataLength;
		if(ErrorCorrectionType == ASF_Audio_Spread)
		{
			Spreadaudio spreadaudio;
			memset(&spreadaudio, 0x00, sizeof(Spreadaudio));
			dwReadCount = fread(&spreadaudio, 1, ErrorCorrectionDataLength, pFile);
			InsertSpreadaudiotype(&spreadaudio, dwAddress, pStreamProObjItem);	
		}
		else if(streamType == ASF_No_Error_Correction)
		{
			fseek(pFile, ErrorCorrectionDataLength, SEEK_CUR);	// MoveForward
		}
	}
	// 5:InsertCodecListObject
	ASF_CodecListObject codeclistobject;
	memset(&codeclistobject, 0x00, sizeof(ASF_CodecListObject));
	dwReadCount = fread(&codeclistobject, 1, sizeof(ASF_CodecListObject), pFile);
	InsertCodecListObject(&codeclistobject, dwAddress, pFile);
	//6:
//	ASF_ScriptCommandObject scriptcommandobject(pFile);
//	InsertScriptCommandObject(&scriptcommandobject, dwAddress);
	//7:
//	ASF_IndexObject indexobject(pFile);
//	InsertIndexObject(&indexobject, dwAddress);
	//8:InsertDataObject
	ASF_DataObject dataobject(pFile);
	InsertDataObject(&dataobject, dwAddress);
	//9:InsertErrorcorrectiondata
	Errorcorrectiondata errorcorrectiondata(pFile);
	InsertErrorcorrectiondata(&errorcorrectiondata, dwAddress);

	fclose(pFile);
	return TRUE;
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertHeaderObject
// Param    :   ASF_HeaderObject* pHeaderObject
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szHeaderObjField[][MAX_PATH];
extern TCHAR g_szHeaderObjDesc[][MAX_PATH];
void CASFShowDlg::InsertHeaderObject(ASF_HeaderObject* pHeaderObject, DWORD& dwAddress)
{
	if(pHeaderObject == NULL)			return;

	// Main
	CTreeItem_* pHeaderObjItem = AddMainItem("Header Object", dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szHeaderObjField[0], dwAddress, ITEMVALUE(pHeaderObject->ObjectID), NULL, g_szHeaderObjDesc[0], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szHeaderObjField[1], dwAddress, ITEMVALUE(pHeaderObject->ObjectSize), NULL, g_szHeaderObjDesc[1], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szHeaderObjField[2], dwAddress, ITEMVALUE(pHeaderObject->dwHeaderObjectCount), NULL, g_szHeaderObjDesc[2], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szHeaderObjField[3], dwAddress, ITEMVALUE(pHeaderObject->Reserved1), NULL, g_szHeaderObjDesc[3], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szHeaderObjField[4], dwAddress, ITEMVALUE(pHeaderObject->Reserved2), NULL, g_szHeaderObjDesc[4], pHeaderObjItem, m_SuperGrid);
}


// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertPropertiesObject
// Param    :   ASF_PropertiesObject* pHeaderObject
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szPropertiesObjField[][MAX_PATH];
extern TCHAR g_szPropertiesObjDesc[][MAX_PATH*10];
void CASFShowDlg::InsertPropertiesObject(ASF_PropertiesObject* pPropertiesObject, DWORD& dwAddress)
{
	if(pPropertiesObject == NULL)			return;
	// Main
	CTreeItem_* pHeaderObjItem = AddMainItem("Properties Object", dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szPropertiesObjField[0], dwAddress, ITEMVALUE(pPropertiesObject->ObjectID), NULL, g_szPropertiesObjDesc[0], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[1], dwAddress, ITEMVALUE(pPropertiesObject->ObjectSize), NULL, g_szPropertiesObjDesc[1], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[2], dwAddress, ITEMVALUE(pPropertiesObject->FileIDGUID), NULL, g_szPropertiesObjDesc[2], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[3], dwAddress, ITEMVALUE(pPropertiesObject->FileSize), NULL, g_szPropertiesObjDesc[3], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[4], dwAddress, ITEMVALUE(pPropertiesObject->CreationDate.ddword64Value), FILETIMETOSTRING(pPropertiesObject->CreationDate.FileTime).GetBuffer(0), g_szPropertiesObjDesc[4], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[5], dwAddress, ITEMVALUE(pPropertiesObject->DataPacketsCount), NULL, g_szPropertiesObjDesc[5], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[6], dwAddress, ITEMVALUE(pPropertiesObject->PlayDuration), NULL, g_szPropertiesObjDesc[6], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[7], dwAddress, ITEMVALUE(pPropertiesObject->SendDuration), NULL, g_szPropertiesObjDesc[7], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[8], dwAddress, ITEMVALUE(pPropertiesObject->Preroll), NULL, g_szPropertiesObjDesc[8], pHeaderObjItem, m_SuperGrid);
	CTreeItem_* pFlagsItem = AddSubItem(g_szPropertiesObjField[9], dwAddress, ITEMVALUE(pPropertiesObject->Flags), NULL, g_szPropertiesObjDesc[9], pHeaderObjItem, m_SuperGrid);
	{
		DWORD dwAddressTemp = dwAddress;
		AddSubItem(g_szPropertiesObjField[10], dwAddressTemp, ITEMVALUE(BroadcastFlag(pPropertiesObject->Flags)), NULL, g_szPropertiesObjDesc[10], pFlagsItem, m_SuperGrid);
		AddSubItem(g_szPropertiesObjField[11], dwAddressTemp, ITEMVALUE(SeekableFlag(pPropertiesObject->Flags)), NULL, g_szPropertiesObjDesc[11], pFlagsItem, m_SuperGrid);
		AddSubItem(g_szPropertiesObjField[12], dwAddressTemp, ITEMVALUE(Reserved_PropertiesFlags(pPropertiesObject->Flags)), NULL, g_szPropertiesObjDesc[12], pFlagsItem, m_SuperGrid);

	}
	AddSubItem(g_szPropertiesObjField[13], dwAddress, ITEMVALUE(pPropertiesObject->MinDataPacketSize), NULL, g_szPropertiesObjDesc[13], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[14], dwAddress, ITEMVALUE(pPropertiesObject->MaxDataPacketSize), NULL, g_szPropertiesObjDesc[14], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szPropertiesObjField[15], dwAddress, ITEMVALUE(pPropertiesObject->MaxBitrate), NULL, g_szPropertiesObjDesc[15], pHeaderObjItem, m_SuperGrid);	
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertClockObject
// Param    :   ASF_ClockObject* pClocksObj
//              DWORD& dwAddress
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szClockObjectField [][MAX_PATH];
extern TCHAR g_szClockObjectDesc [][MAX_PATH];
void CASFShowDlg::InsertClockObject(ASF_ClockObject* pClocksObj, DWORD& dwAddress)
{
	if(pClocksObj == NULL)			return;
	// Main
	CTreeItem_* pHeaderObjItem = AddMainItem("Clock Object", dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szClockObjectField[0], dwAddress, ITEMVALUE(pClocksObj->ObjectID), NULL, g_szClockObjectDesc[0], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szClockObjectField[1], dwAddress, ITEMVALUE(pClocksObj->ObjectSize), NULL, g_szClockObjectDesc[1], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szClockObjectField[2], dwAddress, ITEMVALUE(pClocksObj->ClockType), NULL, g_szClockObjectDesc[2], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szClockObjectField[3], dwAddress, ITEMVALUE(pClocksObj->ClockSize), NULL, g_szClockObjectDesc[3], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szClockObjectField[4], dwAddress, ITEMVALUE(pClocksObj->ClockSpecificDataLength), NULL, g_szClockObjectDesc[4], pHeaderObjItem, m_SuperGrid);
}

// -----------------------------------------------------------//
// Function :   InsertStreamPropertiesObject
// Param    :   ASF_StreamPropertiesObject* pStreamPropertiesObj
//              DWORD& dwAddress
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szStreamPropertiesObjectField [][MAX_PATH];
extern TCHAR g_szStreamPropertiesObjectDesc [][MAX_PATH*10];
CTreeItem_* CASFShowDlg::InsertStreamPropertiesObject(ASF_StreamPropertiesObject* pStreamPropertiesObj, DWORD& dwAddress)
{
	if(pStreamPropertiesObj == NULL)			return NULL;
	// Main
	CTreeItem_* pHeaderObjItem = AddMainItem("Stream Properties Object", dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szStreamPropertiesObjectField[0], dwAddress, ITEMVALUE(pStreamPropertiesObj->ObjectID), NULL, g_szStreamPropertiesObjectDesc[0], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[1], dwAddress, ITEMVALUE(pStreamPropertiesObj->ObjectSize), NULL, g_szStreamPropertiesObjectDesc[1], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[2], dwAddress, ITEMVALUE(pStreamPropertiesObj->StreamType), NULL, g_szStreamPropertiesObjectDesc[2], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[3], dwAddress, ITEMVALUE(pStreamPropertiesObj->ErrorCorrectionType), NULL, g_szStreamPropertiesObjectDesc[3], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[4], dwAddress, ITEMVALUE(pStreamPropertiesObj->TimeOffset), NULL, g_szPropertiesObjDesc[4], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[5], dwAddress, ITEMVALUE(pStreamPropertiesObj->TypeSpecificDataLength), NULL, g_szStreamPropertiesObjectDesc[5], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szStreamPropertiesObjectField[6], dwAddress, ITEMVALUE(pStreamPropertiesObj->ErrorCorrectionDataLength), NULL, g_szStreamPropertiesObjectDesc[6], pHeaderObjItem, m_SuperGrid);
	CTreeItem_* pFlagsItem = AddSubItem(g_szStreamPropertiesObjectField[7], dwAddress, ITEMVALUE(pStreamPropertiesObj->Flags), NULL, g_szStreamPropertiesObjectDesc[7], pHeaderObjItem, m_SuperGrid);
	{
		DWORD dwAddressTemp = dwAddress;
		AddSubItem(g_szStreamPropertiesObjectField[8], dwAddressTemp, ITEMVALUE(StreamNumber_Flags(pStreamPropertiesObj->Flags)), NULL, g_szStreamPropertiesObjectDesc[8], pFlagsItem, m_SuperGrid);
		AddSubItem(g_szStreamPropertiesObjectField[9], dwAddressTemp, ITEMVALUE(Reserved_Flags(pStreamPropertiesObj->Flags)), NULL, g_szStreamPropertiesObjectDesc[9], pFlagsItem, m_SuperGrid);
		AddSubItem(g_szStreamPropertiesObjectField[10], dwAddressTemp, ITEMVALUE(EncryptedContentFlag(pStreamPropertiesObj->Flags)), NULL, g_szStreamPropertiesObjectDesc[10], pFlagsItem, m_SuperGrid);
	}
	AddSubItem(g_szStreamPropertiesObjectField[11], dwAddress, ITEMVALUE(pStreamPropertiesObj->Reserved), NULL, g_szStreamPropertiesObjectDesc[11], pHeaderObjItem, m_SuperGrid);
//	AddSubItem(g_szStreamPropertiesObjectField[12], dwAddress, ITEMVALUE(pStreamPropertiesObj->TypeSpecificData), NULL, g_szStreamPropertiesObjectDesc[12], pHeaderObjItem, m_SuperGrid);
//	AddSubItem(g_szStreamPropertiesObjectField[13], dwAddress, ITEMVALUE(pStreamPropertiesObj->ErrorCorrectionData), NULL, g_szStreamPropertiesObjectDesc[13], pHeaderObjItem, m_SuperGrid);

	return pHeaderObjItem;
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertAudiomediatype
// Param    :   Audiomediatype* pStreamPropertiesObj
//              DWORD& dwAddress
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szAudiomediatypeField [][MAX_PATH];
extern TCHAR g_szAudiomediatypeDesc [][MAX_PATH];
void CASFShowDlg::InsertAudiomediatype(Audiomediatype* pAudiomediatype, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pAudiomediatype == NULL)			return; 
	// Main
	CTreeItem_* pHeaderObjItem = AddSubMainItem("Audio media type", "Audio media type", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szAudiomediatypeField[0], dwAddress, ITEMVALUE(pAudiomediatype->CodecID), NULL, g_szAudiomediatypeDesc[0], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[1], dwAddress, ITEMVALUE(pAudiomediatype->NumberofChannels), NULL, g_szAudiomediatypeDesc[1], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[2], dwAddress, ITEMVALUE(pAudiomediatype->SamplesPerSecond), NULL, g_szAudiomediatypeDesc[2], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[3], dwAddress, ITEMVALUE(pAudiomediatype->AverageNumberofBytesPerSecond), NULL, g_szAudiomediatypeDesc[3], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[4], dwAddress, ITEMVALUE(pAudiomediatype->BlockAlignment), NULL, g_szAudiomediatypeDesc[4], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[5], dwAddress, ITEMVALUE(pAudiomediatype->BitsPerSample), NULL, g_szAudiomediatypeDesc[5], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[6], dwAddress, ITEMVALUE(pAudiomediatype->CodecSpecificDataSize), NULL, g_szAudiomediatypeDesc[6], pHeaderObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[7], dwAddress, ITEMVALUE(pAudiomediatype->CodecSpecificData), NULL, g_szAudiomediatypeDesc[7], pHeaderObjItem, m_SuperGrid);
}

// -----------------------------------------------------------//
// Function :   InsertVideomediatype
// Param    :   Videomediatype* pVideomediatype
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
TCHAR g_szVideomediatypeField [][MAX_PATH];
TCHAR g_szVideomediatypeDesc [][MAX_PATH*2]; 
void CASFShowDlg::InsertVideomediatype(Videomediatype* pVideomediatype, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pVideomediatype == NULL)			return;
	// Main
	CTreeItem_* pVideomediatypeItem = AddSubMainItem("Video media type", "Video media type", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szVideomediatypeField[0], dwAddress, ITEMVALUE(pVideomediatype->EncodedImageWidth), NULL, g_szVideomediatypeDesc[0], pVideomediatypeItem, m_SuperGrid);
	AddSubItem(g_szVideomediatypeField[1], dwAddress, ITEMVALUE(pVideomediatype->EncodedImageHeight), NULL, g_szVideomediatypeDesc[1], pVideomediatypeItem, m_SuperGrid);
	AddSubItem(g_szVideomediatypeField[2], dwAddress, ITEMVALUE(pVideomediatype->ReservedFlags), NULL, g_szVideomediatypeDesc[2], pVideomediatypeItem, m_SuperGrid);
	AddSubItem(g_szVideomediatypeField[3], dwAddress, ITEMVALUE(pVideomediatype->FormatDataSize), NULL, g_szVideomediatypeDesc[3], pVideomediatypeItem, m_SuperGrid);

	CTreeItem_* pBitmapInfoItem = AddSubMainItem(g_szVideomediatypeField[4], g_szVideomediatypeDesc[4], dwAddress,  pVideomediatypeItem, m_SuperGrid);
	{
		DWORD dwAddressTemp = dwAddress;
		AddSubItem(g_szVideomediatypeField[5], dwAddressTemp, ITEMVALUE(pVideomediatype->_FormatDataSize), NULL, g_szVideomediatypeDesc[5], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[6], dwAddressTemp, ITEMVALUE(pVideomediatype->ImageWidth), NULL, g_szVideomediatypeDesc[6], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[7], dwAddressTemp, ITEMVALUE(pVideomediatype->ImageHeight), NULL, g_szVideomediatypeDesc[7], pBitmapInfoItem, m_SuperGrid);
		
		AddSubItem(g_szVideomediatypeField[8], dwAddressTemp, ITEMVALUE(pVideomediatype->Reserved), NULL, g_szVideomediatypeDesc[8], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[9], dwAddressTemp, ITEMVALUE(pVideomediatype->BitsPerPixelCount), NULL, g_szVideomediatypeDesc[9], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[10], dwAddressTemp, ITEMVALUE(pVideomediatype->CompressionID), NULL, g_szVideomediatypeDesc[10], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[11], dwAddressTemp, ITEMVALUE(pVideomediatype->ImageSize), NULL, g_szVideomediatypeDesc[11], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[12], dwAddressTemp, ITEMVALUE(pVideomediatype->HorizontalPixelsPerMeter), NULL, g_szVideomediatypeDesc[12], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[13], dwAddressTemp, ITEMVALUE(pVideomediatype->VerticalPixelsPerMeter), NULL, g_szVideomediatypeDesc[13], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[14], dwAddressTemp, ITEMVALUE(pVideomediatype->ColorsUsedCount), NULL, g_szVideomediatypeDesc[14], pBitmapInfoItem, m_SuperGrid);
		AddSubItem(g_szVideomediatypeField[15], dwAddressTemp, ITEMVALUE(pVideomediatype->ImportantColorsCount), NULL, g_szVideomediatypeDesc[15], pBitmapInfoItem, m_SuperGrid);
	}
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::IInsertJFIF_JPEGmediatype
// Param    :   JFIF_JPEGmediatype* pJFIF_JPEGmediatype
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szJFIF_JPEGmediatypeField [][MAX_PATH] ;
extern TCHAR g_szJFIF_JPEGmediatypeDesc [][MAX_PATH];
void CASFShowDlg::InsertJFIF_JPEGmediatype(JFIF_JPEGmediatype* pJFIF_JPEGmediatype, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pJFIF_JPEGmediatype == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddSubMainItem("JFIFJPEG media type", "JFIF_JPEGmediatype", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szAudiomediatypeField[0], dwAddress, ITEMVALUE(pJFIF_JPEGmediatype->Imagewidth), NULL, g_szAudiomediatypeDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[1], dwAddress, ITEMVALUE(pJFIF_JPEGmediatype->Imageheight), NULL, g_szAudiomediatypeDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szAudiomediatypeField[2], dwAddress, ITEMVALUE(pJFIF_JPEGmediatype->Reserved), NULL, g_szAudiomediatypeDesc[2], pSubParentObjItem, m_SuperGrid);

}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::IInsertDegradableJPEGmediatype
// Param    :   DegradableJPEGmediatype* pDegradableJPEGmediatype
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szDegradableJPEGmediatypeField [][MAX_PATH];
extern TCHAR g_szDegradableJPEGmediatypeDesc [][MAX_PATH] ;
void CASFShowDlg::InsertDegradableJPEGmediatype(DegradableJPEGmediatype* pDegradableJPEGmediatype, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pDegradableJPEGmediatype == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddSubMainItem("JFIFJPEG media type", "JFIF_JPEGmediatype", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szDegradableJPEGmediatypeField[0], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Imagewidth), NULL, g_szDegradableJPEGmediatypeDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDegradableJPEGmediatypeField[1], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Imageheight), NULL, g_szDegradableJPEGmediatypeDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDegradableJPEGmediatypeField[2], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Reserved1), NULL, g_szDegradableJPEGmediatypeDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDegradableJPEGmediatypeField[3], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Reserved2), NULL, g_szDegradableJPEGmediatypeDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDegradableJPEGmediatypeField[4], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Reserved3), NULL, g_szDegradableJPEGmediatypeDesc[4], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDegradableJPEGmediatypeField[5], dwAddress, ITEMVALUE(pDegradableJPEGmediatype->Interchangedatalength), NULL, g_szDegradableJPEGmediatypeDesc[5], pSubParentObjItem, m_SuperGrid);

}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertFiletransferandbinarymediatypes
// Param    :   Filetransferandbinarymediatypes* pFiletransferandbinarymediatypes
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szFiletransferandbinarymediatypesField [][MAX_PATH] ;
extern TCHAR g_szFiletransferandbinarymediatypesDesc [][MAX_PATH*2] ;
CTreeItem_*  CASFShowDlg::InsertFiletransferandbinarymediatypes(Filetransferandbinarymediatypes* pFiletransferandbinarymediatypes, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pFiletransferandbinarymediatypes == NULL)			return NULL; 
	// Main
	CTreeItem_* pSubParentObjItem = AddSubMainItem("File transfer and binary media types", "File transfer and binary media types", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szFiletransferandbinarymediatypesField[0], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->mediatype), NULL, g_szFiletransferandbinarymediatypesDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[1], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Mediasubtype), NULL, g_szFiletransferandbinarymediatypesDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[2], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Fixedsizesamples), NULL, g_szFiletransferandbinarymediatypesDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[3], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Temporalcompression), NULL, g_szFiletransferandbinarymediatypesDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[4], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Samplesize), NULL, g_szFiletransferandbinarymediatypesDesc[4], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[5], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Formattype), NULL, g_szFiletransferandbinarymediatypesDesc[5], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szFiletransferandbinarymediatypesField[6], dwAddress, ITEMVALUE(pFiletransferandbinarymediatypes->Formatdatasize), NULL, g_szFiletransferandbinarymediatypesDesc[6], pSubParentObjItem, m_SuperGrid);

	return pSubParentObjItem;
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertWebstreams
// Param    :   Webstreams* pWebstreams
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szWebstreamField[][MAX_PATH] ;
extern TCHAR g_szmediaobjectsForWebstreamField [][MAX_PATH];
extern TCHAR g_szWebstreamDesc [][MAX_PATH];
extern TCHAR g_szmediaobjectsForWebstreamDesc [][MAX_PATH];
void CASFShowDlg::InsertWebstreams(Webstreams* pWebstreams, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pWebstreams == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddSubMainItem("Web stream", "Web stream", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szWebstreamField[0], dwAddress, ITEMVALUE(pWebstreams->Webstreamformatdatasize), NULL, g_szmediaobjectsForWebstreamField[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szWebstreamField[1], dwAddress, ITEMVALUE(pWebstreams->Fixedsampleheadersize), NULL, g_szmediaobjectsForWebstreamField[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szWebstreamField[2], dwAddress, ITEMVALUE(pWebstreams->Versionnumber), NULL, g_szmediaobjectsForWebstreamField[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szWebstreamField[3], dwAddress, ITEMVALUE(pWebstreams->Reserved), NULL, g_szmediaobjectsForWebstreamField[3], pSubParentObjItem, m_SuperGrid);
	
	AddSubItem(g_szmediaobjectsForWebstreamField[0], dwAddress, ITEMVALUE(pWebstreams->mediaobjects.Totalheaderlength), NULL, g_szmediaobjectsForWebstreamDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szmediaobjectsForWebstreamField[1], dwAddress, ITEMVALUE(pWebstreams->mediaobjects.Partnumber), NULL, g_szmediaobjectsForWebstreamDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szmediaobjectsForWebstreamField[2], dwAddress, ITEMVALUE(pWebstreams->mediaobjects.Totalpartcount), NULL, g_szmediaobjectsForWebstreamDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szmediaobjectsForWebstreamField[3], dwAddress, ITEMVALUE(pWebstreams->mediaobjects.Sampletype), NULL, g_szmediaobjectsForWebstreamDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szmediaobjectsForWebstreamField[4], dwAddress, ITEMVALUE(pWebstreams->mediaobjects.URLstring), NULL, g_szmediaobjectsForWebstreamDesc[4], pSubParentObjItem, m_SuperGrid);
	
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertSpreadaudiotype
// Param    :   Spreadaudio* pSpreadaudio
//              DWORD& dwAddress
//              CTreeItem_* Parent
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern  TCHAR g_szSpreadaudioField [][MAX_PATH];
extern  TCHAR g_szSpreadaudioDesc [][MAX_PATH];
void CASFShowDlg::InsertSpreadaudiotype(Spreadaudio* pSpreadaudio, DWORD& dwAddress, CTreeItem_* Parent)
{
	if(pSpreadaudio == NULL)			return; 
	// Main
	CTreeItem_* pSpreadaudioItem = AddSubMainItem("Spread audio type", "Spread audio type", dwAddress, Parent, m_SuperGrid);
	// Sub
	AddSubItem(g_szSpreadaudioField[0], dwAddress, ITEMVALUE(pSpreadaudio->Span), NULL, g_szSpreadaudioDesc[0], pSpreadaudioItem, m_SuperGrid);
	AddSubItem(g_szSpreadaudioField[1], dwAddress, ITEMVALUE(pSpreadaudio->VirtualPacketLength), NULL, g_szSpreadaudioDesc[1], pSpreadaudioItem, m_SuperGrid);
	AddSubItem(g_szSpreadaudioField[2], dwAddress, ITEMVALUE(pSpreadaudio->VirtualChunkLength), NULL, g_szSpreadaudioDesc[2], pSpreadaudioItem, m_SuperGrid);
	AddSubItem(g_szSpreadaudioField[3], dwAddress, ITEMVALUE(pSpreadaudio->SilenceDataLength), NULL, g_szSpreadaudioDesc[3], pSpreadaudioItem, m_SuperGrid);
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertCodecListObject
// Param    :   ASF_CodecListObject* pCodecListObject
//              DWORD& dwAddress
//              FILE* pFile
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
//ASF_HeaderExtensionObject
extern  TCHAR g_szCodecListObjectField [][MAX_PATH];
extern TCHAR g_szCodecListObjectDesc [][MAX_PATH];
extern TCHAR g_szCodecEntriesField [][MAX_PATH];
extern TCHAR g_szCodecEntriesDesc [][MAX_PATH];
void CASFShowDlg::InsertCodecListObject(ASF_CodecListObject* pCodecListObject, DWORD& dwAddress,  FILE* pFile)
{
	if(pCodecListObject == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddMainItem("Codec List Object",  dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szCodecListObjectField[0], dwAddress, ITEMVALUE(pCodecListObject->ObjectID), NULL, g_szCodecListObjectDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szCodecListObjectField[1], dwAddress, ITEMVALUE(pCodecListObject->ObjectSize), NULL, g_szCodecListObjectDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szCodecListObjectField[2], dwAddress, ITEMVALUE(pCodecListObject->Reserved), NULL, g_szCodecListObjectDesc[2], pSubParentObjItem, m_SuperGrid);
	CTreeItem_* pEntryItem = AddSubItem(g_szCodecListObjectField[3], dwAddress, ITEMVALUE(pCodecListObject->CodecEntriesCount), NULL, g_szCodecListObjectDesc[3], pSubParentObjItem, m_SuperGrid);
	for(DWORD i = 0; i < pCodecListObject->CodecEntriesCount; i++)
	{
		CTreeItem_* pSubEntryItem = AddSubMainItem(INDEX(i), NULL, dwAddress,  pEntryItem, m_SuperGrid);
		
		CodecEntries entry(pFile);
		AddSubItem(g_szCodecEntriesField[0], dwAddress, ITEMVALUE(entry.Type), NULL, g_szCodecEntriesDesc[0], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[1], dwAddress, ITEMVALUE(entry.CodecNameLength), NULL, g_szCodecEntriesDesc[1], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[2], dwAddress, ITEMVALUE(entry.wszCodecName), NULL, g_szCodecEntriesDesc[2], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[3], dwAddress, ITEMVALUE(entry.CodecDescriptionLength), NULL, g_szCodecEntriesDesc[3], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[4], dwAddress, ITEMVALUE(entry.wszCodecDescription), NULL, g_szCodecEntriesDesc[4], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[5], dwAddress, ITEMVALUE(entry.CodecInformationLength), NULL, g_szCodecEntriesDesc[5], pSubEntryItem, m_SuperGrid);
		AddSubItem(g_szCodecEntriesField[6], dwAddress, ITEMVALUE(entry.bszCodecInformation), NULL, g_szCodecEntriesDesc[6], pSubEntryItem, m_SuperGrid);
	
	}
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertScriptCommandObject
// Param    :   ASF_ScriptCommandObject* pScriptCommandObject
//              DWORD& dwAddress
//              FILE* pFile
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szScriptCommandObjectField [][MAX_PATH];
extern TCHAR g_szScriptCommandObjectDesc [][MAX_PATH];
void CASFShowDlg::InsertScriptCommandObject(ASF_ScriptCommandObject* pScriptCommandObject, DWORD& dwAddress)
{
	if(pScriptCommandObject == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddMainItem("Script Command Object",  dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szScriptCommandObjectField[0], dwAddress, ITEMVALUE(pScriptCommandObject->ObjectID), NULL, g_szScriptCommandObjectDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szScriptCommandObjectField[1], dwAddress, ITEMVALUE(pScriptCommandObject->ObjectSize), NULL, g_szScriptCommandObjectDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szScriptCommandObjectField[2], dwAddress, ITEMVALUE(pScriptCommandObject->Reserved), NULL, g_szScriptCommandObjectDesc[2], pSubParentObjItem, m_SuperGrid);
	CTreeItem_* pCommandsItem = AddSubItem(g_szScriptCommandObjectField[3], dwAddress, ITEMVALUE(pScriptCommandObject->CommandsCount), NULL, g_szScriptCommandObjectDesc[3], pSubParentObjItem, m_SuperGrid);
	CTreeItem_* pCommandTypesItem = AddSubItem(g_szScriptCommandObjectField[4], dwAddress, ITEMVALUE(pScriptCommandObject->CommandTypesCount), NULL, g_szScriptCommandObjectDesc[4], pSubParentObjItem, m_SuperGrid);
	for(DWORD i = 0; i < pScriptCommandObject->CommandTypesCount; i++)
	{
		CTreeItem_* pSubCommandsTypeItem = AddSubMainItem(INDEX(i), NULL, dwAddress,  pCommandTypesItem, m_SuperGrid);
		CommandTypesstruct commandtypesstruct = pScriptCommandObject->pCommandTypesstruct[i];
		
		AddSubItem(g_szScriptCommandObjectField[5], dwAddress, ITEMVALUE(commandtypesstruct.PresentationTime), NULL, g_szScriptCommandObjectField[5], pSubCommandsTypeItem, m_SuperGrid);
		AddSubItem(g_szScriptCommandObjectField[6], dwAddress, ITEMVALUE(commandtypesstruct.TypeIndex), NULL, g_szScriptCommandObjectField[6], pSubCommandsTypeItem, m_SuperGrid);
		AddSubItem(g_szScriptCommandObjectField[7], dwAddress, ITEMVALUE(commandtypesstruct.CommandNameLength), NULL, g_szScriptCommandObjectField[7], pSubCommandsTypeItem, m_SuperGrid);
		AddSubItem(g_szScriptCommandObjectField[8], dwAddress, ITEMVALUE(commandtypesstruct.wszCommandName), NULL, g_szScriptCommandObjectField[8], pSubCommandsTypeItem, m_SuperGrid);
		
	}
	for(i = 0; i < pScriptCommandObject->CommandsCount; i++)
	{
		CTreeItem_* pSubCommandsItem = AddSubMainItem(INDEX(i), NULL, dwAddress,  pCommandsItem, m_SuperGrid);
		Commandstruct commandstruct = pScriptCommandObject->pCommandstruct[i];

		AddSubItem(g_szScriptCommandObjectField[9], dwAddress, ITEMVALUE(commandstruct.CommandTypeNameLength), NULL, g_szScriptCommandObjectField[9], pSubCommandsItem, m_SuperGrid);
		AddSubItem(g_szScriptCommandObjectField[10], dwAddress, ITEMVALUE(commandstruct.wszCommandTypeName), NULL, g_szScriptCommandObjectField[10], pSubCommandsItem, m_SuperGrid);
	}
}

// -----------------------------------------------------------//
// Function :   CASFShowDlg::InsertIndexObject
// Param    :   ASF_IndexObject* pIndexObject
//              DWORD& dwAddress
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
extern TCHAR g_szIndexObjectField [][MAX_PATH];
extern TCHAR g_szIndexObjectDesc [][MAX_PATH*2];
void CASFShowDlg::InsertIndexObject(ASF_IndexObject* pIndexObject, DWORD& dwAddress)
{
	if(pIndexObject == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddMainItem("Index Object",  dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szIndexObjectField[0], dwAddress, ITEMVALUE(pIndexObject->ObjectID), NULL, g_szIndexObjectDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szIndexObjectField[1], dwAddress, ITEMVALUE(pIndexObject->ObjectSize), NULL, g_szIndexObjectDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szIndexObjectField[2], dwAddress, ITEMVALUE(pIndexObject->FileID), NULL, g_szIndexObjectDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szIndexObjectField[3], dwAddress, ITEMVALUE(pIndexObject->IndexEntryTimeInterval), NULL, g_szIndexObjectDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szIndexObjectField[4], dwAddress, ITEMVALUE(pIndexObject->MaximumPacketCount), NULL, g_szIndexObjectDesc[4], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szIndexObjectField[5], dwAddress, ITEMVALUE(pIndexObject->IndexEntriesCount), NULL, g_szIndexObjectDesc[5], pSubParentObjItem, m_SuperGrid);

	for(DWORD i = 0; i < pIndexObject->IndexEntriesCount; i++)
	{
		CTreeItem_* pSubItem = AddSubMainItem(INDEX(i), NULL, dwAddress,  pSubParentObjItem, m_SuperGrid);
		IndexEntries indexentries = pIndexObject->pIndexEntries[i];
		
		AddSubItem(g_szIndexObjectField[6], dwAddress, ITEMVALUE(indexentries.PacketCount), NULL, g_szIndexObjectDesc[6], pSubItem, m_SuperGrid);
		AddSubItem(g_szIndexObjectField[7], dwAddress, ITEMVALUE(indexentries.PacketNumber), NULL, g_szIndexObjectDesc[7], pSubItem, m_SuperGrid);
	}
}

extern TCHAR g_szDataObjectField [][MAX_PATH];
extern TCHAR g_szDataObjectDesc [][MAX_PATH*2];
void CASFShowDlg::InsertDataObject(ASF_DataObject* pDataObject, DWORD& dwAddress)
{
	if(pDataObject == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddMainItem("Data Object",  dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szDataObjectField[0], dwAddress, ITEMVALUE(pDataObject->ObjectID), NULL, g_szDataObjectDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDataObjectField[1], dwAddress, ITEMVALUE(pDataObject->ObjectSize), NULL, g_szDataObjectDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDataObjectField[2], dwAddress, ITEMVALUE(pDataObject->FileID), NULL, g_szDataObjectDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDataObjectField[3], dwAddress, ITEMVALUE(pDataObject->TotalDataPackets), NULL, g_szDataObjectDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szDataObjectField[4], dwAddress, ITEMVALUE(pDataObject->Reserved), NULL, g_szDataObjectDesc[4], pSubParentObjItem, m_SuperGrid);
	CTreeItem_* pSubItem = AddSubMainItem(g_szDataObjectField[5], NULL, dwAddress,  pSubParentObjItem, m_SuperGrid);
//	for(DWORD i = 0; i < pDataObject->; i++)
//	{
//		CTreeItem_* pSubItem = AddSubMainItem(INDEX(i), NULL, dwAddress,  pSubParentObjItem, m_SuperGrid);
//		IndexEntries indexentries = pIndexObject->pIndexEntries[i];
//		
//		AddSubItem(g_szIndexObjectField[6], dwAddress, ITEMVALUE(indexentries.PacketCount), NULL, g_szIndexObjectDesc[6], pSubItem, m_SuperGrid);
//		AddSubItem(g_szIndexObjectField[7], dwAddress, ITEMVALUE(indexentries.PacketNumber), NULL, g_szIndexObjectDesc[7], pSubItem, m_SuperGrid);
//	}
}

extern TCHAR g_szErrorcorrectiondataField [][MAX_PATH];
extern TCHAR g_szErrorcorrectiondataDesc [][MAX_PATH*2];
void CASFShowDlg::InsertErrorcorrectiondata(Errorcorrectiondata* pErrorcorrectiondata, DWORD& dwAddress)
{
	if(pErrorcorrectiondata == NULL)			return; 
	// Main
	CTreeItem_* pSubParentObjItem = AddMainItem("Error correction data",  dwAddress, m_SuperGrid);
	// Sub
	AddSubItem(g_szErrorcorrectiondataField[0], dwAddress, ITEMVALUE(pErrorcorrectiondata->ErrorCorrectionFlags), NULL, g_szErrorcorrectiondataDesc[0], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szErrorcorrectiondataField[1], dwAddress, ITEMVALUE(ErrorCorrectionDataLength(pErrorcorrectiondata->ErrorCorrectionFlags)), NULL, g_szErrorcorrectiondataDesc[1], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szErrorcorrectiondataField[2], dwAddress, ITEMVALUE(OpaqueDataPresent(pErrorcorrectiondata->ErrorCorrectionFlags)), NULL, g_szErrorcorrectiondataDesc[2], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szErrorcorrectiondataField[3], dwAddress, ITEMVALUE(ErrorCorrectionLengthType(pErrorcorrectiondata->ErrorCorrectionFlags)), NULL, g_szErrorcorrectiondataDesc[3], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szErrorcorrectiondataField[4], dwAddress, ITEMVALUE(ErrorCorrectionPresent(pErrorcorrectiondata->ErrorCorrectionFlags)), NULL, g_szErrorcorrectiondataDesc[4], pSubParentObjItem, m_SuperGrid);
	AddSubItem(g_szErrorcorrectiondataField[5], dwAddress, ITEMVALUE(pErrorcorrectiondata->pErrorCorrectionData), NULL, g_szErrorcorrectiondataDesc[5], pSubParentObjItem, m_SuperGrid);
	
}