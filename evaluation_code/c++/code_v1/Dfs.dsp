# Microsoft Developer Studio Project File - Name="DFS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DFS - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak" CFG="DFS - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "DFS - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "DFS - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DFS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DFS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "DFS - Win32 Release"
# Name "DFS - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Array_f.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\D_ELS.cpp
# End Source File
# Begin Source File

SOURCE=.\D_INF.cpp
# End Source File
# Begin Source File

SOURCE=.\DFS.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\DFS.hpj

!IF  "$(CFG)" == "DFS - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Dfs
InputPath=.\hlp\DFS.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "DFS - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Dfs
InputPath=.\hlp\DFS.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DFS.rc
# End Source File
# Begin Source File

SOURCE=.\DFSDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DFSView.cpp
# End Source File
# Begin Source File

SOURCE=.\DgExpInd.cpp
# End Source File
# Begin Source File

SOURCE=.\Exprimnt.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\V_Dwell.cpp
# End Source File
# Begin Source File

SOURCE=.\V_ELS.cpp
# End Source File
# Begin Source File

SOURCE=.\V_ELSDwell.cpp
# End Source File
# Begin Source File

SOURCE=.\V_INF.cpp
# End Source File
# Begin Source File

SOURCE=.\V_MPerfIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\V_PerfIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\V_TimeTr.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Array_f.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\D_ELS.h
# End Source File
# Begin Source File

SOURCE=.\d_inf.h
# End Source File
# Begin Source File

SOURCE=.\DFS.h
# End Source File
# Begin Source File

SOURCE=.\DFSDoc.h
# End Source File
# Begin Source File

SOURCE=.\DFSView.h
# End Source File
# Begin Source File

SOURCE=.\DgExpInd.h
# End Source File
# Begin Source File

SOURCE=.\Exprimnt.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\V_Dwell.h
# End Source File
# Begin Source File

SOURCE=.\V_ELS.h
# End Source File
# Begin Source File

SOURCE=.\V_ELSDwell.h
# End Source File
# Begin Source File

SOURCE=.\V_INF.h
# End Source File
# Begin Source File

SOURCE=.\V_MPerfIndex.h
# End Source File
# Begin Source File

SOURCE=.\V_PerfIndex.h
# End Source File
# Begin Source File

SOURCE=.\V_TimeTr.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DFS.ico
# End Source File
# Begin Source File

SOURCE=.\res\DFS.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DFSDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\droshsw.bmp
# End Source File
# Begin Source File

SOURCE=.\res\droso.bmp
# End Source File
# Begin Source File

SOURCE=.\res\heat_0_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\heat_0_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\heat_90_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\heat_90_.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_elst.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
# Section DFS : {D893AFD3-B75E-11CF-A059-444553540000}
# 	1:17:CG_IDS_DISK_SPACE:103
# 	1:19:CG_IDS_PHYSICAL_MEM:102
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:104
# 	2:10:SysInfoKey:1234
# End Section
# Section DFS : {D893AFD2-B75E-11CF-A059-444553540000}
# 	1:17:ID_INDICATOR_TIME:105
# 	2:2:BH:
# 	2:17:ID_INDICATOR_TIME:ID_INDICATOR_TIME
# End Section
