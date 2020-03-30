// V_PerfIndex.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "V_PerfIndex.h"
#include "D_INF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPerfIndex

IMPLEMENT_DYNCREATE(CViewPerfIndex, CFormView)

CViewPerfIndex::CViewPerfIndex()
	: CFormView(CViewPerfIndex::IDD)
{
	//{{AFX_DATA_INIT(CViewPerfIndex)
	m_CHECK_SubPref = FALSE;
	m_CHECK_WeightedIndices = FALSE;
	m_ED_Preference = 0.0f;
	//}}AFX_DATA_INIT
}

CViewPerfIndex::~CViewPerfIndex()
{
}

void CViewPerfIndex::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewPerfIndex)
	DDX_Control(pDX, IDC_BMP_HEAT, m_BMP_Heat);
	DDX_Control(pDX, IDC_HEAT_90_270, m_BMP_Heat_90_270);
	DDX_Control(pDX, IDC_HEAT_0_180, m_BMP_Heat_0_180);
	DDX_Control(pDX, IDC_LIST_PERF_INDICEES, m_LB_Index);
	DDX_Check(pDX, IDC_CHECK_SUB_PREF, m_CHECK_SubPref);
	DDX_Check(pDX, IDC_CHECK_WEIGHTED_INDICES, m_CHECK_WeightedIndices);
	DDX_Text(pDX, IDC_PREFERENCE, m_ED_Preference);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewPerfIndex, CFormView)
	//{{AFX_MSG_MAP(CViewPerfIndex)
	ON_BN_CLICKED(IDC_CHECK_SUB_PREF, OnCheckSubPref)
	ON_BN_CLICKED(IDC_CHECK_WEIGHTED_INDICES, OnCheckWeightedIndices)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPerfIndex diagnostics

#ifdef _DEBUG
void CViewPerfIndex::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewPerfIndex::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewPerfIndex message handlers

void CViewPerfIndex::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	CDocINF *pDoc = (CDocINF *)GetDocument();

	// CheckBox Einstellungen initialisieren
	m_CHECK_SubPref = FALSE;
	m_CHECK_WeightedIndices = FALSE;

	HBITMAP hBitmap;
	if (pDoc->m_Experiment.m_iHeat == HEAT_0_180)
		hBitmap = m_BMP_Heat_0_180.GetBitmap();
	else hBitmap = m_BMP_Heat_90_270.GetBitmap();
	m_BMP_Heat.SetBitmap(hBitmap);

	UpdateData(FALSE);

	// Fensterabmessungen an Fensterinhalt anpassen
	ResizeParentToFit(FALSE);
}

void CViewPerfIndex::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocINF *pDoc = (CDocINF *)GetDocument();

	pDoc->m_Experiment.CalcPerfIndices(m_CHECK_SubPref, m_CHECK_WeightedIndices);
	CString s, t;
	int i; 
	m_LB_Index.ResetContent();
	for (i = 0; i <	pDoc->m_Experiment.m_nOfBlocks; i++)
	{
		t = GetBlockType(pDoc->m_Experiment.m_BlockType[i]);
		s.Format("PI%i = % .3f (%s)", i + 1, 
			pDoc->m_Experiment.m_PerfIndex[i], t);
		m_LB_Index.AddString(s);
	}
	m_ED_Preference = pDoc->m_Experiment.m_PrefIndex;

	DrawDiagram();
	UpdateData(FALSE);
}

void CViewPerfIndex::OnDraw(CDC* pDC) 
{
	int oldDC = pDC->SaveDC();
	DrawDiagram();
	pDC->RestoreDC(oldDC);
}

void CViewPerfIndex::DrawDiagram()
{
	
	int i, j, xaxzero, x, oldx, dxax, dyax, ymax;
	double time, relpos, rely, ysmin, ysmax, dys, dy;
	CString s;
	
	CDocINF* pDoc = (CDocINF *)GetDocument();
	
	CWnd *pWnd = GetDlgItem(IDC_FRAME_PERF_INDEX);
	CDC *pDC = pWnd->GetDC();

	COLORREF dgrColor = RGB(255, 255, 255);
	COLORREF heatColor = RGB(196, 0, 0);
	COLORREF bkColor = RGB(192, 192, 192);
	COLORREF scaleColor = RGB(0, 0, 0);
	CPen *pOldPen;
	CPen scalePen;
	scalePen.CreatePen(PS_SOLID, 1, scaleColor);
	CBrush *pOldBrush, *pIndexBrush;
	CBrush dgrBrush, testModeBrush, trainModeBrush, scaleBrush;
	dgrBrush.CreateSolidBrush(dgrColor);
	scaleBrush.CreateSolidBrush(scaleColor);
	testModeBrush.CreateHatchBrush(HS_FDIAGONAL, scaleColor);
	trainModeBrush.CreateHatchBrush(HS_DIAGCROSS, heatColor);

	CFont *pOldFont;
	CFont scaleFont;
	scaleFont.CreatePointFont(80, "MS Sans Serif", pDC);
	pOldFont = pDC->SelectObject(&scaleFont);
	CSize text;
	text = pDC->GetTextExtent("-1.0");

	CRect r, p;
	pWnd->GetClientRect(r);
	r.TopLeft().Offset(1, 1);
	r.BottomRight().Offset(-1, -1);

	// Diagrammhintergrund 
	pOldPen = pDC->SelectObject(&scalePen);
	pOldBrush = pDC->SelectObject(&dgrBrush);
	pDC->FillRect(r, &dgrBrush);

	// Achsen zeichnen und beschriften
	pDC->SetBkColor(bkColor);
	pDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
	dxax = r.right - r.left - 1;
	dyax = r.bottom - r.top - 1;
	xaxzero = dyax / 2 + r.top;
	ymax = r.bottom - xaxzero;
	pDC->MoveTo(r.left, xaxzero);
	pDC->LineTo(r.left + dxax, xaxzero);
	ysmax = 1.0;
	ysmin = -1.0;
	if (m_CHECK_WeightedIndices == TRUE)
	{
		ysmax = 5.0;
		ysmin = -5.0;
	}
	dys = ysmax - ysmin;
	dy = dys / 10;
	for (rely = ysmax, i = 0; rely >= ysmin;  rely -= dy, i++)
	{
		j = (int)(dyax * dy * i / dys) + r.top;
		pDC->MoveTo(r.left - 2, j);
		pDC->LineTo(r.left - 8, j);
		s.Format("%.1f", rely);
		pDC->TextOut(r.left - 10, j + text.cy / 2, s);
	}
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	relpos = 0.0;
	time = 0.0;
	for (i = -1; i < pDoc->m_Experiment.m_nOfBlocks; i++)
	{
		if (i < 0) time = 0.0;
		else time += pDoc->m_Experiment.m_BlockDur[i];
		relpos = time / pDoc->m_Experiment.m_ExpDur;
		x = (int)(dxax * relpos) + r.left;
		pDC->MoveTo(x, r.bottom + 2);
		pDC->LineTo(x, r.bottom + 8);
		s.Format("%i' %02i", (int)time / 60, (int)time % 60);
		pDC->TextOut(x, r.bottom + 10, s);
	}
	s = "Time [min' sec]";
	pDC->TextOut(r.left + x / 2, r.bottom + text.cy + 12, s);

	// Indizees zeichnen
	pDC->SetBkColor(dgrColor);
	relpos = 0.0;
	time = 0.0;
	for (i = -1; i < pDoc->m_Experiment.m_nOfBlocks; i++)
	{
		if (i < 0)
		{
			time = 0.0;
			oldx = 2;
		}
		else 
		{
			time += pDoc->m_Experiment.m_BlockDur[i];
			relpos = time / pDoc->m_Experiment.m_ExpDur;
			x = (int)(dxax * relpos) + r.left + 1;
			p.left = oldx - 1;
			p.right = x;
			rely = pDoc->m_Experiment.m_PerfIndex[i];
			if (m_CHECK_WeightedIndices == TRUE) rely /= ysmax;
			if (rely >= 0)
			{
				if (rely > 1.0) rely = 1.0;
				p.top = xaxzero - (int)(rely * ymax);
				p.bottom = xaxzero + 1;
			}
			else
			{
				if (rely < -1.0) rely = -1.0;
				p.top = xaxzero;
				p.bottom = xaxzero - (int)(rely * ymax) + 1;
			}
			switch (pDoc->m_Experiment.m_BlockType[i])
			{
				case EXPTYPE_TEST:
					pIndexBrush = &testModeBrush;
					break;
				case EXPTYPE_TRAIN:
				case EXPTYPE_REPL:
					pIndexBrush = &trainModeBrush;
					break;
			}
			pDC->FillRect(p, pIndexBrush);
			pDC->FrameRect(p, &scaleBrush);
			oldx = x;
		}
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
}

void CViewPerfIndex::OnCheckSubPref() 
{
	CDocINF *pDoc = (CDocINF *)GetDocument();

	UpdateData();
	pDoc->UpdateAllViews(NULL);
}

void CViewPerfIndex::OnCheckWeightedIndices() 
{
	CDocINF *pDoc = (CDocINF *)GetDocument();

	UpdateData();
	pDoc->UpdateAllViews(NULL);
}
