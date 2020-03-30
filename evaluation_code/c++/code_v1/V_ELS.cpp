// V_ELS.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "V_ELS.h"
#include "D_ELS.h"
#include "DgExpInd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewELS

IMPLEMENT_DYNCREATE(CViewELS, CEditView)

CViewELS::CViewELS()
{
}

CViewELS::~CViewELS()
{
}


BEGIN_MESSAGE_MAP(CViewELS, CEditView)
	//{{AFX_MSG_MAP(CViewELS)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_SETFONT, OnViewSetFont)
	ON_COMMAND(ID_FILE_EXPORT_INDICES, OnFileExportIndices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewELS drawing

void CViewELS::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewELS diagnostics

#ifdef _DEBUG
void CViewELS::AssertValid() const
{
	CEditView::AssertValid();
}

void CViewELS::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewELS message handlers

int CViewELS::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	m_screenFont.CreatePointFont(100, "Courier New");
	SetFont(&m_screenFont);
	
	return 0;
}

void CViewELS::OnViewSetFont() 
{
	CFont* pFont = GetFont();
	LOGFONT lf;
	if (pFont != NULL) 
		pFont->GetObject(sizeof(LOGFONT), &lf);
	else 
		::GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
	
	CFontDialog dlg(&lf, CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT);
	if (dlg.DoModal() == IDOK)
	{
		m_screenFont.DeleteObject();
		if (m_screenFont.CreateFontIndirect(&lf))
		SetFont(&m_screenFont);
	}
}

void CViewELS::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here
}

void CViewELS::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDocELS *pDoc = (CDocELS *)GetDocument();

	CEdit *pEd = &GetEditCtrl();
	CWaitCursor wait;
	pDoc->ParseExpScript(pEd);
}

void CViewELS::OnFileExportIndices() 
{
	CDlgExportIndices eDlg;
	eDlg.m_pDoc = (CDocELS *)GetDocument();
	eDlg.m_pEd = &GetEditCtrl();
	eDlg.DoModal();
}

int CViewELS::ParseExpScript()
{
	CDocELS *pDoc = (CDocELS *)GetDocument();
	CEdit *pEd = &GetEditCtrl();
	return pDoc->ParseExpScript(pEd);
}
