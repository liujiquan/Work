#if !defined(AFX_ACCEMBFINDDLG_H__292C934F_454F_4D06_A792_DE63AF83A78D__INCLUDED_)
#define AFX_ACCEMBFINDDLG_H__292C934F_454F_4D06_A792_DE63AF83A78D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AccembFindDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAccembFindDlg dialog

class CAccembFindDlg : public CDialog
{
// Construction
public:
	CAccembFindDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccembFindDlg)
	enum { IDD = IDD_DIALOG_ASSEM_FIND };
	CComboBox	m_FindCmb;
	int			m_FindDirect;
	CString		m_strFindText;
	CStringArray	m_findStrArr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccembFindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccembFindDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFindNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCEMBFINDDLG_H__292C934F_454F_4D06_A792_DE63AF83A78D__INCLUDED_)
