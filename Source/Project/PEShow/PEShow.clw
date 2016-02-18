; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDirBoundImportPage_
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PEShow.h"
LastPage=0

ClassCount=14
Class1=CPEShowApp
Class2=CPEShowDoc
Class3=CPEShowView
Class4=CMainFrame

ResourceCount=25
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_DIALOG_DIR_PAGE_EXPORT
Class6=CDosHeaderDlg
Resource3=IDD_DIALOG_PE
Class7=CShowMemory
Resource4=IDD_DIALOG_DIR_PAGE_RESOURCE
Class8=CPEStruct
Resource5="IDD_DIALOG_DIR_PAGE_IMPORT"
Class9=CNTHeader
Resource6=IDD_DIALOG_DOS_HEADER
Class10=CDirectoryInfoDlg
Resource7=IDD_DIALOG_DIR_PAGE0
Class11=CDirPage0
Resource8=IDD_DIALOG_NTHEADER
Resource9=IDD_DIALOG_DIRECTORYINFO
Resource10=IDD_DIALOG_SHOWMEMORY
Resource11="IDD_DIALOG_DIR_PAGE_EXPORT"
Resource12=IDD_DIALOG_DIR_PAGE_BOUND_IMPORT (English (U.S.))
Class12=CDirExportPage
Class13=CDirResourcePage
Resource13=IDD_ABOUTBOX
Class14=CDirBoundImportPage_
Resource14=IDD_DIALOG_DIR_PAGE_IMPORT
Resource15=IDD_DIALOG_DIR_PAGE_IMPORT (English (U.S.))
Resource16=IDD_ABOUTBOX (English (U.S.))
Resource17=IDR_MAINFRAME (English (U.S.))
Resource18=IDD_DIALOG_DIR_PAGE_EXPORT (English (U.S.))
Resource19=IDD_DIALOG_DIR_PAGE_RESOURCE (English (U.S.))
Resource20=IDD_DIALOG_DOS_HEADER (English (U.S.))
Resource21=IDD_DIALOG_SHOWMEMORY (English (U.S.))
Resource22=IDD_DIALOG_PE (English (U.S.))
Resource23=IDD_DIALOG_NTHEADER (English (U.S.))
Resource24=IDD_DIALOG_DIRECTORYINFO (English (U.S.))
Resource25=IDD_DIALOG_DIR_PAGE_BOUND_IMPORT

[CLS:CPEShowApp]
Type=0
HeaderFile=PEShow.h
ImplementationFile=PEShow.cpp
Filter=N

[CLS:CPEShowDoc]
Type=0
HeaderFile=PEShowDoc.h
ImplementationFile=PEShowDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_FILE_OPEN

[CLS:CPEShowView]
Type=0
HeaderFile=PEShowView.h
ImplementationFile=PEShowView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPEShowView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=PEShow.cpp
ImplementationFile=PEShow.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_LIST1,listbox,1352663296

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_DOS_HEADER]
Type=1
Class=CDosHeaderDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:CDosHeaderDlg]
Type=0
HeaderFile=DosHeaderDlg.h
ImplementationFile=DosHeaderDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDosHeaderDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_SHOWMEMORY]
Type=1
Class=CShowMemory
ControlCount=1
Control1=IDC_LIST1,listbox,1344340225

[CLS:CShowMemory]
Type=0
HeaderFile=ShowMemory.h
ImplementationFile=ShowMemory.cpp
BaseClass=CDialog
Filter=D
LastObject=CShowMemory
VirtualFilter=dWC

[DLG:IDD_DIALOG_PE]
Type=1
Class=CPEStruct
ControlCount=1
Control1=IDC_TREE1,SysTreeView32,1350631431

[CLS:CPEStruct]
Type=0
HeaderFile=PEStruct.h
ImplementationFile=PEStruct.cpp
BaseClass=CDialogBar
Filter=D
LastObject=CPEStruct
VirtualFilter=dWC

[DLG:IDD_DIALOG_NTHEADER]
Type=1
Class=CNTHeader
ControlCount=0

[CLS:CNTHeader]
Type=0
HeaderFile=NTHeader.h
ImplementationFile=NTHeader.cpp
BaseClass=CDialogBar
Filter=D
LastObject=CNTHeader
VirtualFilter=dWC

[DLG:IDD_DIALOG_DIRECTORYINFO]
Type=1
Class=CDirectoryInfoDlg
ControlCount=1
Control1=IDC_TAB1,SysTabControl32,1342193664

[CLS:CDirectoryInfoDlg]
Type=0
HeaderFile=DirectoryInfoDlg.h
ImplementationFile=DirectoryInfoDlg.cpp
BaseClass=CDialogBar
Filter=D
LastObject=IDC_TAB1
VirtualFilter=dWC

[DLG:IDD_DIALOG_DIR_PAGE0]
Type=1
Class=CDirPage0
ControlCount=0

[CLS:CDirPage0]
Type=0
HeaderFile=DirPage0.h
ImplementationFile=DirPage0.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDirPage0

[DLG:"IDD_DIALOG_DIR_PAGE_IMPORT"]
Type=1
Class=?
ControlCount=0

[DLG:"IDD_DIALOG_DIR_PAGE_EXPORT"]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_DIR_PAGE_IMPORT]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_DIR_PAGE_EXPORT]
Type=1
Class=CDirExportPage
ControlCount=0

[CLS:CDirExportPage]
Type=0
HeaderFile=DirExportPage.h
ImplementationFile=DirExportPage.cpp
BaseClass=CDialog
Filter=D
LastObject=CDirExportPage
VirtualFilter=dWC

[DLG:IDD_DIALOG_DIR_PAGE_RESOURCE]
Type=1
Class=CDirResourcePage
ControlCount=0

[CLS:CDirResourcePage]
Type=0
HeaderFile=DirResourcePage.h
ImplementationFile=DirResourcePage.cpp
BaseClass=CDialog
Filter=D
LastObject=CDirResourcePage
VirtualFilter=dWC

[DLG:IDD_DIALOG_DIR_PAGE_BOUND_IMPORT]
Type=1
Class=CDirBoundImportPage_
ControlCount=0

[CLS:CDirBoundImportPage_]
Type=0
HeaderFile=DirBoundImportPage_.h
ImplementationFile=DirBoundImportPage_.cpp
BaseClass=CDialog
Filter=D
LastObject=CDirBoundImportPage_

[DLG:IDD_DIALOG_DIR_PAGE_BOUND_IMPORT (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_PE (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_TREE1,SysTreeView32,1350631431

[DLG:IDD_DIALOG_SHOWMEMORY (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST1,listbox,1344340225

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_LIST1,listbox,1352663296

[DLG:IDD_DIALOG_DOS_HEADER (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[DLG:IDD_DIALOG_NTHEADER (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_DIRECTORYINFO (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_TAB1,SysTabControl32,1342193664

[DLG:IDD_DIALOG_DIR_PAGE_IMPORT (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_DIR_PAGE_EXPORT (English (U.S.))]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DIALOG_DIR_PAGE_RESOURCE (English (U.S.))]
Type=1
Class=?
ControlCount=0

