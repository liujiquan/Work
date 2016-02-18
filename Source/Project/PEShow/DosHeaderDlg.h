#if !defined(AFX_DOSHEADERDLG_H__F466C354_4AB8_44EA_BACF_CB8E06411E70__INCLUDED_)
#define AFX_DOSHEADERDLG_H__F466C354_4AB8_44EA_BACF_CB8E06411E70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DosHeaderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDosHeaderDlg dialog

class CDosHeaderDlg : public CDialogBar
{
// Construction
public:
	CDosHeaderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDosHeaderDlg)
	enum { IDD = IDD_DIALOG_DOS_HEADER };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDosHeaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDosHeaderDlg)
	virtual BOOL OnInitDialog(WPARAM wparam, LONG lparam);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetImageDosHeadeData(IMAGE_DOS_HEADER* pData);
	void InitListCtrl();
private:
	IMAGE_DOS_HEADER m_DosheaderData;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSHEADERDLG_H__F466C354_4AB8_44EA_BACF_CB8E06411E70__INCLUDED_)
