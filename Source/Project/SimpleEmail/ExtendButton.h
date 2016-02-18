#if !defined(AFX_EXTENDBUTTON_H__8E884DEE_20D4_4B66_A03B_5EA91D5ABE52__INCLUDED_)
#define AFX_EXTENDBUTTON_H__8E884DEE_20D4_4B66_A03B_5EA91D5ABE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendButton window

class CExtendButton : public CButton
{
// Construction
public:
	CExtendButton();

// Attributes
public:
	CBitmap	m_BitmapFocus;
	CBitmap	m_Bitmap;
// Operations
public:
	void Initlize();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDBUTTON_H__8E884DEE_20D4_4B66_A03B_5EA91D5ABE52__INCLUDED_)
