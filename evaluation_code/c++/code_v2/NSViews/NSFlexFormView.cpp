// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "NSFlexFormView.h"
#include "NSFlexConstraintList.h"
#include "NSFlexMDIChildWnd.h"
#include "NSViewsMessages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CNSFlexFormView, CFormView)

BEGIN_MESSAGE_MAP(CNSFlexFormView, CFormView)
	//{{AFX_MSG_MAP(CNSFlexFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CNSFlexFormView::CNSFlexFormView(UINT nIDTemplate) :
	CFormView(nIDTemplate)
{
	m_pFlexConstraintList = new CNSFlexConstraintList(this);

	// REVISION 4/10/97 TO WORK WITH SDI APPLICATIONS (Ed Smetak)
	m_bNeedInitialUpdate = TRUE;
	// END REVISION (Ver 1.04)
}

CNSFlexFormView::CNSFlexFormView(LPCTSTR lpszTemplateName) :
	CFormView(lpszTemplateName)
{
	m_pFlexConstraintList = new CNSFlexConstraintList(this);

	// REVISION 4/10/97 TO WORK WITH SDI APPLICATIONS (Ed Smetak)
	m_bNeedInitialUpdate = TRUE;
	// END REVISION (Ver 1.04)
}

CNSFlexFormView::~CNSFlexFormView()
{
    delete m_pFlexConstraintList;
}

void CNSFlexFormView::AddFlexConstraint(UINT nControlID, 
	const CNSFlexHorizontalConstraint& HorizontalConstraint,
	const CNSFlexVerticalConstraint& VerticalConstraint)
{
	m_pFlexConstraintList->AddConstraint(nControlID,
		HorizontalConstraint, VerticalConstraint);
}

int CNSFlexFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    m_pFlexConstraintList->
		SetClientBaseSize(lpCreateStruct->cx,lpCreateStruct->cy);
	
	return 0;
}

void CNSFlexFormView::OnInitialUpdate() 
{
	// REVISION 4/10/97 TO WORK WITH SDI APPLICATIONS (Ed Smetak)
	if (m_bNeedInitialUpdate)
	{
		m_bNeedInitialUpdate = FALSE;
	// END REVISION (Ver 1.04)


    //ResizeParentToFit(FALSE); // By Xie jignwei 10.10.1997

	CWnd *pParentFrame = GetParentFrame();
	ASSERT(pParentFrame);

	if (pParentFrame->IsKindOf(RUNTIME_CLASS(CNSFlexMDIChildWnd)))
		pParentFrame->SendMessage(WM_SETMINTRACKSIZE);
#ifdef _DEBUG
	else
		TRACE0("Warning!  "
			   "CNSFlexFormView used without CNSFlexMDIChildWnd frame.\n");
#endif

	CFormView::OnInitialUpdate();

	ASSERT(m_pFlexConstraintList->AssertAllFlexControlsExist());

	// REVISION 4/10/97 TO WORK WITH SDI APPLICATIONS (Ed Smetak)
	}
	else
		CFormView::OnInitialUpdate();
	// END REVISION (Ver 1.04)
}

void CNSFlexFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
    if (nType != SIZE_MINIMIZED)
        m_pFlexConstraintList->PositionControls(cx,cy);
}
