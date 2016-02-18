// SimpleEmailView.cpp : implementation of the CSimpleEmailView class
//

#include "stdafx.h"
#include "SimpleEmail.h"
#include "SimpleEmailDoc.h"
#include "SimpleEmailView.h"
#include "InternetAccounts.h"
#include "MailUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int				g_AccountSize;			// account size
extern vector<Account>	g_AccountVector;		// account
extern int				g_UserSize;				// recvUser Size
extern set<CString>		g_userSet;				// recvUser
/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView
IMPLEMENT_DYNCREATE(CSimpleEmailView, CView)

BEGIN_MESSAGE_MAP(CSimpleEmailView, CView)
	//{{AFX_MSG_MAP(CSimpleEmailView)
	ON_COMMAND(ID_MENUITEM_ACCOUNT, OnMenuitemAccount)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_SEND, OnEditSend)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView construction/destruction
CSimpleEmailView::CSimpleEmailView()
{
	// TODO: add construction code here
}

CSimpleEmailView::~CSimpleEmailView()
{
}

BOOL CSimpleEmailView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.cx = VIEW_WID;
//	cs.cy = VIEW_HEI;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView drawing
void CSimpleEmailView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView printing
BOOL CSimpleEmailView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimpleEmailView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimpleEmailView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView diagnostics

#ifdef _DEBUG
void CSimpleEmailView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleEmailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleEmailDoc* CSimpleEmailView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleEmailDoc)));
	return (CSimpleEmailDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpleEmailView message handlers
// -----------------------------------------------------------//
// Function :   CSimpleEmailView::OnInitialUpdate
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	InitInstance();
	
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailView::InitInstance
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailView::InitInstance()
{
	CSimpleEmailDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->InitInstance();
	}

	m_SendMailDlg.InitInstance();
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailView::OnCreate
// Param    :   LPCREATESTRUCT lpCreateStruct
// Return   :   int
// Comment  :   
// -----------------------------------------------------------//
int CSimpleEmailView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->cx = VIEW_WID ;
	lpCreateStruct->cy = VIEW_HEI;
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_SendMailDlg.Create(this, IDD_DIALOG_SENDMAIL		,
		WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_TOOLTIPS|CBRS_GRIPPER|CBRS_FLYBY, 
	IDD_DIALOG_SENDMAIL);
	CRect rect(0, 0, VIEW_WID, VIEW_HEI);
	m_SendMailDlg.SetWindowPos(NULL, 0, 0, VIEW_WID, VIEW_HEI, SWP_NOMOVE|SWP_NOZORDER);
	m_SendMailDlg.ShowWindow(SW_SHOW);

	return 0;
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailView::OnSize
// Param    :   UINT nType
//              int cx
//              int cy
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	m_SendMailDlg.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE|SWP_NOZORDER);
}
// -----------------------------------------------------------//
// Function :   CSimpleEmailView::OnMenuitemAccount
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailView::OnMenuitemAccount() 
{
	CInternetAccounts accountInfoDlg(this);
	accountInfoDlg.DoModal();
	CSimpleEmailDoc* pDoc = GetDocument();
	if(pDoc)
	{
		pDoc->Update();
		m_SendMailDlg.FlushServerInfo();
	}
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailView::OnEditSend
// Return   :   void
// Comment  :   
// -----------------------------------------------------------//
void CSimpleEmailView::OnEditSend() 
{
	Account* pAccount = m_SendMailDlg.GetEmailServerAccount();		// account
	CString strTo = m_SendMailDlg.GetEmailTO();						// to
	CString strCC = m_SendMailDlg.GetEmailCC();						// cc
	CString strBCC = m_SendMailDlg.GetEmailBCC();					// bcc
	CString strSubject = m_SendMailDlg.GetEmailSubject();			// subject
	CArray<TEXTINFO, TEXTINFO> textArr;
	m_SendMailDlg.GetEmailText(textArr);							// textArr
	CStringArray& fileArr = m_SendMailDlg.GetEmailFileArr();		// file

	// prepare
	BOOL bSendText = TRUE;
	BOOL bSendFile = (fileArr.GetSize() != 0); 
	SOCKET sock = PrepareSendEmail(pAccount);	
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] Start
//	if(sock == INVALID_SOCKET)																		return;
//	if(MailAuthLogin(sock, pAccount) == FALSE)														return;
//	if(MailFromTo(sock, CString(pAccount->szE_mailAddress), strTo, strCC, strBCC) == FALSE)			return;
//	if(MailBegin(sock, pAccount, strTo, strCC, strBCC, strSubject, bSendText, bSendFile) == FALSE)	return;
	if(sock == INVALID_SOCKET)																		
	{
		ReleaseSock(sock);
		return;
	}
	if(MailAuthLogin(sock, pAccount) == FALSE)														
	{
		ReleaseSock(sock);
		return;
	}
	if(MailFromTo(sock, CString(pAccount->szE_mailAddress), strTo, strCC, strBCC) == FALSE)			
	{
		ReleaseSock(sock);
		return;
	}
	if(MailBegin(sock, pAccount, strTo, strCC, strBCC, strSubject, bSendText, bSendFile) == FALSE)	
	{
		ReleaseSock(sock);
		return;
	}
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] End
	if(bSendText)
	{
//		MailText(sock, strText);
		MailTextArr(sock, textArr);
	}
	if(bSendFile)
	{
		MailFile(sock, fileArr);
	}
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] Start
//	if(MailEnd(sock) == FALSE)																		return;	
	if(MailEnd(sock) == FALSE)																		
	{
		ReleaseSock(sock);
		return;
	}
// 2015.03.03 Ver10.9.0.2 [Menu/Send Mail Failed] End
	CStringArray recvUserArr;
	SplitString(strTo, recvUserArr, SPLITCHAR);
	SplitString(strCC, recvUserArr, SPLITCHAR);
	SplitString(strBCC, recvUserArr, SPLITCHAR);
	
	for(int i = 0; i < recvUserArr.GetSize(); i++)
	{
		g_userSet.insert(recvUserArr.GetAt(i));
	}

	ReleaseSock(sock);
}

// -----------------------------------------------------------//
// Function :   CSimpleEmailView::PreTranslateMessage
// Param    :   MSG* pMsg
// Return   :   BOOL
// Comment  :   ESC:exit  CTRL+S:Send
// -----------------------------------------------------------//
#define VK_S	0x41 + 'S' - 'A'
BOOL CSimpleEmailView::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)  
    {  
        switch(pMsg->wParam)  
        {  
		case VK_ESCAPE: 
			::SendMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			return true;  
//		case VK_RETURN:  
//			OnEditSend();
//			return true;  
		default:  
			;  
        }  
    }  
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		HACCEL haccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
		if(haccel && TranslateAccelerator(m_hWnd, haccel, pMsg))
		{
			if(pMsg->wParam == VK_S)
			{
				OnEditSend();
				return true;  
			}
		}
	}

	return CView::PreTranslateMessage(pMsg);
}
