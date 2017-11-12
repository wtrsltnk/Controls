# Microsoft Developer Studio Project File - Name="Controls" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Controls - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Controls.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Controls.mak" CFG="Controls - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Controls - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Controls - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Controls - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTROLS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTROLS_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../bin/Wouter.Controls.dll"

!ELSEIF  "$(CFG)" == "Controls - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTROLS_EXPORTS" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "CONTROLS_EXPORTS" /D "DIALOGS_EXPORTS" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comctl32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../bin/debug/Wouter.Controls.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Controls - Win32 Release"
# Name "Controls - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonControl.cpp
# End Source File
# Begin Source File

SOURCE=.\Control.cpp
# End Source File
# Begin Source File

SOURCE=.\ControlError.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomControl.cpp
# End Source File
# Begin Source File

SOURCE=.\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ListView.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitterControl.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\Window.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Button.h
# End Source File
# Begin Source File

SOURCE=.\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\ComboListBox.h
# End Source File
# Begin Source File

SOURCE=.\CommonControl.h
# End Source File
# Begin Source File

SOURCE=.\Control.h
# End Source File
# Begin Source File

SOURCE=.\ControlError.h
# End Source File
# Begin Source File

SOURCE=.\Controls.h
# End Source File
# Begin Source File

SOURCE=.\CustomControl.h
# End Source File
# Begin Source File

SOURCE=.\EditBox.h
# End Source File
# Begin Source File

SOURCE=.\ListBox.h
# End Source File
# Begin Source File

SOURCE=.\ListView.h
# End Source File
# Begin Source File

SOURCE=.\SplitterControl.h
# End Source File
# Begin Source File

SOURCE=.\StatusBar.h
# End Source File
# Begin Source File

SOURCE=.\ToolBox.h
# End Source File
# Begin Source File

SOURCE=.\ToolBoxControl.h
# End Source File
# Begin Source File

SOURCE=.\TreeView.h
# End Source File
# Begin Source File

SOURCE=.\Window.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource\resource.h
# End Source File
# Begin Source File

SOURCE=.\resource\resource.rc
# End Source File
# End Group
# End Target
# End Project
