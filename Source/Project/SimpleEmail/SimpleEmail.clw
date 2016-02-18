; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInsertUser
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SimpleEmail.h"
LastPage=0

ClassCount=17
Class1=CSimpleEmailApp
Class2=CSimpleEmailDoc
Class3=CSimpleEmailView
Class4=CMainFrame

ResourceCount=13
Resource1=IDR_ACCELERATOR_RICKEDITCTRL
Class5=CAboutDlg
Resource2=IDD_DIALOG_ACCOUNTINFO
Class6=CInternetAccounts
Resource3=IDD_DIALOG_SENDMAIL
Class7=CAccountInfo
Resource4=IDR_ACCELERATOR_LISTBOX_DEL
Class8=CSendMailDlg
Resource5=IDR_MAINFRAME
Class9=CSendMailFormView
Resource6=IDD_ABOUTBOX
Class10=CExtendStatusBar
Class11=CExtendListBox
Resource7=IDR_MENU_RICHEDIT
Class12=CExtendRichEdit
Class13=CExtendRichEditCtrl
Resource8=IDD_DIALOG_ACCOUNT
Class14=CExtendButton
Resource9=IDR_ACCELERATOR_EDIT
Class15=CSuspensionDlg
Resource10=IDD_DIALOG_SENDMAILFORMVIEW
Resource11=IDD_DIALOG_Suspension
Class16=CInsertInfoDlg
Resource12=IDD_DIALOG_RICHEDIT_INSERT
Class17=CInsertUser
Resource13=IDD_DIALOG_INSERTUSER

[CLS:CSimpleEmailApp]
Type=0
HeaderFile=SimpleEmail.h
ImplementationFile=SimpleEmail.cpp
Filter=N
LastObject=CSimpleEmailApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSimpleEmailDoc]
Type=0
HeaderFile=SimpleEmailDoc.h
ImplementationFile=SimpleEmailDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CSimpleEmailDoc

[CLS:CSimpleEmailView]
Type=0
HeaderFile=SimpleEmailView.h
ImplementationFile=SimpleEmailView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CSimpleEmailView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=AFX_HELP
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=SimpleEmail.cpp
ImplementationFile=SimpleEmail.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_SEND
Command2=ID_APP_EXIT
Command3=ID_VIEW_TOOLBAR
Command4=ID_VIEW_STATUS_BAR
Command5=ID_MENUITEM_ACCOUNT
Command6=AFX_HELP
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SEND
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_SEND
Command2=ID_APP_ABOUT
CommandCount=2

[DLG:IDD_DIALOG_ACCOUNT]
Type=1
Class=CInternetAccounts
ControlCount=6
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_LIST2,SysListView32,1350631425
Control4=IDC_BUTTON_ADD,button,1342242816
Control5=IDC_BUTTON_MODIFY,button,1342242816
Control6=IDC_BUTTON_DELETE,button,1342242816

[CLS:CInternetAccounts]
Type=0
HeaderFile=InternetAccounts.h
ImplementationFile=InternetAccounts.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST2
VirtualFilter=dWC

[DLG:IDD_DIALOG_ACCOUNTINFO]
Type=1
Class=CAccountInfo
ControlCount=18
Control1=IDOK,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT1,edit,1350631552
Control11=IDC_EDIT2,edit,1350631552
Control12=IDC_EDIT3,edit,1350631552
Control13=IDC_EDIT4,edit,1350631552
Control14=IDC_EDIT5,edit,1350639744
Control15=IDC_EDIT6,edit,1350639744
Control16=IDC_EDIT7,edit,1350631552
Control17=IDC_EDIT8,edit,1350631552
Control18=IDCANCEL,button,1342242816

[CLS:CAccountInfo]
Type=0
HeaderFile=AccountInfo.h
ImplementationFile=AccountInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAccountInfo

[DLG:IDD_DIALOG_SENDMAIL]
Type=1
Class=CSendMailDlg
ControlCount=18
Control1=IDC_COMBO1,combobox,1344339971
Control2=IDC_EDIT_TO,edit,1350631552
Control3=IDC_EDIT_CC,edit,1350631552
Control4=IDC_EDIT_BCC,edit,1350631552
Control5=IDC_EDIT_Subject,edit,1350631552
Control6=IDC_LIST_FileArr,listbox,1353777409
Control7=IDC_RICHEDIT_TEXT,RICHEDIT,1353781252
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_POPUP_TO,button,1342181417
Control17=IDC_POPUP_CC,button,1342181417
Control18=IDC_POPUP_BCC,button,1342181417

[CLS:CSendMailDlg]
Type=0
HeaderFile=SendMailDlg.h
ImplementationFile=SendMailDlg.cpp
BaseClass=CDialogBar
Filter=D
LastObject=IDC_BUTTON_POPUP_TO2
VirtualFilter=dWC

[DLG:IDD_DIALOG_SENDMAILFORMVIEW]
Type=1
Class=CSendMailFormView
ControlCount=0

[CLS:CSendMailFormView]
Type=0
HeaderFile=SendMailFormView.h
ImplementationFile=SendMailFormView.cpp
BaseClass=CFormView
Filter=D
LastObject=CSendMailFormView

[CLS:CExtendStatusBar]
Type=0
HeaderFile=ExtendStatusBar.h
ImplementationFile=ExtendStatusBar.cpp
BaseClass=CStatusBar
Filter=W
LastObject=CExtendStatusBar

[CLS:CExtendListBox]
Type=0
HeaderFile=ExtendListBox.h
ImplementationFile=ExtendListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CExtendListBox

[ACL:IDR_ACCELERATOR_LISTBOX_DEL]
Type=1
Class=?
Command1=IDR_DELETE
CommandCount=1

[CLS:CExtendRichEdit]
Type=0
HeaderFile=ExtendRichEdit.h
ImplementationFile=ExtendRichEdit.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CExtendRichEdit

[CLS:CExtendRichEditCtrl]
Type=0
HeaderFile=ExtendRichEditCtrl.h
ImplementationFile=ExtendRichEditCtrl.cpp
BaseClass=CRichEditCtrl
Filter=W
VirtualFilter=WC
LastObject=CExtendRichEditCtrl

[ACL:IDR_ACCELERATOR_RICKEDITCTRL]
Type=1
Class=?
Command1=IDR_CTRL_A2
Command2=IDR_CTRL_C2
Command3=IDR_CTRL_LINK
Command4=IDR_CTRL_V2
Command5=IDR_CTRL_X2
Command6=IDR_CTRL_Z2
CommandCount=6

[ACL:IDR_ACCELERATOR_EDIT]
Type=1
Class=?
Command1=IDR_CTRL_A
Command2=IDR_CTRL_C
Command3=IDR_CTRL_V
Command4=IDR_DOWN
Command5=IDR_UP
Command6=IDR_CTRL_X
Command7=IDR_CTRL_Z
CommandCount=7

[CLS:CExtendButton]
Type=0
HeaderFile=ExtendButton.h
ImplementationFile=ExtendButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CExtendButton

[DLG:IDD_DIALOG_Suspension]
Type=1
Class=CSuspensionDlg
ControlCount=1
Control1=IDC_LIST1,listbox,1352728833

[CLS:CSuspensionDlg]
Type=0
HeaderFile=SuspensionDlg.h
ImplementationFile=SuspensionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[MNU:IDR_MENU_RICHEDIT]
Type=1
Class=?
Command1=ID_MENUITEM_INSERTHREF
Command2=ID_MENUITEM_INSERTIMG
Command3=ID_MENUITEM_INSERTAUDIO
Command4=ID_MENUITEM_INSERTVEDIO
CommandCount=4

[DLG:IDD_DIALOG_RICHEDIT_INSERT]
Type=1
Class=CInsertInfoDlg
ControlCount=1
Control1=IDC_EDIT1,edit,1350631552

[CLS:CInsertInfoDlg]
Type=0
HeaderFile=InsertInfoDlg.h
ImplementationFile=InsertInfoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInsertInfoDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_INSERTUSER]
Type=1
Class=CInsertUser
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LIST_From,listbox,1352728835
Control3=IDC_STATIC,button,1342177287
Control4=IDC_LIST_To,listbox,1352728835
Control5=IDOK,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_BUTTON_DEL,button,1342242816
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON_ADD,button,1342242816

[CLS:CInsertUser]
Type=0
HeaderFile=InsertUser.h
ImplementationFile=InsertUser.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_HELP

