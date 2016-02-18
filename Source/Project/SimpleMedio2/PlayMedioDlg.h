#if !defined(AFX_PLAYMEDIODLG_H__122DAEDF_4CC0_497E_BA42_CF0121ADCEA0__INCLUDED_)
#define AFX_PLAYMEDIODLG_H__122DAEDF_4CC0_497E_BA42_CF0121ADCEA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayMedioDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayMedioDlg dialog

class CPlayMedioDlg : public CDialogBar
{
// Construction
public:
	CPlayMedioDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayMedioDlg)
	enum { IDD = IDD_DIALOGPlayMedio };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayMedioDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPlayMedioDlg)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HANDLE		m_hThread;
public:
	static DWORD WINAPI Thread_(LPVOID lparam);
	DWORD WINAPI Thread();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYMEDIODLG_H__122DAEDF_4CC0_497E_BA42_CF0121ADCEA0__INCLUDED_)
