; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CASFShowDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ASFShow.h"

ClassCount=3
Class1=CASFShowApp
Class2=CASFShowDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ASFSHOW_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_ACCELERATOR1

[CLS:CASFShowApp]
Type=0
HeaderFile=ASFShow.h
ImplementationFile=ASFShow.cpp
Filter=N

[CLS:CASFShowDlg]
Type=0
HeaderFile=ASFShowDlg.h
ImplementationFile=ASFShowDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CASFShowDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ASFShowDlg.h
ImplementationFile=ASFShowDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ASFSHOW_DIALOG]
Type=1
Class=CASFShowDlg
ControlCount=1
Control1=IDC_LIST1,listbox,1218511105

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDR_CTRL_C
CommandCount=1

