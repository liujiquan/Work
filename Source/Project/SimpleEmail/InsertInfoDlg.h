#if !defined(AFX_INSERTINFODLG_H__E44DF85C_0393_49E8_900C_BBF4B642C867__INCLUDED_)
#define AFX_INSERTINFODLG_H__E44DF85C_0393_49E8_900C_BBF4B642C867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertInfoDlg dialog

class CInsertInfoDlg : public CDialog
{
// Construction
public:
	CInsertInfoDlg(CWnd* pParent = NULL);   // standard constructor
private:
	int		m_nFlags;
public:
	void SetInsertFlag(int nFlag)
	{
		m_nFlags = nFlag;
	}
// Dialog Data
	//{{AFX_DATA(CInsertInfoDlg)
	enum { IDD = IDD_DIALOG_RICHEDIT_INSERT };
	CString	m_InserInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertInfoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTINFODLG_H__E44DF85C_0393_49E8_900C_BBF4B642C867__INCLUDED_)
