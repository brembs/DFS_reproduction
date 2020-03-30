// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "IntroViewFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIntroViewFrm, CNSFlexMDIChildWnd)

BEGIN_MESSAGE_MAP(CIntroViewFrm, CNSFlexMDIChildWnd)
	//{{AFX_MSG_MAP(CIntroViewFrm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIntroViewFrm::CIntroViewFrm()
{
	
}

CIntroViewFrm::~CIntroViewFrm()
{

}

BOOL CIntroViewFrm::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG

void CIntroViewFrm::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CIntroViewFrm::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

void CIntroViewFrm::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);

	CString csTitle;
	GetWindowText(csTitle);

	SetWindowText("NSViews Introduction - " + csTitle);
}
