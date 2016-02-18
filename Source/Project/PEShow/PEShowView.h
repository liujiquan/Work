// PEShowView.h : interface of the CPEShowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PESHOWVIEW_H__AF704628_26E2_48B4_91A1_1772EED9C8D9__INCLUDED_)
#define AFX_PESHOWVIEW_H__AF704628_26E2_48B4_91A1_1772EED9C8D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NTHeader.h"
#include "PEFileHeader.h"
#include "SuperGridCtrl\supergridctrl.h"
#define CTreeItem_ CSuperGridCtrl::CTreeItem
class CPEShowView : public CView
{
protected: // create from serialization only
	CPEShowView();
	DECLARE_DYNCREATE(CPEShowView)

// Attributes
public:
	CPEShowDoc* GetDocument();
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPEShowView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPEShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
//	CTreeCtrl* m_listTree;
//	CListCtrl* m_ListCtrl;
public:
// Generated message map functions
protected:
	//{{AFX_MSG(CPEShowView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void InitGridColumn(CMySuperGrid& m_ListGrid);
	CTreeItem_* AddMainItem(CMySuperGrid& m_ListGrid);
	CTreeItem_* Add_IMAGE_DOS_HEADER(IMAGE_DOS_HEADER* pHeader, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem);
	CTreeItem_* Add_MS_DOS_Stub(CHAR* pBuffer, DWORD dwAddressBase, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem);
	CTreeItem_* Add_IMAGE_NT_HEADERS(IMAGE_NT_HEADERS* pBuffer, DWORD dwAddressBase, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem);
	CTreeItem_* Add_IMAGE_SECTION_HEADER(CHAR* pBuffer, DWORD dwAddressBase, UINT nSectionNum, CMySuperGrid& m_ListGrid,CTreeItem_* parentItem);
	
	CTreeItem_* Add_Directory_ImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid);
	CTreeItem_* Add_Directory_ExportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid);
	CTreeItem_* Add_Directory_ResourceTable(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid);
	CTreeItem_* Add_Directory_BoundImportSymbols(DWORD dwVirtualAddress, DWORD dwSize, CMySuperGrid& m_ListGrid);

};

#ifndef _DEBUG  // debug version in PEShowView.cpp
inline CPEShowDoc* CPEShowView::GetDocument()
   { return (CPEShowDoc*)m_pDocument; }
#endif

/************************************************************************/
/* Macro                                                                     */
/************************************************************************/
#define TREEID			WM_USER+1	
#define LISTCTRL		WM_USER+2
#define LISTBOX			WM_USER+3
/************************************************************************/
/* Define                                                                     */
/************************************************************************/
//  2014.09.24 Ver1.00[X64/X32 PE] Start
#define X64_PE	0x8664			// 62bits PE
#define X32_PE	0x014c			// 32bits PE
//  2014.09.24 Ver1.00[X64/X32 PE] End

BOOL _OpenFile(LPCTSTR pszFileName);
IMAGE_DOS_HEADER* _GetMSDosHeader();
IMAGE_NT_HEADERS* _GetNTHeaders();
CHAR* _GetSECTION_INFO();
TCHAR* _GetDosStubBuffer();
CHAR* GetData();
BOOL _Release();
DWORD GetMaxSize();
CString FormatTime(DWORD TimeDateStamp);
void GetPEVersion();
// 
CTreeItem_*  AddItenm(CString strTitle, DWORD& dwAddress,  ITEMTYPE type, DWORD data, CString strDesc, CTreeItem_* parentItem, CMySuperGrid& m_ListGrid, UINT nSize = 0, LPCTSTR pStringData = NULL);


#endif // !defined(AFX_PESHOWVIEW_H__AF704628_26E2_48B4_91A1_1772EED9C8D9__INCLUDED_)

