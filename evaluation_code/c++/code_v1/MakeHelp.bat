@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DFS.HPJ. >"hlp\DFS.hm"
echo. >>"hlp\DFS.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DFS.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DFS.hm"
echo. >>"hlp\DFS.hm"
echo // Prompts (IDP_*) >>"hlp\DFS.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DFS.hm"
echo. >>"hlp\DFS.hm"
echo // Resources (IDR_*) >>"hlp\DFS.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DFS.hm"
echo. >>"hlp\DFS.hm"
echo // Dialogs (IDD_*) >>"hlp\DFS.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DFS.hm"
echo. >>"hlp\DFS.hm"
echo // Frame Controls (IDW_*) >>"hlp\DFS.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DFS.hm"
REM -- Make help for Project DFS


echo Building Win32 Help files
start /wait hcrtf -x "hlp\DFS.hpj"
echo.
if exist Debug\nul copy "hlp\DFS.hlp" Debug
if exist Debug\nul copy "hlp\DFS.cnt" Debug
if exist Release\nul copy "hlp\DFS.hlp" Release
if exist Release\nul copy "hlp\DFS.cnt" Release
echo.


