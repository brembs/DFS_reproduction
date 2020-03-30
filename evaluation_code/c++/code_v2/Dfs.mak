# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Dfs - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Dfs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Dfs - Win32 Release" && "$(CFG)" != "Dfs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak" CFG="Dfs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Dfs - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Dfs - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Dfs - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Dfs - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Dfs.exe"

CLEAN : 
	-@erase "$(INTDIR)\Array_f.obj"
	-@erase "$(INTDIR)\Dfs.obj"
	-@erase "$(INTDIR)\Dfs.pch"
	-@erase "$(INTDIR)\Dfs.res"
	-@erase "$(INTDIR)\DfsDoc.obj"
	-@erase "$(INTDIR)\DfsExperiment.obj"
	-@erase "$(INTDIR)\ElsDoc.obj"
	-@erase "$(INTDIR)\ElsExportPI.obj"
	-@erase "$(INTDIR)\ElsPropPageExperimentList.obj"
	-@erase "$(INTDIR)\ElsPropPageFixation.obj"
	-@erase "$(INTDIR)\ElsPropPagePerformance.obj"
	-@erase "$(INTDIR)\ElsPropPageTorquePI.obj"
	-@erase "$(INTDIR)\ElsPropSheetView.obj"
	-@erase "$(INTDIR)\ElsPropSheetViewFrm.obj"
	-@erase "$(INTDIR)\InfDoc.obj"
	-@erase "$(INTDIR)\InfPropPageOverview.obj"
	-@erase "$(INTDIR)\InfPropPagePerformance.obj"
	-@erase "$(INTDIR)\InfPropSheetView.obj"
	-@erase "$(INTDIR)\InfPropSheetViewFrm.obj"
	-@erase "$(INTDIR)\IntroView.obj"
	-@erase "$(INTDIR)\IntroViewFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Dfs.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\NSViews" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\NSViews" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dfs.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dfs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dfs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\NSViews\Release\NSViews.lib ..\StaDev\32BIT\Stadev32.lib;d:\brembs\C++\DFS2\NSViews\debug\NSViews.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=..\NSViews\Release\NSViews.lib\
 ..\StaDev\32BIT\Stadev32.lib;d:\brembs\C++\DFS2\NSViews\debug\NSViews.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Dfs.pdb" /machine:I386\
 /out:"$(OUTDIR)/Dfs.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Array_f.obj" \
	"$(INTDIR)\Dfs.obj" \
	"$(INTDIR)\Dfs.res" \
	"$(INTDIR)\DfsDoc.obj" \
	"$(INTDIR)\DfsExperiment.obj" \
	"$(INTDIR)\ElsDoc.obj" \
	"$(INTDIR)\ElsExportPI.obj" \
	"$(INTDIR)\ElsPropPageExperimentList.obj" \
	"$(INTDIR)\ElsPropPageFixation.obj" \
	"$(INTDIR)\ElsPropPagePerformance.obj" \
	"$(INTDIR)\ElsPropPageTorquePI.obj" \
	"$(INTDIR)\ElsPropSheetView.obj" \
	"$(INTDIR)\ElsPropSheetViewFrm.obj" \
	"$(INTDIR)\InfDoc.obj" \
	"$(INTDIR)\InfPropPageOverview.obj" \
	"$(INTDIR)\InfPropPagePerformance.obj" \
	"$(INTDIR)\InfPropSheetView.obj" \
	"$(INTDIR)\InfPropSheetViewFrm.obj" \
	"$(INTDIR)\IntroView.obj" \
	"$(INTDIR)\IntroViewFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Dfs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Dfs.exe"

CLEAN : 
	-@erase "$(INTDIR)\Array_f.obj"
	-@erase "$(INTDIR)\Dfs.obj"
	-@erase "$(INTDIR)\Dfs.pch"
	-@erase "$(INTDIR)\Dfs.res"
	-@erase "$(INTDIR)\DfsDoc.obj"
	-@erase "$(INTDIR)\DfsExperiment.obj"
	-@erase "$(INTDIR)\ElsDoc.obj"
	-@erase "$(INTDIR)\ElsExportPI.obj"
	-@erase "$(INTDIR)\ElsPropPageExperimentList.obj"
	-@erase "$(INTDIR)\ElsPropPageFixation.obj"
	-@erase "$(INTDIR)\ElsPropPagePerformance.obj"
	-@erase "$(INTDIR)\ElsPropPageTorquePI.obj"
	-@erase "$(INTDIR)\ElsPropSheetView.obj"
	-@erase "$(INTDIR)\ElsPropSheetViewFrm.obj"
	-@erase "$(INTDIR)\InfDoc.obj"
	-@erase "$(INTDIR)\InfPropPageOverview.obj"
	-@erase "$(INTDIR)\InfPropPagePerformance.obj"
	-@erase "$(INTDIR)\InfPropSheetView.obj"
	-@erase "$(INTDIR)\InfPropSheetViewFrm.obj"
	-@erase "$(INTDIR)\IntroView.obj"
	-@erase "$(INTDIR)\IntroViewFrm.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Dfs.exe"
	-@erase "$(OUTDIR)\Dfs.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\NSViews" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\NSViews" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dfs.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Dfs.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dfs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 d:\brembs\C++\DFS2\NSViews\Debug\NSViews.lib d:\brembs\C++\DFS2\StaDev\32BIT\Stadev32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386
LINK32_FLAGS=d:\brembs\C++\DFS2\NSViews\Debug\NSViews.lib\
 d:\brembs\C++\DFS2\StaDev\32BIT\Stadev32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Dfs.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Dfs.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Array_f.obj" \
	"$(INTDIR)\Dfs.obj" \
	"$(INTDIR)\Dfs.res" \
	"$(INTDIR)\DfsDoc.obj" \
	"$(INTDIR)\DfsExperiment.obj" \
	"$(INTDIR)\ElsDoc.obj" \
	"$(INTDIR)\ElsExportPI.obj" \
	"$(INTDIR)\ElsPropPageExperimentList.obj" \
	"$(INTDIR)\ElsPropPageFixation.obj" \
	"$(INTDIR)\ElsPropPagePerformance.obj" \
	"$(INTDIR)\ElsPropPageTorquePI.obj" \
	"$(INTDIR)\ElsPropSheetView.obj" \
	"$(INTDIR)\ElsPropSheetViewFrm.obj" \
	"$(INTDIR)\InfDoc.obj" \
	"$(INTDIR)\InfPropPageOverview.obj" \
	"$(INTDIR)\InfPropPagePerformance.obj" \
	"$(INTDIR)\InfPropSheetView.obj" \
	"$(INTDIR)\InfPropSheetViewFrm.obj" \
	"$(INTDIR)\IntroView.obj" \
	"$(INTDIR)\IntroViewFrm.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Dfs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Dfs - Win32 Release"
# Name "Dfs - Win32 Debug"

!IF  "$(CFG)" == "Dfs - Win32 Release"

!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Dfs.cpp
DEP_CPP_DFS_C=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsDoc.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsPropPageExperimentList.h"\
	".\ElsPropPageFixation.h"\
	".\ElsPropPagePerformance.h"\
	".\ElsPropPageTorquePI.h"\
	".\ElsPropSheetView.h"\
	".\ElsPropSheetViewFrm.h"\
	".\InfDoc.h"\
	".\InfPropPageOverview.h"\
	".\InfPropPagePerformance.h"\
	".\InfPropSheetView.h"\
	".\InfPropSheetViewFrm.h"\
	".\IntroView.h"\
	".\IntroViewFrm.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexFormView.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	{$(INCLUDE)}"\NSFlexPropertySheet.h"\
	{$(INCLUDE)}"\NSFlexPropertySheetView.h"\
	

"$(INTDIR)\Dfs.obj" : $(SOURCE) $(DEP_CPP_DFS_C) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Dfs - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\NSViews" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dfs.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dfs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\NSViews" /D "WIN32" /D "_DEBUG"\
 /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Dfs.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dfs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\Dfs.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DfsDoc.cpp
DEP_CPP_DFSDO=\
	".\Dfs.h"\
	".\DfsDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DfsDoc.obj" : $(SOURCE) $(DEP_CPP_DFSDO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dfs.rc
DEP_RSC_DFS_R=\
	".\res\Dfs.rc2"\
	".\res\DfsDoc.ico"\
	".\res\droso.bmp"\
	".\res\droso.ico"\
	".\res\idr_inft.ico"\
	".\res\idr_main.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\Dfs.res" : $(SOURCE) $(DEP_RSC_DFS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntroViewFrm.cpp
DEP_CPP_INTRO=\
	".\Dfs.h"\
	".\IntroViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	

"$(INTDIR)\IntroViewFrm.obj" : $(SOURCE) $(DEP_CPP_INTRO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntroView.cpp
DEP_CPP_INTROV=\
	".\Dfs.h"\
	".\DfsDoc.h"\
	".\IntroView.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexFormView.h"\
	

"$(INTDIR)\IntroView.obj" : $(SOURCE) $(DEP_CPP_INTROV) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropPageExperimentList.cpp

!IF  "$(CFG)" == "Dfs - Win32 Release"

DEP_CPP_ELSPR=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsPropPageExperimentList.h"\
	".\ElsPropSheetViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPageExperimentList.obj" : $(SOURCE) $(DEP_CPP_ELSPR)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

DEP_CPP_ELSPR=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsPropPageExperimentList.h"\
	".\ElsPropSheetViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPageExperimentList.obj" : $(SOURCE) $(DEP_CPP_ELSPR)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropSheetViewFrm.cpp
DEP_CPP_ELSPRO=\
	".\Dfs.h"\
	".\ElsPropSheetViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	

"$(INTDIR)\ElsPropSheetViewFrm.obj" : $(SOURCE) $(DEP_CPP_ELSPRO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropSheetView.cpp
DEP_CPP_ELSPROP=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsPropPageExperimentList.h"\
	".\ElsPropPageFixation.h"\
	".\ElsPropPagePerformance.h"\
	".\ElsPropPageTorquePI.h"\
	".\ElsPropSheetView.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	{$(INCLUDE)}"\NSFlexPropertySheet.h"\
	{$(INCLUDE)}"\NSFlexPropertySheetView.h"\
	

"$(INTDIR)\ElsPropSheetView.obj" : $(SOURCE) $(DEP_CPP_ELSPROP) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\InfDoc.cpp
DEP_CPP_INFDO=\
	".\Dfs.h"\
	".\InfDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\InfDoc.obj" : $(SOURCE) $(DEP_CPP_INFDO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsDoc.cpp
DEP_CPP_ELSDO=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ElsDoc.obj" : $(SOURCE) $(DEP_CPP_ELSDO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\InfPropPageOverview.cpp
DEP_CPP_INFPR=\
	".\Dfs.h"\
	".\InfPropPageOverview.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\InfPropPageOverview.obj" : $(SOURCE) $(DEP_CPP_INFPR) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\InfPropPagePerformance.cpp
DEP_CPP_INFPRO=\
	".\Dfs.h"\
	".\InfPropPagePerformance.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\InfPropPagePerformance.obj" : $(SOURCE) $(DEP_CPP_INFPRO)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\InfPropSheetView.cpp
DEP_CPP_INFPROP=\
	".\Dfs.h"\
	".\InfPropPageOverview.h"\
	".\InfPropPagePerformance.h"\
	".\InfPropSheetView.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	{$(INCLUDE)}"\NSFlexPropertySheet.h"\
	{$(INCLUDE)}"\NSFlexPropertySheetView.h"\
	

"$(INTDIR)\InfPropSheetView.obj" : $(SOURCE) $(DEP_CPP_INFPROP) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\InfPropSheetViewFrm.cpp
DEP_CPP_INFPROPS=\
	".\Dfs.h"\
	".\InfPropSheetViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	

"$(INTDIR)\InfPropSheetViewFrm.obj" : $(SOURCE) $(DEP_CPP_INFPROPS) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropPageFixation.cpp
DEP_CPP_ELSPROPP=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\ElsPropPageFixation.h"\
	".\ElsPropSheetViewFrm.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexMDIChildWnd.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPageFixation.obj" : $(SOURCE) $(DEP_CPP_ELSPROPP) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropPagePerformance.cpp

!IF  "$(CFG)" == "Dfs - Win32 Release"

DEP_CPP_ELSPROPPA=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\ElsPropPagePerformance.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPagePerformance.obj" : $(SOURCE) $(DEP_CPP_ELSPROPPA)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

DEP_CPP_ELSPROPPA=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\ElsPropPagePerformance.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPagePerformance.obj" : $(SOURCE) $(DEP_CPP_ELSPROPPA)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Array_f.cpp
DEP_CPP_ARRAY=\
	".\Array_f.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Array_f.obj" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DfsExperiment.cpp
DEP_CPP_DFSEX=\
	".\Array_f.h"\
	".\DfsExperiment.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DfsExperiment.obj" : $(SOURCE) $(DEP_CPP_DFSEX) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsExportPI.cpp
DEP_CPP_ELSEX=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\stadev32.h"\
	

"$(INTDIR)\ElsExportPI.obj" : $(SOURCE) $(DEP_CPP_ELSEX) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ElsPropPageTorquePI.cpp

!IF  "$(CFG)" == "Dfs - Win32 Release"

DEP_CPP_ELSPROPPAG=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\ElsPropPageTorquePI.h"\
	".\StdAfx.h"\
	"C:\Msdev\NSViews\NSFlexConstraints.h"\
	"C:\Msdev\NSViews\NSViewsAfxExt.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPageTorquePI.obj" : $(SOURCE) $(DEP_CPP_ELSPROPPAG)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ELSEIF  "$(CFG)" == "Dfs - Win32 Debug"

DEP_CPP_ELSPROPPAG=\
	".\Array_f.h"\
	".\Dfs.h"\
	".\DfsExperiment.h"\
	".\ElsDoc.h"\
	".\ElsExportPI.h"\
	".\ElsPropPageTorquePI.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\NSFlexPropertyPage.h"\
	

"$(INTDIR)\ElsPropPageTorquePI.obj" : $(SOURCE) $(DEP_CPP_ELSPROPPAG)\
 "$(INTDIR)" "$(INTDIR)\Dfs.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
