#if !defined(AFX_ASSEMGOTODLG_H__9E97F32B_42F7_4EC1_AD7C_40F99016A0E7__INCLUDED_)
#define AFX_ASSEMGOTODLG_H__9E97F32B_42F7_4EC1_AD7C_40F99016A0E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssemGotoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAssemGotoDlg dialog

class CAssemGotoDlg : public CDialog
{
// Construction
public:
	CAssemGotoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAssemGotoDlg)
	enum { IDD = IDD_DIALOG_ACCEM_GO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssemGotoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssemGotoDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSEMGOTODLG_H__9E97F32B_42F7_4EC1_AD7C_40F99016A0E7__INCLUDED_)
