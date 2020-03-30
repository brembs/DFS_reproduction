// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "NSFlexPropertySheetView.h"
#include "NSFlexPropertySheet.h"
#include "NSFlexMDIChildWnd.h"
#include "NSFlexPropertyPage.h"
#include "NSViewsMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNSFlexPropertySheetView, CScrollView)

BEGIN_MESSAGE_MAP(CNSFlexPropertySheetView, CScrollView)
	//{{AFX_MSG_MAP(CNSFlexPropertySheetView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNSFlexPropertySheetView::CNSFlexPropertySheetView(UINT nSelectPage /*=0*/)
{
	m_pFlexPropertySheet = new CNSFlexPropertySheet("",this,nSelectPage);
}

CNSFlexPropertySheetView::~CNSFlexPropertySheetView()
{
	delete m_pFlexPropertySheet;
}

CNSFlexPropertySheet* CNSFlexPropertySheetView::GetFlexPropertySheet()
{
	return m_pFlexPropertySheet;
}

void CNSFlexPropertySheetView::OnInitialUpdate() 
{
	// REVISION 4/10/97 TO WORK WITH SDI APPLICATIONS (Ed Smetak)
	// If File/New for SDI application, m_pFlexPropertySheet already
	// has been created, so just return in this case.
	if (m_pFlexPropertySheet->m_hWnd) 
		return;
	// END REVISION (Ver 1.04)

	// dont show the sheet
	m_pFlexPropertySheet->Create(this,WS_SYSMENU|WS_CHILD,0); 

	ASSERT(::IsWindow(m_pFlexPropertySheet->GetSafeHwnd()));
	ASSERT(m_pFlexPropertySheet->GetPageCount() > 0);

    ::SetWindowLong(m_pFlexPropertySheet->m_hWnd,GWL_STYLE,
		(::GetWindowLong(m_pFlexPropertySheet->m_hWnd,GWL_STYLE)
		& ~(LONG)WS_SYSMENU));   

	CRect rectWindow;
	m_pFlexPropertySheet->GetWindowRect(rectWindow);
    SetScrollSizes(MM_TEXT,rectWindow.Size());

	// By Xie jignwei 10.10.1997
	// show sheet right here
	GetWindowRect(rectWindow);
	m_pFlexPropertySheet->SetWindowPos(NULL, 0, 0, rectWindow.Width(),
		rectWindow.Height(), SWP_SHOWWINDOW|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);

	DWORD dwExStyle = GetExStyle();
	if (dwExStyle & WS_EX_CLIENTEDGE)
    {
		dwExStyle &= ~((DWORD)WS_EX_CLIENTEDGE); 
			::SetWindowLong(m_hWnd,GWL_EXSTYLE,(LONG)dwExStyle);
	}

	//ResizeParentToFit(FALSE); // By Xie jignwei 10.10.1997

	CWnd *pParentFrame = GetParentFrame();
	ASSERT(pParentFrame);
	if (pParentFrame->IsKindOf(RUNTIME_CLASS(CNSFlexMDIChildWnd)))
		pParentFrame->SendMessage(WM_SETMINTRACKSIZE);
#ifdef _DEBUG
	else
		TRACE0("Warning!  CNSFlexPropertySheetView used without "
		       "a CNSFlexMDIChildWnd frame.\n");
#endif
}

void CNSFlexPropertySheetView::OnSetFocus(CWnd* pOldWnd) 
{
	if(::IsWindow(m_pFlexPropertySheet->GetSafeHwnd()))
		m_pFlexPropertySheet->SetFocus();
}

void CNSFlexPropertySheetView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);

    if (nType != SIZE_MINIMIZED && 
		::IsWindow(m_pFlexPropertySheet->GetSafeHwnd()))
	{
        CRect rect;
        GetWindowRect(rect);
        CSize sizeScroll = GetTotalSize();
        int cxNew = max(rect.Width(), sizeScroll.cx);
        int cyNew = max(rect.Height(), sizeScroll.cy);
		m_pFlexPropertySheet->SetWindowPos(NULL,0,0,cxNew,
			cyNew,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);
	}
}

void CNSFlexPropertySheetView::OnUpdate(CView* pSender, LPARAM lHint,
	CObject* pHint) 
{
	for (int nPage = 0; nPage < m_pFlexPropertySheet->GetPageCount(); nPage++)
	{
		CNSFlexPropertyPage* pPropertyPage = 
			(CNSFlexPropertyPage*)m_pFlexPropertySheet->GetPage(nPage);

		if(::IsWindow(pPropertyPage->GetSafeHwnd()))
			pPropertyPage->OnUpdate(pSender,lHint,pHint);
	}
}

BOOL CNSFlexPropertySheetView::PreCreateWindow(CREATESTRUCT& cs) 
{
    cs.style |= WS_CLIPCHILDREN;
	return CScrollView::PreCreateWindow(cs);
}

BOOL CNSFlexPropertySheetView::PreTranslateMessage(MSG* pMsg) 
{
	// check for Shift+F1 help
	CFrameWnd* pFrameWnd = GetTopLevelFrame();
	if (pFrameWnd && pFrameWnd->m_bHelpMode)
		return FALSE;

	// make sure accelerators work
	pFrameWnd = GetParentFrame();
	while (pFrameWnd)
	{
		if (pFrameWnd->PreTranslateMessage(pMsg))
			return TRUE;

		pFrameWnd = pFrameWnd->GetParentFrame();
	}

	return FALSE;
}