; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CViewMPerfIndex
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dfs.h"
LastPage=0

ClassCount=16
Class1=CChildFrame
Class2=CDocELS
Class3=CDocINF
Class4=CDFSApp
Class5=CAboutDlg
Class6=CDFSDoc
Class7=CDFSView
Class8=CDlgExportIndices
Class9=CMainFrame
Class10=CViewDwell
Class11=CViewELS
Class12=CViewELSDwell
Class13=CViewINF
Class14=CViewMPerfIndex
Class15=CViewPerfIndex
Class16=CViewTimeTrace

ResourceCount=17
Resource1=IDD_VIEW_PERFINDEX
Resource2=IDR_ELS_PERFINDEX (English (U.S.))
Resource3=IDD_ABOUTBOX
Resource4=IDD_VIEW_INF
Resource5=IDD_VIEW_TIMETRACE
Resource6=IDD_VIEW_M_PERFINDEX
Resource7=IDD_EXPORT_INDICES
Resource8=IDD_VIEW_DWELL
Resource9=IDD_VIEW_ELS_DWELL
Resource10=IDR_ELS_DWELL (English (U.S.))
Resource11=IDR_DFSTYPE (English (U.S.))
Resource12=IDR_INF (English (U.S.))
Resource13=IDR_INF_TIMETRACE (English (U.S.))
Resource14=IDR_INF_PERFINDEX (English (U.S.))
Resource15=IDR_ELS (English (U.S.))
Resource16=IDR_INF_DWELL (English (U.S.))
Resource17=IDR_MAINFRAME (English (U.S.))

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDocELS]
Type=0
BaseClass=CDocument
HeaderFile=D_ELS.h
ImplementationFile=D_ELS.cpp

[CLS:CDocINF]
Type=0
BaseClass=CDocument
HeaderFile=D_INF.h
ImplementationFile=D_INF.cpp

[CLS:CDFSApp]
Type=0
BaseClass=CWinApp
HeaderFile=DFS.h
ImplementationFile=DFS.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DFS.cpp
ImplementationFile=DFS.cpp

[CLS:CDFSDoc]
Type=0
BaseClass=CDocument
HeaderFile=DFSDoc.h
ImplementationFile=DFSDoc.cpp

[CLS:CDFSView]
Type=0
BaseClass=CView
HeaderFile=DFSView.h
ImplementationFile=DFSView.cpp

[CLS:CDlgExportIndices]
Type=0
BaseClass=CDialog
HeaderFile=DgExpInd.h
ImplementationFile=DgExpInd.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CViewDwell]
Type=0
BaseClass=CFormView
HeaderFile=V_Dwell.h
ImplementationFile=V_Dwell.cpp

[CLS:CViewELS]
Type=0
BaseClass=CEditView
HeaderFile=V_ELS.h
ImplementationFile=V_ELS.cpp

[CLS:CViewELSDwell]
Type=0
BaseClass=CFormView
HeaderFile=V_ELSDwell.h
ImplementationFile=V_ELSDwell.cpp

[CLS:CViewINF]
Type=0
BaseClass=CFormView
HeaderFile=V_INF.h
ImplementationFile=V_INF.cpp

[CLS:CViewMPerfIndex]
Type=0
BaseClass=CFormView
HeaderFile=V_MPerfIndex.h
ImplementationFile=V_MPerfIndex.cpp
LastObject=CViewMPerfIndex

[CLS:CViewPerfIndex]
Type=0
BaseClass=CFormView
HeaderFile=V_PerfIndex.h
ImplementationFile=V_PerfIndex.cpp

[CLS:CViewTimeTrace]
Type=0
BaseClass=CFormView
HeaderFile=V_TimeTr.h
ImplementationFile=V_TimeTr.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342181390
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PHYSICAL_MEM,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DISK_SPACE,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342181383

[DLG:IDD_EXPORT_INDICES]
Type=1
Class=CDlgExportIndices
ControlCount=15
Control1=IDC_START_EXPORT,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EXPORT_FORMAT,button,1342373897
Control5=IDC_EXPORT_FORMAT_2,button,1476460553
Control6=IDC_EXPORT_FORMAT_3,button,1476460553
Control7=IDC_STATIC,button,1342177287
Control8=IDC_WEIGHT_AREATANH,button,1342373891
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EXPORT_FILE_PATH,edit,1350631552
Control11=IDC_BTN_EXPORT_DESTINATION,button,1342242816
Control12=IDC_MESSAGE,static,1342308364
Control13=IDC_STATIC,button,1342177287
Control14=IDC_EXPORT_PERFORMANCE,button,1342242819
Control15=IDC_EXPORT_DWELLINGS,button,1342242819

[DLG:IDD_VIEW_DWELL]
Type=1
Class=CViewDwell
ControlCount=21
Control1=IDC_BLOCK_NO,edit,1350633600
Control2=IDC_SPIN_BLOCKNO,msctls_updown32,1342242850
Control3=IDC_RADIO_HOT_COLD,button,1342373897
Control4=IDC_RADIO_HOT_COLD1,button,1342242825
Control5=IDC_RADIO_HOT_COLD2,button,1342242825
Control6=IDC_MEAN_DWELL_COLD,edit,1350633600
Control7=IDC_MEAN_DWELL_HOT,edit,1350633600
Control8=IDC_TIME_RESOLUTION,edit,1350633600
Control9=IDC_SPIN_RESOLUTION,msctls_updown32,1342242850
Control10=IDC_RADIO_X_LIN_LOG,button,1342373897
Control11=IDC_RADIO_X_LIN_LOG2,button,1342242825
Control12=IDC_SPINBUDDY_BLOCK_NO,edit,1082130560
Control13=IDC_SPINBUDDY_TIME_RESOLUTION,edit,1082130560
Control14=IDC_FRAME_DIAGRAM,static,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352

[DLG:IDD_VIEW_ELS_DWELL]
Type=1
Class=CViewELSDwell
ControlCount=1
Control1=IDC_BUTTON1,button,1342242816

[DLG:IDD_VIEW_INF]
Type=1
Class=CViewINF
ControlCount=26
Control1=IDC_STATIC,static,1342308352
Control2=IDC_INF_EXPERIMENT_NAME,edit,1350764672
Control3=IDC_STATIC,static,1342308352
Control4=IDC_INF_FLY,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INF_HEATEDPATTERN,edit,1350633600
Control7=IDC_STATIC,static,1342308352
Control8=IDC_INF_DATE,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_INF_TIME,edit,1350633600
Control11=IDC_STATIC,static,1342308352
Control12=IDC_INF_REMARKS,edit,1350633600
Control13=IDC_STATIC,static,1342308352
Control14=IDC_INF_NOFFILES,edit,1350764672
Control15=IDC_STATIC,static,1342308352
Control16=IDC_INF_NOFRECORDS,edit,1350633600
Control17=IDC_STATIC,static,1342308352
Control18=IDC_INF_NOFPERIODS,edit,1350633600
Control19=IDC_STATIC,static,1342308352
Control20=IDC_INF_NOFDATA,edit,1350633600
Control21=IDC_POS_RANGE,button,1342308361
Control22=IDC_POS_RANGE_2,button,1342177289
Control23=IDC_DETECTED_2048,static,1342308352
Control24=IDC_DETECTED_1800,static,1342308352
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342177287

[DLG:IDD_VIEW_M_PERFINDEX]
Type=1
Class=CViewMPerfIndex
ControlCount=19
Control1=IDC_LB_EXP_NAMES,listbox,1352745217
Control2=IDC_HEAT_0_180,static,1342181390
Control3=IDC_ED_N_0_180,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ED_N_OF_FILES,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_HEAT_90_270,static,1342181390
Control9=IDC_ED_N_90_270,edit,1350633600
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_LB_PERF_INDICES,listbox,1352745217
Control13=IDC_CHECK_SUB_PREF,button,1342242819
Control14=IDC_CHECK_WEIGHTED_INDICES,button,1342242819
Control15=IDC_FRAME_MULT_PERF_IND,static,1342177288
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_MESSAGE,static,1342308352
Control19=IDC_RECALC,button,1342242816

[DLG:IDD_VIEW_PERFINDEX]
Type=1
Class=CViewPerfIndex
ControlCount=11
Control1=IDC_FRAME_PERF_INDEX,static,1342177288
Control2=IDC_LIST_PERF_INDICEES,listbox,1352745217
Control3=IDC_CHECK_SUB_PREF,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BMP_HEAT,static,1342181390
Control6=IDC_HEAT_0_180,static,1073741838
Control7=IDC_HEAT_90_270,static,1073741838
Control8=IDC_CHECK_WEIGHTED_INDICES,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_PREFERENCE,edit,1350631552
Control11=IDC_STATIC,button,1342177287

[DLG:IDD_VIEW_TIMETRACE]
Type=1
Class=CViewTimeTrace
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CHECK_POSITIONTRACE,button,1342242819
Control3=IDC_BTN_POSTRACE_CLR,button,1342242816
Control4=IDC_CHECK_TORQUETRACE,button,1342242819
Control5=IDC_BTN_TRQTRACE_CLR,button,1342242816
Control6=IDC_SB_TIME,scrollbar,1342242816
Control7=IDC_FRAME_TIMETRACE,static,1342177287
Control8=IDC_FRAME_EXPMODE,static,1342181383
Control9=IDC_DEBUG,edit,1082130560
Control10=IDC_FRAME_POSCOLOR,static,1342177287
Control11=IDC_FRAME_TRQCOLOR,static,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287

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
Command9=ID_CONTEXT_HELP
CommandCount=9

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
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_DFSTYPE (English (U.S.))]
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
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_HELP_FINDER
Command22=ID_APP_ABOUT
CommandCount=22

[MNU:IDR_INF (English (U.S.))]
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
Command15=ID_VIEW_EXPERIMENTOVERVIEW
Command16=ID_VIEW_TIMETRACES
Command17=ID_VIEW_PERFORMANCEINDICEES
Command18=ID_VIEW_POSITIONHISTO
Command19=ID_VIEW_DWELLINGTIMES
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_HELP_FINDER
Command27=ID_APP_ABOUT
CommandCount=27

[MNU:IDR_INF_TIMETRACE (English (U.S.))]
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
Command15=ID_VIEW_EXPERIMENTOVERVIEW
Command16=ID_VIEW_TIMETRACES
Command17=ID_VIEW_PERFORMANCEINDICEES
Command18=ID_VIEW_POSITIONHISTO
Command19=ID_VIEW_DWELLINGTIMES
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_HELP_FINDER
Command27=ID_APP_ABOUT
CommandCount=27

[MNU:IDR_INF_PERFINDEX (English (U.S.))]
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
Command15=ID_VIEW_EXPERIMENTOVERVIEW
Command16=ID_VIEW_TIMETRACES
Command17=ID_VIEW_PERFORMANCEINDICEES
Command18=ID_VIEW_POSITIONHISTO
Command19=ID_VIEW_DWELLINGTIMES
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_HELP_FINDER
Command27=ID_APP_ABOUT
CommandCount=27

[MNU:IDR_ELS (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_EXPORT_INDICES
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_VIEW_MULTI_EXP_LST_OV
Command17=ID_VIEW_MULTI_EXP_PERF_HISTO
Command18=ID_VIEW_MULTI_EXP_POS_HISTO
Command19=ID_VIEW_MULTI_DWELLINGTIMES
Command20=ID_VIEW_SETFONT
Command21=ID_VIEW_TOOLBAR
Command22=ID_VIEW_STATUS_BAR
Command23=ID_WINDOW_NEW
Command24=ID_WINDOW_CASCADE
Command25=ID_WINDOW_TILE_HORZ
Command26=ID_WINDOW_ARRANGE
Command27=ID_HELP_FINDER
Command28=ID_APP_ABOUT
CommandCount=28

[MNU:IDR_INF_DWELL (English (U.S.))]
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
Command15=ID_VIEW_EXPERIMENTOVERVIEW
Command16=ID_VIEW_TIMETRACES
Command17=ID_VIEW_PERFORMANCEINDICEES
Command18=ID_VIEW_POSITIONHISTO
Command19=ID_VIEW_DWELLINGTIMES
Command20=ID_VIEW_TOOLBAR
Command21=ID_VIEW_STATUS_BAR
Command22=ID_WINDOW_NEW
Command23=ID_WINDOW_CASCADE
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_ARRANGE
Command26=ID_HELP_FINDER
Command27=ID_APP_ABOUT
CommandCount=27

[MNU:IDR_ELS_PERFINDEX (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_EXPORT_INDICES
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_MULTI_EXP_LST_OV
Command15=ID_VIEW_MULTI_EXP_PERF_HISTO
Command16=ID_VIEW_MULTI_EXP_POS_HISTO
Command17=ID_VIEW_MULTI_DWELLINGTIMES
Command18=ID_VIEW_SETFONT
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_WINDOW_NEW
Command22=ID_WINDOW_CASCADE
Command23=ID_WINDOW_TILE_HORZ
Command24=ID_WINDOW_ARRANGE
Command25=ID_HELP_FINDER
Command26=ID_APP_ABOUT
CommandCount=26

[MNU:IDR_ELS_DWELL (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_EXPORT_INDICES
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_WINDOW_NEW
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_HELP_FINDER
Command19=ID_APP_ABOUT
CommandCount=19

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
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

