// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "InfPropSheetViewFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CInfPropSheetViewFrm, CNSFlexMDIChildWnd)

BEGIN_MESSAGE_MAP(CInfPropSheetViewFrm, CNSFlexMDIChildWnd)
	//{{AFX_MSG_MAP(CInfPropSheetViewFrm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CInfPropSheetViewFrm::CInfPropSheetViewFrm()
{
	
}

CInfPropSheetViewFrm::~CInfPropSheetViewFrm()
{

}

BOOL CInfPropSheetViewFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG

void CInfPropSheetViewFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CInfPropSheetViewFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void CInfPropSheetViewFrm::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);

	CString csTitle;
	GetWindowText(csTitle);

	SetWindowText("DFS Single Experiment Evaluation - "
		+ csTitle);
}
