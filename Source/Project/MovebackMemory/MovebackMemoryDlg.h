// MovebackMemoryDlg.h : header file
//

#if !defined(AFX_MOVEBACKMEMORYDLG_H__B6DBD9D3_3734_448C_9A21_03D1476C201D__INCLUDED_)
#define AFX_MOVEBACKMEMORYDLG_H__B6DBD9D3_3734_448C_9A21_03D1476C201D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMovebackMemoryDlg dialog

class CMovebackMemoryDlg : public CDialog
{
// Construction
public:
	CMovebackMemoryDlg(CWnd* pParent = NULL);	// standard constructor
	~CMovebackMemoryDlg();
// Dialog Data
	//{{AFX_DATA(CMovebackMemoryDlg)
	enum { IDD = IDD_MOVEBACKMEMORY_DIALOG };
	CListCtrl	m_list;
	UINT	m_SectionNum;
	CString	m_FileSize;
	DWORD	m_offset;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovebackMemoryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMovebackMemoryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONOpen();
	afx_msg void OnButtonMoveback();
	afx_msg void OnButton2();
	afx_msg void OnBUTTONExtendedPeHeader();
	afx_msg void OnBUTTONInsertSection();
	afx_msg void OnBUTTONInsertSection2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitListColumn();
	void SetListInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEBACKMEMORYDLG_H__B6DBD9D3_3734_448C_9A21_03D1476C201D__INCLUDED_)
