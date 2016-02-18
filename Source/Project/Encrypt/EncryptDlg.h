// EncryptDlg.h : header file
//

#if !defined(AFX_ENCRYPTDLG_H__A2344E84_2A66_4F5B_92E8_486CACD992EC__INCLUDED_)
#define AFX_ENCRYPTDLG_H__A2344E84_2A66_4F5B_92E8_486CACD992EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ExtendEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CEncryptDlg dialog

class CEncryptDlg : public CDialog 
{
// Construction
public:
	CEncryptDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEncryptDlg)
	enum { IDD = IDD_ENCRYPT_DIALOG };
	CExtendEdit	m_CyberXEdit;
	CExtendEdit	m_m_ed2kedit;
	CExtendEdit	m_Decode_EncodeEdit;
	CExtendEdit	m_SourceEdit;
	CExtendEdit	m_FlashgetSourceEdit;
	CExtendEdit	m_qqdlSourceEdit;
	CExtendEdit	m_thunderSourceEdit;
	CExtendEdit	m_DecrptyBase64SourceEdit;
	CExtendEdit	m_Base64SourceEdit;
	CString	m_source;
	CString	m_Base64Source;
	CString	m_DecrptyBase64Source;
	CString	m_thunderSource;
	CString	m_m_qqdlSource;
	CString	m_FlashgetSource;
	CString	m_Decode_Encode;
	int		m_UTF8;
	CString	m_ed2k;
	CString	m_MD5;
	CExtendDropFileEdit m_m_MD5Edit;
	int		m_HashCodeIndex;
	CString	m_CyberXStr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEncryptDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEncryptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONEncrypt();
	afx_msg void OnBUTTONDecrypt();
	afx_msg void OnBUTTONURLEncode();
	afx_msg void OnBUTTONURLDecode();
	afx_msg void OnBUTTONDecryptEd2k();
	afx_msg void OnBUTTONEncryptEd2k();
	afx_msg void OnButton1();
	afx_msg void OnRadioutf8();
	afx_msg void OnRadioutfascii();
	afx_msg void OnBUTTONCyberX();
	afx_msg void OnBUTTONCyberXDecrypt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENCRYPTDLG_H__A2344E84_2A66_4F5B_92E8_486CACD992EC__INCLUDED_)
