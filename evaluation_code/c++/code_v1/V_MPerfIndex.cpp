// V_MPerfIndex.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "math.h"
#include "D_ELS.h"
#include "V_ELS.h"
#include "V_MPerfIndex.h"
#include "Exprimnt.h"
#include "dgexpind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDFSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CViewMPerfIndex

IMPLEMENT_DYNCREATE(CViewMPerfIndex, CFormView)

CViewMPerfIndex::CViewMPerfIndex()
	: CFormView(CViewMPerfIndex::IDD)
{
	//{{AFX_DATA_INIT(CViewMPerfIndex)
	m_CHECK_SubPref = FALSE;
	m_CHECK_WeightedIndices = FALSE;
	m_ED_nHeat_0_180 = 0;
	m_ED_nHeat_90_270 = 0;
	m_ED_nOfFiles = 0;
	//}}AFX_DATA_INIT
}

CViewMPerfIndex::~CViewMPerfIndex()
{
}

void CViewMPerfIndex::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewMPerfIndex)
	DDX_Control(pDX, IDC_MESSAGE, m_STATIC_Message);
	DDX_Control(pDX, IDC_LB_PERF_INDICES, m_LB_PerfIndices);
	DDX_Control(pDX, IDC_LB_EXP_NAMES, m_LB_ExpNames);
	DDX_Check(pDX, IDC_CHECK_SUB_PREF, m_CHECK_SubPref);
	DDX_Check(pDX, IDC_CHECK_WEIGHTED_INDICES, m_CHECK_WeightedIndices);
	DDX_Text(pDX, IDC_ED_N_0_180, m_ED_nHeat_0_180);
	DDX_Text(pDX, IDC_ED_N_90_270, m_ED_nHeat_90_270);
	DDX_Text(pDX, IDC_ED_N_OF_FILES, m_ED_nOfFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewMPerfIndex, CFormView)
	//{{AFX_MSG_MAP(CViewMPerfIndex)
	ON_BN_CLICKED(IDC_CHECK_WEIGHTED_INDICES, OnCheckWeightedIndices)
	ON_BN_CLICKED(IDC_CHECK_SUB_PREF, OnCheckSubPref)
	ON_COMMAND(ID_FILE_EXPORTINDICES, OnFileExportIndices)
	ON_BN_CLICKED(IDC_RECALC, OnRecalc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewMPerfIndex diagnostics

#ifdef _DEBUG
void CViewMPerfIndex::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewMPerfIndex::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewMPerfIndex message handlers

void CViewMPerfIndex::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(FALSE);
	ResizeParentToFit(FALSE);
}

void CViewMPerfIndex::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CDocELS *pDoc = (CDocELS *)GetDocument();

	int i, j, N, nFiles, nPaths;
	double s_x2[MAX_BLOCKS], sx[MAX_BLOCKS], sx_2[MAX_BLOCKS];
	CString s, s1, t, lastPath;
	CExperiment exp;
	
	// pruefen ob View mit Experimenteliste geoeffnet ist:
	BOOL ELSisActive = FALSE;
	CView* pView;
	POSITION pos = pDoc->GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CViewELS)))
		{
			ELSisActive = TRUE;
			((CViewELS *)pView)->ParseExpScript();
		}
	}
	if (!ELSisActive) pDoc->ParseExpScript();

	for (i = 0; i < MAX_BLOCKS; i++)
	{
		pDoc->m_perfIndex[i] = 0.0;
		pDoc->m_SEM[i] = 0.0;
		s_x2[i] = 0.0;
		sx[i] = 0.0;
		sx_2[i] = 0.0;
	}
	pDoc->m_nHeat_0_180 = 0;
	pDoc->m_nHeat_90_270 = 0;
	nFiles = pDoc->m_fileList.GetSize();
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
	for (i = 0, N = 0; i < nFiles; i++)
	{
		CWaitCursor wait;
		s = exp.MakeFullName(lastPath, pDoc->m_fileList[i]);
		if (!exp.LoadExperiment(s))
		{
			for (j = 0; j < nPaths; j++)
			{
				s = exp.MakeFullName(pDoc->m_pathList[j], pDoc->m_fileList[i]);
				if (exp.LoadExperiment(s))
				{
					lastPath = s;
					break;
				}
			}
		}
		s.Format("Calculating indices: %i%%, Experiment: %s...", 
			(i * 100) / nFiles, exp.m_ExpName);
		m_STATIC_Message.SetWindowText(s);
		UpdateData(FALSE);
		if (exp.IsValid()) 
		{
			N++;
			if (N == 1)
			{
				pDoc->m_ExpDur = exp.m_ExpDur;
				pDoc->m_nOfBlocks = exp.m_nOfBlocks;
				for (j = 0; j < pDoc->m_nOfBlocks; j++)
				{
					pDoc->m_BlockDur[j] = exp.m_BlockDur[j];
					pDoc->m_BlockLen[j] = exp.m_BlockLen[j];
					pDoc->m_BlockType[j] = exp.m_BlockType[j];
				}
			}
			// Indices der einzelnen Experimente berechnen
			exp.CalcPerfIndices(m_CHECK_SubPref, m_CHECK_WeightedIndices);
			if (exp.m_iHeat == HEAT_0_180) pDoc->m_nHeat_0_180++;
			else pDoc->m_nHeat_90_270++;
			s.Format("Calculating indices: %i%%, Experiment: %s. O.k.", 
				(i * 100) / nFiles, exp.m_ExpName);
			m_STATIC_Message.SetWindowText(s);
			UpdateData(FALSE);
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				pDoc->m_perfIndex[j] += exp.m_PerfIndex[j];
				s_x2[j] += exp.m_PerfIndex[j] * exp.m_PerfIndex[j];
				sx[j] += exp.m_PerfIndex[j];
				sx_2[j] = sx[j] * sx[j];
				if (N < 2) continue;
				pDoc->m_SEM[j] = s_x2[j] - (sx_2[j] / N);
				pDoc->m_SEM[j] /= N * (N - 1);
				pDoc->m_SEM[j] = sqrt(pDoc->m_SEM[j]);
			}
		}
		else
		{
			s.Format("Calculating indices: %i%%, Experiment: %s. Error!", 
				(i * 100) / nFiles, exp.m_ExpName);
			m_STATIC_Message.SetWindowText(s);
			UpdateData(FALSE);
		}
	}
	s.Format("Indices of %i out of %i experiments calculated. Done.",
		N, nFiles);
	m_STATIC_Message.SetWindowText(s);
	UpdateData(FALSE);
	m_LB_PerfIndices.ResetContent();
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		pDoc->m_perfIndex[i] /= N;
		switch (pDoc->m_BlockType[i])
		{
			case EXPTYPE_TEST: t = "test"; break;
			case EXPTYPE_TRAIN: t = "training"; break;
			case EXPTYPE_REPL: t = "replay"; break;
			default: t = "?"; break;
		}
		s.Format("PI%i = % .3f +/- %.3f (%s)", i + 1, pDoc->m_perfIndex[i],
			pDoc->m_SEM[i], t);
		m_LB_PerfIndices.AddString(s);
	}
	m_LB_ExpNames.ResetContent();
	j = pDoc->m_fileList.GetSize();
	for (i = 0; i < j; i++)
	{
		s.Format("%s", pDoc->m_fileList[i]);
		m_LB_ExpNames.AddString(s);
	}
	m_ED_nOfFiles = nFiles;
	m_ED_nHeat_0_180 = pDoc->m_nHeat_0_180;
	m_ED_nHeat_90_270 = pDoc->m_nHeat_90_270;
	UpdateData(FALSE);
	DrawDiagram();
}

void CViewMPerfIndex::OnCheckWeightedIndices() 
{
	UpdateData();

	CDocELS *pDoc = (CDocELS *)GetDocument();
	pDoc->UpdateAllViews(NULL);
}

void CViewMPerfIndex::OnCheckSubPref() 
{
	UpdateData();

	CDocELS *pDoc = (CDocELS *)GetDocument();
	pDoc->UpdateAllViews(NULL);
}

void CViewMPerfIndex::OnRecalc() 
{
	UpdateData();

	CDocELS *pDoc = (CDocELS *)GetDocument();
	pDoc->UpdateAllViews(NULL);
}

void CViewMPerfIndex::OnDraw(CDC* pDC) 
{
	int oldDC = pDC->SaveDC();
	DrawDiagram();
	pDC->RestoreDC(oldDC);
}

void CViewMPerfIndex::DrawDiagram()
{
	
	int i, j, xaxzero, x, oldx, dxax, dyax, ymax;
	double time, relpos, rely, ysmin, ysmax, dys, dy;
	CString s;
	
	CDocELS* pDoc = (CDocELS *)GetDocument();
	
	CWnd *pWnd = GetDlgItem(IDC_FRAME_MULT_PERF_IND);
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
		ysmax = 1.0;
		ysmin = -1.0;
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
	for (i = -1; i < pDoc->m_nOfBlocks; i++)
	{
		if (i < 0) time = 0.0;
		else time += pDoc->m_BlockDur[i];
		relpos = time / pDoc->m_ExpDur;
		x = (int)(dxax * relpos) + r.left;
		pDC->MoveTo(x, r.bottom + 2);
		pDC->LineTo(x, r.bottom + 8);
		s.Format("%i' %02i", (int)time / 60, (int)time % 60);
		pDC->TextOut(x, r.bottom + 10, s);
	}
	s = "Time [min' sec]";
	pDC->TextOut(r.left + x / 2, r.bottom + text.cy + 12, s);

	// Indizees zeichnen
	CRect sem;
	pDC->SetBkColor(dgrColor);
	relpos = 0.0;
	time = 0.0;
	for (i = -1; i < pDoc->m_nOfBlocks; i++)
	{
		if (i < 0)
		{
			time = 0.0;
			oldx = 2;
		}
		else 
		{
			time += pDoc->m_BlockDur[i];
			relpos = time / pDoc->m_ExpDur;
			x = (int)(dxax * relpos) + r.left + 1;
			p.left = oldx - 1;
			p.right = x;
			sem.left = p.left + (int)(p.Width() / 2.0);
			sem.right = sem.left;
			rely = pDoc->m_perfIndex[i] / ysmax;
			if (rely >= 0)
			{
				if (rely > 1.0) rely = 1.0;
				p.top = xaxzero - (int)(rely * ymax);
				p.bottom = xaxzero + 1;
				sem.bottom = p.top + int(pDoc->m_SEM[i] * ymax / ysmax);
				sem.top = p.top - int(pDoc->m_SEM[i] * ymax / ysmax);
				if (sem.top < xaxzero - ymax) sem.top = xaxzero - ymax;
				if (sem.bottom > xaxzero + ymax) sem.bottom = xaxzero + ymax;
			}
			else
			{
				if (rely < -1.0) rely = -1.0;
				p.top = xaxzero;
				p.bottom = xaxzero - (int)(rely * ymax) + 1;
				sem.bottom = p.bottom + int(pDoc->m_SEM[i] * ymax / ysmax);
				sem.top = p.bottom - int(pDoc->m_SEM[i] * ymax / ysmax);
				if (sem.top < xaxzero - ymax) sem.top = xaxzero - ymax;
				if (sem.bottom > xaxzero + ymax) sem.bottom = xaxzero + ymax;
			}
			switch (pDoc->m_BlockType[i])
			{
				case EXPTYPE_TEST:
					pIndexBrush = &testModeBrush;
					break;
				case EXPTYPE_TRAIN:
				case EXPTYPE_REPL:
					pIndexBrush = &trainModeBrush;
					break;
				default:
					pIndexBrush = &dgrBrush;
					break;
			}
			pDC->FillRect(p, pIndexBrush);
			pDC->FrameRect(p, &scaleBrush);
			pDC->FrameRect(sem, &scaleBrush);
			oldx = x;
		}
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);

}

void CViewMPerfIndex::OnFileExportIndices() 
{
	/*
	CDlgExportIndices eDlg;
	eDlg.m_pDoc = (CDocELS *)GetDocument();
	eDlg.m_pEd = &GetEditCtrl();
	eDlg.DoModal();
	*/
}
