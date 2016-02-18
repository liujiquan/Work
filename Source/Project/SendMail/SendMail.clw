; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSendMailDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SendMail.h"

ClassCount=4
Class1=CSendMailApp
Class2=CSendMailDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SENDMAIL_DIALOG

[CLS:CSendMailApp]
Type=0
HeaderFile=SendMail.h
ImplementationFile=SendMail.cpp
Filter=N

[CLS:CSendMailDlg]
Type=0
HeaderFile=SendMailDlg.h
ImplementationFile=SendMailDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=SendMailDlg.h
ImplementationFile=SendMailDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SENDMAIL_DIALOG]
Type=1
Class=CSendMailDlg
ControlCount=19
Control1=IDC_EDIT_MAILSERVER,edit,1350633600
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_PORT,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_FROM,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_TO,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_UserName,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_Pwd,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_Title,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_Data,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_BUTTON_SENDMAIL,button,1342242816
Control18=IDC_LIST1,listbox,1353777409
Control19=IDC_BUTTON_FIND,button,1342242816

