# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DFS - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DFS - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DFS - Win32 Release" && "$(CFG)" != "DFS - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Dfs.mak" CFG="DFS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DFS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DFS - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DFS - Win32 Debug"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DFS - Win32 Release"

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

ALL : "$(OUTDIR)\Dfs.exe" "$(OUTDIR)\Dfs.bsc" "$(OUTDIR)\Dfs.hlp"

CLEAN : 
	-@erase "$(INTDIR)\Array_f.obj"
	-@erase "$(INTDIR)\Array_f.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\D_ELS.obj"
	-@erase "$(INTDIR)\D_ELS.sbr"
	-@erase "$(INTDIR)\D_INF.obj"
	-@erase "$(INTDIR)\D_INF.sbr"
	-@erase "$(INTDIR)\Dfs.hlp"
	-@erase "$(INTDIR)\DFS.obj"
	-@erase "$(INTDIR)\Dfs.pch"
	-@erase "$(INTDIR)\DFS.res"
	-@erase "$(INTDIR)\DFS.sbr"
	-@erase "$(INTDIR)\DFSDoc.obj"
	-@erase "$(INTDIR)\DFSDoc.sbr"
	-@erase "$(INTDIR)\DFSView.obj"
	-@erase "$(INTDIR)\DFSView.sbr"
	-@erase "$(INTDIR)\DgExpInd.obj"
	-@erase "$(INTDIR)\DgExpInd.sbr"
	-@erase "$(INTDIR)\Exprimnt.obj"
	-@erase "$(INTDIR)\Exprimnt.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\V_Dwell.obj"
	-@erase "$(INTDIR)\V_Dwell.sbr"
	-@erase "$(INTDIR)\V_ELS.obj"
	-@erase "$(INTDIR)\V_ELS.sbr"
	-@erase "$(INTDIR)\V_ELSDwell.obj"
	-@erase "$(INTDIR)\V_ELSDwell.sbr"
	-@erase "$(INTDIR)\V_INF.obj"
	-@erase "$(INTDIR)\V_INF.sbr"
	-@erase "$(INTDIR)\V_MPerfIndex.obj"
	-@erase "$(INTDIR)\V_MPerfIndex.sbr"
	-@erase "$(INTDIR)\V_PerfIndex.obj"
	-@erase "$(INTDIR)\V_PerfIndex.sbr"
	-@erase "$(INTDIR)\V_TimeTr.obj"
	-@erase "$(INTDIR)\V_TimeTr.sbr"
	-@erase "$(OUTDIR)\Dfs.bsc"
	-@erase "$(OUTDIR)\Dfs.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DFS.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dfs.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Array_f.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\D_ELS.sbr" \
	"$(INTDIR)\D_INF.sbr" \
	"$(INTDIR)\DFS.sbr" \
	"$(INTDIR)\DFSDoc.sbr" \
	"$(INTDIR)\DFSView.sbr" \
	"$(INTDIR)\DgExpInd.sbr" \
	"$(INTDIR)\Exprimnt.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\V_Dwell.sbr" \
	"$(INTDIR)\V_ELS.sbr" \
	"$(INTDIR)\V_ELSDwell.sbr" \
	"$(INTDIR)\V_INF.sbr" \
	"$(INTDIR)\V_MPerfIndex.sbr" \
	"$(INTDIR)\V_PerfIndex.sbr" \
	"$(INTDIR)\V_TimeTr.sbr"

"$(OUTDIR)\Dfs.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Dfs.pdb" /machine:I386 /out:"$(OUTDIR)/Dfs.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Array_f.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\D_ELS.obj" \
	"$(INTDIR)\D_INF.obj" \
	"$(INTDIR)\DFS.obj" \
	"$(INTDIR)\DFS.res" \
	"$(INTDIR)\DFSDoc.obj" \
	"$(INTDIR)\DFSView.obj" \
	"$(INTDIR)\DgExpInd.obj" \
	"$(INTDIR)\Exprimnt.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\V_Dwell.obj" \
	"$(INTDIR)\V_ELS.obj" \
	"$(INTDIR)\V_ELSDwell.obj" \
	"$(INTDIR)\V_INF.obj" \
	"$(INTDIR)\V_MPerfIndex.obj" \
	"$(INTDIR)\V_PerfIndex.obj" \
	"$(INTDIR)\V_TimeTr.obj"

"$(OUTDIR)\Dfs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DFS - Win32 Debug"

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

ALL : "$(OUTDIR)\Dfs.exe" "$(OUTDIR)\Dfs.bsc" "$(OUTDIR)\Dfs.hlp"

CLEAN : 
	-@erase "$(INTDIR)\Array_f.obj"
	-@erase "$(INTDIR)\Array_f.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\D_ELS.obj"
	-@erase "$(INTDIR)\D_ELS.sbr"
	-@erase "$(INTDIR)\D_INF.obj"
	-@erase "$(INTDIR)\D_INF.sbr"
	-@erase "$(INTDIR)\Dfs.hlp"
	-@erase "$(INTDIR)\DFS.obj"
	-@erase "$(INTDIR)\Dfs.pch"
	-@erase "$(INTDIR)\DFS.res"
	-@erase "$(INTDIR)\DFS.sbr"
	-@erase "$(INTDIR)\DFSDoc.obj"
	-@erase "$(INTDIR)\DFSDoc.sbr"
	-@erase "$(INTDIR)\DFSView.obj"
	-@erase "$(INTDIR)\DFSView.sbr"
	-@erase "$(INTDIR)\DgExpInd.obj"
	-@erase "$(INTDIR)\DgExpInd.sbr"
	-@erase "$(INTDIR)\Exprimnt.obj"
	-@erase "$(INTDIR)\Exprimnt.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\V_Dwell.obj"
	-@erase "$(INTDIR)\V_Dwell.sbr"
	-@erase "$(INTDIR)\V_ELS.obj"
	-@erase "$(INTDIR)\V_ELS.sbr"
	-@erase "$(INTDIR)\V_ELSDwell.obj"
	-@erase "$(INTDIR)\V_ELSDwell.sbr"
	-@erase "$(INTDIR)\V_INF.obj"
	-@erase "$(INTDIR)\V_INF.sbr"
	-@erase "$(INTDIR)\V_MPerfIndex.obj"
	-@erase "$(INTDIR)\V_MPerfIndex.sbr"
	-@erase "$(INTDIR)\V_PerfIndex.obj"
	-@erase "$(INTDIR)\V_PerfIndex.sbr"
	-@erase "$(INTDIR)\V_TimeTr.obj"
	-@erase "$(INTDIR)\V_TimeTr.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Dfs.bsc"
	-@erase "$(OUTDIR)\Dfs.exe"
	-@erase "$(OUTDIR)\Dfs.ilk"
	-@erase "$(OUTDIR)\Dfs.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DFS.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Dfs.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Array_f.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\D_ELS.sbr" \
	"$(INTDIR)\D_INF.sbr" \
	"$(INTDIR)\DFS.sbr" \
	"$(INTDIR)\DFSDoc.sbr" \
	"$(INTDIR)\DFSView.sbr" \
	"$(INTDIR)\DgExpInd.sbr" \
	"$(INTDIR)\Exprimnt.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\V_Dwell.sbr" \
	"$(INTDIR)\V_ELS.sbr" \
	"$(INTDIR)\V_ELSDwell.sbr" \
	"$(INTDIR)\V_INF.sbr" \
	"$(INTDIR)\V_MPerfIndex.sbr" \
	"$(INTDIR)\V_PerfIndex.sbr" \
	"$(INTDIR)\V_TimeTr.sbr"

"$(OUTDIR)\Dfs.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Dfs.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Dfs.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Array_f.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\D_ELS.obj" \
	"$(INTDIR)\D_INF.obj" \
	"$(INTDIR)\DFS.obj" \
	"$(INTDIR)\DFS.res" \
	"$(INTDIR)\DFSDoc.obj" \
	"$(INTDIR)\DFSView.obj" \
	"$(INTDIR)\DgExpInd.obj" \
	"$(INTDIR)\Exprimnt.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\V_Dwell.obj" \
	"$(INTDIR)\V_ELS.obj" \
	"$(INTDIR)\V_ELSDwell.obj" \
	"$(INTDIR)\V_INF.obj" \
	"$(INTDIR)\V_MPerfIndex.obj" \
	"$(INTDIR)\V_PerfIndex.obj" \
	"$(INTDIR)\V_TimeTr.obj"

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

# Name "DFS - Win32 Release"
# Name "DFS - Win32 Debug"

!IF  "$(CFG)" == "DFS - Win32 Release"

!ELSEIF  "$(CFG)" == "DFS - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DFS.cpp
DEP_CPP_DFS_C=\
	".\Array_f.h"\
	".\ChildFrm.h"\
	".\D_ELS.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\DFSDoc.h"\
	".\DFSView.h"\
	".\Exprimnt.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\V_Dwell.h"\
	".\V_ELS.h"\
	".\V_ELSDwell.h"\
	".\V_INF.h"\
	".\V_MPerfIndex.h"\
	".\V_PerfIndex.h"\
	".\V_TimeTr.h"\
	

"$(INTDIR)\DFS.obj" : $(SOURCE) $(DEP_CPP_DFS_C) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\DFS.sbr" : $(SOURCE) $(DEP_CPP_DFS_C) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DFS - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Dfs.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dfs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DFS - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Dfs.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dfs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\DFS.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	".\V_Dwell.h"\
	".\V_ELSDwell.h"\
	".\V_INF.h"\
	".\V_MPerfIndex.h"\
	".\V_PerfIndex.h"\
	".\V_TimeTr.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\ChildFrm.h"\
	".\DFS.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DFSDoc.cpp
DEP_CPP_DFSDO=\
	".\DFS.h"\
	".\DFSDoc.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DFSDoc.obj" : $(SOURCE) $(DEP_CPP_DFSDO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\DFSDoc.sbr" : $(SOURCE) $(DEP_CPP_DFSDO) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DFSView.cpp
DEP_CPP_DFSVI=\
	".\DFS.h"\
	".\DFSDoc.h"\
	".\DFSView.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\DFSView.obj" : $(SOURCE) $(DEP_CPP_DFSVI) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\DFSView.sbr" : $(SOURCE) $(DEP_CPP_DFSVI) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DFS.rc
DEP_RSC_DFS_R=\
	".\res\DFS.ico"\
	".\res\DFS.rc2"\
	".\res\DFSDoc.ico"\
	".\res\droshsw.bmp"\
	".\res\droso.bmp"\
	".\res\heat_0_1.bmp"\
	".\res\heat_0_1.ico"\
	".\res\heat_90_.bmp"\
	".\res\heat_90_.ico"\
	".\res\ico00001.ico"\
	".\res\ico00002.ico"\
	".\res\idr_elst.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\DFS.res" : $(SOURCE) $(DEP_RSC_DFS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
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
################################################################################
# Begin Source File

SOURCE=.\Exprimnt.cpp
DEP_CPP_EXPRI=\
	".\Array_f.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Exprimnt.obj" : $(SOURCE) $(DEP_CPP_EXPRI) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\Exprimnt.sbr" : $(SOURCE) $(DEP_CPP_EXPRI) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Array_f.cpp
DEP_CPP_ARRAY=\
	".\Array_f.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\Array_f.obj" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\Array_f.sbr" : $(SOURCE) $(DEP_CPP_ARRAY) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\D_ELS.cpp
DEP_CPP_D_ELS=\
	".\Array_f.h"\
	".\D_ELS.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_ELS.h"\
	

"$(INTDIR)\D_ELS.obj" : $(SOURCE) $(DEP_CPP_D_ELS) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\D_ELS.sbr" : $(SOURCE) $(DEP_CPP_D_ELS) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_ELS.cpp
DEP_CPP_V_ELS=\
	".\Array_f.h"\
	".\D_ELS.h"\
	".\DFS.h"\
	".\DgExpInd.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_ELS.h"\
	

"$(INTDIR)\V_ELS.obj" : $(SOURCE) $(DEP_CPP_V_ELS) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_ELS.sbr" : $(SOURCE) $(DEP_CPP_V_ELS) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_INF.cpp
DEP_CPP_V_INF=\
	".\Array_f.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_INF.h"\
	

"$(INTDIR)\V_INF.obj" : $(SOURCE) $(DEP_CPP_V_INF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_INF.sbr" : $(SOURCE) $(DEP_CPP_V_INF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\D_INF.cpp
DEP_CPP_D_INF=\
	".\Array_f.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\D_INF.obj" : $(SOURCE) $(DEP_CPP_D_INF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\D_INF.sbr" : $(SOURCE) $(DEP_CPP_D_INF) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_TimeTr.cpp
DEP_CPP_V_TIM=\
	".\Array_f.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_TimeTr.h"\
	

"$(INTDIR)\V_TimeTr.obj" : $(SOURCE) $(DEP_CPP_V_TIM) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_TimeTr.sbr" : $(SOURCE) $(DEP_CPP_V_TIM) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DgExpInd.cpp
DEP_CPP_DGEXP=\
	".\Array_f.h"\
	".\D_ELS.h"\
	".\DFS.h"\
	".\DgExpInd.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_ELS.h"\
	

"$(INTDIR)\DgExpInd.obj" : $(SOURCE) $(DEP_CPP_DGEXP) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\DgExpInd.sbr" : $(SOURCE) $(DEP_CPP_DGEXP) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_Dwell.cpp
DEP_CPP_V_DWE=\
	".\Array_f.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_Dwell.h"\
	

"$(INTDIR)\V_Dwell.obj" : $(SOURCE) $(DEP_CPP_V_DWE) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_Dwell.sbr" : $(SOURCE) $(DEP_CPP_V_DWE) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_MPerfIndex.cpp
DEP_CPP_V_MPE=\
	".\Array_f.h"\
	".\D_ELS.h"\
	".\DFS.h"\
	".\DgExpInd.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_ELS.h"\
	".\V_MPerfIndex.h"\
	

"$(INTDIR)\V_MPerfIndex.obj" : $(SOURCE) $(DEP_CPP_V_MPE) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_MPerfIndex.sbr" : $(SOURCE) $(DEP_CPP_V_MPE) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_PerfIndex.cpp
DEP_CPP_V_PER=\
	".\Array_f.h"\
	".\d_inf.h"\
	".\DFS.h"\
	".\Exprimnt.h"\
	".\StdAfx.h"\
	".\V_PerfIndex.h"\
	

"$(INTDIR)\V_PerfIndex.obj" : $(SOURCE) $(DEP_CPP_V_PER) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_PerfIndex.sbr" : $(SOURCE) $(DEP_CPP_V_PER) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\V_ELSDwell.cpp
DEP_CPP_V_ELSD=\
	".\DFS.h"\
	".\StdAfx.h"\
	".\V_ELSDwell.h"\
	

"$(INTDIR)\V_ELSDwell.obj" : $(SOURCE) $(DEP_CPP_V_ELSD) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"

"$(INTDIR)\V_ELSDwell.sbr" : $(SOURCE) $(DEP_CPP_V_ELSD) "$(INTDIR)"\
 "$(INTDIR)\Dfs.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section DFS : {D893AFD2-B75E-11CF-A059-444553540000}
# 	1:17:ID_INDICATOR_TIME:105
# 	2:2:BH:
# 	2:17:ID_INDICATOR_TIME:ID_INDICATOR_TIME
# End Section
################################################################################
################################################################################
# Section DFS : {D893AFD3-B75E-11CF-A059-444553540000}
# 	1:17:CG_IDS_DISK_SPACE:103
# 	1:19:CG_IDS_PHYSICAL_MEM:102
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:104
# 	2:10:SysInfoKey:1234
# End Section
################################################################################
