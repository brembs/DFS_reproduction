// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "ElsPropPageTorquePI.h"
#include "ElsExportPI.h"
#include "ElsDoc.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElsPropPageTorquePI, CNSFlexPropertyPage)

BEGIN_MESSAGE_MAP(CElsPropPageTorquePI, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CElsPropPageTorquePI)
	ON_BN_CLICKED(IDC_CHECK_ELS_HEAT0180, OnCheckElsHeat0180)
	ON_BN_CLICKED(IDC_CHECK_ELS_HEAT90270, OnCheckElsHeat90270)
	ON_BN_CLICKED(IDC_CHECK_ELS_NEGPREF, OnCheckElsNegpref)
	ON_BN_CLICKED(IDC_CHECK_ELS_POSPREF, OnCheckElsPospref)
	ON_BN_CLICKED(IDC_CHECK_ELS_SUBPREF, OnCheckElsSubpref)
	ON_BN_CLICKED(IDC_CHECK_ELS_TRANSFORMARTANH, OnCheckElsTransformartanh)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_ELS_EXPORT_PI, OnButtonElsExportPI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CElsPropPageTorquePI::CElsPropPageTorquePI() :
	CNSFlexPropertyPage(CElsPropPageTorquePI::IDD)
{
	AddFlexConstraint(IDC_BUTTON_ELS_EXPORT_PI, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_FRAME_ELS_PERFORMANCE, NSFlexExpandRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_CHECK_ELS_HEAT0180, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_CHECK_ELS_HEAT90270, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_CHECK_ELS_TRANSFORMARTANH, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_CHECK_ELS_SUBPREF, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_CHECK_ELS_NEGPREF, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_CHECK_ELS_POSPREF, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_STATIC_ELSPP2_1, NSFlexShiftRight, NSFlexExpandDown); 
	AddFlexConstraint(IDC_LIST_ELS_PERFINDICES, NSFlexShiftRight, NSFlexExpandDown); 
	AddFlexConstraint(IDC_EDIT_ELS_N_POS_PREF, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_EDIT_ELS_N_NEG_PREF, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_EDIT_ELS_N_REINF_0180, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_EDIT_ELS_N_REINF_90270, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_EDIT_ELS_N_ALL_FILES, NSFlexShiftRight, NSFlexShiftDown); 
	AddFlexConstraint(IDC_STATIC_ELSPP2_2, NSFlexShiftRight, NSFlexShiftDown); 

	//{{AFX_DATA_INIT(CElsPropPageTorquePI)
	m_CHECK_ElsPreferenceSubstracted = FALSE;
	m_CHECK_ElsInclPosPreference = FALSE;
	m_CHECK_ElsInclNegPreference = FALSE;
	m_CHECK_ElsInclReinf0180 = FALSE;
	m_CHECK_ElsInclReinf90270 = FALSE;
	m_CHECK_ElsTransformArtanh = FALSE;
	m_EDIT_ElsNPosPref = 0;
	m_EDIT_ElsNNegPref = 0;
	m_EDIT_ElsNReinf0180 = 0;
	m_EDIT_ElsNReinf90270 = 0;
	m_EDIT_ElsNAllFiles = 0;
	//}}AFX_DATA_INIT

	m_DialogInitialized = 0;
}

CElsPropPageTorquePI::~CElsPropPageTorquePI()
{

}

void CElsPropPageTorquePI::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsPropPageTorquePI)
	DDX_Control(pDX, IDC_FRAME_ELS_PERFORMANCE, m_FRAME_ElsPIs);
	DDX_Control(pDX, IDC_LIST_ELS_PERFINDICES, m_LIST_ElsPIs);
	DDX_Check(pDX, IDC_CHECK_ELS_SUBPREF, m_CHECK_ElsPreferenceSubstracted);
	DDX_Check(pDX, IDC_CHECK_ELS_POSPREF, m_CHECK_ElsInclPosPreference);
	DDX_Check(pDX, IDC_CHECK_ELS_NEGPREF, m_CHECK_ElsInclNegPreference);
	DDX_Check(pDX, IDC_CHECK_ELS_HEAT0180, m_CHECK_ElsInclReinf0180);
	DDX_Check(pDX, IDC_CHECK_ELS_HEAT90270, m_CHECK_ElsInclReinf90270);
	DDX_Check(pDX, IDC_CHECK_ELS_TRANSFORMARTANH, m_CHECK_ElsTransformArtanh);
	DDX_Text(pDX, IDC_EDIT_ELS_N_POS_PREF, m_EDIT_ElsNPosPref);
	DDX_Text(pDX, IDC_EDIT_ELS_N_NEG_PREF, m_EDIT_ElsNNegPref);
	DDX_Text(pDX, IDC_EDIT_ELS_N_REINF_0180, m_EDIT_ElsNReinf0180);
	DDX_Text(pDX, IDC_EDIT_ELS_N_REINF_90270, m_EDIT_ElsNReinf90270);
	DDX_Text(pDX, IDC_EDIT_ELS_N_ALL_FILES, m_EDIT_ElsNAllFiles);
	//}}AFX_DATA_MAP
}

BOOL CElsPropPageTorquePI::OnInitDialog() 
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	m_CHECK_ElsInclPosPreference = TRUE;
	m_CHECK_ElsInclNegPreference = TRUE;
	m_CHECK_ElsInclReinf0180 = TRUE;
	m_CHECK_ElsInclReinf90270 = TRUE;

	UpdateData(FALSE);
	
	m_DialogInitialized++;

	CNSFlexPropertyPage::OnInitDialog();
	
	return TRUE;  
}

void CElsPropPageTorquePI::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (!m_DialogInitialized) return;

	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	int i, j;
	double s_x2[MAX_EXP_BLOCKS], sx[MAX_EXP_BLOCKS], sx_2[MAX_EXP_BLOCKS];
	double x;
	CString s, t;
	
	m_EDIT_ElsNPosPref = 0;
	m_EDIT_ElsNNegPref = 0;
	m_EDIT_ElsNReinf0180 = 0;
	m_EDIT_ElsNReinf90270 = 0;
	m_EDIT_ElsNAllFiles = 0;

	for (j = 0; j < pDoc->m_nOfBlocks; j++)
	{
		pDoc->m_TI_Mean[j] = 0.0;
		pDoc->m_TI_SEM[j] = 0.0;
		s_x2[j] = 0.0;
		sx[j] = 0.0;
		sx_2[j] = 0.0;
	}
	int nIncl = 0;
	for (i = 0; i < pDoc->m_nExpOk; i++)
	{
		CWaitCursor wait;
		if (pDoc->m_PIArray[i].TIPreference < 0.0)
		{
			if (!m_CHECK_ElsInclNegPreference) continue;
			m_EDIT_ElsNNegPref++;
		}
		else
		{
			if (!m_CHECK_ElsInclPosPreference) continue;
			m_EDIT_ElsNPosPref++;
		}

		if (pDoc->m_PIArray[i].iHeat == HEAT_0_180)
		{
			if (!m_CHECK_ElsInclReinf0180) continue;
			m_EDIT_ElsNReinf0180++;
		}
		else
		{
			if (!m_CHECK_ElsInclReinf90270) continue;
			m_EDIT_ElsNReinf90270++;
		}

		nIncl++;
		for (j = 0; j < pDoc->m_nOfBlocks; j++)
		{
			if (m_CHECK_ElsPreferenceSubstracted)
			{
				if (m_CHECK_ElsTransformArtanh)
					x = TransformArtanh(pDoc->m_PIArray[i].TI[j] - 
						pDoc->m_PIArray[i].TIPreference);
				else
					x = pDoc->m_PIArray[i].TI[j] - pDoc->m_PIArray[i].TIPreference;
			}
			else
			{
				if (m_CHECK_ElsTransformArtanh)
					x = TransformArtanh(pDoc->m_PIArray[i].TI[j]);
				else 
					x = pDoc->m_PIArray[i].TI[j];
			}
			pDoc->m_TI_Mean[j] += x;
			s_x2[j] += x * x;
			sx[j] += x;
			sx_2[j] = sx[j] * sx[j];
			if (nIncl < 2) continue;
			pDoc->m_TI_SEM[j] = s_x2[j] - (sx_2[j] / (double)nIncl);
			pDoc->m_TI_SEM[j] /= (double)(nIncl * (nIncl - 1));
			pDoc->m_TI_SEM[j] = sqrt(pDoc->m_TI_SEM[j]);
		}
	}
	m_LIST_ElsPIs.ResetContent();
	for (j = 0; j < pDoc->m_nOfBlocks; j++)
	{
		if (nIncl > 0) 
			pDoc->m_TI_Mean[j] /= (double)nIncl;
		switch (pDoc->m_BlockType[j])
		{
			case EXPTYPE_TEST: t = "test"; break;
			case EXPTYPE_TRAIN: t = "training"; break;
			case EXPTYPE_REPL: t = "replay"; break;
			default: t = "?"; break;
		}
		s.Format("TI%0i: % .3f +/- %.3f (%s)", j + 1, pDoc->m_TI_Mean[j],
			pDoc->m_TI_SEM[j], t);
		m_LIST_ElsPIs.AddString(s);
	}	
	m_EDIT_ElsNAllFiles = nIncl;
	UpdateData(FALSE);
	DrawPerformanceHistogram();
}

void CElsPropPageTorquePI::DrawPerformanceHistogram()
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	if (pDoc == NULL) return;
	ASSERT(pDoc);

	CWnd *pWnd = GetDlgItem(IDC_FRAME_ELS_PERFORMANCE);
	CDC *pDC = pWnd->GetDC();

	int i, xaxzero, x, y, oldx, dxax, dyax, ymax;
	double time, relpos, ysmin, ysmax, dys, dy;
	double rely, ypilo, ypihi, relsem, ysemlo, ysemhi;
	CString s;

	// colors:
	COLORREF auxlineColor = RGB(224, 224, 224);	// aux. lines
	COLORREF dgrbkColor = RGB(255, 255, 255);	// diagram background
	COLORREF heatColor = RGB(196, 0, 0);		// training index bar
	COLORREF bkColor = RGB(192, 192, 192);		// window background
	COLORREF scaleColor = RGB(0, 0, 0);			// scales
	
	// pens and brushes:
	CPen *pOldPen;
	CPen scalePen, auxlinePen;
	scalePen.CreatePen(PS_SOLID, 1, scaleColor);
	auxlinePen.CreatePen(PS_SOLID, 1, auxlineColor);
	CBrush *pOldBrush, *pIndexBrush;
	CBrush dgrBrush, testModeBrush, trainModeBrush, scaleBrush;
	dgrBrush.CreateSolidBrush(dgrbkColor);
	scaleBrush.CreateSolidBrush(scaleColor);
	testModeBrush.CreateHatchBrush(HS_FDIAGONAL, scaleColor);
	trainModeBrush.CreateHatchBrush(HS_DIAGCROSS, heatColor);

	// fonts:
	CFont *pOldFont;
	CFont scaleFont;
	scaleFont.CreatePointFont(80, "MS Sans Serif", pDC);
	pOldFont = pDC->SelectObject(&scaleFont);
	CSize textsize;
	textsize = pDC->GetTextExtent("-1.0");

	CRect frame, pane, bar;
	m_FRAME_ElsPIs.GetClientRect(frame);
	frame.TopLeft().Offset(1, 1);
	frame.BottomRight().Offset(-1, -1);
	pane = frame;
	pane.BottomRight().Offset(-1, -1);

	// diagram background 
	pOldPen = pDC->SelectObject(&scalePen);
	pOldBrush = pDC->SelectObject(&dgrBrush);
	pDC->FillRect(frame, &dgrBrush);
	pDC->SetBkColor(bkColor);

	pDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
	dxax = pane.right - pane.left;
	dyax = pane.bottom - pane.top;
	xaxzero = dyax / 2 + pane.top;
	ymax = pane.bottom - xaxzero;
	
	// x-axis zero line
	pDC->MoveTo(pane.left, xaxzero);
	pDC->MoveTo(pane.right, xaxzero);
	
	// y-axis
	ysmax = 1.0;
	ysmin = -1.0;
	if (m_CHECK_ElsTransformArtanh == TRUE)
	{
		ysmax = 1.0;
		ysmin = -1.0;
	}
	dys = ysmax - ysmin;
	dy = dys / 10;
	for (rely = ysmax, i = 0; rely >= ysmin;  rely -= dy, i++)
	{
		y = (int)(dyax * dy * i / dys) + frame.top;
		pDC->SelectObject(&scalePen);
		pDC->MoveTo(frame.left - 2, y);
		pDC->LineTo(frame.left - 8, y);
		s.Format("%.1f", rely);
		pDC->TextOut(frame.left - 10, y + textsize.cy / 2, s);
		if (i > 0 && rely > ysmin)
		{
			pDC->SelectObject(&auxlinePen);
			pDC->MoveTo(pane.left, y);
			pDC->LineTo(pane.right, y);
		}
	}

	// x-axis
	pDC->SelectObject(&scalePen);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	if (pDoc->m_nOfBlocks == 0)
	{
		pDoc->m_nOfBlocks = 1;
		pDoc->m_BlockDur[0] = 60;
		pDoc->m_ExpDur = 60;
	}
	relpos = 0.0;
	time = 0.0;
	for (i = -1; i < pDoc->m_nOfBlocks; i++)
	{
		if (i < 0) time = 0.0;
		else time += pDoc->m_BlockDur[i];
		relpos = time / pDoc->m_ExpDur;
		x = (int)(dxax * relpos) + frame.left;
		pDC->MoveTo(x, frame.bottom + 2);
		pDC->LineTo(x, frame.bottom + 8);
		s.Format("%i' %02i", (int)time / 60, (int)time % 60);
		pDC->TextOut(x, frame.bottom + 10, s);
	}
	if (pDoc->m_nOfBlocks == 0) x = (int)(dxax) + frame.left;
	s = "Time [min' sec]";
	pDC->TextOut(frame.left + x / 2, frame.bottom + textsize.cy + 12, s);

	// drawing index bars:
	CRect sem;
	pDC->SetBkColor(dgrbkColor);
	relpos = 0.0;
	time = 0.0;
	oldx = 2;
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		time += pDoc->m_BlockDur[i];
		relpos = time / pDoc->m_ExpDur;
		x = (int)(dxax * relpos) + frame.left + 1;
		bar.left = oldx - 1;
		bar.right = x;
		sem.left = bar.left + (int)(bar.Width() / 2.0);
		sem.right = sem.left;
		rely = pDoc->m_TI_Mean[i] / ysmax;
		if (rely < 0) 
		{
			ypihi = 0.0;
			ypilo = rely;
			if (ypilo < -1.0) ypilo = -1.0;
		}
		else
		{
			ypihi = rely;
			if (ypihi > 1.0) ypihi = 1.0;
			ypilo = 0.0;
		}
		bar.bottom = xaxzero - (int)(ypilo * ymax) + 1;
		bar.top = xaxzero - (int)(ypihi * ymax);
		relsem = pDoc->m_TI_SEM[i] / ysmax;
		ysemlo = rely - relsem;
		if (ysemlo < -1.0) ysemlo = -1.0;
		ysemhi = rely + relsem;
		if (ysemhi > 1.0) ysemhi = 1.0;
		sem.bottom = xaxzero - (int)(ysemlo * ymax) + 1;
		sem.top = xaxzero - (int)(ysemhi * ymax) - 1;

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
		pDC->FillRect(bar, pIndexBrush);
		pDC->FrameRect(bar, &scaleBrush);
		pDC->FrameRect(sem, &scaleBrush);
		oldx = x;
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
}

void CElsPropPageTorquePI::UpdateDocumentData()
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	// insert updates here
}

void CElsPropPageTorquePI::OnCheckElsHeat0180() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnCheckElsHeat90270() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnCheckElsNegpref() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnCheckElsPospref() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnCheckElsSubpref() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnCheckElsTransformartanh() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnUpdate(NULL, 0, NULL);
}

void CElsPropPageTorquePI::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	DrawPerformanceHistogram();
	
	// Do not call CNSFlexPropertyPage::OnPaint() for painting messages
}


void CElsPropPageTorquePI::OnButtonElsExportPI() 
{
	// TODO: Add your control notification handler code here
	CElsExportTI dlg;
	dlg.m_pDoc = GetDocument();
	
	dlg.DoModal();
}
