# Microsoft Developer Studio Project File - Name="Dfs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Dfs - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak" CFG="Dfs - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "Dfs - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "Dfs - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Dfs - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\NSViews" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 NSViews\Release\NSViews.lib StaDev\32BIT\Stadev32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\NSViews" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 .\NSViews\Debug\NSViews.lib .\StaDev\32BIT\Stadev32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Dfs - Win32 Release"
# Name "Dfs - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\Array_f.cpp
# End Source File
# Begin Source File

SOURCE=.\Dfs.cpp
# End Source File
# Begin Source File

SOURCE=.\Dfs.rc
# End Source File
# Begin Source File

SOURCE=.\DfsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DfsExperiment.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsExportPI.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageExperimentList.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageFixation.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropPagePerformance.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageTorquePI.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropSheetView.cpp
# End Source File
# Begin Source File

SOURCE=.\ElsPropSheetViewFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\InfDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\InfPropPageOverview.cpp
# End Source File
# Begin Source File

SOURCE=.\InfPropPagePerformance.cpp
# End Source File
# Begin Source File

SOURCE=.\InfPropSheetView.cpp
# End Source File
# Begin Source File

SOURCE=.\InfPropSheetViewFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\IntroView.cpp
# End Source File
# Begin Source File

SOURCE=.\IntroViewFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Array_f.h
# End Source File
# Begin Source File

SOURCE=.\Dfs.h
# End Source File
# Begin Source File

SOURCE=.\DfsDoc.h
# End Source File
# Begin Source File

SOURCE=.\DfsExperiment.h
# End Source File
# Begin Source File

SOURCE=.\ElsDoc.h
# End Source File
# Begin Source File

SOURCE=.\ElsExportPI.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageExperimentList.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageFixation.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropPagePerformance.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropPageTorquePI.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropSheetView.h
# End Source File
# Begin Source File

SOURCE=.\ElsPropSheetViewFrm.h
# End Source File
# Begin Source File

SOURCE=.\InfDoc.h
# End Source File
# Begin Source File

SOURCE=.\InfPropPageOverview.h
# End Source File
# Begin Source File

SOURCE=.\InfPropPagePerformance.h
# End Source File
# Begin Source File

SOURCE=.\InfPropSheetView.h
# End Source File
# Begin Source File

SOURCE=.\InfPropSheetViewFrm.h
# End Source File
# Begin Source File

SOURCE=.\IntroView.h
# End Source File
# Begin Source File

SOURCE=.\IntroViewFrm.h
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
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Dfs.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DfsDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\droso.bmp
# End Source File
# Begin Source File

SOURCE=.\res\droso.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_inft.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
