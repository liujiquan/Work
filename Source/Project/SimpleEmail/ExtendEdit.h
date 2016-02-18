//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   ExtendEdit.h
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   CExtendEdit: 复制 粘贴 全选 剪切 回滚功能 
//*				 CExtendDropFileEdit: 继承CExtendEdit 文件拖拽功能
//*				 CExtendSuspensionEdit:CExtendEdit 双击弹出提示栏 选择数据填充
//*-----------------------------------------------------------------------------*/
#if !defined(AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_)
#define AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtendEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExtendEdit window

class CExtendEdit : public CEdit
{
// Construction
public:
	CExtendEdit();
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExtendEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendEdit)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CExtendDropFileEdit
class CExtendDropFileEdit : public CExtendEdit
{
// Construction
public:
	CExtendDropFileEdit();
// Attributes
public:
	CStringArray m_strFileNameArr;
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendDropFileEdit)
	//}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CExtendDropFileEdit();
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendDropFileEdit)
	afx_msg LRESULT OnDragAcceptFiles(WPARAM wparam,LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CExtendSuspensionEdit
class CExtendSuspensionEdit : public CExtendEdit
{
	// Construction
public:
	CExtendSuspensionEdit();
	// Attributes
public:
public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtendSuspensionEdit)
	//}}AFX_VIRTUAL
	// Implementation
public:
	virtual ~CExtendSuspensionEdit();
	// Generated message map functions
protected:
	//{{AFX_MSG(CExtendSuspensionEdit)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTENDEDIT_H__D4FDA783_D873_41E6_9F23_1202BE1366B0__INCLUDED_)
