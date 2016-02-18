#if !defined(AFX_SHOWMEMORY_H__EB56EE22_9ADD_4B9C_BCA8_5E70BAD9F408__INCLUDED_)
#define AFX_SHOWMEMORY_H__EB56EE22_9ADD_4B9C_BCA8_5E70BAD9F408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowMemory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowMemory dialog

class CShowMemory : public CDialogBar
{
// Construction
public:
	CShowMemory(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShowMemory)
	enum { IDD = IDD_DIALOG_SHOWMEMORY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowMemory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowMemory)
	virtual BOOL OnInitDialog(UINT wparam, long lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
public:
	void InitMemoryInfo(LPCTSTR pBuffer, DWORD nSize);
};
/************************************************************************/
/*                                                                      */
/************************************************************************/
TCHAR ToChar(CHAR c);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWMEMORY_H__EB56EE22_9ADD_4B9C_BCA8_5E70BAD9F408__INCLUDED_)
