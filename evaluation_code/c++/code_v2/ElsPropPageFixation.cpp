// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "stdafx.h"
#include "Dfs.h"
#include "ElsPropSheetViewFrm.h"
#include "ElsPropPageFixation.h"
#include "ElsExportPI.h"
#include "ElsDoc.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElsPropPageFixation, CNSFlexPropertyPage)

BEGIN_MESSAGE_MAP(CElsPropPageFixation, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CElsPropPageFixation)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_EDIT_ELS_SPINBUDDY_BLOCK, OnChangeEditElsSpinbuddyBlock)
	ON_CBN_SELCHANGE(IDC_COMBO_ELS_DISPLAY_RESOLUTION, OnSelchangeComboElsDisplayResolution)
	ON_BN_CLICKED(IDC_RADIO_ELS_HEAT2, OnRadioElsSelectHeat90270)
	ON_BN_CLICKED(IDC_RADIO_ELS_HEAT, OnRadioElsSelectHeat0180)
	ON_BN_CLICKED(IDC_RADIO_ELS_HEAT3, OnRadioElsSelectHeatAll)
	ON_BN_CLICKED(IDC_CHECK_ELS_HALF_ARENA, OnCheckElsHalfArena)
	ON_BN_CLICKED(IDC_CHECK_ELS_SUPERIMPOSED, OnCheckElsSuperimposed)
	ON_BN_CLICKED(IDC_BUTTON_ELS_EXPORT_FI, OnButtonElsExportFi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CElsPropPageFixation::CElsPropPageFixation() :
	CNSFlexPropertyPage(CElsPropPageFixation::IDD)
{
	AddFlexConstraint(IDC_BUTTON_ELS_EXPORT_FI, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_FRAME_ELS_FIXATION, NSFlexExpandRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_STATIC_ELSPP3_1, NSFlexShiftRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_LIST_ELS_FIXATON_INDICES, NSFlexShiftRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_CHECK_ELS_HALF_ARENA, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_RADIO_ELS_HEAT, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_RADIO_ELS_HEAT2, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_RADIO_ELS_HEAT3, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_EDIT_ELS_N_REINF_0180, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_EDIT_ELS_N_REINF_90270, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_CHECK_ELS_SUPERIMPOSED, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_EDIT_ELS_N_ALL_FILES, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_STATIC_ELSPP3_2, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_STATIC_ELSPP3_3, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_STATIC_ELSPP3_4, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_STATIC_ELSPP3_5, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_COMBO_ELS_DISPLAY_RESOLUTION, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_EDIT_ELS_DISPLAYED_BLOCK, NSFlexShiftRight, NSFlexVerticallyFixed);
	AddFlexConstraint(IDC_SPIN_ELS_DISPLAYED_BLOCK, NSFlexShiftRight, NSFlexVerticallyFixed);

	//{{AFX_DATA_INIT(CElsPropPageFixation)
	m_EDIT_ElsNReinf0180 = 0;
	m_EDIT_ElsNReinf90270 = 0;
	m_EDIT_ElsNAllFiles = 0;
	m_EDIT_ElsDisplayedBlock = _T("");
	m_EDIT_ElsSpinBuddyBlock = 0;
	m_RADIO_ElsSelectReinforcement = -1;
	m_CHECK_ElsSuperimposeHeat = FALSE;
	m_CHECK_ElsMirroredQuadrants = FALSE;
	//}}AFX_DATA_INIT
	
	m_DialogInitialized = 0;
}

CElsPropPageFixation::~CElsPropPageFixation()
{
}

void CElsPropPageFixation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsPropPageFixation)
	DDX_Control(pDX, IDC_COMBO_ELS_DISPLAY_RESOLUTION, m_COMBO_ElsDisplayResolution);
	DDX_Control(pDX, IDC_SPIN_ELS_DISPLAYED_BLOCK, m_SPIN_ElsDisplayedBlock);
	DDX_Control(pDX, IDC_LIST_ELS_FIXATON_INDICES, m_LIST_ElsFixationIndices);
	DDX_Text(pDX, IDC_EDIT_ELS_N_REINF_0180, m_EDIT_ElsNReinf0180);
	DDX_Text(pDX, IDC_EDIT_ELS_N_REINF_90270, m_EDIT_ElsNReinf90270);
	DDX_Text(pDX, IDC_EDIT_ELS_N_ALL_FILES, m_EDIT_ElsNAllFiles);
	DDX_Text(pDX, IDC_EDIT_ELS_DISPLAYED_BLOCK, m_EDIT_ElsDisplayedBlock);
	DDX_Text(pDX, IDC_EDIT_ELS_SPINBUDDY_BLOCK, m_EDIT_ElsSpinBuddyBlock);
	DDX_Radio(pDX, IDC_RADIO_ELS_HEAT, m_RADIO_ElsSelectReinforcement);
	DDX_Check(pDX, IDC_CHECK_ELS_SUPERIMPOSED, m_CHECK_ElsSuperimposeHeat);
	DDX_Check(pDX, IDC_CHECK_ELS_HALF_ARENA, m_CHECK_ElsMirroredQuadrants);
	//}}AFX_DATA_MAP
}


BOOL CElsPropPageFixation::OnInitDialog() 
{
	// TODO: Add extra initialization here
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	CNSFlexPropertyPage::OnInitDialog();

	m_SPIN_ElsDisplayedBlock.SetBuddy(GetDlgItem(IDC_EDIT_ELS_SPINBUDDY_BLOCK));
	m_SPIN_ElsDisplayedBlock.SetRange(0, pDoc->m_nOfBlocks);
	m_SPIN_ElsDisplayedBlock.SetPos(m_EDIT_ElsSpinBuddyBlock);
	
	m_DisplayRes.RemoveAll();
	m_DisplayRes.Add(1.0);
	m_DisplayRes.Add(2.0);
	m_DisplayRes.Add(5.0);
	m_DisplayRes.Add(7.5);
	m_DisplayRes.Add(10.0);
	m_DisplayRes.Add(15.0);
	m_DisplayRes.Add(18.0);
	m_DisplayRes.Add(22.5);
	m_DisplayRes.Add(30.0);
	m_DisplayRes.Add(45.0);

	CString s;
	int i, n;
	double r;

	n = m_DisplayRes.GetSize();
	m_COMBO_ElsDisplayResolution.ResetContent();
	for (i = 0; i < n; i++)
	{
		r = m_DisplayRes.GetAt(i);
		s.Format("%.1f° (%.0f div/quadrant)", r, 90 / r);
		m_COMBO_ElsDisplayResolution.AddString(s);
	}
	m_COMBO_ElsDisplayResolution.SetCurSel(1);
	m_RADIO_ElsSelectReinforcement = 2;
	m_CHECK_ElsSuperimposeHeat = TRUE;
	m_CHECK_ElsMirroredQuadrants = FALSE;

	m_DialogInitialized++;		// prevents calling of OnUpdate() with
								// uninitialized property page data
	CNSFlexPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElsPropPageFixation::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (!m_DialogInitialized) return;	// prevents calling of OnUpdate() with
										// uninitialized property page data

	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	CElsPropSheetViewFrm *pFrmWnd = 
		(CElsPropSheetViewFrm*)GetParentFrame();

	int i, n;
	CString s, name, lastpath;
	CExperiment exp;

	m_BlockDescr.RemoveAll();
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		s.Format("%i/%i: %is %s", i + 1, 
			pDoc->m_nOfBlocks, pDoc->m_BlockDur[i], 
			GetBlockType(pDoc->m_BlockType[i]));
		m_BlockDescr.Add(s);
	}
	if (pDoc->m_nOfBlocks < 1) m_BlockDescr.Add(" ");
	m_EDIT_ElsDisplayedBlock = m_BlockDescr.GetAt(m_EDIT_ElsSpinBuddyBlock);
	
	// Calculate position distribution of all blocks:

	n = m_COMBO_ElsDisplayResolution.GetCurSel();
	m_UnitsPerDiv = MAX_POSRANGE * m_DisplayRes[n] / 360.0;
 	m_nDiv = int(MAX_POSRANGE / m_UnitsPerDiv);

	if (lHint != IDD_PP_ELS_FIXATION)
	{
		CalcRawFreqencies();	// recalculate only when script has been changed
		CalcFixationIndices();
	}
	CalcHistogramValues();
	m_nDisplayedFiles = m_EDIT_ElsNAllFiles;
	switch (m_RADIO_ElsSelectReinforcement)
	{
		case 0:
			m_nDisplayedFiles = m_EDIT_ElsNReinf0180;
			break;
		case 1:
			m_nDisplayedFiles = m_EDIT_ElsNReinf90270;
			break;
	}
	UpdateData(FALSE);
	DrawHistogram();
}

void CElsPropPageFixation::CalcRawFreqencies()
{
	int i, j, k, n, pos;
	int nFiles;
	CString s, name, lastpath;
	CExperiment exp;

	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	CElsPropSheetViewFrm *pFrmWnd = 
		(CElsPropSheetViewFrm*)GetParentFrame();

	ResetPosArray();
	lastpath = "";
	m_EDIT_ElsNReinf0180 = 0;
	m_EDIT_ElsNReinf90270 = 0;
	nFiles = pDoc->m_fileList.GetSize();
	for (i = 0; i < nFiles; i++)
	{
		CWaitCursor wait;
		name = pDoc->m_fileList[i];
		s.Format("Loading experiments: %i%%...", (i * 100) / nFiles);
		pFrmWnd->m_wndStatusBar.SetPaneText(0, s);
		if (exp.FindAndLoadExperiment(&pDoc->m_pathList, &lastpath, &name))
		{
			if (exp.m_iHeat == HEAT_0_180) m_EDIT_ElsNReinf0180++;
			else m_EDIT_ElsNReinf90270++;
			pos = 0;
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				for (k = 0; k < exp.m_BlockLen[j]; k++, pos++)
				{
					n = exp.m_Pos[pos] + 2048;	// translate range (-2048..2047 -> 0..4095)
					// prevent under- and overflow of index n by defect files 
					// (remember to implement a warning!!!!):
					if (n < 0) n = 0;
					if (n > 4095) n = 4095;
					if (exp.m_iHeat == HEAT_0_180) m_PosCount0180[j][n]++;
					else m_PosCount90270[j][n]++;
				}
			}
		}
	}

	for (j = 0; j < exp.m_nOfBlocks; j++)
	{
		// rotate 0-quadrant to the left:
		int r, t;
		t = 1536;
		for (n = 0, r = t; n < 4096; n++, r++)
		{
			if (r == 4096) r = 0;
			m_PosCount[n] = m_PosCount0180[j][r];
		}
		for (n = 0; n < 4096; n++) m_PosCount0180[j][n] = m_PosCount[n];
		for (n = 0, r = t; n < 4096; n++, r++)
		{
			if (r == 4096) r = 0;
			m_PosCount[n] = m_PosCount90270[j][r];
		}
		for (n = 0; n < 4096; n++) m_PosCount90270[j][n] = m_PosCount[n];
	}
	s = " ";
	pFrmWnd->m_wndStatusBar.SetPaneText(0, s);
	m_EDIT_ElsNAllFiles = m_EDIT_ElsNReinf0180 + m_EDIT_ElsNReinf90270;
}

void CElsPropPageFixation::CalcHistogramValues()
{
	int i, j, n, m, nBlocks;

	nBlocks = m_BlockDescr.GetSize();

	for (i = 0; i < nBlocks; i++)
	{
		for (j = 0; j < 360; j++) 
			m_PosCountHg[i][j] = 0;
		for (j = 0; j < 4096; j++)
		{
			n = int(j / m_UnitsPerDiv);
			if (m_CHECK_ElsMirroredQuadrants)
			{
				if (j >= 2048) n = int((j - 2048) / m_UnitsPerDiv);
				else n = int(j / m_UnitsPerDiv);
			}
			if (m_RADIO_ElsSelectReinforcement != 1)
			{
				m_PosCountHg[i][n] += m_PosCount0180[i][j];
			}
			if (m_RADIO_ElsSelectReinforcement != 0)
			{
				if (m_CHECK_ElsSuperimposeHeat)
				{
					if (j < 3072) m = j + 1024;
					else m = j - 3072;
				}
				else m = j;
				m_PosCountHg[i][n] += m_PosCount90270[i][m];
			}
		}
	}
	
}

void CElsPropPageFixation::CalcFixationIndices()
{
	int i, j;
	double hs_x2[MAX_EXP_BLOCKS], hsx[MAX_EXP_BLOCKS], hsx_2[MAX_EXP_BLOCKS];
	double cs_x2[MAX_EXP_BLOCKS], csx[MAX_EXP_BLOCKS], csx_2[MAX_EXP_BLOCKS];
	double x;
	CString s, t;

	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);
	for (j = 0; j < pDoc->m_nOfBlocks; j++)
	{
		pDoc->m_FIh_Mean[j] = 0.0;
		pDoc->m_FIh_SEM[j] = 0.0;
		pDoc->m_FIc_Mean[j] = 0.0;
		pDoc->m_FIc_SEM[j] = 0.0;
		hs_x2[j] = 0.0;	cs_x2[j] = 0.0;
		hsx[j] = 0.0; csx[j] = 0.0;
		hsx_2[j] = 0.0; csx_2[j] = 0.0;
	}
	int nIncl = 0;
	for (i = 0; i < pDoc->m_nExpOk; i++)
	{
		CWaitCursor wait;
		if (pDoc->m_PIArray[i].iHeat == HEAT_0_180)
		{
			if (m_RADIO_ElsSelectReinforcement == 1) continue;
			// m_EDIT_ElsNReinf0180++;
		}
		else
		{
			if (m_RADIO_ElsSelectReinforcement == 0) continue;
			// m_EDIT_ElsNReinf90270++;
		}

		nIncl++;
		for (j = 0; j < pDoc->m_nOfBlocks; j++)
		{
			// hot sectors:
			x = pDoc->m_PIArray[i].FIh[j];
			pDoc->m_FIh_Mean[j] += x;
			hs_x2[j] += x * x;
			hsx[j] += x;
			hsx_2[j] = hsx[j] * hsx[j];
			if (nIncl < 2) continue;
			pDoc->m_FIh_SEM[j] = hs_x2[j] - (hsx_2[j] / (double)nIncl);
			pDoc->m_FIh_SEM[j] /= (double)(nIncl * (nIncl - 1));
			pDoc->m_FIh_SEM[j] = sqrt(pDoc->m_FIh_SEM[j]);
		}
		for (j = 0; j < pDoc->m_nOfBlocks; j++)
		{
			// cold sectors
			x = pDoc->m_PIArray[i].FIc[j];
			pDoc->m_FIc_Mean[j] += x;
			cs_x2[j] += x * x;
			csx[j] += x;
			csx_2[j] = csx[j] * csx[j];
			if (nIncl < 2) continue;
			pDoc->m_FIc_SEM[j] = cs_x2[j] - (csx_2[j] / (double)nIncl);
			pDoc->m_FIc_SEM[j] /= (double)(nIncl * (nIncl - 1));
			pDoc->m_FIc_SEM[j] = sqrt(pDoc->m_FIc_SEM[j]);
		}
	}
	m_LIST_ElsFixationIndices.ResetContent();
	for (j = 0; j < pDoc->m_nOfBlocks; j++)
	{
		if (nIncl > 0)
		{
			pDoc->m_FIh_Mean[j] /= (double)nIncl;
		}
		switch (pDoc->m_BlockType[j])
		{
			case EXPTYPE_TEST: t = "test"; break;
			case EXPTYPE_TRAIN: t = "training"; break;
			case EXPTYPE_REPL: t = "replay"; break;
			default: t = "?"; break;
		}
		s.Format("FIh%0i: % .3f +/- %.3f (%s)",
			j + 1, pDoc->m_FIh_Mean[j],	pDoc->m_FIh_SEM[j],	t);
		m_LIST_ElsFixationIndices.AddString(s);
	}	
	for (j = 0; j < pDoc->m_nOfBlocks; j++)
	{
		if (nIncl > 0)
		{
			pDoc->m_FIc_Mean[j] /= (double)nIncl;
		}
		switch (pDoc->m_BlockType[j])
		{
			case EXPTYPE_TEST: t = "test"; break;
			case EXPTYPE_TRAIN: t = "training"; break;
			case EXPTYPE_REPL: t = "replay"; break;
			default: t = "?"; break;
		}
		s.Format("FIc%0i: % .3f +/- %.3f (%s)",
			j + 1, pDoc->m_FIc_Mean[j],	pDoc->m_FIc_SEM[j], t);
		m_LIST_ElsFixationIndices.AddString(s);
	}	
	m_EDIT_ElsNAllFiles = nIncl;
	UpdateData(FALSE);
}

void CElsPropPageFixation::DrawHistogram()
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	if (pDoc == NULL) return;
	ASSERT(pDoc);

	CWnd *pWnd = GetDlgItem(IDC_FRAME_ELS_FIXATION);
	CDC *pDC = pWnd->GetDC();

	int i, n, ddeg, deg0, deg90, xaxzero, x, y, dxax, dyax, ymax;
	double h, basicUnit, rely, ysmin, ysmax, dys, dy;
	CString s, sc0, sc90;

	// colors:
	COLORREF dgrbkColor = RGB(255, 255, 255);	// diagram background
	COLORREF heatColor = RGB(196, 0, 0);		// training index bar
	COLORREF bkColor = RGB(192, 192, 192);		// window background
	COLORREF scaleColor = RGB(0, 0, 0);			// scales
	COLORREF histoColor = RGB(0, 0, 192);		// histogram bar
	
	// pens and brushes:
	CPen *pOldPen;
	CPen scalePen, histoPen, grayPen;
	scalePen.CreatePen(PS_SOLID, 1, scaleColor);
	histoPen.CreatePen(PS_SOLID, 1, histoColor);
	grayPen.CreatePen(PS_SOLID, 1, bkColor);
	CBrush *pOldBrush;
	CBrush dgrbkBrush, bkBrush, barBrush, heatBrush, scaleBrush;
	dgrbkBrush.CreateSolidBrush(dgrbkColor);
	bkBrush.CreateSolidBrush(bkColor);
	scaleBrush.CreateSolidBrush(scaleColor);
	barBrush.CreateSolidBrush(histoColor);
	heatBrush.CreateHatchBrush(HS_DIAGCROSS, bkColor);

	// fonts:
	CFont *pOldFont;
	CFont scaleFont;
	scaleFont.CreatePointFont(80, "MS Sans Serif", pDC);
	pOldFont = pDC->SelectObject(&scaleFont);
	CSize textsize;
	textsize = pDC->GetTextExtent("-1.0");

	CRect frame, pane;
	pWnd->GetClientRect(frame);
	frame.TopLeft().Offset(1, 1);
	frame.BottomRight().Offset(-1, -1);
	pane = frame;
	pane.BottomRight().Offset(-1, -1);

	// diagram background 
	pOldPen = pDC->SelectObject(&scalePen);
	pOldBrush = pDC->SelectObject(&dgrbkBrush);
	pDC->FillRect(frame, &dgrbkBrush);
	pDC->SetBkColor(bkColor);

	pDC->SetTextAlign(TA_RIGHT | TA_BOTTOM);
	dxax = pane.right - pane.left;
	dyax = pane.bottom - pane.top;
	xaxzero = pane.bottom;
	ymax = pane.bottom - xaxzero;

	n = pDoc->m_BlockLen[m_EDIT_ElsSpinBuddyBlock];
	basicUnit = n / 360.0;
	if (basicUnit < 1) basicUnit = 1;

	// y-axis:
	ysmax = 1.0;
	ysmin = 0.0;
	dys = ysmax - ysmin;
	dy = dys / 10;
	for (rely = ysmin, i = 0; rely <= ysmax;  rely += dy, i++)
	{
		y = xaxzero - (int)(dyax * dy * i / dys);
		pDC->MoveTo(frame.left - 2, y);
		pDC->LineTo(frame.left - 8, y);
		s.Format("%.1f", rely);
//		pDC->TextOut(frame.left - 10, y + textsize.cy / 2, s);
	}
	

	// x-axis:
	CRect r;
	r.top = frame.bottom + 7;
	r.bottom = frame.bottom + 3 * textsize.cy;
	r.left = frame.left - textsize.cx;
	r.right = frame.right + textsize.cx;
	pDC->FillRect(r, &bkBrush);
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	ddeg = 45;
	deg0 = 315;
	deg90 = 45;
	for (i = 0; i < 9; i++, deg0 += ddeg, deg90 += ddeg)
	{
		pDC->SelectObject(&scalePen);
		x = pane.left + dxax * i / 8;
		pDC->MoveTo(x, xaxzero + 2);
		pDC->LineTo(x, xaxzero + 8);
//		pDC->MoveTo(x, xaxzero + 10);
		if (deg0 >= 360) deg0 = 0;
		sc0.Format("%i°", deg0);
		if (deg90 >= 360) deg90 = 0;
		sc90.Format("%i°", deg90);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(dgrbkColor);
		r.top = pane.top;
		r.bottom = pane.bottom;
		if (m_RADIO_ElsSelectReinforcement == 0)
		{
			pDC->TextOut(x, frame.bottom + 10, sc0);
			r.left = pane.left;
			r.right = pane.left + dxax / 4;
			pDC->FillRect(r, &heatBrush);
			r.left = pane.left + dxax / 2 + 1;
			r.right = pane.right - dxax / 4 - 1;
			pDC->FillRect(r, &heatBrush);
		}
		else
		if (m_RADIO_ElsSelectReinforcement == 1)
		{
			if (!m_CHECK_ElsSuperimposeHeat)
			{
				pDC->TextOut(x, frame.bottom + 10, sc0);
				r.left = pane.left + dxax / 4 + 1;
				r.right = pane.left + dxax / 2;
				pDC->FillRect(r, &heatBrush);
				r.left = pane.right - dxax / 4;
				r.right = pane.right;
				pDC->FillRect(r, &heatBrush);
			}
			else 
			{
				pDC->TextOut(x, frame.bottom + 10, sc90);
				r.left = pane.left;
				r.right = pane.left + dxax / 4;
				pDC->FillRect(r, &heatBrush);
				r.left = pane.left + dxax / 2 + 1;
				r.right = pane.right - dxax / 4 - 1;
				pDC->FillRect(r, &heatBrush);
			}
		}
		else
		if (m_RADIO_ElsSelectReinforcement == 2)
		{
			pDC->TextOut(x, frame.bottom + 10, sc0);
			if (m_CHECK_ElsSuperimposeHeat)
			{
				pDC->TextOut(x, frame.bottom + 24, sc90);
				r.left = pane.left;
				r.right = pane.left + dxax / 4;
				pDC->FillRect(r, &heatBrush);
				r.left = pane.left + dxax / 2 + 1;
				r.right = pane.right - dxax / 4 - 1;
				pDC->FillRect(r, &heatBrush);
			}
		}


		if ((i % 2) == 0)
		{
			pDC->SelectObject(&grayPen);
			pDC->MoveTo(x, xaxzero);
			pDC->LineTo(x, ymax);
		}
	}
	
	// drawing histogram for currently selected block:
	pDC->SelectObject(&histoPen);
	UINT *p = m_PosCountHg[m_EDIT_ElsSpinBuddyBlock];
	h = 1.0;
	if (m_CHECK_ElsMirroredQuadrants) h = 0.5;
	double fnorm = h * m_nDiv / n / m_nDisplayedFiles / basicUnit;
	CRect bar;
	for (i = 0; i < (int)m_nDiv; i++)
	{
		y = int(p[i] * fnorm * dyax);
		if (y > dyax) y = dyax;
		x = int(i * (dxax + 1) / (double)m_nDiv) + pane.left;
		bar.top = xaxzero - y;
		bar.bottom = xaxzero + 1;
		bar.left = x;
		bar.right = x + (dxax + 1) / m_nDiv + 1;
		pDC->FillRect(bar , &barBrush);
		pDC->MoveTo(x, xaxzero);
		pDC->LineTo(x, xaxzero - y);
	}
	y = int(dyax / basicUnit);
	pDC->SelectObject(&scalePen);
	pDC->MoveTo(pane.left, xaxzero - y);
	pDC->LineTo(pane.right, xaxzero - y);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldFont);
	pWnd->ReleaseDC(pDC);
}

void CElsPropPageFixation::ResetPosArray()
{
	int i, j;
	for (i = 0; i < MAX_EXP_BLOCKS; i++)
	{
		for (j = 0; j < 4096; j++)
		{
			m_PosCount0180[i][j] = 0;
			m_PosCount90270[i][j] = 0;
			if (j < 360) m_PosCountHg[i][j] = 0;
 		}
	}
}

void CElsPropPageFixation::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	DrawHistogram();
	// Do not call CNSFlexPropertyPage::OnPaint() for painting messages
}

void CElsPropPageFixation::UpdateDocumentData()
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);
}

void CElsPropPageFixation::OnRadioElsSelectHeat0180() 
{
	UpdateData();
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnRadioElsSelectHeat90270() 
{
	UpdateData();
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnRadioElsSelectHeatAll() 
{
	UpdateData();
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnCheckElsHalfArena() 
{
	UpdateData();
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnCheckElsSuperimposed() 
{
	UpdateData();
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnChangeEditElsSpinbuddyBlock() 
{
	// TODO: Add your control notification handler code here
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	if (pDoc == NULL) return;
	ASSERT(pDoc);
	UpdateData();
	if (m_EDIT_ElsSpinBuddyBlock >= pDoc->m_nOfBlocks) 
		m_EDIT_ElsSpinBuddyBlock = pDoc->m_nOfBlocks - 1;
	if (m_EDIT_ElsSpinBuddyBlock < 0) m_EDIT_ElsSpinBuddyBlock = 0;
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnSelchangeComboElsDisplayResolution() 
{
	// TODO: Add your control notification handler code here
	OnUpdate(NULL, IDD_PP_ELS_FIXATION, NULL);
}

void CElsPropPageFixation::OnButtonElsExportFi() 
{
	// TODO: Add your control notification handler code here
	
	CElsExportFI dlg;
	dlg.m_pDoc = GetDocument();
	
	dlg.DoModal();
}
