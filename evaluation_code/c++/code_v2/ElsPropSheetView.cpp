// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "ElsPropSheetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElsPropSheetView, CNSFlexPropertySheetView)

BEGIN_MESSAGE_MAP(CElsPropSheetView, CNSFlexPropertySheetView)
	//{{AFX_MSG_MAP(CElsPropSheetView)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CElsPropSheetView::CElsPropSheetView()
{
	GetFlexPropertySheet()->AddPage(&m_ElsPropPageExperimentList);
	GetFlexPropertySheet()->AddPage(&m_ElsPropPagePerformance);
	GetFlexPropertySheet()->AddPage(&m_ElsPropPageFixation);
	GetFlexPropertySheet()->AddPage(&m_ElsPropPageTorquePI);
}

CElsPropSheetView::~CElsPropSheetView()
{

}

void CElsPropSheetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

#ifdef _DEBUG

void CElsPropSheetView::AssertValid() const
{
	CView::AssertValid();
}

void CElsPropSheetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

void CElsPropSheetView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	SendMessageToDescendants(WM_COPY);
}

void CElsPropSheetView::OnEditCut() 
{
	// TODO: Add your command handler code here
	SendMessageToDescendants(WM_CUT);
}

void CElsPropSheetView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	SendMessageToDescendants(WM_PASTE);
}

void CElsPropSheetView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	SendMessageToDescendants(WM_UNDO);
}
