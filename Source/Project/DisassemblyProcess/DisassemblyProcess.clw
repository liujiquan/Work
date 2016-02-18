; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExtendListBox
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DisassemblyProcess.h"

ClassCount=6
Class1=CDisassemblyProcessApp
Class2=CDisassemblyProcessDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DISASSEMBLYPROCESS_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_POOCESS
Class4=CProcessInfo
Class5=CExtendListBox
Class6=CExtendListCtrl
Resource4=IDD_ABOUTBOX
Resource5=IDR_ACCELERATOR1

[CLS:CDisassemblyProcessApp]
Type=0
HeaderFile=DisassemblyProcess.h
ImplementationFile=DisassemblyProcess.cpp
Filter=N

[CLS:CDisassemblyProcessDlg]
Type=0
HeaderFile=DisassemblyProcessDlg.h
ImplementationFile=DisassemblyProcessDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST2

[CLS:CAboutDlg]
Type=0
HeaderFile=DisassemblyProcessDlg.h
ImplementationFile=DisassemblyProcessDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DISASSEMBLYPROCESS_DIALOG]
Type=1
Class=CDisassemblyProcessDlg
ControlCount=4
Control1=IDC_COMBO1,combobox,1344340226
Control2=IDC_BUTTON_OPEN,button,1342242816
Control3=IDC_LIST1,listbox,1352730961
Control4=IDC_CHECK_FUNC_RVA,button,1342242819

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
LastObject=CProcessInfo
VirtualFilter=dWC

[CLS:CExtendListBox]
Type=0
HeaderFile=ExtendListBox.h
ImplementationFile=ExtendListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CExtendListBox

[CLS:CExtendListCtrl]
Type=0
HeaderFile=ExtendListCtrl.h
ImplementationFile=ExtendListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CExtendListCtrl

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDR_CTRL_A
Command2=IDR_CTRL_C
CommandCount=2

