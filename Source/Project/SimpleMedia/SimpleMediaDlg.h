// SimpleMediaDlg.h : header file
//

#if !defined(AFX_SIMPLEMEDIADLG_H__9874EFCB_DB50_4018_95D1_FD12DCAECB9F__INCLUDED_)
#define AFX_SIMPLEMEDIADLG_H__9874EFCB_DB50_4018_95D1_FD12DCAECB9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSimpleMediaDlg dialog

class CSimpleMediaDlg : public CDialog
{
// Construction
public:
	CSimpleMediaDlg(CWnd* pParent = NULL);	// standard constructor
	~CSimpleMediaDlg();
// Dialog Data
	//{{AFX_DATA(CSimpleMediaDlg)
	enum { IDD = IDD_SIMPLEMEDIA_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleMediaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSimpleMediaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HANDLE		m_hThread;
	CListBox*	m_pListBox;
public:
	static DWORD WINAPI Thread_(LPVOID lparam);
	DWORD WINAPI Thread();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEMEDIADLG_H__9874EFCB_DB50_4018_95D1_FD12DCAECB9F__INCLUDED_)
