// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DFS.h"

#include "MainFrm.h"
#include "V_TimeTr.h"
#include "V_Dwell.h"
#include "V_ELSDwell.h"
#include "V_MPerfIndex.h"
#include "V_PerfIndex.h"
#include "V_INF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDFSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TIMETRACES, OnViewTimetraces)
	ON_COMMAND(ID_VIEW_PERFORMANCEINDICEES, OnViewPerformanceindices)
	ON_COMMAND(ID_VIEW_EXPERIMENTOVERVIEW, OnViewExperimentoverview)
	ON_COMMAND(ID_VIEW_MULTI_EXP_LST_OV, OnViewMultiExpLstOv)
	ON_COMMAND(ID_VIEW_DWELLINGTIMES, OnViewDwellingTimes)
	ON_COMMAND(ID_VIEW_MULTI_DWELLINGTIMES, OnViewELSDwellings)
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


void CMainFrame::CreateOrActivateFrame(CDocTemplate* pTemplate,
	CRuntimeClass* pViewClass)
{
	// If a view (specified by pViewClass) already exists, then 
	// activate the MDI child window containing
	// the view. Otherwise, create a new view for the document.

	CMDIChildWnd* pMDIActive = MDIGetActive();
	ASSERT(pMDIActive != NULL);
	CDocument* pDoc = pMDIActive->GetActiveDocument();
	ASSERT(pDoc != NULL);

	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))
		{
			pView->GetParentFrame()->ActivateFrame();
			return;
		}
	}

	CMDIChildWnd* pNewFrame
		= (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
	if (pNewFrame == NULL) return;     // not created
	ASSERT_KINDOF(CMDIChildWnd, pNewFrame);
	pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewTimetraces() 
{
	CreateOrActivateFrame(theApp.m_pINF_TimeTrace_Template,
		RUNTIME_CLASS(CViewTimeTrace));
}

void CMainFrame::OnViewPerformanceindices() 
{
	CreateOrActivateFrame(theApp.m_pINF_PerfIndex_Template,
		RUNTIME_CLASS(CViewPerfIndex));
}
	
void CMainFrame::OnViewDwellingTimes() 
{
	CreateOrActivateFrame(theApp.m_pINF_DwellingTimes_Template,
		RUNTIME_CLASS(CViewDwell));
}

void CMainFrame::OnViewExperimentoverview() 
{
	CreateOrActivateFrame(theApp.m_pINF_Template,
		RUNTIME_CLASS(CViewINF));
}

void CMainFrame::OnViewMultiExpLstOv() 
{
	CreateOrActivateFrame(theApp.m_pELS_PerfIndex_Template,
		RUNTIME_CLASS(CViewMPerfIndex));
}

void CMainFrame::OnViewELSDwellings() 
{
	CreateOrActivateFrame(theApp.m_pELS_Dwellings_Template,
		RUNTIME_CLASS(CViewELSDwell));
}

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%X"));

	// BLOCK: compute the width of the date string
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(strTime);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}

	// Update the pane to reflect the current time
	UINT nID, nStyle;
	int nWidth;
	m_wndStatusBar.GetPaneInfo(m_nTimePaneNo, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(m_nTimePaneNo, nID, nStyle, size.cx);
	pCmdUI->SetText(strTime);
	pCmdUI->Enable(TRUE);

}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Create an index for the TIME pane
	m_nTimePaneNo = nSize++;
	nSeconds = 1;

	// TODO: Select an appropriate time interval for updating
	// the status bar when idling.
	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);

}
