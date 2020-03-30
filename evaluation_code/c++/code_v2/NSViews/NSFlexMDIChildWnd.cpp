// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "NSFlexMDIChildWnd.h"
#include "NSViewsMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CNSFlexMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CNSFlexMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CNSFlexMDIChildWnd)
	//ON_WM_GETMINMAXINFO() // modified by Xie jingwei, 10.10.1997
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_SETMINTRACKSIZE, OnSetMinTrackSize)
END_MESSAGE_MAP()

CNSFlexMDIChildWnd::CNSFlexMDIChildWnd() :
	m_nMinTrackingWidth(0), m_nMinTrackingHeight(0) 
{

}

CNSFlexMDIChildWnd::~CNSFlexMDIChildWnd()
{

}

void CNSFlexMDIChildWnd::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);

    lpMMI->ptMinTrackSize.x = m_nMinTrackingWidth;
    lpMMI->ptMinTrackSize.y = m_nMinTrackingHeight;
}

LRESULT CNSFlexMDIChildWnd::OnSetMinTrackSize(WPARAM wParam, LPARAM lParam)
{
    CRect rect;

	GetWindowRect(rect);
    m_nMinTrackingWidth = rect.Width();
    m_nMinTrackingHeight = rect.Height();

	return 1;
}
