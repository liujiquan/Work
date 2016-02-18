; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInjectSimpleCodeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "InjectSimpleCode.h"

ClassCount=4
Class1=CInjectSimpleCodeApp
Class2=CInjectSimpleCodeDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_INJECTSIMPLECODE_DIALOG

[CLS:CInjectSimpleCodeApp]
Type=0
HeaderFile=InjectSimpleCode.h
ImplementationFile=InjectSimpleCode.cpp
Filter=N

[CLS:CInjectSimpleCodeDlg]
Type=0
HeaderFile=InjectSimpleCodeDlg.h
ImplementationFile=InjectSimpleCodeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=InjectSimpleCodeDlg.h
ImplementationFile=InjectSimpleCodeDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_INJECTSIMPLECODE_DIALOG]
Type=1
Class=CInjectSimpleCodeDlg
ControlCount=1
Control1=IDC_BUTTON_INJECT,button,1342242816

