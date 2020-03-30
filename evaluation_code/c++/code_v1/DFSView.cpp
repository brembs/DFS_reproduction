// DFSView.cpp : implementation of the CDFSView class
//

#include "stdafx.h"
#include "DFS.h"

#include "DFSDoc.h"
#include "DFSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDFSView

IMPLEMENT_DYNCREATE(CDFSView, CView)

BEGIN_MESSAGE_MAP(CDFSView, CView)
	//{{AFX_MSG_MAP(CDFSView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFSView construction/destruction

CDFSView::CDFSView()
{
	// TODO: add construction code here

}

CDFSView::~CDFSView()
{
}

BOOL CDFSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDFSView drawing

void CDFSView::OnDraw(CDC* pDC)
{
	CDFSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDFSView printing

BOOL CDFSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDFSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDFSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDFSView diagnostics

#ifdef _DEBUG
void CDFSView::AssertValid() const
{
	CView::AssertValid();
}

void CDFSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDFSDoc* CDFSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDFSDoc)));
	return (CDFSDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDFSView message handlers
