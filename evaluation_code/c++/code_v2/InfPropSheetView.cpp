// InfPropSheetView.cpp : implementation file
//

#include "stdafx.h"
#include "Dfs.h"
#include "InfPropSheetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfPropSheetView

IMPLEMENT_DYNCREATE(CInfPropSheetView, CNSFlexPropertySheetView)

BEGIN_MESSAGE_MAP(CInfPropSheetView, CNSFlexPropertySheetView)
	//{{AFX_MSG_MAP(CInfPropSheetView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CInfPropSheetView::CInfPropSheetView()
{
	GetFlexPropertySheet()->AddPage(&m_pInfPropPageOverview);
	GetFlexPropertySheet()->AddPage(&m_pInfPropPagePerformance);
}

CInfPropSheetView::~CInfPropSheetView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CInfPropSheetView drawing

void CInfPropSheetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CInfPropSheetView diagnostics

#ifdef _DEBUG
void CInfPropSheetView::AssertValid() const
{
	CView::AssertValid();
}

void CInfPropSheetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfPropSheetView message handlers
