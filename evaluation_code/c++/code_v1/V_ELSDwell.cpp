// V_ELSDwell.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "V_ELSDwell.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewELSDwell

IMPLEMENT_DYNCREATE(CViewELSDwell, CFormView)

CViewELSDwell::CViewELSDwell()
	: CFormView(CViewELSDwell::IDD)
{
	//{{AFX_DATA_INIT(CViewELSDwell)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CViewELSDwell::~CViewELSDwell()
{
}

void CViewELSDwell::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewELSDwell)
	DDX_Control(pDX, IDC_BUTTON1, m_BTN_Test);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewELSDwell, CFormView)
	//{{AFX_MSG_MAP(CViewELSDwell)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewELSDwell diagnostics

#ifdef _DEBUG
void CViewELSDwell::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewELSDwell::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewELSDwell message handlers

void CViewELSDwell::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	ResizeParentToFit(FALSE);
}

void CViewELSDwell::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CViewELSDwell::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CViewELSDwell::OnButton() 
{

	CString ext, filter, title;
	int flags;
	CString fpath, s;
	CFile f;

	int i, j;

	ext = "*.asc";
	filter = "ASCII file (*.asc)|*.asc|All files (*.*)|*.*||";
	title = "Choose ASCII file";
	flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	CFileDialog fDlg(FALSE, ext, NULL, flags, filter);
	fDlg.m_ofn.lpstrTitle = title;
	
	if (fDlg.DoModal() == IDOK)
	{
		fpath = fDlg.GetPathName();
		f.Open(fpath, CFile::modeCreate | CFile::modeWrite);
		srand(37);
		int a, b, c, m;
		int ap, bp, cp, k;
		a = 84; b = 37; c = 17;
		k = 10;
		for (i = 0; i < 16384; i++)
		{
			ap = (rand() * k / RAND_MAX) - (k / 2) + i;
			ap %= a;
			if (ap == 0) ap = 1; else ap = 0;
			bp = (rand() * k / RAND_MAX) - (k / 2) + i; 
			bp %= b;
			if (bp == 0) bp = 1; else bp = 0;
			cp = (rand() * k / RAND_MAX) - (k / 2) + i; 
			cp %= c;
			if (cp == 0) cp = 1; else cp = 0;
			m = ap || bp || cp;

			s.Format("%i\n", m);
			f.Write(s, s.GetLength() * sizeof(char));
		}
		f.Close();
	}
}
