// ASFShowDlg.h : header file
//

#if !defined(AFX_ASFSHOWDLG_H__E5D4D364_9F3B_4DFE_8CD9_04776F356C61__INCLUDED_)
#define AFX_ASFSHOWDLG_H__E5D4D364_9F3B_4DFE_8CD9_04776F356C61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CASFShowDlg dialog
#include "AsfInfo.h"
class CASFShowDlg : public CDialog
{
// Construction
public:
	CASFShowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CASFShowDlg)
	enum { IDD = IDD_ASFSHOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CASFShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CASFShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMySuperGrid	m_SuperGrid;
public:
	void InitGridColumn();																						// InitGridColumn
	BOOL ReadAsfFile(LPCTSTR pszFileName);																		// ReadAsfFile
	void InsertHeaderObject(ASF_HeaderObject* pHeaderObject, DWORD& dwAddress);									// InsertHeaderObject
	void InsertPropertiesObject(ASF_PropertiesObject* pPropertiesObject, DWORD& dwAddress);						// InsertPropertiesObject  
	void InsertClockObject(ASF_ClockObject* pClocksObj, DWORD& dwAddress);										// InsertClockObject
	
	CTreeItem_* InsertStreamPropertiesObject(ASF_StreamPropertiesObject* pStreamPropertiesObj, DWORD& dwAddress);// InsertStreamPropertiesObject
	void InsertAudiomediatype(Audiomediatype* pAudiomediatype, DWORD& dwAddress, CTreeItem_* Parent);			// InsertAudiomediatype
	void InsertVideomediatype(Videomediatype* pVideomediatype, DWORD& dwAddress, CTreeItem_* Parent);			// void InsertVideomediatype
	void InsertJFIF_JPEGmediatype(JFIF_JPEGmediatype* pJFIF_JPEGmediatype, DWORD& dwAddress, CTreeItem_* Parent);	
	void InsertDegradableJPEGmediatype(DegradableJPEGmediatype* pDegradableJPEGmediatype, DWORD& dwAddress, CTreeItem_* Parent);	
	CTreeItem_*  InsertFiletransferandbinarymediatypes(Filetransferandbinarymediatypes* pFiletransferandbinarymediatypes, DWORD& dwAddress, CTreeItem_* Parent);
	void InsertWebstreams(Webstreams* pWebstreams, DWORD& dwAddress, CTreeItem_* Parent);
	
	void InsertSpreadaudiotype(Spreadaudio* pSpreadaudio, DWORD& dwAddress, CTreeItem_* Parent);							// InsertSpreadaudiotype
	void InsertCodecListObject(ASF_CodecListObject* pCodecListObject, DWORD& dwAddress, FILE* pFile);						// InsertCodecListObject
	void InsertScriptCommandObject(ASF_ScriptCommandObject* pScriptCommandObject, DWORD& dwAddress);			// InsertScriptCommandObject
	void InsertIndexObject(ASF_IndexObject* pIndexObject, DWORD& dwAddress);												// InsertIndexObject
	void InsertDataObject(ASF_DataObject* pDataObject, DWORD& dwAddress);
	void InsertErrorcorrectiondata(Errorcorrectiondata* pErrorcorrectiondata, DWORD& dwAddress);
	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASFSHOWDLG_H__E5D4D364_9F3B_4DFE_8CD9_04776F356C61__INCLUDED_)
