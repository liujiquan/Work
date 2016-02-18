# Microsoft Developer Studio Project File - Name="PEShow" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PEShow - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PEShow.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PEShow.mak" CFG="PEShow - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PEShow - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PEShow - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PEShow - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PEShow - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PEShow - Win32 Release"
# Name "PEShow - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DosHeaderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\NTHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\PEShow.cpp
# End Source File
# Begin Source File

SOURCE=.\PEShow.rc
# End Source File
# Begin Source File

SOURCE=.\PEShowDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PEShowView.cpp
# End Source File
# Begin Source File

SOURCE=.\PEStruct.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowMemory.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DosHeaderDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\NTHeader.h
# End Source File
# Begin Source File

SOURCE=.\PEShow.h
# End Source File
# Begin Source File

SOURCE=.\PEShowDoc.h
# End Source File
# Begin Source File

SOURCE=.\PEShowView.h
# End Source File
# Begin Source File

SOURCE=.\PEStruct.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowMemory.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\folders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PEShow.ico
# End Source File
# Begin Source File

SOURCE=.\res\PEShow.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PEShowDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "SuperGridCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SuperGridCtrl\ComboInListView.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\ComboInListView.h
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\listeditctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\listeditctrl.h
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\MySuperGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\MySuperGrid.h
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\supergridctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperGridCtrl\supergridctrl.h
# End Source File
# End Group
# Begin Group "PEFIles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\addItem_MS_DOS_Stub.cpp
# End Source File
# Begin Source File

SOURCE=.\addItemIMAGE_DOS_HEADER.cpp
# End Source File
# Begin Source File

SOURCE=.\AddItemIMAGE_NT_HEADER.cpp
# End Source File
# Begin Source File

SOURCE=.\addItemIMAGE_SECTION_HEADER.cpp
# End Source File
# Begin Source File

SOURCE=.\PEFileHeader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\PEFileHeader.h
# End Source File
# End Group
# Begin Group "Directory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\addItem_DirBoudImportTable.cpp
# End Source File
# Begin Source File

SOURCE=.\addItem_DirExportSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\addItem_DirImportSymbols.cpp
# End Source File
# Begin Source File

SOURCE=.\addItem_DirResourceTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DirBoundImportPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirBoundImportPage.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DirExportPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirExportPage.h
# End Source File
# Begin Source File

SOURCE=.\DirImportPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirImportPage.h
# End Source File
# Begin Source File

SOURCE=.\DirResourcePage.cpp
# End Source File
# Begin Source File

SOURCE=.\DirResourcePage.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
