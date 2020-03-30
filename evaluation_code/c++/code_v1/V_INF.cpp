// V_INF.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "D_INF.h"
#include "V_INF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewINF

IMPLEMENT_DYNCREATE(CViewINF, CFormView)

CViewINF::CViewINF()
	: CFormView(CViewINF::IDD)
{
	//{{AFX_DATA_INIT(CViewINF)
	m_ED_nOfFiles = 0;
	m_ED_Fly = _T("");
	m_ED_HeatedSectors = _T("");
	m_ED_Remarks = _T("");
	m_ED_Time = _T("");
	m_ED_nOfRecords = 0;
	m_ED_nOfData = 0;
	m_ED_ExperimentName = _T("");
	m_ED_Date = _T("");
	m_ED_nOfPeriods = 0;
	m_RADIO_ArenaPosRange = -1;
	//}}AFX_DATA_INIT
}

CViewINF::~CViewINF()
{
}

void CViewINF::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewINF)
	DDX_Control(pDX, IDC_DETECTED_1800, m_STATIC_Detected1800);
	DDX_Control(pDX, IDC_DETECTED_2048, m_STATIC_Detected2048);
	DDX_Text(pDX, IDC_INF_NOFFILES, m_ED_nOfFiles);
	DDV_MinMaxUInt(pDX, m_ED_nOfFiles, 0, 5);
	DDX_Text(pDX, IDC_INF_FLY, m_ED_Fly);
	DDX_Text(pDX, IDC_INF_HEATEDPATTERN, m_ED_HeatedSectors);
	DDX_Text(pDX, IDC_INF_REMARKS, m_ED_Remarks);
	DDX_Text(pDX, IDC_INF_TIME, m_ED_Time);
	DDX_Text(pDX, IDC_INF_NOFRECORDS, m_ED_nOfRecords);
	DDX_Text(pDX, IDC_INF_NOFDATA, m_ED_nOfData);
	DDX_Text(pDX, IDC_INF_EXPERIMENT_NAME, m_ED_ExperimentName);
	DDX_Text(pDX, IDC_INF_DATE, m_ED_Date);
	DDX_Text(pDX, IDC_INF_NOFPERIODS, m_ED_nOfPeriods);
	DDX_Radio(pDX, IDC_POS_RANGE, m_RADIO_ArenaPosRange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewINF, CFormView)
	//{{AFX_MSG_MAP(CViewINF)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_POS_RANGE, OnPosRange2048)
	ON_BN_CLICKED(IDC_POS_RANGE_2, OnPosRange1800)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewINF diagnostics

#ifdef _DEBUG
void CViewINF::AssertValid() const
{
	CFormView::AssertValid();
}

void CViewINF::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewINF message handlers

void CViewINF::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CDocINF *pDoc = (CDocINF *)GetDocument();
	m_ED_ExperimentName = pDoc->m_Experiment.m_ExpName;
	m_ED_HeatedSectors = pDoc->m_Experiment.m_sHeat;
	m_ED_Fly = pDoc->m_Experiment.m_Fly;
	if (m_ED_Fly == "") m_ED_Fly = "no entry";
	m_ED_Remarks = pDoc->m_Experiment.m_Remarks;
	if (m_ED_Remarks == "") m_ED_Remarks = "no entry";
	
	m_ED_Date = pDoc->m_Experiment.m_Date;
	m_ED_Time = pDoc->m_Experiment.m_Time;

	m_ED_nOfFiles = pDoc->m_Experiment.m_nOfFiles;
	m_ED_nOfData = pDoc->m_Experiment.m_nOfData;
	m_ED_nOfRecords = pDoc->m_Experiment.m_nOfAllRecords;
	m_ED_nOfPeriods = pDoc->m_Experiment.m_nOfBlocks;

	char *detect = "<- detected";
	if (pDoc->m_Experiment.m_ArenaType == ARENA_2048) 
	{
		m_RADIO_ArenaPosRange = 0;
		m_STATIC_Detected1800.SetWindowText("");
		m_STATIC_Detected2048.SetWindowText(detect);
	}
	else  
	{
		m_RADIO_ArenaPosRange = 1;
		m_STATIC_Detected1800.SetWindowText(detect);
		m_STATIC_Detected2048.SetWindowText("");
	}

	UpdateData(FALSE);
	ResizeParentToFit(FALSE);
}

void CViewINF::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
}

int CViewINF::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CViewINF::OnPosRange2048()
{
	CDocINF *pDoc = (CDocINF *)GetDocument();
	UpdateData();
	if (m_RADIO_ArenaPosRange == 0) pDoc->m_Experiment.m_ArenaType = ARENA_2048;
	else  pDoc->m_Experiment.m_ArenaType = ARENA_1800;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(NULL);
}

void CViewINF::OnPosRange1800()
{
	CDocINF *pDoc = (CDocINF *)GetDocument();
	UpdateData();
	if (m_RADIO_ArenaPosRange == 0) pDoc->m_Experiment.m_ArenaType = ARENA_2048;
	else  pDoc->m_Experiment.m_ArenaType = ARENA_1800;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(NULL);
}

