#if !defined(AFX_SETDIALOG_H__AA9F8DDA_8C40_462D_8B0E_D2D3932E1CBE__INCLUDED_)
#define AFX_SETDIALOG_H__AA9F8DDA_8C40_462D_8B0E_D2D3932E1CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDialog dialog

class CSetDialog : public CDialog
{
// Construction
public:
	CSetDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDialog)
	enum { IDD = IDD_DIALOG_SET };
	UINT	m_ReadSize;
	UINT	m_ThreadCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDIALOG_H__AA9F8DDA_8C40_462D_8B0E_D2D3932E1CBE__INCLUDED_)
