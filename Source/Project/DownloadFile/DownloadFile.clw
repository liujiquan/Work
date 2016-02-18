; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "downloadfile.h"
LastPage=0

ClassCount=4
Class1=CDownloadFileApp
Class2=CAboutDlg
Class3=CDownloadFileDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX (English (U.S.))
Resource2=IDD_DIALOG_SET (English (U.S.))
Resource3=IDD_DOWNLOADFILE_DIALOG (English (U.S.))
Class4=CSetDialog
Resource4=IDR_MENU1
Resource5=IDD_DOWNLOADFILE_DIALOG

[CLS:CDownloadFileApp]
Type=0
BaseClass=CWinApp
HeaderFile=DownloadFile.h
ImplementationFile=DownloadFile.cpp
LastObject=CDownloadFileApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DownloadFileDlg.cpp
ImplementationFile=DownloadFileDlg.cpp

[CLS:CDownloadFileDlg]
Type=0
BaseClass=CDialog
HeaderFile=DownloadFileDlg.h
ImplementationFile=DownloadFileDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DOWNLOADFILE_DIALOG]
Type=1
Class=CDownloadFileDlg
ControlCount=6
Control1=IDC_EDIT1,edit,1352728580
Control2=IDC_BUTTON_DOWNLOAD,button,1342242816
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_STATIC_CUR,static,1342308354
Control5=IDC_STATIC_MAX,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM_SET
Command2=ID_MENUITEM_ABOUT
CommandCount=2

[DLG:IDD_DOWNLOADFILE_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_EDIT1,edit,1352728580
Control2=IDC_BUTTON_DOWNLOAD,button,1342242816
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_STATIC_CUR,static,1342308354
Control5=IDC_STATIC_MAX,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_SET (English (U.S.))]
Type=1
Class=CSetDialog
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350639744
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350639744

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CSetDialog]
Type=0
HeaderFile=SetDialog.h
ImplementationFile=SetDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSetDialog

