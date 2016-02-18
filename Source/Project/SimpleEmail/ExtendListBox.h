//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendListBox.h
//* Author   :   liujiquan
//* DateTime :   11/19/2014
//* Version  :   1.0
//* Comment  :   实现文件拖拽功能 
//*				 del删除功能
//*				 水平滚动条功能
//*-----------------------------------------------------------------------------*/
#if !defined(AFX_EXTENDLISTBOX_H__F35A10FD_6CCB_424E_82CE_EB8E7FAF34D3__INCLUDED_)
#define AFX_EXTENDLISTBOX_H__F35A10FD_6CCB_424E_82CE_EB8E7FAF34D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendListBox window

class CExtendListBox : public CListBox
{
// Construction
public:
	CExtendListBox();

// Attributes
public:
	CStringArray m_strFileNameArr;
// Operations
public:
	void RefushHorizontalScrollBar( void );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendListBox)
	public:
	virtual int AddString( LPCTSTR lpszItem );
	virtual int InsertString( int nIndex, LPCTSTR lpszItem );
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CExtendListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendListBox)
	afx_msg LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDLISTBOX_H__F35A10FD_6CCB_424E_82CE_EB8E7FAF34D3__INCLUDED_)
