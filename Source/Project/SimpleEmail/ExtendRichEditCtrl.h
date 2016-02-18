//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendRichEditCtrl.h
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#if !defined(AFX_EXTENDRICHEDITCTRL_H__0611BD07_01FF_4680_A5FE_5E4EB2866409__INCLUDED_)
#define AFX_EXTENDRICHEDITCTRL_H__0611BD07_01FF_4680_A5FE_5E4EB2866409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendRichEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendRichEditCtrl window
#include <afxtempl.h>
#include "MailUtil.h"
// SortData
struct SortData
{
	long nStartIndex;
	TEXTTYPE type;
};
class CExtendRichEditCtrl : public CRichEditCtrl
{
// Construction
public:
	CExtendRichEditCtrl();
private:
	CHARFORMAT					m_Defaultcf;
	CHARFORMAT					m_LinkCf;
//	CArray<TEXTINFO, TEXTINFO>	m_TextArr;	
public:
	BOOL Initlize();
	void AddSelLink();				// add hyper link
	BOOL DelLink();					// delete hyper link
	void Split(CArray<TEXTINFO, TEXTINFO>& textArr);
	long FindNextData(long nBeginIndex, long& lFindDataStart, TEXTTYPE& findType, CString& strRightData);
	BOOL SortFindIndex(long a, long b, long c, long d, SortData findDataArr[]);
	void InsertInfo(int nFlag = 0);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendRichEditCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CExtendRichEditCtrl();
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendRichEditCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnChange();
	afx_msg void OnMenuitemInserthref();
	afx_msg void OnMenuitemInsertimg();
	afx_msg void OnMenuitemInsertvedio();
	afx_msg void OnMenuitemInsertaudio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDRICHEDITCTRL_H__0611BD07_01FF_4680_A5FE_5E4EB2866409__INCLUDED_)
