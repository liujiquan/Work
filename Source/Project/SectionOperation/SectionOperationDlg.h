// SectionOperationDlg.h : header file
//

#if !defined(AFX_SECTIONOPERATIONDLG_H__60B8038D_7F71_421F_9ED1_49A8442B8B47__INCLUDED_)
#define AFX_SECTIONOPERATIONDLG_H__60B8038D_7F71_421F_9ED1_49A8442B8B47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSectionOperationDlg dialog

class CSectionOperationDlg : public CDialog
{
// Construction
public:
	CSectionOperationDlg(CWnd* pParent = NULL);	// standard constructor
	~CSectionOperationDlg();
// Dialog Data
	//{{AFX_DATA(CSectionOperationDlg)
	enum { IDD = IDD_SECTIONOPERATION_DIALOG };
	CListCtrl	m_SectionList;
	CString	m_FileSize;
	CString	m_sectionAlignment;
	CString	m_SecionData;
	CString	m_ExtendedSize;
	CString	m_SectionName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSectionOperationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSectionOperationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONOpenFIle();
	afx_msg void OnButtonRemovedosnt();
	afx_msg void OnButtonCreatefile();
	afx_msg void OnBUTTONInsertSection();
	afx_msg void OnButtonExtenedsecsize();
	afx_msg void OnButtonDeletesec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitListColumn();
	void SetListInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECTIONOPERATIONDLG_H__60B8038D_7F71_421F_9ED1_49A8442B8B47__INCLUDED_)
