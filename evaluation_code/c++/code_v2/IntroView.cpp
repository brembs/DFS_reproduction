// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "IntroView.h"
#include "DfsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CIntroView, CNSFlexFormView)

BEGIN_MESSAGE_MAP(CIntroView, CNSFlexFormView)
	//{{AFX_MSG_MAP(CIntroView)
	ON_BN_CLICKED(IDC_BUTTON_FORM_VIEW, OnButtonFormView)
	ON_BN_CLICKED(IDC_BUTTON_PROP_SHEET, OnButtonPropSheet)
	ON_BN_CLICKED(IDC_BUTTON_PROP_SHEET_VIEW, OnButtonPropSheetView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CIntroView::CIntroView()
	: CNSFlexFormView(CIntroView::IDD)
{
	// The first one really isn't needed since this is the default
	// constraint for all controls

	AddFlexConstraint(IDC_EDIT_INTRO,
		NSFlexExpandRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_BUTTON_PROP_SHEET,
		NSFlexHorizontallyFixed, NSFlexShiftDown);
	AddFlexConstraint(IDC_BUTTON_FORM_VIEW,
		NSFlexHorizontallyFixed, NSFlexShiftDown);
	AddFlexConstraint(IDC_BUTTON_PROP_SHEET_VIEW,
		NSFlexHorizontallyFixed, NSFlexShiftDown);

	//{{AFX_DATA_INIT(CIntroView)
	m_csIntroduction = _T("");
	//}}AFX_DATA_INIT
}

CIntroView::~CIntroView()
{

}

void CIntroView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntroView)
	DDX_Text(pDX, IDC_EDIT_INTRO, m_csIntroduction);
	//}}AFX_DATA_MAP
}

#ifdef _DEBUG

void CIntroView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIntroView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif //_DEBUG


void CIntroView::OnButtonFormView() 
{
	PostMessage(WM_COMMAND,ID_DEMO_FLEXIBLE_FORM_VIEW);
}

void CIntroView::OnButtonPropSheet() 
{
	PostMessage(WM_COMMAND,ID_DEMO_FLEXIBLE_PROPERTY_SHEET);
}

void CIntroView::OnButtonPropSheetView() 
{
	PostMessage(WM_COMMAND,ID_DEMO_FLEXIBLE_PROPERTY_SHEET_VIEW);
}

void CIntroView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	
}

void CIntroView::OnInitialUpdate() 
{
	CDfsDoc* pDoc = (CDfsDoc*)GetDocument();
	ASSERT(pDoc);


	CNSFlexFormView::OnInitialUpdate();
}
