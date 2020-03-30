// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "ElsPropSheetViewFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElsPropSheetViewFrm, CNSFlexMDIChildWnd)

BEGIN_MESSAGE_MAP(CElsPropSheetViewFrm, CNSFlexMDIChildWnd)
	//{{AFX_MSG_MAP(CElsPropSheetViewFrm)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

CElsPropSheetViewFrm::CElsPropSheetViewFrm()
{
	
}

CElsPropSheetViewFrm::~CElsPropSheetViewFrm()
{

}

BOOL CElsPropSheetViewFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG

void CElsPropSheetViewFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CElsPropSheetViewFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void CElsPropSheetViewFrm::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);

	CString csTitle;
	GetWindowText(csTitle);

	SetWindowText("DFS Multiple Experiment Evaluation - "
		+ csTitle);
}

int CElsPropSheetViewFrm::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CNSFlexMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneStyle(0, SBPS_STRETCH);
	return 0;
}
