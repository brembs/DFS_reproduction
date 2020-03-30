// V_TimeTr.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "V_TimeTr.h"
#include "D_INF.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTimeTrace

IMPLEMENT_DYNCREATE(CViewTimeTrace, CFormView)

CViewTimeTrace::CViewTimeTrace()
	: CFormView(CViewTimeTrace::IDD)
{
	m_PosRange = 4096;
	m_MaxPosValue = 2047;
	m_MinPosValue = -2048;

	//{{AFX_DATA_INIT(CViewTimeTrace)
	m_CHECK_PositionTrace = FALSE;
	m_CHECK_TorqueTrace = FALSE;
	m_ED_Debug = 0;
	//}}AFX_DATA_INIT
}

CViewTimeTrace::~CViewTimeTrace()
{
}

void CViewTimeTrace::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewTimeTrace)
	DDX_Control(pDX, IDC_SB_TIME, m_SB_Time);
	DDX_Check(pDX, IDC_CHECK_POSITIONTRACE, m_CHECK_PositionTrace);
	DDX_Check(pDX, IDC_CHECK_TORQUETRACE, m_CHECK_TorqueTrace);
	DDX_Text(pDX, IDC_DEBUG, m_ED_Debug);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewTimeTrace, CFormView)
	//{{AFX_MSG_MAP(CViewTimeTrace)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_POSITIONTRACE, OnCheckPositionTrace)
	ON_BN_CLICKED(IDC_CHECK_TORQUETRACE, OnCheckTorqueTrace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TIMETRACES, OnUpdateViewTimetraces)
	ON_BN_CLICKED(IDC_BTN_POSTRACE_CLR, OnPostraceColor)
	ON_BN_CLICKED(IDC_BTN_TRQTRACE_CLR, OnTrqtraceColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTimeTrace diagnostics

#ifdef _DEBUG
void CViewTimeTrace::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewTimeTrace::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewTimeTrace message handlers

void CViewTimeTrace::OnDraw(CDC* pDC) 
{
	CDocINF* pDoc = (CDocINF *)GetDocument();


	int oldDC = pDC->SaveDC();
	
    DrawAxes();
	DrawScales();
	DrawTrace();
	DrawColorBox();

	pDC->RestoreDC(oldDC);
}

// Skalen und Diagrammhintergrund zeichnen
void CViewTimeTrace::DrawAxes()
{
	CDocINF* pDoc = (CDocINF *)GetDocument();

	int xAxLeft, xAxRight, i;
	int yp45deg, yp135deg, ym45deg, ym135deg;
	float y, dy;
	CRect r;

	CPen dotPen(PS_DOT, 1, RGB(0, 0, 0));
	CPen solidPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *pOldPen;

	CBrush *pOldBrush;
	CBrush posBrush;
	posBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush blackBrush;
	blackBrush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush hatchBrush;
	hatchBrush.CreateHatchBrush(HS_DIAGCROSS, RGB(224, 224, 224));

	CWnd *pTraceWnd = GetDlgItem(IDC_FRAME_TIMETRACE);
	m_pTraceDC = pTraceWnd->GetDC();

	// Diagrammhintergrund 
	pOldBrush = m_pTraceDC->SelectObject(&posBrush);
	m_pTraceDC->FillRect(m_TraceRect, &posBrush);
	
	// bestrafte Sektoren schraffieren
	dy = (float)m_TraceRect.Height() / 4.0f;
	y = dy / 2.0f + m_TraceRect.top;
	for (i = 0; i < 4; i++)
	{
		if (i == 0) yp135deg = (int)y;
		else
		if (i == 1) yp45deg = (int)y;
		else
		if (i == 2) ym45deg = (int)y;
		else
		if (i == 3) ym135deg = (int)y;
		y += dy;
	}
	m_pTraceDC->SelectObject(&hatchBrush);
	r.left = m_TraceRect.left;
	r.right = m_TraceRect.right;
	if (pDoc->m_Experiment.m_iHeat == HEAT_0_180)
	{
		r.top = m_TraceRect.top;
		r.bottom = yp135deg;
		m_pTraceDC->FillRect(r, &hatchBrush);
		r.top = yp45deg;
		r.bottom = ym45deg;
		m_pTraceDC->FillRect(r, &hatchBrush);
		r.top = ym135deg;
		r.bottom = m_TraceRect.bottom;
		m_pTraceDC->FillRect(r, &hatchBrush);
	}
	else
	if (pDoc->m_Experiment.m_iHeat == HEAT_90_270)
	{
		r.top = yp135deg;
		r.bottom = yp45deg;
		m_pTraceDC->FillRect(r, &hatchBrush);
		r.top = ym45deg;
		r.bottom = ym135deg;
		m_pTraceDC->FillRect(r, &hatchBrush);
	}

	// x-Achsen zeichnen
	pOldPen = m_pTraceDC->SelectObject(&dotPen);
	xAxLeft = m_TraceRect.left;
	xAxRight = m_TraceRect.right;

	dy = (float)m_TraceRect.Height() / 4.0f;
	y = dy / 2.0f + m_TraceRect.top;
	for (i = 0; i < 4; i++)
	{
		m_pTraceDC->MoveTo(xAxLeft, (int)y);
		m_pTraceDC->LineTo(xAxRight, (int)y);
		y += dy;
	}
	m_pTraceDC->SelectObject(&solidPen);
	y = (float)m_TraceRect.Height() / 2.0f + m_TraceRect.top;
	m_pTraceDC->MoveTo(xAxLeft, (int)y);
	m_pTraceDC->LineTo(xAxRight, (int)y);

	//m_pTraceDC->SelectObject(&blackBrush);
	//m_pTraceDC->FrameRect(m_TraceRect, &blackBrush);

	// Original GDI-Objekte wiederherstellen
	m_pTraceDC->SelectObject(pOldPen);
	m_pTraceDC->SelectObject(pOldBrush);
	pTraceWnd->ReleaseDC(m_pTraceDC);
}

void CViewTimeTrace::DrawExpType()
{
	CDocINF* pDoc = (CDocINF *)GetDocument();
	
	CWnd *pWnd = GetDlgItem(IDC_FRAME_EXPMODE);
	CDC *pDC = pWnd->GetDC();

	int i, maxi;

	maxi = m_SB_TimePos + m_SB_TimePage;
	for (i = m_SB_TimePos; i < maxi; i++)
	{
	}

	pWnd->ReleaseDC(pDC);
}

void CViewTimeTrace::DrawScales()
{
	CDC *pDC = GetDC();
	if (pDC == NULL) return;

	int	i, j, k, time, left, tickwidth, tickno;
	CString s;
	
	CFont *pOldFont;
	CFont scaleFont;
	scaleFont.CreatePointFont(80, "MS Sans Serif", pDC);
	pOldFont = pDC->SelectObject(&scaleFont);
	
	CSize text;
	text = pDC->GetTextExtent("0");

	CRect r, t;
	CWnd *pWnd = GetDlgItem(IDC_FRAME_TIMETRACE);
	pWnd->GetWindowRect(r);
	GetWindowRect(t);
	r -= t.TopLeft();
	r.left -= 1;
	r.right -= 4;
	t = r;
	t.top = r.bottom - 2;
	t.bottom = t.top + text.cy + 10;

	COLORREF bkColor = RGB(192, 192, 192);
	CBrush *pOldBrush;
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(bkColor);
	pOldBrush = pDC->SelectObject(&bkBrush);
	r = t;
	r.left = 0;
	r.right += text.cx * 5;
	pDC->FillRect(r, &bkBrush);

	COLORREF tickColor = RGB(0, 0, 0);
	CPen tickPen(PS_SOLID, 1, tickColor);
	CPen *pOldPen;
	
	pOldPen = pDC->SelectObject(&tickPen);
	// drawing main ticks of timescale
	tickwidth = SAMPLE_FREQ * 5/*seconds*/;
	tickno = m_TraceRect.Width() / tickwidth;
	left = m_SB_TimePos / tickwidth;
	if ((m_SB_TimePos % tickwidth) != 0) left++;
	left *= tickwidth;
	left -= m_SB_TimePos;
	m_ED_Debug = left;
	UpdateData(FALSE);
	pDC->SetBkColor(bkColor);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	for (i = 0, j = 0; i <= tickno; i++, j += tickwidth)
	{
		if ((j + left) >= t.Width()) break;
		time = (m_SB_TimePos + left + j) / SAMPLE_FREQ;
		s.Format("%i' %02i", time / 60, time % 60);
		k = t.left + j + left;
		pDC->MoveTo(k, t.top);
		pDC->LineTo(k, t.top + 10);
		pDC->TextOut(k, t.top + 11, s);
	}
	// drawing small ticks of timescale
	tickwidth = SAMPLE_FREQ;	// one tick every second
	tickno = m_TraceRect.Width() / tickwidth;
	left = m_SB_TimePos / tickwidth;
	if ((m_SB_TimePos % tickwidth) != 0) left++;
	left *= tickwidth;
	left -= m_SB_TimePos;
	//m_ED_Debug = left;
	//UpdateData(FALSE);
	for (i = 0, j = 0; i <= tickno; i++, j += tickwidth)
	{
		if ((j + left) >= t.Width()) break;
		k = t.left + j + left;
		pDC->MoveTo(k, t.top);
		pDC->LineTo(k, t.top + 6);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldBrush);
	ReleaseDC(pDC);
}

void CViewTimeTrace::DrawTrace()
{
	CDocINF* pDoc = (CDocINF *)GetDocument();

	CWnd *pTraceWnd = GetDlgItem(IDC_FRAME_TIMETRACE);
	m_pTraceDC = pTraceWnd->GetDC();
	
	COLORREF posColor = m_PosTraceColor;
	COLORREF trqColor = m_TrqTraceColor;
	COLORREF borderColor = RGB(0, 0, 128);

	CPen posPen(PS_SOLID, 1, posColor);
	CPen trqPen(PS_SOLID, 1, trqColor);
	CPen borderPen(PS_SOLID, 2, borderColor);
	CPen *pOldPen;

	int a, i, j, maxi, x, y, lasty, newy;
	int k;
	float f, fy, fdy, fdy2;

	fdy = (float)m_TraceRect.Height() - 1;
	fy = fdy / 2.0f / m_MinPosValue;
	fdy2 = fdy / 2.0f;

	a = m_SB_TimePos;
	maxi = m_SB_TimePage;
	
	// Positionsspur zeichnen
	pOldPen = m_pTraceDC->SelectObject(&posPen);
	if (m_CHECK_PositionTrace == TRUE)
	{
		j = 1;		// Spur nicht in den Rahmen zeichnen
		newy = pDoc->m_Experiment.m_Pos[0];
		f =  newy * fy + fdy2;
		y = int(f) + m_TraceRect.top;
		m_pTraceDC->MoveTo(j, y);
		lasty = newy;
		for (i = 1, j = 2, x = a; i < maxi; i++, j++, x++)
		{
			newy = pDoc->m_Experiment.m_Pos[x];
			f = newy * fy + fdy2;
			y = int(f) + m_TraceRect.top;
			if (abs(lasty - newy) > 1000)
			{
				// grosse Spruenge nicht als durchgehende Linie zeichnen
				m_pTraceDC->MoveTo(j, y);
				m_pTraceDC->SetPixel(j, y, posColor);
			}
			else m_pTraceDC->LineTo(j, y);
			m_pTraceDC->LineTo(j, y);
			lasty = newy;
		}
	}

	// Torquespur zeichnen
	m_pTraceDC->SelectObject(&trqPen);
	if (m_CHECK_TorqueTrace == TRUE)
	{
		j = 1;			// Spur nicht in den Rahmen zeichnen
		f = pDoc->m_Experiment.m_Trq[0] * fy + fdy2;
		y = int(f) + m_TraceRect.top;
		m_pTraceDC->MoveTo(j, y);
		for (i = 1, j = 2, x = a; i < maxi; i++, j++, x++)
		{
			f = pDoc->m_Experiment.m_Trq[x] * fy + fdy2;
			y = int(f) + m_TraceRect.top;
			m_pTraceDC->LineTo(j, y);
		}
	}

	// Blockgrenze einzeichnen
	m_pTraceDC->SelectObject(&borderPen);
	for (i = 1, j = 2, x = a; i < maxi; i++, j++, x++)
	{
		for (k = 0; k < pDoc->m_Experiment.m_nOfBlocks; k++)
		{
			if (x == pDoc->m_Experiment.m_BlockEnd[k])
			{
				j = x - a + 1;
				m_pTraceDC->MoveTo(j, m_TraceRect.top);
				m_pTraceDC->LineTo(j, m_TraceRect.bottom);
			}
		}
	}

	m_pTraceDC->SelectObject(pOldPen);
	pTraceWnd->ReleaseDC(m_pTraceDC);
}

void CViewTimeTrace::DrawColorBox()
{
	CRect r;

	CBrush *pOldBrush;
	CBrush posBrush;
	posBrush.CreateSolidBrush(m_PosTraceColor);
	CBrush trqBrush;
	trqBrush.CreateSolidBrush(m_TrqTraceColor);

	CWnd *pWnd;
	CDC *pDC;
	
	pWnd = GetDlgItem(IDC_FRAME_POSCOLOR);
	pDC = pWnd->GetDC();
	pWnd->GetClientRect(r);
	pOldBrush = pDC->SelectObject(&posBrush);
	pDC->FillRect(r, &posBrush);
	pDC->SelectObject(pOldBrush);
	pWnd->ReleaseDC(pDC);
	pWnd->RedrawWindow();

	pWnd = GetDlgItem(IDC_FRAME_TRQCOLOR);
	pDC = pWnd->GetDC();
	pWnd->GetClientRect(r);
	pOldBrush = pDC->SelectObject(&trqBrush);
	pDC->FillRect(r, &trqBrush);
	pDC->SelectObject(pOldBrush);
	pWnd->ReleaseDC(pDC);
	pWnd->RedrawWindow();
}

void CViewTimeTrace::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar == &m_SB_Time)
	{
		switch (nSBCode)
		{
			case SB_LINELEFT:
				if (m_SB_TimePos == 0) break; 
				if (m_SB_TimePos > m_SB_TimeLine) m_SB_TimePos -= m_SB_TimeLine;
				else m_SB_TimePos = 0;
				m_SB_Time.SetScrollPos(m_SB_TimePos);
				DrawAxes();
				DrawTrace();
				DrawScales();
			break;
			case SB_LINERIGHT:
				if (m_SB_TimePos == m_SB_TimeMax) break; 
				if (m_SB_TimePos < m_SB_TimeMax - m_SB_TimeLine) 
					m_SB_TimePos += m_SB_TimeLine;
				else m_SB_TimePos = m_SB_TimeMax;
				m_SB_Time.SetScrollPos(m_SB_TimePos);
				DrawAxes();
				DrawTrace();
				DrawScales();
			break;
			case SB_PAGELEFT:
				if (m_SB_TimePos == 0) break; 
				if (m_SB_TimePos > m_SB_TimePage) m_SB_TimePos -= m_SB_TimePage;
				else m_SB_TimePos = 0;
				m_SB_Time.SetScrollPos(m_SB_TimePos);
				DrawAxes();
				DrawTrace();
				DrawScales();
			break;
			case SB_PAGERIGHT:
				if (m_SB_TimePos == m_SB_TimeMax) break; 
				if (m_SB_TimePos < m_SB_TimeMax - m_SB_TimePage) 
					m_SB_TimePos += m_SB_TimePage;
				else m_SB_TimePos = m_SB_TimeMax;
				m_SB_Time.SetScrollPos(m_SB_TimePos);
				DrawAxes();
				DrawTrace();
				DrawScales();
			break;
			case SB_THUMBTRACK:
				m_SB_TimePos = nPos;
				m_SB_Time.SetScrollPos(m_SB_TimePos);
				DrawAxes();
				DrawTrace();
				DrawScales();
			break;
		}
	}
	else
	{
		CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CViewTimeTrace::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	
	// Zeiger auf zugehoeriges Dokument ermitteln
	CDocINF *pDoc = (CDocINF *)GetDocument();
	m_pDoc = pDoc;

	// Koordinaten der Rahmen fuer die Diagramme ermitteln
	GetDiagramFrame();

	// ScrollBar Einstellungen initialisieren
	m_SB_TimeMin = 0;
	m_SB_TimeMax = pDoc->m_Experiment.m_nOfData - m_TraceRect.Width();
	m_SB_TimePos = 0;
	m_SB_TimePage = m_TraceRect.Width();
	m_SB_TimeLine = m_SB_TimePage / 10;
	m_SB_Time.SetScrollRange(m_SB_TimeMin, m_SB_TimeMax);
	m_SB_Time.SetScrollPos(m_SB_TimePos);
	
	// CheckBox Einstellungen initialisieren
	m_CHECK_PositionTrace = TRUE;
	m_CHECK_TorqueTrace = TRUE;
	m_ED_Debug = 0;
	m_PosTraceColor = RGB(0, 128, 0);
	m_TrqTraceColor = RGB(128, 64, 0);

	UpdateData(FALSE);
	
	// Fensterabmessungen an Fensterinhalt anpassen
	ResizeParentToFit(FALSE);	
}

void CViewTimeTrace::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDocINF *pDoc = (CDocINF *)GetDocument();

	// Arena Positionswertebreich beruecksichtigen
	if (pDoc->m_Experiment.m_ArenaType == ARENA_2048) 
	{
		m_PosRange = 4096;
		m_MaxPosValue = 2047;
		m_MinPosValue = -2048;
	}
	else
	{
		m_PosRange = 3600;
		m_MaxPosValue = 1800;
		m_MinPosValue = -1800;
	}
	UpdateData();
    DrawAxes();
	DrawTrace();
}

void CViewTimeTrace::GetDiagramFrame()
{
	// Koordinaten der Rahmen fuer die Diagramme ermitteln
	CWnd *pWnd;
	
	pWnd = GetDlgItem(IDC_FRAME_TIMETRACE);
	pWnd->GetClientRect(m_TraceRect);
	m_TraceRect.TopLeft().Offset(1, 1);
	m_TraceRect.BottomRight().Offset(-1, -1);
}

void CViewTimeTrace::OnCheckPositionTrace() 
{
	UpdateData();
    DrawAxes();
	DrawTrace();
}

void CViewTimeTrace::OnCheckTorqueTrace() 
{
 	UpdateData();
	DrawAxes();
	DrawTrace();
}

void CViewTimeTrace::OnUpdateViewTimetraces(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


void CViewTimeTrace::OnPostraceColor() 
{
	CColorDialog dlg(m_PosTraceColor);
	if (dlg.DoModal() == IDOK)
	{
		m_PosTraceColor = dlg.GetColor();
		DrawColorBox();
		DrawTrace();
	}
}

void CViewTimeTrace::OnTrqtraceColor() 
{
	CColorDialog dlg(m_TrqTraceColor);
	if (dlg.DoModal() == IDOK)
	{
		m_TrqTraceColor = dlg.GetColor();
		DrawColorBox();
		DrawTrace();
	}
}
