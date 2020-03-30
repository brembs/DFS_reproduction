// ElsPropPageExperimentList.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "ElsPropPageExperimentList.h"
#include "ElsPropSheetViewFrm.h"
#include "ElsDoc.h"
#include "DfsExperiment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageExperimentList property page

IMPLEMENT_DYNCREATE(CElsPropPageExperimentList, CNSFlexPropertyPage)

BEGIN_MESSAGE_MAP(CElsPropPageExperimentList, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CElsPropPageExperimentList)
	ON_EN_CHANGE(IDC_EDIT_ELS_EXPERIMENTSCRIPT, OnChangeEditElsExperimentScript)
	ON_BN_CLICKED(ID_BUTTON_COMPILE_SCRIPT, OnButtonCompileScript)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CElsPropPageExperimentList::CElsPropPageExperimentList() :
	CNSFlexPropertyPage(CElsPropPageExperimentList::IDD)
{
	AddFlexConstraint(IDC_EDIT_ELS_EXPERIMENTSCRIPT, NSFlexExpandRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_LIST_ELS_EXPERIMENTNAMES, NSFlexShiftRight, NSFlexExpandDown);
	AddFlexConstraint(ID_BUTTON_COMPILE_SCRIPT, NSFlexHorizontallyFixed, NSFlexShiftDown);
	AddFlexConstraint(IDC_EDIT_ELS_N_OF_FILES, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_EDIT_ELS_N_0_180, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_EDIT_ELS_N_90_270, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_EDIT_ELS_FILES_OK, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_MESSAGE, NSFlexHorizontallyFixed, NSFlexShiftDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_1, NSFlexShiftRight, NSFlexExpandDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_2, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_3, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_4, NSFlexShiftRight, NSFlexShiftDown);
	AddFlexConstraint(IDC_STATIC_ELSPP1_5, NSFlexShiftRight, NSFlexShiftDown);
	//{{AFX_DATA_INIT(CElsPropPageExperimentList)
	m_EDIT_ElsNOfFiles = 0;
	m_EDIT_ElsN0180 = 0;
	m_EDIT_ElsN90270 = 0;
	m_EDIT_ElsFilesOk = 0;
	m_STATIC_ElsPP1Message = _T("");
	//}}AFX_DATA_INIT
}

CElsPropPageExperimentList::~CElsPropPageExperimentList()
{
//	CElsDoc* pDoc = (CElsDoc*)GetDocument();
//	ASSERT(pDoc);
//	if (pDoc->m_PIArray != NULL) delete pDoc->m_PIArray;
}

void CElsPropPageExperimentList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsPropPageExperimentList)
	DDX_Control(pDX, IDC_EDIT_ELS_EXPERIMENTSCRIPT, m_EDIT_ElsExperimentScript);
	DDX_Control(pDX, IDC_LIST_ELS_EXPERIMENTNAMES, m_LIST_ElsExperimentNames);
	DDX_Text(pDX, IDC_EDIT_ELS_N_OF_FILES, m_EDIT_ElsNOfFiles);
	DDX_Text(pDX, IDC_EDIT_ELS_N_0_180, m_EDIT_ElsN0180);
	DDX_Text(pDX, IDC_EDIT_ELS_N_90_270, m_EDIT_ElsN90270);
	DDX_Text(pDX, IDC_EDIT_ELS_FILES_OK, m_EDIT_ElsFilesOk);
	DDX_Text(pDX, IDC_STATIC_ELSPP1_MESSAGE, m_STATIC_ElsPP1Message);
	//}}AFX_DATA_MAP
}

void CElsPropPageExperimentList::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{

	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);


	CElsPropSheetViewFrm *pFrmWnd = 
		(CElsPropSheetViewFrm*)GetParentFrame();

	// load script into edit control of dialog:
	m_EDIT_ElsExperimentScript.SetWindowText(pDoc->m_Script);

	// parse script and get filenames and pathnames:

	pDoc->m_fileList.RemoveAll();
	pDoc->m_pathList.RemoveAll();
	pFrmWnd->m_wndStatusBar.SetWindowText("Parsing script...");
	pFrmWnd->m_wndStatusBar.UpdateWindow();
	pDoc->ParseExpScript(&m_EDIT_ElsExperimentScript);

	unsigned int i;
	int j;
	CString s, tag;
	CString lastpath, name;
	CExperiment exp;
	m_LIST_ElsExperimentNames.ResetContent();
	m_EDIT_ElsNOfFiles = pDoc->m_fileList.GetSize();
	
	// initialize memory for indices:
	pDoc->m_nExpOk = 0;
	if (pDoc->m_PIArray != NULL) 
	{
		delete pDoc->m_PIArray;
		pDoc->m_PIArray = NULL;
	}
	pDoc->m_PIArray = new PI_ARRAY[m_EDIT_ElsNOfFiles];
	if (pDoc->m_PIArray == NULL)
	{
		s.Format("Not enough memory to load all %i experiments\r\nof script %s!",
			m_EDIT_ElsNOfFiles, pDoc->GetTitle());
		AfxMessageBox(s, MB_OK);
		pFrmWnd->m_wndStatusBar.SetWindowText(s);
		UpdateData(FALSE);
		return;
	}

	// load files:
	m_EDIT_ElsFilesOk = 0;
	m_EDIT_ElsN0180 = 0;
	m_EDIT_ElsN90270 = 0;
	lastpath = "";
	for (i = 0; i < m_EDIT_ElsNOfFiles; i++)
	{
		CWaitCursor wait;
		name = pDoc->m_fileList[i];
		if (exp.FindAndLoadExperiment(&pDoc->m_pathList, &lastpath, &name))
		{
			m_EDIT_ElsFilesOk++;
			if (exp.m_iHeat == HEAT_0_180) m_EDIT_ElsN0180++;
			else m_EDIT_ElsN90270++;
			tag = "o.k.";
			if (m_EDIT_ElsFilesOk == 1)
			{
				pDoc->m_ExpDur = exp.m_ExpDur;
				pDoc->m_nOfBlocks = exp.m_nOfBlocks;
				int j;
				for (j = 0; j < pDoc->m_nOfBlocks; j++)
				{
					pDoc->m_BlockDur[j] = exp.m_BlockDur[j];
					pDoc->m_BlockLen[j] = exp.m_BlockLen[j];
					pDoc->m_BlockType[j] = exp.m_BlockType[j];
				}
			}
		}
		else
		{
			tag = "error!";
		}
		s.Format("%s - %s", pDoc->m_fileList[i], tag);
		m_LIST_ElsExperimentNames.AddString(s);
		s.Format("Loading experiments: %i%%...", (i * 100) / m_EDIT_ElsNOfFiles);
		pFrmWnd->m_wndStatusBar.SetWindowText(s);
		pFrmWnd->m_wndStatusBar.UpdateWindow();
		// Calculate all indices:
		exp.CalcPerfIndices(FALSE, FALSE);
 		pDoc->m_PIArray[i].iHeat = exp.m_iHeat;
		pDoc->m_PIArray[i].PIPreference = exp.m_PIPreference;
		exp.CalcFixationIndices();
		exp.CalcTorqueIndices();
		pDoc->m_PIArray[i].TIPreference = exp.m_TIPreference;
		for (j = 0; j < exp.m_nOfBlocks; j++)
		{
			pDoc->m_PIArray[i].PI[j] = exp.m_PI[j];
			pDoc->m_PIArray[i].FIh[j] = exp.m_FIh[j];
			pDoc->m_PIArray[i].FIc[j] = exp.m_FIc[j];
			pDoc->m_PIArray[i].TI[j] = exp.m_TI[j];
		}
	}

	pDoc->m_nExpOk = m_EDIT_ElsFilesOk;

	if (m_EDIT_ElsFilesOk == 0)
	{
		s = "Warning: current script contains no valid experiment names!";
	}
	else s = " ";	// do not set s = "", otherwise there will be memory leaks (why?)
	pFrmWnd->m_wndStatusBar.SetPaneText(0, s);
	UpdateData(FALSE);
	pDoc->m_ScriptIsCompiled = TRUE;
  }

void CElsPropPageExperimentList::UpdateDocumentData()
{
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	m_EDIT_ElsExperimentScript.GetWindowText(pDoc->m_Script);
}

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageExperimentList message handlers

void CElsPropPageExperimentList::OnChangeEditElsExperimentScript() 
{
	// TODO: Add your control notification handler code here
	CElsDoc*  pDoc = (CElsDoc*)GetDocument();
	UpdateData();
	UpdateDocumentData();
	pDoc->SetModifiedFlag();
	pDoc->m_ScriptIsCompiled = FALSE;
	pDoc->UpdateAllViews(GetView());

	CElsPropSheetViewFrm *pFrmWnd = 
		(CElsPropSheetViewFrm*)GetParentFrame();
	CString s = "Warning: script has been modified but not compiled!";
	pFrmWnd->m_wndStatusBar.SetPaneText(0, s);
}

BOOL CElsPropPageExperimentList::OnInitDialog() 
{
	CNSFlexPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	CWnd *pWnd = GetDlgItem(IDC_EDIT_ELS_EXPERIMENTSCRIPT);
	m_scriptFont.CreatePointFont(90, "Courier New");
	pWnd->SetFont(&m_scriptFont);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElsPropPageExperimentList::OnButtonCompileScript() 
{
	// TODO: Add your control notification handler code here
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);
//	OnUpdate(NULL, 0, NULL);	
	pDoc->UpdateAllViews(NULL, 0, NULL);
}

BOOL CElsPropPageExperimentList::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CElsDoc* pDoc = (CElsDoc*)GetDocument();
	ASSERT(pDoc);

	// Prevent activation of other pages when script contains no valid files
	if (m_EDIT_ElsFilesOk < 1) 
	{
		CNSFlexPropertyPage::OnKillActive();
		return FALSE;
	}


	CString s = "Warning: script has been modified but not compiled!\r\n";
	s += "Changes made will not be reflected by any other page,\r\n";
	s += "compile script now?";
	
	if (!pDoc->m_ScriptIsCompiled)
	{
		switch (AfxMessageBox(s, MB_YESNOCANCEL))
		{
			case IDYES:
				OnButtonCompileScript();
				break;
			case IDNO:
				break;
			case IDCANCEL:
				return FALSE;
				break;
		}
	}

	return CNSFlexPropertyPage::OnKillActive();
}
