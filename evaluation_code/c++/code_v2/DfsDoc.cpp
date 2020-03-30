// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "DfsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDfsDoc, CDocument)

BEGIN_MESSAGE_MAP(CDfsDoc, CDocument)
	//{{AFX_MSG_MAP(CDfsDoc)
	ON_COMMAND(ID_DEMO_FLEXIBLE_FORM_VIEW, OnDemoFlexibleFormView)
	ON_COMMAND(ID_DEMO_FLEXIBLE_PROPERTY_SHEET, OnDemoFlexiblePropertySheet)
	ON_COMMAND(ID_DEMO_FLEXIBLE_PROPERTY_SHEET_VIEW, OnDemoFlexiblePropertySheetView)
	ON_COMMAND(ID_DEMO_INTRODUCTION, OnDemoIntroduction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CDfsDoc::CDfsDoc()
{
//	m_csIntroduction  = "";
}

CDfsDoc::~CDfsDoc()
{

}

BOOL CDfsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
/*
	m_csEdit1 = "Flexible views are cool!";
	m_csList1 = "CNSFlexDialog";
	m_csCombo1 = "NSFlexDialog.h";
	m_csCombo2 = "NSFlexHorizontallyFixed";
	m_csCombo3 = "NSFlexDialog.cpp";

	m_csTab2Edit1 = "Flexible views are cool!";
*/
	return TRUE;
}

void CDfsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG

void CDfsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDfsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG


void CDfsDoc::OnDemoFlexibleFormView() 
{
/*
	CDfsApp* pDfsApp = (CDfsApp*)AfxGetApp();
	CMultiDocTemplate* pMultiDocTemplate = pDfsApp->m_pFlexFormViewDocTemplate;
	CFrameWnd* pFrameWnd = pMultiDocTemplate->CreateNewFrame(this,NULL);
	pMultiDocTemplate->InitialUpdateFrame(pFrameWnd,this);
*/
}

void CDfsDoc::OnDemoFlexiblePropertySheet() 
{
/*
	CFlexPropertySheet FlexPropertySheet;
	FlexPropertySheet.SetSubject(this);
	FlexPropertySheet.DoModal();
*/
}

void CDfsDoc::OnDemoFlexiblePropertySheetView() 
{
	CDfsApp* pDfsApp = (CDfsApp*)AfxGetApp();
	CMultiDocTemplate* pMultiDocTemplate = pDfsApp->m_pElsDocTemplate;
	CFrameWnd* pFrameWnd = pMultiDocTemplate->CreateNewFrame(this,NULL);
	pMultiDocTemplate->InitialUpdateFrame(pFrameWnd,this);
}

void CDfsDoc::OnDemoIntroduction() 
{
	CDfsApp* pDfsApp = (CDfsApp*)AfxGetApp();
	CMultiDocTemplate* pMultiDocTemplate = pDfsApp->m_pIntroViewDocTemplate;
	CFrameWnd* pFrameWnd = pMultiDocTemplate->CreateNewFrame(this,NULL);
	pMultiDocTemplate->InitialUpdateFrame(pFrameWnd,this);
}
