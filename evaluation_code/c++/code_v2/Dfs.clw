; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CElsExportTI
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dfs.h"
LastPage=0

ClassCount=21
Class1=CDfsApp
Class2=CAboutDlg
Class3=CDfsDoc
Class4=CElsDoc
Class5=CElsPropPageExperimentList
Class6=CElsPropPageFixation
Class7=CElsPropPageTorquePI
Class8=CElsPropPagePerformance
Class9=CElsPropSheetView
Class10=CElsPropSheetViewFrm
Class11=CInfDoc
Class12=CInfPropPageOverview
Class13=CInfPropPagePerformance
Class14=CInfPropSheetView
Class15=CInfPropSheetViewFrm
Class16=CIntroView
Class17=CIntroViewFrm
Class18=CMainFrame

ResourceCount=16
Resource1=IDD_PP_ELS_PERFORMANCE (English (U.S.))
Resource2=IDD_PP_INF_PERFORMANCE (English (U.S.))
Resource3=IDR_ELSTYPE (English (U.S.))
Resource4=IDR_NSVIEWTYPE (English (U.S.))
Resource5=IDR_INFTYPE (English (U.S.))
Resource6=IDR_MAINFRAME (English (U.S.))
Resource7=IDD_PP_ELS_FIXATION (English (U.S.))
Resource8=IDD_FORM1 (English (U.S.))
Resource9=IDD_FORM2 (English (U.S.))
Resource10=IDD_ABOUTBOX (English (U.S.))
Resource11=IDD_PP_ELS_EXPERIMENTLIST (English (U.S.))
Resource12=IDD_PP_INF_OVERVIEW (English (U.S.))
Resource13=IDD_EXPORT_FI
Resource14=IDD_EXPORT_PI
Class19=CElsPropPageTorquePI
Resource15=IDD_PP_ELS_TORQUEPI (English (U.S.))
Class20=CElsExportPI
Resource16=IDD_EXPORT_TI
Class21=CElsExportTI

[CLS:CDfsApp]
Type=0
BaseClass=CWinApp
HeaderFile=Dfs.h
ImplementationFile=Dfs.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Dfs.cpp
ImplementationFile=Dfs.cpp
LastObject=IDC_EDIT_JR_DATE

[CLS:CDfsDoc]
Type=0
BaseClass=CDocument
HeaderFile=Dfsdoc.h
ImplementationFile=Dfsdoc.cpp

[CLS:CElsDoc]
Type=0
BaseClass=CDocument
HeaderFile=Elsdoc.h
ImplementationFile=Elsdoc.cpp

[CLS:CElsPropPageExperimentList]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=ElsPropPageExperimentList.h
ImplementationFile=ElsPropPageExperimentList.cpp

[CLS:CElsPropPageFixation]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=ElsPropPageFixation.h
ImplementationFile=ElsPropPageFixation.cpp
Filter=D
VirtualFilter=idWC
LastObject=CElsPropPageFixation

[CLS:CElsPropPageTorquePI]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=ElsPropPageTorquePI.h
ImplementationFile=ElsPropPageTorquePI.cpp
LastObject=CElsPropPageTorquePI
Filter=D
VirtualFilter=idWC

[CLS:CElsPropPagePerformance]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=ElsPropPagePerformance.h
ImplementationFile=ElsPropPagePerformance.cpp

[CLS:CElsPropSheetView]
Type=0
BaseClass=CNSFlexPropertySheetView
HeaderFile=ElsPropSheetView.h
ImplementationFile=ElsPropSheetView.cpp

[CLS:CElsPropSheetViewFrm]
Type=0
BaseClass=CNSFlexMDIChildWnd
HeaderFile=ElsPropSheetViewFrm.h
ImplementationFile=ElsPropSheetViewFrm.cpp

[CLS:CInfDoc]
Type=0
BaseClass=CDocument
HeaderFile=Infdoc.h
ImplementationFile=Infdoc.cpp

[CLS:CInfPropPageOverview]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=InfPropPageOverview.h
ImplementationFile=InfPropPageOverview.cpp

[CLS:CInfPropPagePerformance]
Type=0
BaseClass=CNSFlexPropertyPage
HeaderFile=InfPropPagePerformance.h
ImplementationFile=InfPropPagePerformance.cpp

[CLS:CInfPropSheetView]
Type=0
BaseClass=CNSFlexPropertySheetView
HeaderFile=InfPropSheetView.h
ImplementationFile=InfPropSheetView.cpp

[CLS:CInfPropSheetViewFrm]
Type=0
BaseClass=CNSFlexMDIChildWnd
HeaderFile=InfPropSheetViewFrm.h
ImplementationFile=InfPropSheetViewFrm.cpp

[CLS:CIntroView]
Type=0
BaseClass=CNSFlexFormView
HeaderFile=IntroView.h
ImplementationFile=IntroView.cpp

[CLS:CIntroViewFrm]
Type=0
BaseClass=CNSFlexMDIChildWnd
HeaderFile=IntroViewFrm.h
ImplementationFile=IntroViewFrm.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=Mainfrm.h
ImplementationFile=Mainfrm.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_PP_ELS_EXPERIMENTLIST]
Type=1
Class=CElsPropPageExperimentList

[DLG:IDD_PP_ELS_FIXATION]
Type=1
Class=CElsPropPageFixation

[DLG:IDD_PP_ELS_NEW]
Type=1
Class=CElsPropPageTorquePI

[DLG:IDD_PP_ELS_PERFORMANCE]
Type=1
Class=CElsPropPageTorquePI

[DLG:IDD_PP_INF_OVERVIEW]
Type=1
Class=CInfPropPageOverview

[DLG:IDD_PP_INF_PERFORMANCE]
Type=1
Class=CInfPropPagePerformance

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_INDEX
Command9=ID_HELP_FINDER
Command10=ID_APP_ABOUT
CommandCount=10

[MNU:IDR_NSVIEWTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_DEMO_INTRODUCTION
Command18=ID_DEMO_FLEXIBLE_DIALOG
Command19=ID_DEMO_FLEXIBLE_PROPERTY_SHEET
Command20=ID_DEMO_FLEXIBLE_FORM_VIEW
Command21=ID_DEMO_FLEXIBLE_PROPERTY_SHEET_VIEW
Command22=ID_WINDOW_CASCADE
Command23=ID_WINDOW_TILE_HORZ
Command24=ID_WINDOW_ARRANGE
Command25=ID_APP_ABOUT
CommandCount=25

[MNU:IDR_INFTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_DEMO_INTRODUCTION
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

[MNU:IDR_ELSTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_DEMO_INTRODUCTION
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_PP_ELS_FIXATION (English (U.S.))]
Type=1
Class=CElsPropPageFixation
ControlCount=20
Control1=IDC_FRAME_ELS_FIXATION,static,1342181383
Control2=IDC_STATIC_ELSPP3_2,button,1342177287
Control3=IDC_EDIT_ELS_DISPLAYED_BLOCK,edit,1350568064
Control4=IDC_SPIN_ELS_DISPLAYED_BLOCK,msctls_updown32,1342242850
Control5=IDC_EDIT_ELS_SPINBUDDY_BLOCK,edit,1082138752
Control6=IDC_COMBO_ELS_DISPLAY_RESOLUTION,combobox,1344339971
Control7=IDC_STATIC_ELSPP3_3,static,1342177280
Control8=IDC_STATIC_ELSPP3_5,static,1342177280
Control9=IDC_STATIC_ELSPP3_1,button,1342177287
Control10=IDC_LIST_ELS_FIXATON_INDICES,listbox,1353793793
Control11=IDC_STATIC_ELSPP3_4,button,1342177287
Control12=IDC_RADIO_ELS_HEAT,button,1342308361
Control13=IDC_RADIO_ELS_HEAT2,button,1342177289
Control14=IDC_RADIO_ELS_HEAT3,button,1342177289
Control15=IDC_EDIT_ELS_N_REINF_0180,edit,1350699136
Control16=IDC_EDIT_ELS_N_REINF_90270,edit,1350568064
Control17=IDC_EDIT_ELS_N_ALL_FILES,edit,1350568064
Control18=IDC_CHECK_ELS_HALF_ARENA,button,1342242819
Control19=IDC_CHECK_ELS_SUPERIMPOSED,button,1342242819
Control20=IDC_BUTTON_ELS_EXPORT_FI,button,1342242816

[DLG:IDD_FORM1 (English (U.S.))]
Type=1
Class=?
ControlCount=11
Control1=IDC_STATIC_5,button,1342177287
Control2=IDC_LIST_1,listbox,1352728835
Control3=IDC_BUTTON_1,button,1342242816
Control4=IDC_STATIC_1,static,1342308352
Control5=IDC_COMBO_1,combobox,1344340227
Control6=IDC_STATIC_2,static,1342308352
Control7=IDC_COMBO_2,combobox,1344340225
Control8=IDC_STATIC_3,static,1342308352
Control9=IDC_COMBO_3,combobox,1344340226
Control10=IDC_STATIC_4,static,1342308352
Control11=IDC_EDIT_1,edit,1350631552

[DLG:IDD_FORM2 (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_BUTTON_PROP_SHEET,button,1342242816
Control2=IDC_BUTTON_FORM_VIEW,button,1342242816
Control3=IDC_BUTTON_PROP_SHEET_VIEW,button,1342242816
Control4=IDC_EDIT_INTRO,edit,1352734724

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342373889
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342181383
Control6=IDC_STATIC,static,1342177294
Control7=IDC_STATIC,static,1342308480

[DLG:IDD_PP_ELS_EXPERIMENTLIST (English (U.S.))]
Type=1
Class=?
ControlCount=13
Control1=ID_BUTTON_COMPILE_SCRIPT,button,1342242817
Control2=IDC_EDIT_ELS_EXPERIMENTSCRIPT,edit,1353781444
Control3=IDC_STATIC_ELSPP1_1,button,1342177287
Control4=IDC_EDIT_ELS_N_0_180,edit,1350633600
Control5=IDC_STATIC_ELSPP1_2,static,1342308352
Control6=IDC_EDIT_ELS_N_OF_FILES,edit,1350633600
Control7=IDC_STATIC_ELSPP1_4,static,1342308352
Control8=IDC_EDIT_ELS_N_90_270,edit,1350633600
Control9=IDC_STATIC_ELSPP1_5,static,1342308352
Control10=IDC_LIST_ELS_EXPERIMENTNAMES,listbox,1352728833
Control11=IDC_STATIC_ELSPP1_3,static,1342308352
Control12=IDC_EDIT_ELS_FILES_OK,edit,1350633600
Control13=IDC_STATIC_ELSPP1_MESSAGE,static,1342308352

[DLG:IDD_PP_INF_OVERVIEW (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PP_INF_PERFORMANCE (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PP_ELS_PERFORMANCE (English (U.S.))]
Type=1
Class=CElsPropPagePerformance
ControlCount=16
Control1=IDC_STATIC_ELSPP2_1,button,1342177287
Control2=IDC_FRAME_ELS_PERFORMANCE,static,1342181383
Control3=IDC_LIST_ELS_PERFINDICES,listbox,1352745217
Control4=IDC_CHECK_ELS_SUBPREF,button,1342242819
Control5=IDC_CHECK_ELS_TRANSFORMARTANH,button,1342242819
Control6=IDC_CHECK_ELS_POSPREF,button,1342242819
Control7=IDC_CHECK_ELS_NEGPREF,button,1342242819
Control8=IDC_CHECK_ELS_HEAT0180,button,1342242819
Control9=IDC_CHECK_ELS_HEAT90270,button,1342242819
Control10=IDC_EDIT_ELS_N_POS_PREF,edit,1350633600
Control11=IDC_EDIT_ELS_N_NEG_PREF,edit,1350633600
Control12=IDC_EDIT_ELS_N_REINF_0180,edit,1350633600
Control13=IDC_EDIT_ELS_N_REINF_90270,edit,1350633600
Control14=IDC_STATIC_ELSPP2_2,static,1342308352
Control15=IDC_EDIT_ELS_N_ALL_FILES,edit,1350633600
Control16=IDC_BUTTON_ELS_EXPORT_PI,button,1342242816

[DLG:IDD_EXPORT_PI]
Type=1
Class=CElsExportPI
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EXPORT_FORMAT,button,1342373897
Control3=IDC_EXPORT_FORMAT_2,button,1342242825
Control4=IDC_STATIC,button,1342308359
Control5=IDC_EXPORT_FILE_PATH,edit,1350631552
Control6=IDC_BUTTON_EXPORT_DESTINATION,button,1342242816
Control7=IDC_EXPORT_MESSAGE,static,1342308364
Control8=IDC_START_EXPORT,button,1342242816
Control9=IDCANCEL,button,1342242816

[DLG:IDD_EXPORT_FI]
Type=1
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EXPORT_FORMAT,button,1342373897
Control3=IDC_EXPORT_FORMAT_2,button,1342242825
Control4=IDC_STATIC,button,1342308359
Control5=IDC_EXPORT_FILE_PATH,edit,1350631552
Control6=IDC_BUTTON_EXPORT_DESTINATION,button,1342242816
Control7=IDC_EXPORT_MESSAGE,static,1342308364
Control8=IDC_START_EXPORT,button,1342242816
Control9=IDCANCEL,button,1342242816

[DLG:IDD_PP_ELS_TORQUEPI (English (U.S.))]
Type=1
Class=CElsPropPageTorquePI
ControlCount=16
Control1=IDC_STATIC_ELSPP2_1,button,1342177287
Control2=IDC_FRAME_ELS_PERFORMANCE,static,1342181383
Control3=IDC_LIST_ELS_PERFINDICES,listbox,1352745217
Control4=IDC_CHECK_ELS_SUBPREF,button,1342242819
Control5=IDC_CHECK_ELS_TRANSFORMARTANH,button,1342242819
Control6=IDC_CHECK_ELS_POSPREF,button,1342242819
Control7=IDC_CHECK_ELS_NEGPREF,button,1342242819
Control8=IDC_CHECK_ELS_HEAT0180,button,1342242819
Control9=IDC_CHECK_ELS_HEAT90270,button,1342242819
Control10=IDC_EDIT_ELS_N_POS_PREF,edit,1350633600
Control11=IDC_EDIT_ELS_N_NEG_PREF,edit,1350633600
Control12=IDC_EDIT_ELS_N_REINF_0180,edit,1350633600
Control13=IDC_EDIT_ELS_N_REINF_90270,edit,1350633600
Control14=IDC_STATIC_ELSPP2_2,static,1342308352
Control15=IDC_EDIT_ELS_N_ALL_FILES,edit,1350633600
Control16=IDC_BUTTON_ELS_EXPORT_PI,button,1342242816

[CLS:CElsExportPI]
Type=0
HeaderFile=elsexportpi.h
ImplementationFile=elsexportpi.cpp
BaseClass=CDialog
LastObject=CElsExportPI

[DLG:IDD_EXPORT_TI]
Type=1
Class=CElsExportTI
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EXPORT_FORMAT,button,1342373897
Control3=IDC_EXPORT_FORMAT_2,button,1342242825
Control4=IDC_STATIC,button,1342308359
Control5=IDC_EXPORT_FILE_PATH,edit,1350631552
Control6=IDC_BUTTON_EXPORT_DESTINATION,button,1342242816
Control7=IDC_EXPORT_MESSAGE,static,1342308364
Control8=IDC_START_EXPORT,button,1342242816
Control9=IDCANCEL,button,1342242816

[CLS:CElsExportTI]
Type=0
HeaderFile=elsexportpi.h
ImplementationFile=elsexportpi.cpp
BaseClass=CDialog
Filter=D

