// SaoleiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Saolei.h"
#include "SaoleiDlg.h"

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
// CSaoleiDlg dialog

CSaoleiDlg::CSaoleiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaoleiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaoleiDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaoleiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaoleiDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSaoleiDlg, CDialog)
	//{{AFX_MSG_MAP(CSaoleiDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaoleiDlg message handlers

BOOL CSaoleiDlg::OnInitDialog()
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

void CSaoleiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSaoleiDlg::OnPaint() 
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
HCURSOR CSaoleiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
#include "Psapi.h"
void __stdcall saolei();
void CSaoleiDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	saolei();
}
void ReadProcessAllMemory(HANDLE hProcess)
{
	if(hProcess == NULL)		return;

	HMODULE module = LoadLibrary("psapi.dll");
	FARPROC pGetProcessMemoryInfo = (FARPROC)GetProcAddress(module, "GetProcessMemoryInfo");
	PROCESS_MEMORY_COUNTERS mem;
	LPVOID hMem = &mem;
	DWORD dwLen = sizeof(PROCESS_MEMORY_COUNTERS);
	_asm
	{
		push dwLen
		push hMem
		push hProcess
		call pGetProcessMemoryInfo
	}
	FreeLibrary(module);

	DWORD dwMemSize = mem.WorkingSetSize;
	DWORD dwReadSize;
	DWORD dwImageBase = 0x01000000;
	DWORD dwAddressOfEntryPoint = 0x00003E21;
	DWORD baseAddr = dwImageBase + dwImageBase;
	TCHAR* szMemBuffer = (TCHAR*)malloc(dwMemSize);
	memset(szMemBuffer, 0x00, dwMemSize);
		
	DWORD dwOldProtected;
	if(VirtualProtectEx(hProcess, (LPVOID)baseAddr, dwMemSize, PAGE_READONLY, &dwOldProtected))
	{
		BOOL bRet = ::ReadProcessMemory(hProcess, (LPCVOID)baseAddr, szMemBuffer, dwMemSize, NULL);
		VirtualProtectEx(hProcess, (LPVOID)baseAddr, dwMemSize, dwOldProtected, NULL);
	}
	free(szMemBuffer);
	szMemBuffer = NULL;
}

BYTE g_szBuffer2[] = 
{
0x55,
0x89,0xE5,
0x83,0xEC,0x20,
0x53,
0x56,
0x57,
0x8D,0x7D,0xF4,
0xB9,0x08,0x00,0x00,0x00,
0xB8,0x00,0x00,0x00,0x00,
0xF3,0xAB,
0xA1,0x38,0x53,0x00,0x01,
0x89,0x45,0xF8,
0xA1,0x34,0x53,0x00,0x01,
0x89,0x45,0xFC,
0xB8,0x00,0x00,0x00,0x00,
0x89,0x45,0xF4,
0xEB,0x09,
0x8B,0x45,0xF4,
0x83,0xC0,0x01,
0x89,0x45,0xF4,
0x8B,0x4D,0xF4,
0x3B,0x4D,0xF8,
0x7D,0x4C,
0xB8,0x00,0x00,0x00,0x00,
0x89,0x45,0xF0,
0xEB,0x09,
0x8B,0x55,0xF0,
0x83,0xC2,0x01,
0x89,0x55,0xF0,
0x8B,0x45,0xF0,
0x3B,0x45,0xFC,
0x7D,0x2F,
0xB8,0x00,0x00,0x00,0x00,
0xBB,0x20,0x00,0x00,0x00,
0x0F,0xAF,0x5D,0xF4,
0x01,0xD8,
0x03,0x45,0xF0,
0x8B,0x18,
0xB8,0x00,0x00,0x00,0x00,
0x39,0xC3,
0x75,0x0F,
0x8B,0x45,0xF4,
0x50,
0x8B,0x45,0xF0,
0x50,
0xB8,0xB1,0x38,0x00,0x01,
0xFF,0xD0,
0xEB,0xC0,
0xEB,0xA3,
0x5F,
0x5E,
0x5B,
0x83,0xC4,0x20,
0x5D,
0xC3
};
void TestFunc2();
void TEstFunc(BOOL (*bValueArr)[36]);
#define STEP_X	16
#define STEP_Y	16
#define    FIRST_MINE_X    20      
#define    FIRST_MINE_Y    62  
void __stdcall saolei()
{
	DWORD addr = 0x1005361;
	DWORD x    = 0x1005334;
	DWORD y    = 0x1005338;

	
	HWND hwnd = ::FindWindow(NULL, "Minesweeper");
	if(hwnd == NULL)	return;
	DWORD hProcessId;
	::GetWindowThreadProcessId(hwnd, &hProcessId);
	HANDLE Process = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcessId);

	int b = 0 ,  nx = 0, ny = 0;
	
	DWORD s = 0;
	BOOL bRet = ::ReadProcessMemory(Process, (LPCVOID)x, &nx, 1, NULL);		//????????
	bRet =::ReadProcessMemory(Process, (LPCVOID)y, &ny, 1, NULL);			//????????
	
//	DWORD xuanzong = 0x010038B1;											//????????
	DWORD x1 = 1;
	DWORD y1 = 1;
	
	BYTE bValueArr[32][32] = {0};
	BYTE bValue;
	for(int i = 0; i < ny; i++)
	{
		for(int j = 0; j < nx; j++)
		{
			LPVOID lpValueAddr = (LPVOID)(addr + i * 32 + j);
			::ReadProcessMemory(Process, lpValueAddr, &bValue, 1, NULL);
			bValueArr[i][j] = bValue;
			// 8F OK  10 OK
			if(bValue == 0x0F)
			{
				POINT pt;
				pt.x = FIRST_MINE_X + ((j)*STEP_X);
				pt.y = FIRST_MINE_Y + ((i)*STEP_Y);
			
				SendMessage(hwnd, WM_LBUTTONDOWN, 1, MAKELPARAM(pt.x, pt.y));
				SendMessage(hwnd, WM_LBUTTONUP, 0, MAKELPARAM(pt.x, pt.y));
			}
		}
	}
//	TestFunc2();
//	TEstFunc(pRecord);
	//param
/*	DWORD dwSize = sizeof(g_szBuffer2);
	LPVOID pParamAddr = VirtualAllocEx(Process, 0, ny*36, MEM_COMMIT, PAGE_READWRITE);
	LPVOID pFuncAddr = VirtualAllocEx(Process, 0, dwSize, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	bRet = WriteProcessMemory(Process, pParamAddr, pRecord, ny*36, NULL);
	DWORD dwValue = (DWORD)(pParamAddr);
	memcpy(g_szBuffer2+0x5F, (char*)&dwValue, 4);
	bRet = WriteProcessMemory(Process, pFuncAddr, g_szBuffer2, dwSize, NULL);
	
	DWORD dwThreadId;
	HANDLE hRemoteThread = CreateRemoteThread(Process, NULL, 0, 
		(LPTHREAD_START_ROUTINE)pFuncAddr, pParamAddr, 0, &dwThreadId);
	if(hRemoteThread)
	{
		DWORD dwRet;
		::WaitForSingleObject( hRemoteThread, INFINITE );
		::GetExitCodeThread( hRemoteThread, &dwRet );
		TRACE("run and return %d/n",dwRet);
		::CloseHandle( hRemoteThread );
		MessageBox(0,"OK",0,0);
	}

	VirtualFreeEx(Process, pParamAddr, ny*36, MEM_RELEASE);
	VirtualFreeEx(Process, pFuncAddr, dwSize, MEM_RELEASE);
	delete []pRecord;
*/
//	for(int i = 0; i < nx * 32; i += 32)
//	{
//		for(int j = 0; j < ny; j++)
//		{
//			::ReadProcessMemory(Process, (LPCVOID)(addr + i+j), &b, 1, NULL);
//			if (b == 0x8E || b == 0x8F)										//?????????????
//			{
//				Rec[i/32][j] = 1;    
//			}
//			else
//				Rec[i/32][j] = 0;
//		}
//	}
//	//Click
//	for(i = 0; i < nx; i ++)
//	{    
//		for(int j = 0; j < ny; j++)
//		{
//			x1 = i + 1;
//			y1 = j + 1;
//			if(Rec[i][j] != 1)          //????????
//			{
//				_asm
//				{
//					push x1        //?????X
//					push y1        //?????Y
//					call xuanzong  //???????
//				}
//			}
//		}
//	}
} 
void TestFunc2()
{
	_asm
	{
		lea		eax, g_szBuffer2
		call	eax
	}

	_asm
	{
		push	ebp			
		mov		ebp,esp		
		sub		esp,0CH		
		push	ebx
		push	esi
		push	edi
		lea		edi, [ebp-0CH]
		mov		ecx, 3H	
		mov		eax, 0H		
		rep		stosd

		mov         dword ptr [ebp-0Ch],0
		jmp         $i_nY
$i__:		
		mov         eax,dword ptr [ebp-0Ch]
		add         eax,1
		mov         dword ptr [ebp-0Ch],eax
$i_nY:
		mov         ecx,dword ptr [ebp-0Ch]
		cmp         ecx,dword ptr [ebp-8]
		jge         $End
		
		mov         dword ptr [ebp-10h],0
		jmp         $j_nX
$j__:	
		mov         edx,dword ptr [ebp-10h]
		add         edx,1
		mov         dword ptr [ebp-10h],edx
$j_nX:
		mov         eax,dword ptr [ebp-10h]
		cmp         eax,dword ptr [ebp-4]
		jge         $Second
		
		mov         ecx,dword ptr [ebp-8]
		imul        ecx,ecx,90h
		mov         edx,dword ptr [ebp+8]
		add         edx,ecx
		mov         eax,dword ptr [ebp-4]
		cmp         dword ptr [edx+eax*4],0
		jne         $First
		push        dword ptr [ebp-0Ch]
		push        dword ptr [ebp-10h]
		mov         eax,10038B1h
		call        eax

$First:	jmp         $j__
$Second:jmp         $i__

$End:
		pop		edi
		pop		esi
		pop		ebx
		add		esp, 0CH
		pop     ebp			
		ret
	}
}

void TEstFunc(BOOL (*bValueArr)[36])
{
	int nx;
	int ny;
//	_asm
//	{
//		mov bh, [01005338H]		; height
//		mov bl, [01005334H]		; width
//		inc bh
//		inc hl
//
//	}
	for(int i = 0; i < ny; i++)
	{
		for(int jj = 0; jj < nx; jj++)
		{
			_asm
			{
				mov	 eax, 0000000H
				mov  ebx, 36
				imul ebx, [ebp-8] ; 36*nY
				add  eax, ebx
				add  eax, [ebp-10h]
				mov  ebx, [eax]
				cmp  ebx, 0
			}
			if(bValueArr[ny][nx] == 0)
			{
				_asm
				{

					push i
					push jj
					mov  eax, 010038B1H
					call eax
				}
			}
		}
	}
}

// CreateRemoteThread
typedef struct _RemoteParam{
	char	szMsg[12];     
	DWORD	dwMessageBox;
} RemoteParam, * PRemoteParam;
typedef int (__stdcall * PFN_MESSAGEBOX)(HWND, LPCTSTR, LPCTSTR, DWORD);

static DWORD __stdcall ThreadProc(LPVOID lpThreadParameter)
{
	RemoteParam* param = (RemoteParam*)lpThreadParameter;
	if(param)
	{
		PFN_MESSAGEBOX pMsgBox = (PFN_MESSAGEBOX)param->dwMessageBox; 
		pMsgBox(NULL, param->szMsg, NULL, 0);
	}

	return 0;
}

BYTE g_szMemoryData[] = 
{
	0x55,0x8B,0xEC,0x83,0xEC,0x48,0x53,0x56,0x57,0x8D,0x7D,0xB8,
	0xB9,0x12,0x00,0x00,0x00,0xB8,0xCC,0xCC,0xCC,0xCC,0xF3,0xAB,
	0x8B,0x45,0x08,0x89,0x45,0xFC,0x83,0x7D,0xFC,0x00,0x74,0x1F,
	0x8B,0x4D,0xFC,0x8B,0x51,0x0C,0x89,0x55,0xF8,0x8B,0xF4,0x6A,
	0x00,0x6A,0x00,0x8B,0x45,0xFC,0x50,0x6A,0x00,0xFF,0x55,0xF8,
	0x33,0xC0,0x5F,0x5E,0x5B,
	0x83,0xC4,0x48,
	0x8B,0xE5,
	0x5D,0xC2,0x04,0x00
};
BOOL CreateRemoteThread_(HANDLE hTargetProcess, DWORD dwThreadID)
{
	if(hTargetProcess == NULL)	return FALSE;
	
	//1:VirtualAllocEx
	RemoteParam param;
	memset(&param, 0x0, sizeof(RemoteParam));
	HINSTANCE hUser32 = LoadLibrary("User32.dll");
	param.dwMessageBox = (DWORD)GetProcAddress(hUser32, "MessageBoxA");
	strcat(param.szMsg, "liujiquan\0");
	FreeLibrary(hUser32);
	LPVOID pRemoteParam = VirtualAllocEx(hTargetProcess, 0, sizeof(RemoteParam), MEM_COMMIT, PAGE_READWRITE);
	if(pRemoteParam == NULL)	return FALSE;
	
	DWORD dwFuncSize = 256;
	LPVOID pRemoteThreadProc = VirtualAllocEx(hTargetProcess, 0, dwFuncSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//2:WriteProcessMemory
	BOOL bRet = WriteProcessMemory(hTargetProcess, pRemoteParam, &param, sizeof(RemoteParam), 0);
	TCHAR szBuffer[1024] = {0};
	memset(szBuffer, 0x00, 1024);
	memcpy(szBuffer, g_szMemoryData, sizeof(g_szMemoryData));
	bRet = WriteProcessMemory(hTargetProcess, pRemoteThreadProc, szBuffer, 1024, 0);

	//3:CreateRemoteThread
	DWORD dwThreadId;
	HANDLE hRemoteThread = CreateRemoteThread(hTargetProcess, NULL, 0, 
		(LPTHREAD_START_ROUTINE)pRemoteThreadProc, pRemoteParam, 0, &dwThreadId);
	if(hRemoteThread)
	{
		DWORD dwRet;
		::WaitForSingleObject( hRemoteThread, INFINITE );
		::GetExitCodeThread( hRemoteThread, &dwRet );
		TRACE("run and return %d/n",dwRet);
		::CloseHandle( hRemoteThread );
		MessageBox(0,"OK",0,0);
	}
	::VirtualFreeEx( hTargetProcess, pRemoteParam, sizeof(RemoteParam),MEM_RELEASE );
	::VirtualFreeEx( hTargetProcess, pRemoteThreadProc, dwFuncSize,MEM_RELEASE );

	return TRUE;
}

DWORD GetFuntion(LPTHREAD_START_ROUTINE func)
{
	func(0);
	DWORD dw = (DWORD)func;
	return dw;
}

// -----------------------------------------------------------//
// Function :   AdjustPrivileges
// Return   :   BOOL
// Comment  :   
// -----------------------------------------------------------//
BOOL AdjustPrivileges()
{
    HANDLE Token;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Token))
    {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (AdjustTokenPrivileges(Token, 0, &tp, sizeof(tp), NULL, NULL) == 0)
		{
			CloseHandle(Token);
            return FALSE; //FAIL
        }
        else
		{
			CloseHandle(Token);
            return TRUE; //SUCCESS
        }
    }
    return FALSE;
}


BOOL Test()
{
	FindResource(NULL, 0, 0);
	LoadResource(NULL, 0);	
	LockResource(0);
	FreeResource(0);	
	ReadFile(0, 0, 0, 0, 0);
	WriteFile(0,0,0,0,0);
	DeleteFile(0);
	return TRUE;
}

void CSaoleiDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	Test();
}

void CSaoleiDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	AdjustPrivileges();
//	ThreadProc(0);
	HWND hwnd = ::FindWindow(NULL, "Minesweeper");
	if(hwnd == NULL)	return;
	DWORD hProcessId;
	::GetWindowThreadProcessId(hwnd, &hProcessId);
	HANDLE Process = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, hProcessId);
	
	CreateRemoteThread_(Process, hProcessId);

	CloseHandle(Process);
}
