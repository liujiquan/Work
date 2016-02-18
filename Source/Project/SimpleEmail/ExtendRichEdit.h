//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendRichEdit.h
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#if !defined(AFX_EXTENDRICHEDIT_H__CEE30607_5F86_4FA5_9F35_344B5FC870F2__INCLUDED_)
#define AFX_EXTENDRICHEDIT_H__CEE30607_5F86_4FA5_9F35_344B5FC870F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendRichEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendRichEdit window

class CExtendRichEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CExtendRichEdit)
// Construction
public:
	CExtendRichEdit();
// Attributes
public:
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendRichEdit)
	public:
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CExtendRichEdit();
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendRichEdit)
	afx_msg void OnPaint();
    afx_msg BOOL OnLink(NMHDR *in_pNotifyHeader, LRESULT *out_pResult);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CWnd*        m_pParentWnd;
    bool        m_bBottom;
    BOOL        m_ShowBorder; 
    COLORREF    m_BorderColor; 
    bool        m_bCreate;
    bool        m_bFocus;
public:
	void Initlize();
    void Append(LPCSTR text,bool newline = false,bool link = false,int nLinkBegin = 0,int nLinkCount = 0);
    void GetText(int nBegin,int nEnd,CString& text);
    void SetScrollBottom(bool bottom=true);
    void StopScroll();
    void SetTextFont(int nBegin,int nEnd,bool bold,bool italic,bool underline,COLORREF color=0,int size=0);
    void AddLink();
    void CancelLink();
    BOOL CheckURL(const CString &szUrl, CString &szMsg);
    void OnSize(CWnd* pParent);
    void OnSize(CRect& rect);
    void OnSpecifySize(CWnd* pParent);
    bool IsCreate();
    void Clear();
    void SetEditFocus(bool focus);
    void ShowBorderLine(BOOL bShow,COLORREF nColor = RGB(53, 104, 187));
    void SetLeftOffset(int nOffset);
	long GetTextLengthEx( DWORD dwFlags,  UINT uCodePage) const;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDRICHEDIT_H__CEE30607_5F86_4FA5_9F35_344B5FC870F2__INCLUDED_)
