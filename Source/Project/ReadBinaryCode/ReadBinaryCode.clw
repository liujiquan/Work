; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAssemblyDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ReadBinaryCode.h"

ClassCount=8
Class1=CReadBinaryCodeApp
Class2=CReadBinaryCodeDlg
Class3=CAboutDlg

ResourceCount=10
Resource1=IDD_READBINARYCODE_DIALOG (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CDropFileEdit
Resource5=IDD_READBINARYCODE_DIALOG
Class5=CProcessInfo
Resource6=IDD_DIALOG_ACCEM_GO
Class6=CAssemblyDlg
Resource7=IDD_DIALOG_POOCESS
Resource8=IDD_DIALOG_ASSEMBLY
Class7=CAccembFindDlg
Resource9=IDD_DIALOG_ASSEM_FIND
Class8=CAssemGotoDlg
Resource10=IDR_ACCELERATOR1

[CLS:CReadBinaryCodeApp]
Type=0
HeaderFile=ReadBinaryCode.h
ImplementationFile=ReadBinaryCode.cpp
Filter=N

[CLS:CReadBinaryCodeDlg]
Type=0
HeaderFile=ReadBinaryCodeDlg.h
ImplementationFile=ReadBinaryCodeDlg.cpp
Filter=D
LastObject=IDC_EDIT_FILEPATH
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ReadBinaryCodeDlg.h
ImplementationFile=ReadBinaryCodeDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_READBINARYCODE_DIALOG]
Type=1
Class=CReadBinaryCodeDlg
ControlCount=19
Control1=IDC_EDIT_FILEPATH,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_LIST1,listbox,1353777417
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT4,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_BUTTON_Flush,button,1342242816
Control10=IDC_BUTTON_CreateFile,button,1342242816
Control11=IDC_BUTTON_OpenFile,button,1342242816
Control12=IDC_BUTTON_ASSEM,button,1342242816
Control13=IDC_STATIC,static,1342177284
Control14=IDC_STATIC,static,1342177284
Control15=IDC_STATIC,static,1342177284
Control16=IDC_STATIC,static,1342177284
Control17=IDC_STATIC,static,1342177284
Control18=IDC_STATIC,static,1342177284
Control19=IDC_STATIC,static,1342177284

[DLG:IDD_READBINARYCODE_DIALOG (English (U.S.))]
Type=1
Class=CReadBinaryCodeDlg
ControlCount=9
Control1=IDC_EDIT_FILEPATH,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_EDIT3,edit,1350631552
Control4=IDC_LIST1,listbox,1353777417
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT4,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_BUTTON_Flush,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CDropFileEdit]
Type=0
HeaderFile=DropFileEdit.h
ImplementationFile=DropFileEdit.cpp
BaseClass=CEdit
Filter=W

[DLG:IDD_DIALOG_POOCESS]
Type=1
Class=CProcessInfo
ControlCount=5
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_Flush,button,1342242816
Control4=IDC_LIST1,SysListView32,1350631425
Control5=IDC_STATIC,button,1342177287

[CLS:CProcessInfo]
Type=0
HeaderFile=ProcessInfo.h
ImplementationFile=ProcessInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProcessInfo

[DLG:IDD_DIALOG_ASSEMBLY]
Type=1
Class=CAssemblyDlg
ControlCount=2
Control1=IDC_RICHEDIT1,RICHEDIT,1353779396
Control2=IDC_EDIT1,edit,1085345988

[CLS:CAssemblyDlg]
Type=0
HeaderFile=AssemblyDlg.h
ImplementationFile=AssemblyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RICHEDIT1
VirtualFilter=dWC

[DLG:IDD_DIALOG_ASSEM_FIND]
Type=1
Class=CAccembFindDlg
ControlCount=10
Control1=IDC_BUTTON_FIND_NEXT,button,1342242816
Control2=IDC_BUTTON_MARK_ALL,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_FINDTEXT,combobox,1344340226
Control6=IDC_CHECK_MATCHALL,button,1342242819
Control7=IDC_CHECK_MATCHCASE,button,1342242819
Control8=IDC_RADIO_DOWN,button,1342308361
Control9=IDC_RADIO_UP,button,1342177289
Control10=IDC_STATIC,button,1342177287

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDR_FIND
Command2=IDR_GO
CommandCount=2

[CLS:CAccembFindDlg]
Type=0
HeaderFile=AccembFindDlg.h
ImplementationFile=AccembFindDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAccembFindDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_ACCEM_GO]
Type=1
Class=CAssemGotoDlg
ControlCount=7
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,button,1342177287
Control5=IDC_CHECK_LINE,button,1342373891
Control6=IDC_CHECK_ADDRESS,button,1342373891
Control7=IDC_STATIC,button,1342177287

[CLS:CAssemGotoDlg]
Type=0
HeaderFile=AssemGotoDlg.h
ImplementationFile=AssemGotoDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAssemGotoDlg

