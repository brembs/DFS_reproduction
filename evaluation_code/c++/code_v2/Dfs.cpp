// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "MainFrm.h"
#include "DfsDoc.h"
#include "InfDoc.h"
#include "ElsDoc.h"

#include "ElsPropSheetView.h"
#include "ElsPropSheetViewFrm.h"
#include "InfPropSheetView.h"
#include "InfPropSheetViewFrm.h"
#include "IntroView.h"
#include "IntroViewFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CDfsApp, CWinApp)
	//{{AFX_MSG_MAP(CDfsApp)
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

CDfsApp::CDfsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CDfsApp theApp;

CDfsApp::~CDfsApp()
{
//	delete m_pElsDocTemplate;
//	delete m_pInfDocTemplate;
}

BOOL CDfsApp::InitInstance()
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

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_NSVIEWTYPE,
		RUNTIME_CLASS(CDfsDoc),
		RUNTIME_CLASS(CIntroViewFrm),
		RUNTIME_CLASS(CIntroView));
	AddDocTemplate(pDocTemplate);
	m_pIntroViewDocTemplate = pDocTemplate;

	m_pInfDocTemplate = new CMultiDocTemplate(
		IDR_INFTYPE,
		RUNTIME_CLASS(CInfDoc),
		RUNTIME_CLASS(CInfPropSheetViewFrm),
		RUNTIME_CLASS(CInfPropSheetView));
	AddDocTemplate(m_pInfDocTemplate);

	m_pElsDocTemplate = new CMultiDocTemplate(
		IDR_ELSTYPE,
		RUNTIME_CLASS(CElsDoc),
		RUNTIME_CLASS(CElsPropSheetViewFrm),
		RUNTIME_CLASS(CElsPropSheetView));
	AddDocTemplate(m_pElsDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	// m_nCmdShow = SW_SHOWMAXIMIZED;	// if the window should be maximized on start
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

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
void CDfsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
