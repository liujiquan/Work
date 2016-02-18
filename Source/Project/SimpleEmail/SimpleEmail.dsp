# Microsoft Developer Studio Project File - Name="SimpleEmail" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SimpleEmail - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SimpleEmail.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleEmail.mak" CFG="SimpleEmail - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleEmail - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SimpleEmail - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimpleEmail - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\include\gfxlog" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 gfxlog.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC" /libpath:"..\lib\gfxlog"
# Begin Custom Build
TargetName=SimpleEmail
InputPath=.\Release\SimpleEmail.exe
SOURCE="$(InputPath)"

"..\Bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\$(TargetName).exe  ..\Bin

# End Custom Build

!ELSEIF  "$(CFG)" == "SimpleEmail - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\include\gfxlog" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gfxlog.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD" /pdbtype:sept /libpath:"..\lib_debug\gfxlog"
# Begin Custom Build
TargetName=SimpleEmail
InputPath=.\Debug\SimpleEmail.exe
SOURCE="$(InputPath)"

"..\Bin_debug\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\$(TargetName).exe  ..\Bin_debug

# End Custom Build

!ENDIF 

# Begin Target

# Name "SimpleEmail - Win32 Release"
# Name "SimpleEmail - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SendMailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleEmail.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleEmailDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleEmailView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SendMailDlg.h
# End Source File
# Begin Source File

SOURCE=.\SimpleEmail.h
# End Source File
# Begin Source File

SOURCE=.\SimpleEmailDoc.h
# End Source File
# Begin Source File

SOURCE=.\SimpleEmailView.h
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

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\popup.ico
# End Source File
# Begin Source File

SOURCE=.\res\popupicon.ico
# End Source File
# Begin Source File

SOURCE=.\res\SimpleEmail.ico
# End Source File
# Begin Source File

SOURCE=.\SimpleEmail.rc
# End Source File
# Begin Source File

SOURCE=.\res\SimpleEmail.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SimpleEmailDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Base64.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Base64.h
# End Source File
# Begin Source File

SOURCE=.\Gfxsock.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Gfxsock.h
# End Source File
# Begin Source File

SOURCE=.\MailUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\MailUtil.h
# End Source File
# Begin Source File

SOURCE=.\URLEncode.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\URLEncode.h
# End Source File
# End Group
# Begin Group "listbox"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ExtendListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendListBox.h
# End Source File
# End Group
# Begin Group "edit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ExtendEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendEdit.h
# End Source File
# End Group
# Begin Group "richeditctrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ExtendRichEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendRichEdit.h
# End Source File
# Begin Source File

SOURCE=.\ExtendRichEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendRichEditCtrl.h
# End Source File
# End Group
# Begin Group "statusbar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ExtendStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendStatusBar.h
# End Source File
# End Group
# Begin Group "button"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ExtendButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtendButton.h
# End Source File
# End Group
# Begin Group "Dialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AccountInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountInfo.h
# End Source File
# Begin Source File

SOURCE=.\InsertInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\InsertUser.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertUser.h
# End Source File
# Begin Source File

SOURCE=.\InternetAccounts.cpp
# End Source File
# Begin Source File

SOURCE=.\InternetAccounts.h
# End Source File
# Begin Source File

SOURCE=.\SuspensionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SuspensionDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
