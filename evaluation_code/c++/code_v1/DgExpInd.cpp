// DgExpInd.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "D_ELS.h"
#include "V_ELS.h"
#include "DgExpInd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExportIndices dialog


CDlgExportIndices::CDlgExportIndices(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExportIndices::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExportIndices)
	m_CHECK_WeightAreaTanh = FALSE;
	m_RADIO_ExportFormat = -1;
	m_ED_ExportFilePath = _T("");
	m_CHECK_ExportPerformance = FALSE;
	m_CHECK_ExportDwellings = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgExportIndices::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExportIndices)
	DDX_Control(pDX, IDC_MESSAGE, m_STATIC_Message);
	DDX_Check(pDX, IDC_WEIGHT_AREATANH, m_CHECK_WeightAreaTanh);
	DDX_Radio(pDX, IDC_EXPORT_FORMAT, m_RADIO_ExportFormat);
	DDX_Text(pDX, IDC_EXPORT_FILE_PATH, m_ED_ExportFilePath);
	DDX_Check(pDX, IDC_EXPORT_PERFORMANCE, m_CHECK_ExportPerformance);
	DDX_Check(pDX, IDC_EXPORT_DWELLINGS, m_CHECK_ExportDwellings);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExportIndices, CDialog)
	//{{AFX_MSG_MAP(CDlgExportIndices)
	ON_BN_CLICKED(IDC_START_EXPORT, OnStartExport)
	ON_BN_CLICKED(IDC_BTN_EXPORT_DESTINATION, OnBtnExportDestination)
	ON_BN_CLICKED(IDC_WEIGHT_AREATANH, OnWeightAreaTanh)
	ON_BN_CLICKED(IDC_EXPORT_DWELLINGS, OnExportDwellings)
	ON_BN_CLICKED(IDC_EXPORT_PERFORMANCE, OnExportPerformance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExportIndices message handlers

BOOL CDlgExportIndices::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CDocELS *pDoc = (CDocELS *)m_pDoc;

	m_RADIO_ExportFormat = 0;	// standardmaessig ASCII Export 
	m_CHECK_ExportPerformance = TRUE;
	m_CHECK_ExportDwellings = FALSE;

	char fname[_MAX_FNAME];

	m_ED_ExportFilePath = m_pDoc->GetPathName();
	_splitpath(m_ED_ExportFilePath, NULL, NULL, fname, NULL);
	m_ED_ExportFilePath = fname;
	if (m_ED_ExportFilePath == "") m_ED_ExportFilePath = "noname";
	m_ED_ExportFilePath += ".asc";

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgExportIndices::OnStartExport() 
{
	if (m_pEd == NULL) return;
	
	CDocELS *pDoc = (CDocELS *)m_pDoc;

	CExperiment exp;
	int i, j, k, h, N, nFiles, nPaths;
	CString s, s1, lastPath;
	CFile exportFile;
	CFileException e;

	UpdateData();
	if (exportFile.Open(m_ED_ExportFilePath, CFile::modeRead, &e))
	{
		exportFile.Close();
		s = "File " + m_ED_ExportFilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES)	return;
	}
	if (!exportFile.Open(m_ED_ExportFilePath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		s = "Unable to write indices\n to file " + m_ED_ExportFilePath + "!";
		AfxMessageBox(s);
		return;
	}
	UpdateData();
	CWaitCursor wait;
	pDoc->ParseExpScript(m_pEd);
	nFiles = pDoc->m_fileList.GetSize();
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
	for (i = 0, N = 0; i < nFiles; i++)
	{
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

		if (i == 0)	// Kopf der Exportdatei schreiben
		{
			s = "FILE,DATE,HEAT";
			if (m_CHECK_ExportPerformance)
			{
				for (j = 0; j < exp.m_nOfBlocks; j++)
				{
					s1.Format("%i", j + 1);
					s += ",PI" + s1;
				}
			}
			if (m_CHECK_ExportDwellings)
			{
			}
			s += "\r\n";
			exportFile.Write(s, s.GetLength() * sizeof(char));
		}
	
		s.Format("Writing indices: %i%%, Experiment: %s...", 
			(i * 100) / nFiles, exp.m_ExpName);
		m_STATIC_Message.SetWindowText(s);
		UpdateData(FALSE);
		if (exp.IsValid()) 
		{
			N++;	// Anzahl der fehlerfrei eingelesenen Experimente
			// Indices der einzelnen Experimente schreiben
			exp.CalcPerfIndices(FALSE, m_CHECK_WeightAreaTanh);
			if (exp.m_iHeat == HEAT_0_180) h = 1;
			else h = -1;
			s.Format("%s, %s, %i", exp.m_ExpName, exp.m_Date, h);
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				s1.Format(",%.5f", exp.m_PerfIndex[j]);
				s += s1;
			}
			s += "\r\n";
			exportFile.Write(s, s.GetLength() * sizeof(char));
			s.Format("Writing indices: %i%%, Experiment: %s. O.k.", 
				(i * 100) / nFiles, exp.m_ExpName);
			m_STATIC_Message.SetWindowText(s);
			UpdateData(FALSE);
		}
		else
		{
			s.Format("%s, error reading file\r\n", exp.m_ExpName);
			exportFile.Write(s, s.GetLength() * sizeof(char));
			s.Format("Writing indices: %i%%, Experiment: %s. Error!", 
				(i * 100) / nFiles, exp.m_ExpName);
			m_STATIC_Message.SetWindowText(s);
			UpdateData(FALSE);
		}
	}
	exportFile.Close();
	s.Format("Indices of %i out of %i experiments\r\nsuccessfully exported. Done.",
		N, nFiles);
	m_STATIC_Message.SetWindowText(s);
	UpdateData(FALSE);
}

void CDlgExportIndices::OnBtnExportDestination() 
{
	CString ext, filter, title;
	DWORD flags;

	ext = "*.asc";
	filter = "ASCII file (*.asc)|*.asc|All files (*.*)|*.*||";
	title = "Choose ASCII file to export to";
	flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	CFileDialog fDlg(FALSE, ext, NULL, flags, filter);
	fDlg.m_ofn.lpstrTitle = title;
	
	if (fDlg.DoModal() == IDOK)
	{
		m_ED_ExportFilePath = fDlg.GetPathName();
	}
	UpdateData(FALSE);
}

void CDlgExportIndices::OnWeightAreaTanh() 
{
	UpdateData();
	UpdateData(FALSE);
}

void CDlgExportIndices::OnExportDwellings() 
{
	UpdateData();
	UpdateData(FALSE);
}

void CDlgExportIndices::OnExportPerformance() 
{
	UpdateData();
	UpdateData(FALSE);
}
