#if !defined(AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_)
#define AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit window

class CExtendEdit : public CEdit
{
// Construction
public:
	CExtendEdit();
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// CExtendDropFileEdit
class CExtendDropFileEdit : public CExtendEdit
{
// Construction
public:
	CExtendDropFileEdit();
// Attributes
public:
	CString m_strFileName;
	int		m_Type;
	HANDLE	m_Handle;
	BOOL	m_bRunning;
// Operations
public:
	void SetEncrptType(int i = 0)
	{
		m_Type = i; 
	}
public:
	static DWORD WINAPI Thread_(LPVOID lparam);
	DWORD WINAPI Thread();
	void MD5(CString strFileName);
	void DecryptMD5(DWORD a, DWORD b, DWORD c, DWORD d, DWORD dwFileSize);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendDropFileEdit)
	public:
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CExtendDropFileEdit();
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendEdit)
	afx_msg LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifdef DWORD64
#undef DWORD64
// DWORD64
struct DWORD64
{
	DWORD dwValueLow;
	DWORD dwValueHi;
}DWORD64;
#endif
#define HIDWORD(dwwValue)	(DWORD)(dwwValue>>32)	
#define LODWORD(dwwValue)	(DWORD)(dwwValue)
// DWORD128
struct DWORD128
{
	DWORD64 dwwValueLow;
	DWORD64 dwwValueHi;
	DWORD128(){	};
	DWORD128(DWORD a, DWORD b, DWORD c, DWORD d)
	{
		dwwValueLow = b >> 32 & a;
		dwwValueHi = d >> 32 & c;
	}
	CString toString()
	{
		CString str;
		str.Format("%016X%016X", dwwValueLow, dwwValueHi);
		return str;
	}
	bool operator ==(const DWORD128& value)
	{
		return this->dwwValueLow == value.dwwValueLow && this->dwwValueHi == value.dwwValueHi;
	}
};
// DWORD512
struct DWORD512
{
	DWORD128 dwLL;
	DWORD128 dwLH;
	DWORD128 dwHL;
	DWORD128 dwHH;

	DWORD512(LPCTSTR pszBuffer)
	{	
		if(pszBuffer)
		{
			memcpy(this, pszBuffer, 64);
		}
	}
	bool operator ==(const DWORD512& value)
	{
		return this->dwLL == value.dwLL && this->dwLH == value.dwLH && this->dwHL == value.dwHL && this->dwHH == value.dwHH;
	}
};
//////////////////////////////////////////////////////////////////////////
//Function
DWORD F_XYZ(DWORD X, DWORD Y, DWORD Z);
DWORD G_XYZ(DWORD X, DWORD Y, DWORD Z);
DWORD H_XYZ(DWORD X, DWORD Y, DWORD Z);
DWORD I_XYZ(DWORD X, DWORD Y, DWORD Z);

void FF(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti);
void GG(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti);
void HH(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti);
void II(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD Mj, int s, DWORD ti);
void Trace__(DWORD a, DWORD b, DWORD c, DWORD d);
DWORD Ti(int i);
DWORD RTL(DWORD value, int n);
void Group512(DWORD512 dword512Value, DWORD& a, DWORD& b, DWORD& c, DWORD& d);
DWORD reverse(DWORD dwValue);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_)
