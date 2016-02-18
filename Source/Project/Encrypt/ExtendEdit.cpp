// ExtendEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Encrypt.h"
#include "ExtendEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit

CExtendEdit::CExtendEdit()
{
}

CExtendEdit::~CExtendEdit()
{
}


BEGIN_MESSAGE_MAP(CExtendEdit, CEdit)
	//{{AFX_MSG_MAP(CExtendEdit)
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit message handlers
#define VK_A	0x41
BOOL CExtendEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HACCEL haccel = LoadAccelerators(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(haccel && TranslateAccelerator(m_hWnd, haccel, pMsg))
		{
			if(pMsg->wParam == VK_A)	SetSel(0, -1);
		}
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CExtendEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CEdit::OnLButtonDown(nFlags, point);
//	SetSel(0, -1);
//	Copy();
}

void CExtendEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
//	SetSel(0, 0);
}

// CExtendDropFileEdit
CExtendDropFileEdit::CExtendDropFileEdit()
{
	m_strFileName = _T("");
	m_Type = 0;
	m_Handle = NULL;
	m_bRunning = FALSE;
}
CExtendDropFileEdit::~CExtendDropFileEdit()
{
}
BEGIN_MESSAGE_MAP(CExtendDropFileEdit, CExtendEdit)
	//{{AFX_MSG_MAP(CExtendEdit)
	ON_MESSAGE(WM_DROPFILES, OnDragAcceptFiles)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
	
BOOL CExtendDropFileEdit::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CExtendEdit::PreTranslateMessage(pMsg);
}

LRESULT CExtendDropFileEdit::OnDragAcceptFiles(WPARAM wparam,LPARAM lparam)
{	
	if(m_bRunning)
	{
		MessageBox("CExtendDropFileEdit Running .");
		return 0;
	}
	HDROP hdrop = (HDROP)wparam;
	if(hdrop == NULL)	return 0;
	
	int nCount = ::DragQueryFile(hdrop, -1, NULL, 0);
	if(nCount == 1)
	{
		m_strFileName = _T("");
		TCHAR szBuffer[MAX_PATH] = {0};
		::DragQueryFile(hdrop, 0, szBuffer, MAX_PATH);
		m_strFileName = (CString)(szBuffer);
		
		m_Handle = CreateThread(NULL, 0, Thread_, this, 0, NULL);
		CloseHandle(m_Handle);
	}
	return 0;
}

DWORD WINAPI CExtendDropFileEdit::Thread_(LPVOID lparam)
{
	CExtendDropFileEdit* _this = (CExtendDropFileEdit*)lparam;
	if(_this)
	{
		_this->Thread();
	}

	return 0;
}

DWORD WINAPI CExtendDropFileEdit::Thread()
{
	m_bRunning = TRUE;

	if(m_Type == 0)	MD5(m_strFileName);

	m_Handle = NULL;

	m_bRunning = FALSE;

	return 0;
}

void CExtendDropFileEdit::OnClose ()
{
	if(m_bRunning)	
	{
		MessageBox("CExtendDropFileEdit Running .");
		return;
	}

	CWnd::OnClose();
}
//////////////////////////////////////////////////////////////////////////
// MD5
#define		GROUPBITS		512
#define		GROUP			64
#define		yushubits		448
#define		yushu			56
#define		ADDSIZEbits		64
#define		ADDSIZE			8
#define		buzuByte1		0x80
#define		buzuByte2		0x00
#define		A				0x67452301
#define		B				0xefcdab89
#define		C				0x98badcfe
#define		D				0x10325476
#define		READCOUNT		(1024*100)
#define		READSIZE		(GROUP*READCOUNT)

void CExtendDropFileEdit::MD5(CString strFileName)
{
	CHAR* szFileBuffer = NULL;
	DWORD64 dwFileSize = 0;
	DWORD dwFileLenLow = 0, dwFileLenHi;
	DWORD dwReadSize = 0;

	// CreateFile
	HANDLE hFile = CreateFile(strFileName.GetBuffer(0), 
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ, 
		NULL, OPEN_EXISTING, 
		FILE_FLAG_SEQUENTIAL_SCAN, 
		NULL);
	if(hFile == INVALID_HANDLE_VALUE)				return;
	// dwBytes
	dwFileLenLow = GetFileSize(hFile, &dwFileLenHi);
	dwFileSize = dwFileLenHi << 32 | dwFileLenLow;
	DWORD dwLastSize = dwFileSize % GROUP;
	DWORD dwBytes = dwLastSize < yushu ? yushu - dwLastSize : yushu + yushu - dwLastSize;
	DWORD64 dwGroupSize =  dwFileSize / GROUP + dwBytes / GROUP + 1;					// dwGroupSize
	// CreateFileMapping
	HANDLE hFileMapping  = CreateFileMapping(hFile, 
		NULL, PAGE_READWRITE, 
		dwFileLenHi, 
		dwFileLenLow, 
		NULL);
	CloseHandle(hFile);
	if(hFileMapping == 0)	
	{
		DWORD dwError = GetLastError();
		return;
	}
	// MapViewOfFile
	CHAR* pszBuffer = (CHAR*)MapViewOfFile(hFileMapping, 
		FILE_MAP_ALL_ACCESS, 
		0, 
		0, 
		0);
	if(pszBuffer == NULL)						
	{
		CloseHandle(hFileMapping);
		return;
	}
	
	// Group
	DWORD a = A;
	DWORD b = B;
	DWORD c = C;
	DWORD d = D;
	CHAR* pszBufferTemp = pszBuffer;
	for(DWORD64 index = 0; index < dwGroupSize; index++)
	{
		if(index == dwGroupSize - 1)
		{
			TCHAR szBuffer[GROUP] = {0};
			memcpy(szBuffer, pszBufferTemp, dwLastSize);
			for(int i = 0; i < dwBytes; i++)											// ²¹×ã1000 0000 0000 0000 0000....
			{
				if(i == 0)
					szBuffer[dwLastSize+i] = buzuByte1;
				else 
					szBuffer[dwLastSize+i] = buzuByte2;
			}
			DWORD64 dwAddFileSize = dwFileSize * 8; 
			memcpy(szBuffer+dwLastSize+dwBytes, (CHAR*)&dwAddFileSize, ADDSIZE);		// ²¹×ã dwfilesize(8bytes)

			DWORD512 dword512Value(szBuffer);

			Group512(dword512Value, a, b, c, d);
		}
		else
		{
			DWORD512 dword512Value(pszBufferTemp);
			Group512(dword512Value, a, b, c, d);
			pszBufferTemp += sizeof(DWORD512);
		}	
	}
	
	// MapViewOfFile
	UnmapViewOfFile(pszBuffer);
	CloseHandle(hFileMapping);

	CString str;
	str.Format("%08X%08X%08X%08X", reverse(a), reverse(b), reverse(c), reverse(d));

	this->SetWindowText(str);
}

void CExtendDropFileEdit::DecryptMD5(DWORD a, DWORD b, DWORD c, DWORD d, DWORD dwFileSize)
{
	a = 0x3842cac4;
	b =	0x8223b9a0;
	c =	0x9a50cc0d;
	d =	0x9b84756f;	
}

#include <cmath>
void Group512(DWORD512 UINT512Value, DWORD& aTemp, DWORD& bTemp, DWORD& cTemp, DWORD& dTemp)
{	
	DWORD a = aTemp ;
	DWORD b = bTemp;
	DWORD c = cTemp;
	DWORD d = dTemp;

	DWORD M0 = LODWORD(UINT512Value.dwLL.dwwValueLow);
	DWORD M1 = HIDWORD(UINT512Value.dwLL.dwwValueLow);
	DWORD M2 = LODWORD(UINT512Value.dwLL.dwwValueHi);
	DWORD M3 = HIDWORD(UINT512Value.dwLL.dwwValueHi);

	DWORD M4 = LODWORD(UINT512Value.dwLH.dwwValueLow);
	DWORD M5 = HIDWORD(UINT512Value.dwLH.dwwValueLow);
	DWORD M6 = LODWORD(UINT512Value.dwLH.dwwValueHi);
	DWORD M7 = HIDWORD(UINT512Value.dwLH.dwwValueHi);

	DWORD M8 = LODWORD(UINT512Value.dwHL.dwwValueLow);
	DWORD M9 = HIDWORD(UINT512Value.dwHL.dwwValueLow);
	DWORD M10 = LODWORD(UINT512Value.dwHL.dwwValueHi);
	DWORD M11 = HIDWORD(UINT512Value.dwHL.dwwValueHi);

	DWORD M12 = LODWORD(UINT512Value.dwHH.dwwValueLow);
	DWORD M13 = HIDWORD(UINT512Value.dwHH.dwwValueLow);
	DWORD M14 = LODWORD(UINT512Value.dwHH.dwwValueHi);
	DWORD M15 = HIDWORD(UINT512Value.dwHH.dwwValueHi);

	// 1
	FF(a,b,c,d,M0,7,	Ti(1));	
	FF(d,a,b,c,M1,12,	Ti(2));	
	FF(c,d,a,b,M2,17,	Ti(3));	
	FF(b,c,d,a,M3,22,	Ti(4)); 
	FF(a,b,c,d,M4,7,	Ti(5));	
	FF(d,a,b,c,M5,12,	Ti(6));	
	FF(c,d,a,b,M6,17,	Ti(7));	
	FF(b,c,d,a,M7,22,	Ti(8));	
	FF(a,b,c,d,M8,7,	Ti(9));	
	FF(d,a,b,c,M9,12,	Ti(10));
	FF(c,d,a,b,M10,17,	Ti(11));
	FF(b,c,d,a,M11,22,	Ti(12));
	FF(a,b,c,d,M12,7,	Ti(13));
	FF(d,a,b,c,M13,12,	Ti(14));
	FF(c,d,a,b,M14,17,	Ti(15));
	FF(b,c,d,a,M15,22,	Ti(16));
	//2
	GG(a,b,c,d,M1,5,	Ti(17));
	GG(d,a,b,c,M6,9,	Ti(18));
	GG(c,d,a,b,M11,14,	Ti(19));
	GG(b,c,d,a,M0,20,	Ti(20));
	GG(a,b,c,d,M5,5,	Ti(21));
	GG(d,a,b,c,M10,9,	Ti(22));
	GG(c,d,a,b,M15,14,	Ti(23));
	GG(b,c,d,a,M4,20,	Ti(24));
	GG(a,b,c,d,M9,5,	Ti(25));
	GG(d,a,b,c,M14,9,	Ti(26));
	GG(c,d,a,b,M3,14,	Ti(27));
	GG(b,c,d,a,M8,20,	Ti(28));
	GG(a,b,c,d,M13,5,	Ti(29));
	GG(d,a,b,c,M2,9,	Ti(30));
	GG(c,d,a,b,M7,14,	Ti(31));
	GG(b,c,d,a,M12,20,	Ti(32));
	//3
	HH(a,b,c,d,M5,4,	Ti(33));
	HH(d,a,b,c,M8,11,	Ti(34));
	HH(c,d,a,b,M11,16,	Ti(35));
	HH(b,c,d,a,M14,23,	Ti(36));
	HH(a,b,c,d,M1,4,	Ti(37));
	HH(d,a,b,c,M4,11,	Ti(38));
	HH(c,d,a,b,M7,16,	Ti(39));
	HH(b,c,d,a,M10,23,	Ti(40));
	HH(a,b,c,d,M13,4,	Ti(41));
	HH(d,a,b,c,M0,11,	Ti(42));
	HH(c,d,a,b,M3,16,	Ti(43));
	HH(b,c,d,a,M6,23,	Ti(44));
	HH(a,b,c,d,M9,4,	Ti(45));
	HH(d,a,b,c,M12,11,	Ti(46));
	HH(c,d,a,b,M15,16,	Ti(47));
	HH(b,c,d,a,M2,23,	Ti(48));
	//4
	II(a,b,c,d,M0,6,	Ti(49));
	II(d,a,b,c,M7,10,	Ti(50));
	II(c,d,a,b,M14,15,	Ti(51));
	II(b,c,d,a,M5,21,	Ti(52));
	II(a,b,c,d,M12,6,	Ti(53));
	II(d,a,b,c,M3,10,	Ti(54));
	II(c,d,a,b,M10,15,	Ti(55));
	II(b,c,d,a,M1,21,	Ti(56));
	II(a,b,c,d,M8,6,	Ti(57));
	II(d,a,b,c,M15,10,	Ti(58));
	II(c,d,a,b,M6,15,	Ti(59));
	II(b,c,d,a,M13,21,	Ti(60));
	II(a,b,c,d,M4,6,	Ti(61));
	II(d,a,b,c,M11,10,	Ti(62));
	II(c,d,a,b,M2,15,	Ti(63));
	II(b,c,d,a,M9,21,	Ti(64));

	aTemp += a ;
    bTemp += b ;
    cTemp += c ; 
    dTemp += d;
}

// F_XYZ
DWORD F_XYZ(DWORD X, DWORD Y, DWORD Z)
{
	return (X&Y) | ((~X) & Z);
}

// G_XYZ
DWORD G_XYZ(DWORD X, DWORD Y, DWORD Z)
{
	return (X&Z) | (Y & (~Z));
}

// H_XYZ
DWORD H_XYZ(DWORD X, DWORD Y, DWORD Z)
{
	return X^Y^Z;
}

// I_XYZ
DWORD I_XYZ(DWORD X, DWORD Y, DWORD Z)
{
	return Y^(X|(~Z));
}

void swap(DWORD& a, DWORD& b, DWORD& c, DWORD& d)
{
	DWORD temp = d;
	d = c;
	c = b;
	b = a;
	a = temp;
}

void FF(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti)
{
	a = b + RTL((a + F_XYZ(b,c,d) + Mj + ti) , s);
}

void GG(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti)
{
	a = b + RTL((a + G_XYZ(b,c,d) + Mj + ti) , s);
}

void HH(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti)
{
	a = b + RTL((a + H_XYZ(b,c,d) + Mj + ti) , s);
}

void II(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti)
{
	a = b + RTL((a + I_XYZ(b,c,d) + Mj + ti) , s);
}

#define ABS(x)	 x > 0 ? x : -x;
DWORD Ti(int i)
{	
	double dValue = 4294967296 * sin(i);
	dValue = ABS(dValue);
	return (DWORD)dValue;							// 4294967296 = 2 << 31 0xd76aa478
}

DWORD RTL(DWORD value, int n)
{  
    return (value << n) | (value >> (32-n));  
}

void Trace__(DWORD a, DWORD b, DWORD c, DWORD d)
{
	TRACE2("%08X-%08X-", a, b);
	TRACE2("%08X-%08X\n", c, d);
}

DWORD reverse(DWORD dwValue)
{
	BYTE b0 = (BYTE)dwValue;
	BYTE b1 = (BYTE)(dwValue>>8);
	BYTE b2 = (BYTE)(dwValue>>16);
	BYTE b3 = (BYTE)(dwValue>>24);

	return b0 << 24 | b1 << 16 | b2 << 8 | b3;
}
/*
DWORD K[]=
{
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
	0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
	0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
	0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
	0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
	0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
	0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
	0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
	0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
	0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
	0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};

DWORD s[]={7,12,17,22,7,12,17,22,7,12,17,22,7,
12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
15,21,6,10,15,21,6,10,15,21,6,10,15,21};

void Group512_(DWORD512 UINT512Value, DWORD& aTemp, DWORD& bTemp, DWORD& cTemp, DWORD& dTemp)
{
	DWORD Marr[16];
	Marr[0] = LODWORD(UINT512Value.dwLL.dwwValueLow);
	Marr[1] = HIDWORD(UINT512Value.dwLL.dwwValueLow);
	Marr[2] = LODWORD(UINT512Value.dwLL.dwwValueHi);
	Marr[3] = HIDWORD(UINT512Value.dwLL.dwwValueHi);

	Marr[4] = LODWORD(UINT512Value.dwLH.dwwValueLow);
	Marr[5] = HIDWORD(UINT512Value.dwLH.dwwValueLow);
	Marr[6] = LODWORD(UINT512Value.dwLH.dwwValueHi);
	Marr[7] = HIDWORD(UINT512Value.dwLH.dwwValueHi);

	Marr[8] = LODWORD(UINT512Value.dwHL.dwwValueLow);
	Marr[9] = HIDWORD(UINT512Value.dwHL.dwwValueLow);
	Marr[10] = LODWORD(UINT512Value.dwHL.dwwValueHi);
	Marr[11] = HIDWORD(UINT512Value.dwHL.dwwValueHi);

	Marr[12] = LODWORD(UINT512Value.dwHH.dwwValueLow);
	Marr[13] = HIDWORD(UINT512Value.dwHH.dwwValueLow);
	Marr[14] = LODWORD(UINT512Value.dwHH.dwwValueHi);
	Marr[15] = HIDWORD(UINT512Value.dwHH.dwwValueHi);

	int F,g;
	int a=aTemp;
	int b=bTemp;
	int c=cTemp;
	int d=dTemp;
	for(int  i=0;i<64;i++){
		if(i<16)
		{
			F=(b&c)|((~b)&d);
			g=i;
		}
		else if(i<32)
		{
			F=(d&b)|((~d)&c);
			g=(5*i+1)%16;
		}
		else if(i<48)
		{
			F=b^c^d;
			g=(3*i+5)%16;
		}
		else
		{
			F=c^(b|(~d));
			g=(7*i)%16;
		}
		int tmp=d;
		d=c;
		c=b;
		b=b+RTL(a+F+Marr[g] + K[i],s[i]);
		a=tmp;

		Trace__(a,b,c,d);
	}
	TRACE("==============================================\n");

	aTemp=a+aTemp;
	bTemp=b+bTemp;
	cTemp=c+cTemp;
	dTemp=d+dTemp;
};*/