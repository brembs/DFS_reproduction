// V_Dwell.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "V_Dwell.h"
#include "D_INF.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewDwell

IMPLEMENT_DYNCREATE(CViewDwell, CFormView)

CViewDwell::CViewDwell()
	: CFormView(CViewDwell::IDD)
{
	//{{AFX_DATA_INIT(CViewDwell)
	m_ED_BlockNo = _T("");
	m_RADIO_HotCold = -1;
	m_ED_MeanDwellHot = _T("");
	m_ED_MeanDwellCold = _T("");
	m_RADIO_XLinLog = -1;
	m_ED_TimeResolution = _T("");
	m_SpinBuddyBlockNo = 0;
	m_SpinBuddyTimeResolution = 0;
	//}}AFX_DATA_INIT
}

CViewDwell::~CViewDwell()
{
}

void CViewDwell::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDwell)
	DDX_Control(pDX, IDC_SPIN_RESOLUTION, m_SPIN_Resolution);
	DDX_Control(pDX, IDC_SPIN_BLOCKNO, m_SPIN_BlockNo);
	DDX_Text(pDX, IDC_BLOCK_NO, m_ED_BlockNo);
	DDX_Radio(pDX, IDC_RADIO_HOT_COLD, m_RADIO_HotCold);
	DDX_Text(pDX, IDC_MEAN_DWELL_HOT, m_ED_MeanDwellHot);
	DDX_Text(pDX, IDC_MEAN_DWELL_COLD, m_ED_MeanDwellCold);
	DDX_Radio(pDX, IDC_RADIO_X_LIN_LOG, m_RADIO_XLinLog);
	DDX_Text(pDX, IDC_TIME_RESOLUTION, m_ED_TimeResolution);
	DDX_Text(pDX, IDC_SPINBUDDY_BLOCK_NO, m_SpinBuddyBlockNo);
	DDX_Text(pDX, IDC_SPINBUDDY_TIME_RESOLUTION, m_SpinBuddyTimeResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewDwell, CFormView)
	//{{AFX_MSG_MAP(CViewDwell)
	ON_BN_CLICKED(IDC_RADIO_HOT_COLD, OnRadioHotCold)
	ON_EN_CHANGE(IDC_SPINBUDDY_BLOCK_NO, OnChangeSpinbuddyBlockNo)
	ON_EN_CHANGE(IDC_SPINBUDDY_TIME_RESOLUTION, OnChangeSpinbuddyTimeResolution)
	ON_BN_CLICKED(IDC_RADIO_X_LIN_LOG, OnRadioXLinLog)
	ON_BN_CLICKED(IDC_RADIO_HOT_COLD1, OnRadioHotCold1)
	ON_BN_CLICKED(IDC_RADIO_X_LIN_LOG2, OnRadioXLinLog2)
	ON_BN_CLICKED(IDC_RADIO_HOT_COLD2, OnRadioHotCold2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDwell diagnostics

#ifdef _DEBUG
void CViewDwell::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewDwell::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewDwell message handlers

void CViewDwell::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	CDocINF *pDoc = (CDocINF *)GetDocument();

	m_SPIN_Resolution.SetBuddy(GetDlgItem(IDC_SPINBUDDY_TIME_RESOLUTION));
	m_SPIN_Resolution.SetRange(1, SAMPLE_FREQ * 10);	// max. 10 Sek.
	m_SpinBuddyTimeResolution = SAMPLE_FREQ / 4;
	m_SPIN_Resolution.SetPos(m_SpinBuddyTimeResolution);
	m_RADIO_XLinLog = 1;
	UpdateData(FALSE);

	pDoc->m_Experiment.CalcDwellingTimes(m_SpinBuddyTimeResolution);

	m_maxBlock = pDoc->m_Experiment.m_nOfBlocks;
	if (m_maxBlock > 0) m_maxBlock--;
	m_SPIN_BlockNo.SetBuddy(GetDlgItem(IDC_SPINBUDDY_BLOCK_NO));
	m_SPIN_BlockNo.SetRange(0, m_maxBlock);
	m_SPIN_BlockNo.SetPos(0);
	m_curBlock = m_SPIN_BlockNo.GetPos();
	m_RADIO_HotCold = 0;
	UpdateData(FALSE);

	// Fensterabmessungen an Fensterinhalt anpassen
	ResizeParentToFit(FALSE);
}

void CViewDwell::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (pHint != this) return;

	CDocINF *pDoc = (CDocINF *)GetDocument();

	UpdateData();
	m_curBlock = m_SpinBuddyBlockNo;
	m_ED_BlockNo.Format("%i/%i (%s)", 
		m_SpinBuddyBlockNo + 1, pDoc->m_Experiment.m_nOfBlocks,
		GetBlockType(pDoc->m_Experiment.m_BlockType[m_SpinBuddyBlockNo]));
	m_ED_MeanDwellHot.Format("%.2f s", pDoc->m_Experiment.m_meanDwellHot[m_SpinBuddyBlockNo]);
	m_ED_MeanDwellCold.Format("%.2f s", pDoc->m_Experiment.m_meanDwellCold[m_SpinBuddyBlockNo]);
	m_ED_TimeResolution.Format("%.2f s", (double)m_SpinBuddyTimeResolution / SAMPLE_FREQ);
	UpdateData(FALSE);

	DrawDiagram();
}

void CViewDwell::OnChangeSpinbuddyBlockNo() 
{
	CDocINF *pDoc = (CDocINF *)GetDocument();
	pDoc->UpdateAllViews(NULL, 0, this);
}

void CViewDwell::OnChangeSpinbuddyTimeResolution() 
{
	CDocINF *pDoc = (CDocINF *)GetDocument();

	UpdateData();
	pDoc->m_Experiment.CalcDwellingTimes(m_SpinBuddyTimeResolution);
	pDoc->UpdateAllViews(NULL, 0, this);
}

void CViewDwell::OnRadioHotCold() 
{
	m_RADIO_HotCold = 0;
	UpdateData(FALSE);
	DrawDiagram();
}

void CViewDwell::OnRadioHotCold1() 
{
	m_RADIO_HotCold = 1;
	UpdateData(FALSE);
	DrawDiagram();
}
void CViewDwell::OnRadioHotCold2() 
{
	m_RADIO_HotCold = 2;
	UpdateData(FALSE);
	DrawDiagram();
}

void CViewDwell::OnRadioXLinLog() 
{
	m_RADIO_XLinLog = 0;
	UpdateData(FALSE);
	DrawDiagram();
}

void CViewDwell::OnRadioXLinLog2() 
{
	m_RADIO_XLinLog = 1;
	UpdateData(FALSE);
	DrawDiagram();
}

void CViewDwell::OnDraw(CDC* pDC) 
{
	DrawDiagram();
}

void CViewDwell::DrawDiagram()
{
	
	int i, j, k, ix, iy, oldx, xaxzero, dxax, dyax, ymax;
	double f, g, x, y, rely, ysmin, ysmax, dys, dy;
	double relx, xsmin, xsmax, dxs, dx;
	CString s;
	
	CDocINF* pDoc = (CDocINF *)GetDocument();
	CExperiment *pExp = &pDoc->m_Experiment;

	CWnd *pWnd = GetDlgItem(IDC_FRAME_DIAGRAM);
	CDC *pDC = pWnd->GetDC();

	COLORREF dgrColor = RGB(255, 255, 255);		// Farbe f. Diagrammhintergrund
	COLORREF bkColor = RGB(192, 192, 192);		// Farbe f. Fensterhintergrund
	COLORREF scaleColor = RGB(0, 0, 0);			// Farbe f. Raender und Achsen
	COLORREF ltgrayColor = RGB(224, 224, 224);	// Farbe f. Gitter
	COLORREF heatColor = RGB(196, 0, 0);		// Farbe f. bestrafte Sektoren
	COLORREF blueColor = RGB(0, 0, 196);		// Farbe f. Balken
	CPen *pOldPen;
	CPen scalePen;
	scalePen.CreatePen(PS_SOLID, 1, scaleColor);
	CPen ltgrayPen;
	ltgrayPen.CreatePen(PS_DOT, 1, ltgrayColor);

	CBrush *pOldBrush, *pIndexBrush;
	CBrush bkBrush, dgrBrush, coldBrush, hotBrush, scaleBrush;
	bkBrush.CreateSolidBrush(bkColor);
	dgrBrush.CreateSolidBrush(dgrColor);
	scaleBrush.CreateSolidBrush(scaleColor);
	coldBrush.CreateSolidBrush(blueColor);
	hotBrush.CreateSolidBrush(heatColor);

	CFont *pOldFont;
	CFont scaleFont;
	scaleFont.CreatePointFont(80, "MS Sans Serif", pDC);
	pOldFont = pDC->SelectObject(&scaleFont);
	CSize text;
	text = pDC->GetTextExtent("-1.0");

	// Diagrammrechteck ermitteln
	CRect r, p, q;
	pWnd->GetClientRect(r);
	r.TopLeft().Offset(1, 1);
	r.BottomRight().Offset(-1, -1);

	// Diagrammhintergrund 
	pDC->SetBkMode(TRANSPARENT);

	pOldPen = pDC->SelectObject(&scalePen);
	pOldBrush = pDC->SelectObject(&dgrBrush);
	pDC->FillRect(r, &dgrBrush);

	// Achsen zeichnen und beschriften
	pDC->SetBkColor(bkColor);
	pDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
	dxax = r.right - r.left - 1;
	dyax = r.bottom - r.top - 1;
	xaxzero = r.bottom;
	ymax = dyax;
	// pDC->MoveTo(r.left, xaxzero);
	// pDC->LineTo(r.left + dxax, xaxzero);
	ysmax = 2.5;
	ysmin = 0.0;
	dys = ysmax - ysmin;
	for (rely = ysmin; rely < ysmax; rely += 1.0)		// Beschriftung y-Achse
	{
		j = r.bottom - (int)(dyax * rely / dys);
		pDC->SelectObject(&ltgrayPen);
		pDC->MoveTo(r.left, j);
		if (rely > ysmin) pDC->LineTo(r.right, j);
		pDC->SelectObject(&scalePen);
		pDC->MoveTo(r.left - 2, j);
		pDC->LineTo(r.left - 9, j);
		s.Format("%.0f", pow(10.0, rely));
		pDC->TextOut(r.left - 10, j + text.cy / 2, s);
		for (f = 1.0; f < 10.0; f += 1.0)				// kurze Teilstriche
		{
			y = rely + log10(f);
			if (y > ysmax) break;
			j = r.bottom - (int)(dyax * y / dys);
			pDC->MoveTo(r.left - 2, j);
			pDC->LineTo(r.left - 6, j);
		}
	}
	
	// x-Achsenbeschriftung loeschen:
	q = r;
	q.top = r.bottom + 2;
	q.left -= 10;
	q.right += 10;
	q.bottom += 25;
	pDC->FillRect(q, &bkBrush);

	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	if (m_RADIO_XLinLog == 0)		// x-Achse, lin. Skala
	{
		xsmin = 0.0;
		xsmax = pExp->m_BlockDur[m_curBlock];
		dxs = xsmax - xsmin;
		dx = GetDiv(dxs);
		for (relx = ysmin; relx <= xsmax; relx += dx)	// Teilstriche
		{
			j = (int)(dxax * relx / dxs) + r.left;
			pDC->SelectObject(&ltgrayPen);
			pDC->MoveTo(j, r.top);
			pDC->LineTo(j, r.bottom);
			pDC->SelectObject(&scalePen);
			pDC->MoveTo(j, r.bottom + 2);
			pDC->LineTo(j, r.bottom + 9);
			s.Format("%i", (int)relx);
			pDC->TextOut(j, r.bottom + 10, s);			// Beschriftung
		}
	}
	else if (m_RADIO_XLinLog == 1)	// x-Achse, log. Skala
	{
		xsmin = log10(0.01);
		x = 0.0 - xsmin;
		xsmax = log10((double)pExp->m_BlockDur[m_curBlock]);
		dxs = xsmax - xsmin;
		for (relx = xsmin; relx < xsmax; relx += 1.0)	// Dekadenteilstriche
		{	
			j = (int)(dxax * (relx + x) / dxs) + r.left;
			pDC->SelectObject(&ltgrayPen);
			pDC->MoveTo(j, r.top);
			pDC->LineTo(j, r.bottom);
			pDC->SelectObject(&scalePen);
			pDC->MoveTo(j, r.bottom + 2);
			pDC->LineTo(j, r.bottom + 9);
			s.Format("%g", pow(10.0, relx));
			pDC->TextOut(j, r.bottom + 10, s);			// Dekadenbeschriftung
			for (g = 1.0; g < 10.0; g += 1.0)			// kurze Teilstriche
			{
				f = relx + log10(g);
				if (f > xsmax) break;
				f += x;
				j = (int)(dxax * f / dxs) + r.left;
				pDC->MoveTo(j, r.bottom + 2);
				pDC->LineTo(j, r.bottom + 6);
			}
		}
	}
	s = "Dwelling Time [sec]";
	pDC->TextOut(r.left + r.Width() / 2, r.bottom + text.cy + 12, s);

	// Aufenthaltsdauern zeichnen
	pDC->SetBkColor(dgrColor);
	j = pExp->m_DwellTimeCold[m_curBlock].GetSize();
	if (m_RADIO_XLinLog == 0)		// Werte zeichnen, lin. Skala
	{
		dx = pExp->m_DwellUnit / dxs;
		oldx = r.left;
		for (i = 0; i < j; i++)
		{
			// rechten Rand des Histogrambalkens berechnen (daher (i + 1) * dx)
			ix = (int)(dxax * (i + 1) * dx) + r.left;
			p.left = oldx;
			p.right = ix;
			if (p.right == p.left) p.right++;
			p.bottom = r.bottom;
			if (m_RADIO_HotCold == 0) 
			{
				pIndexBrush = &coldBrush;
				k = pExp->m_DwellTimeCold[m_curBlock][i];
			}
			else
			if (m_RADIO_HotCold == 1)   
			{
				pIndexBrush = &hotBrush;
				k = pExp->m_DwellTimeHot[m_curBlock][i];
			}
			else
			{
				pIndexBrush = &scaleBrush;
				k = pExp->m_DwellTimeCold[m_curBlock][i] +
				pExp->m_DwellTimeHot[m_curBlock][i];
			}
			rely = log10((double)k);
			iy = (int)(dyax * rely / dys);
			p.top = r.bottom - iy - 1;
			if (k > 0) pDC->FillRect(p, pIndexBrush);
			oldx = ix;
			q = p;
			q.bottom = q.top + 1;
			q.top--;
			// if (k > 0) pDC->FillRect(q, pIndexBrush);
		}
	}
	else if (m_RADIO_XLinLog == 1)		// Werte zeichnen, log. Skala
	{
		x =  pExp->m_DwellUnit; 
		oldx = (int)(dxax * (log10(x) - xsmin) / dxs) + r.left;
		for (i = 0; i < j; i++)	
		{
			x = (i + 1) * pExp->m_DwellUnit; 
			ix = (int)(dxax * (log10(x) - xsmin) / dxs) + r.left;
			p.left = oldx;
			p.right = ix;
			if (p.right == p.left) p.right++;
			p.bottom = r.bottom;

			if (m_RADIO_HotCold == 0) 
			{
				k = pExp->m_DwellTimeCold[m_curBlock][i];
				pIndexBrush = &coldBrush;
			}
			else
			if (m_RADIO_HotCold == 1) 
			{
				k = pExp->m_DwellTimeHot[m_curBlock][i];
				pIndexBrush = &hotBrush;
			}
			else
			{
				pIndexBrush = &scaleBrush;
				k = pExp->m_DwellTimeCold[m_curBlock][i] +
				pExp->m_DwellTimeHot[m_curBlock][i];
			}
			rely = log10((double)k);
			iy = (int)(dyax * rely / dys);
			p.top = r.bottom - iy - 1;
			//if (k > 0) pDC->FillRect(p, pIndexBrush);
			oldx = ix;
			q = p;
			q.left = ix - 2;
			q.right = q.left + 4;
			q.bottom = q.top + 1;
			q.top -= 3;
			if (k > 0) pDC->FillRect(q, pIndexBrush);
		}
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
}

double CViewDwell::GetDiv(double range)
{
	if (range <= 0.75) return 0.05;
	else if (range <= 1.5) return 0.1;
	else if (range <= 7.5) return 0.5;
	else if (range <= 15.0) return 1.0;
	else if (range <= 75.0) return 5.0;
	else if (range <= 150.0) return 10.0;
	else if (range <= 750.0) return 50.0;
	else if (range <= 1500.0) return 100.0;
	else return 500.0;
}
