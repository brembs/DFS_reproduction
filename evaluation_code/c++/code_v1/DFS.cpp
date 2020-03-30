// DFS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DFS.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DFSDoc.h"
#include "DFSView.h"
#include "D_ELS.h"
#include "V_ELS.h"
#include "D_INF.h"
#include "V_INF.h"
#include "V_TimeTr.h"
#include "V_ELSDwell.h"
#include "V_Dwell.h"
#include "V_MPerfIndex.h"
#include "V_PerfIndex.h"
#include <dos.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDFSApp

BEGIN_MESSAGE_MAP(CDFSApp, CWinApp)
	//{{AFX_MSG_MAP(CDFSApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFSApp construction

CDFSApp::CDFSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDFSApp object

CDFSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDFSApp initialization

BOOL CDFSApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDFS_Template = new CMultiDocTemplate(
			IDR_DFSTYPE,
			RUNTIME_CLASS(CDFSDoc),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CDFSView));
	AddDocTemplate(m_pDFS_Template);

	m_pINF_Template = new CMultiDocTemplate(
			IDR_INF,
			RUNTIME_CLASS(CDocINF),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewINF));
	AddDocTemplate(m_pINF_Template);
	
	m_pINF_TimeTrace_Template = new CMultiDocTemplate(
			IDR_INF_TIMETRACE,
			RUNTIME_CLASS(CDocINF),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewTimeTrace));
	AddDocTemplate(m_pINF_TimeTrace_Template);

	m_pINF_PerfIndex_Template = new CMultiDocTemplate(
			IDR_INF_PERFINDEX,
			RUNTIME_CLASS(CDocINF),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewPerfIndex));
	AddDocTemplate(m_pINF_PerfIndex_Template);

	m_pINF_DwellingTimes_Template = new CMultiDocTemplate(
			IDR_INF_DWELL,
			RUNTIME_CLASS(CDocINF),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewDwell));
	AddDocTemplate(m_pINF_DwellingTimes_Template);

	m_pELS_Template = new CMultiDocTemplate(
			IDR_ELS,
			RUNTIME_CLASS(CDocELS),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewELS));
	AddDocTemplate(m_pELS_Template);

	m_pELS_PerfIndex_Template = new CMultiDocTemplate(
			IDR_ELS_PERFINDEX,
			RUNTIME_CLASS(CDocELS),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewMPerfIndex));
	AddDocTemplate(m_pELS_PerfIndex_Template);

	m_pELS_Dwellings_Template = new CMultiDocTemplate(
			IDR_ELS_DWELL,
			RUNTIME_CLASS(CDocELS),
			RUNTIME_CLASS(CChildFrame),
			RUNTIME_CLASS(CViewELSDwell));
	AddDocTemplate(m_pELS_Dwellings_Template);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	m_nCmdShow = SW_MAXIMIZE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDFSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDFSApp commands

BOOL CAboutDlg::OnInitDialog()
{
	// CG: Folowing code is added by System Info Component
	{
	CDialog::OnInitDialog();
#ifndef _MAC
	CString strFreeDiskSpace;
	CString strFreeMemory;
	CString strFmt;

	// Fill available memory
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	strFmt.LoadString(CG_IDS_PHYSICAL_MEM);
	strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

	//TODO: Add a static control to your About Box to receive the memory
	//      information.  Initialize the control with code like this:
	SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory);

	// Fill disk free information
	struct _diskfree_t diskfree;
	int nDrive = _getdrive(); // use current default drive
	if (_getdiskfree(nDrive, &diskfree) == 0)
	{
		strFmt.LoadString(CG_IDS_DISK_SPACE);
		strFreeDiskSpace.Format(strFmt,
			(DWORD)diskfree.avail_clusters *
			(DWORD)diskfree.sectors_per_cluster *
			(DWORD)diskfree.bytes_per_sector / (DWORD)1024L,
			nDrive-1 + _T('A'));
	}
 	else
 		strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);

	//TODO: Add a static control to your About Box to receive the memory
	//      information.  Initialize the control with code like this:
	SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);

#endif //_MAC
	}

	return TRUE;
}
