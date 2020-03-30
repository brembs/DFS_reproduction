// ElsExportPI.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "ElsExportPI.h"
#include "ElsDoc.h"
#include "stadev/32BIT/stadev32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElsExportPI dialog


CElsExportPI::CElsExportPI(CWnd* pParent /*=NULL*/)
	: CDialog(CElsExportPI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElsExportPI)
	m_EDIT_FilePath = _T("");
	m_RADIO_ExportFormat = -1;
	m_STATIC_ExportMessage = _T("");
	//}}AFX_DATA_INIT
}


void CElsExportPI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsExportPI)
	DDX_Control(pDX, IDC_START_EXPORT, m_BUTTON_Export);
	DDX_Control(pDX, IDC_BUTTON_EXPORT_DESTINATION, m_BUTTON_ExportPI);
	DDX_Text(pDX, IDC_EXPORT_FILE_PATH, m_EDIT_FilePath);
	DDX_Radio(pDX, IDC_EXPORT_FORMAT, m_RADIO_ExportFormat);
	DDX_Text(pDX, IDC_EXPORT_MESSAGE, m_STATIC_ExportMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElsExportPI, CDialog)
	//{{AFX_MSG_MAP(CElsExportPI)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_DESTINATION, OnButtonExportDestination)
	ON_BN_CLICKED(IDC_START_EXPORT, OnStartExport)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT, OnExportFormat)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT_2, OnExportFormat2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElsExportPI message handlers

BOOL CElsExportPI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	m_EDIT_FilePath = m_pDoc->GetTitle();
	
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s", m_fname);

	m_RADIO_ExportFormat = 0;	// standardmaessig ASCII Export 
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElsExportPI::OnButtonExportDestination() 
{
	CString defext, filter, title;
	DWORD flags;
	int index;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	filter = "ASCII file (*.txt)|*.txt|Statistica file (*.sta)|*.sta||";
	flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	title = "Choose export file name";
	switch (m_RADIO_ExportFormat)
	{
		default:
		case 0: 
			defext = ".txt";		// ASCII Format
			index = 1;
			break;
		case 1: 
			defext = ".sta";		// Statistica Format
			index = 2;
			break;
	}
	m_EDIT_FilePath = m_fname;
	UpdateData(FALSE);
	CFileDialog fDlg(FALSE, defext, m_EDIT_FilePath, flags, filter);
	fDlg.m_ofn.nFilterIndex = index;
	fDlg.m_ofn.lpstrTitle = title;
	if (fDlg.DoModal() == IDOK)
	{
		m_EDIT_FilePath = fDlg.GetPathName();
		switch (fDlg.m_ofn.nFilterIndex)
		{
			case 1: 
				m_RADIO_ExportFormat = 0;
				break;
			case 2: 
				m_RADIO_ExportFormat = 1;
				break;
		}
	}
	UpdateData(FALSE);
}

void CElsExportPI::OnStartExport() 
{
	CFile fExport;
	CFileException e;
	CString s;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	
	s = m_ext;
	
	switch (m_RADIO_ExportFormat)
	{
		default:			// ASCII Format
			ExportASCII();
			break;
		case 0:				// ASCII Format
			if (s == "") 
			{
				s = ".txt";		
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportASCII();
			break;
		case 1: 			// Statistica Format
			if (s == "") 
			{
				s = ".sta";	
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportStat();
		break;
	}
}

void CElsExportPI::ExportASCII(void)
{
	CFile fExport;
	CFileException e;
	CExperiment exp;
	CString s, t, lastPath;
	int i, j, N, heat;
	int nPaths, nFiles;

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;

	UpdateData();
	if (fExport.Open(m_EDIT_FilePath, CFile::modeRead, &e))
	{
		fExport.Close();
		s = "File " + m_EDIT_FilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES) 
			return;
	}
	if (!fExport.Open(m_EDIT_FilePath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		s = "Unable to write indices\n to file " + m_EDIT_FilePath + "!";
		AfxMessageBox(s);
		return;
	}
	
	// Header of export file:
	s = "FILE;DATE;HEAT";
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		t.Format(";PI%i", i + 1);
		s += t;
	}
	s += "\r\n";
	fExport.Write(s, s.GetLength());
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
	nFiles = pDoc->m_fileList.GetSize();
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
		s = exp.m_ExpName;
		m_STATIC_ExportMessage.Format("Writing indices: %2i%%...\r\nExperiment: %s - ",
			i * 100 / nFiles, s);
		UpdateData(FALSE);
		if (exp.IsValid())
		{
			m_STATIC_ExportMessage += "ok!";
			N++;
			exp.CalcPerfIndices();
			if (exp.m_iHeat == HEAT_0_180) heat = 1;
			else heat = -1;
			t.Format(";%i/%i/%i;%i", exp.m_Day, exp.m_Month, exp.m_Year, heat);
			s += t;
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				t.Format(";%.3f", exp.m_PI[j]);
				s += t;
			}
			s += "\r\n";
		}
		else
		{
			m_STATIC_ExportMessage += "error!";
			s += " - error!\r\n";
		}
		fExport.Write(s, s.GetLength());
		UpdateData(FALSE);
	}
	m_STATIC_ExportMessage.Format("Indices of %i out of %i experiments\r\nsuccessfully exported.",
		N, nFiles);
	UpdateData(FALSE);
	fExport.Close();
}

void CElsExportPI::ExportStat(void)
{
	HSTAFILE fExport;
	HRES res;
	CExperiment exp;
	CString s, t, lastPath;
	int i, j, N, heat, nVars, staCase, staYear;
	int nPaths, nFiles;
	double date;
	int mlen[] =
	{
		0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	}; 
	
	CElsDoc *pDoc = (CElsDoc *)m_pDoc;

	UpdateData();
	fExport = StaOpenFile(m_EDIT_FilePath);
	if (fExport != 0)
	{
		StaCloseFile(fExport);
		s = "File " + m_EDIT_FilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES)
			return;
	}
	nVars = pDoc->m_nOfBlocks + 3;
	nFiles = pDoc->m_fileList.GetSize();
	fExport = StaCreateFile(nVars, nFiles, m_EDIT_FilePath);
	if (fExport == 0)
	{
		s = "Unable to write indices\n to file " + m_EDIT_FilePath + "!";
		AfxMessageBox(s);
		return;
	}
	// setting variable names and formats:
	res = StaSetVarName(fExport, 1, "FILE");
	res = StaSetVarFormat(fExport, 1, 8, 0, 0, 0);
	StaSetVarName(fExport, 2, "DATE");
	StaSetVarFormat(fExport, 2, 8, 0, 1, 5);
	StaSetVarName(fExport, 3, "HEAT");
	StaSetVarFormat(fExport, 3, 8, 0, 0, 0);
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		s.Format("PI%i", i + 1);
		res = StaSetVarName(fExport, i + 4, s);
		res = StaSetVarFormat(fExport, i + 4, 8, 3, 0, 0);
	}
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
//	nFiles = pDoc->m_fileList.GetSize();
	for (i = 0, N = 0; i < nFiles; i++)
	{
		staCase = i + 1;
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
		s = exp.m_ExpName;
		m_STATIC_ExportMessage.Format("Writing indices: %2i%%...\r\nExperiment: %s - ",
			i * 100 / nFiles, s);
		UpdateData(FALSE);
		if (exp.IsValid())
		{
			m_STATIC_ExportMessage += "ok!";
			N++;
			exp.CalcPerfIndices();
			if (exp.m_iHeat == HEAT_0_180) heat = 1;
			else heat = -1;
			res = StaSetCaseNameLength (fExport, 8);
			res = StaSetCaseName(fExport, staCase, pDoc->m_fileList[i]);
			res = StaSetData(fExport, 1, staCase, staCase);
			s.Format("%i", staCase * 100);
			res = StaAddLabel(fExport, 1, staCase, pDoc->m_fileList[i], NULL); 
			staYear = exp.m_Year - 1900;
			date = exp.m_Day + mlen[exp.m_Month] + (staYear * 365) + (staYear / 4) + 1;
			res = StaSetData(fExport, 2, staCase, date);
			res = StaSetData(fExport, 3, staCase, heat);

			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				res = StaSetData(fExport, j + 4, staCase, exp.m_PI[j]);
			}
		}
		else
		{
			m_STATIC_ExportMessage += "error!";
			res = StaSetData(fExport, 1, i, 0);
		}
		UpdateData(FALSE);
	}
	m_STATIC_ExportMessage.Format("Indices of %i out of %i experiments\r\nsuccessfully exported.",
		N, nFiles);
	UpdateData(FALSE);

	StaCloseFile(fExport);
}

void CElsExportPI::OnExportFormat() 
{
	// ASCII data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".txt");
	UpdateData(FALSE);
}

void CElsExportPI::OnExportFormat2() 
{
	// Statistica data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".sta");
	UpdateData(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CElsExportFI dialog


CElsExportFI::CElsExportFI(CWnd* pParent /*=NULL*/)
	: CDialog(CElsExportFI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElsExportFI)
	m_EDIT_FilePath = _T("");
	m_RADIO_ExportFormat = -1;
	m_STATIC_ExportMessage = _T("");
	//}}AFX_DATA_INIT
}


void CElsExportFI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsExportFI)
	DDX_Control(pDX, IDC_START_EXPORT, m_BUTTON_Export);
	DDX_Control(pDX, IDC_BUTTON_EXPORT_DESTINATION, m_BUTTON_ExportFormat);
	DDX_Text(pDX, IDC_EXPORT_FILE_PATH, m_EDIT_FilePath);
	DDX_Radio(pDX, IDC_EXPORT_FORMAT, m_RADIO_ExportFormat);
	DDX_Text(pDX, IDC_EXPORT_MESSAGE, m_STATIC_ExportMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElsExportFI, CDialog)
	//{{AFX_MSG_MAP(CElsExportFI)
	ON_BN_CLICKED(IDC_START_EXPORT, OnStartExport)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_DESTINATION, OnButtonExportDestination)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT, OnExportFormat)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT_2, OnExportFormat2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElsExportFI message handlers


BOOL CElsExportFI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	m_EDIT_FilePath = m_pDoc->GetTitle();
	
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s", m_fname);

	m_RADIO_ExportFormat = 0;	// standardmaessig ASCII Export 
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElsExportFI::OnButtonExportDestination() 
{
	CString defext, filter, title;
	DWORD flags;
	int index;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	filter = "ASCII file (*.txt)|*.txt|Statistica file (*.sta)|*.sta||";
	flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	title = "Choose export file name";
	switch (m_RADIO_ExportFormat)
	{
		default:
		case 0: 
			defext = ".txt";		// ASCII Format
			index = 1;
			break;
		case 1: 
			defext = ".sta";		// Statistica Format
			index = 2;
			break;
	}
	m_EDIT_FilePath = m_fname;
	UpdateData(FALSE);
	CFileDialog fDlg(FALSE, defext, m_EDIT_FilePath, flags, filter);
	fDlg.m_ofn.nFilterIndex = index;
	fDlg.m_ofn.lpstrTitle = title;
	if (fDlg.DoModal() == IDOK)
	{
		m_EDIT_FilePath = fDlg.GetPathName();
		switch (fDlg.m_ofn.nFilterIndex)
		{
			case 1: 
				m_RADIO_ExportFormat = 0;
				break;
			case 2: 
				m_RADIO_ExportFormat = 1;
				break;
		}
	}
	UpdateData(FALSE);
}

void CElsExportFI::OnStartExport() 
{
	CFile fExport;
	CFileException e;
	CString s;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	
	s = m_ext;
	
	switch (m_RADIO_ExportFormat)
	{
		default:			// ASCII Format
			ExportASCII();
			break;
		case 0:				// ASCII Format
			if (s == "") 
			{
				s = ".txt";		
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportASCII();
			break;
		case 1: 			// Statistica Format
			if (s == "") 
			{
				s = ".sta";	
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportStat();
		break;
	}
}

void CElsExportFI::ExportASCII(void)
{
	CFile fExport;
	CFileException e;
	CExperiment exp;
	CString s, t, lastPath;
	int i, j, N, heat;
	int nPaths, nFiles;

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;

	UpdateData();
	if (fExport.Open(m_EDIT_FilePath, CFile::modeRead, &e))
	{
		fExport.Close();
		s = "File " + m_EDIT_FilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES) 
			return;
	}
	if (!fExport.Open(m_EDIT_FilePath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		s = "Unable to write indices\n to file " + m_EDIT_FilePath + "!";
		AfxMessageBox(s);
		return;
	}
	
	// Header of export file:
	s = "FILE;DATE;HEAT";
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		t.Format(";FI%i", i + 1);
		s += t;
	}
	s += "\r\n";
	fExport.Write(s, s.GetLength());
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
	nFiles = pDoc->m_fileList.GetSize();
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
		s = exp.m_ExpName;
		m_STATIC_ExportMessage.Format("Writing indices: %2i%%...\r\nExperiment: %s - ",
			i * 100 / nFiles, s);
		UpdateData(FALSE);
		if (exp.IsValid())
		{
			m_STATIC_ExportMessage += "ok!";
			N++;
			exp.CalcFixationIndices();
			if (exp.m_iHeat == HEAT_0_180) heat = 1;
			else heat = -1;
			t.Format(";%i/%i/%i;%i", exp.m_Day, exp.m_Month, exp.m_Year, heat);
			s += t;
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				t.Format(";%.3f", exp.m_FIc[j]);
				s += t;
			}
			s += "\r\n";
		}
		else
		{
			m_STATIC_ExportMessage += "error!";
			s += " - error!\r\n";
		}
		fExport.Write(s, s.GetLength());
		UpdateData(FALSE);
	}
	m_STATIC_ExportMessage.Format("Indices of %i out of %i experiments\r\nsuccessfully exported.",
		N, nFiles);
	UpdateData(FALSE);
	fExport.Close();
}
void CElsExportFI::ExportStat(void)
{
}
void CElsExportFI::OnExportFormat() 
{
	// ASCII data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".txt");
	UpdateData(FALSE);
}

void CElsExportFI::OnExportFormat2() 
{
	// Statistica data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".sta");
	UpdateData(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CElsExportTI dialog


CElsExportTI::CElsExportTI(CWnd* pParent /*=NULL*/)
	: CDialog(CElsExportTI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CElsExportTI)
	m_EDIT_FilePath = _T("");
	m_RADIO_ExportFormat = -1;
	m_STATIC_ExportMessage = _T("");
	//}}AFX_DATA_INIT
}


void CElsExportTI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsExportTI)
	DDX_Control(pDX, IDC_START_EXPORT, m_BUTTON_Export);
	DDX_Control(pDX, IDC_BUTTON_EXPORT_DESTINATION, m_BUTTON_ExportTI);
	DDX_Text(pDX, IDC_EXPORT_FILE_PATH, m_EDIT_FilePath);
	DDX_Radio(pDX, IDC_EXPORT_FORMAT, m_RADIO_ExportFormat);
	DDX_Text(pDX, IDC_EXPORT_MESSAGE, m_STATIC_ExportMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElsExportTI, CDialog)
	//{{AFX_MSG_MAP(CElsExportTI)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_DESTINATION, OnButtonExportDestination)
	ON_BN_CLICKED(IDC_START_EXPORT, OnStartExport)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT, OnExportFormat)
	ON_BN_CLICKED(IDC_EXPORT_FORMAT_2, OnExportFormat2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElsExportTI message handlers

BOOL CElsExportTI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	m_EDIT_FilePath = m_pDoc->GetTitle();
	
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s", m_fname);

	m_RADIO_ExportFormat = 0;	// standardmaessig ASCII Export 
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CElsExportTI::OnButtonExportDestination() 
{
	CString defext, filter, title;
	DWORD flags;
	int index;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	CElsDoc *pDoc = (CElsDoc *)m_pDoc;	
	filter = "ASCII file (*.txt)|*.txt|Statistica file (*.sta)|*.sta||";
	flags = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	title = "Choose export file name";
	switch (m_RADIO_ExportFormat)
	{
		default:
		case 0: 
			defext = ".txt";		// ASCII Format
			index = 1;
			break;
		case 1: 
			defext = ".sta";		// Statistica Format
			index = 2;
			break;
	}
	m_EDIT_FilePath = m_fname;
	UpdateData(FALSE);
	CFileDialog fDlg(FALSE, defext, m_EDIT_FilePath, flags, filter);
	fDlg.m_ofn.nFilterIndex = index;
	fDlg.m_ofn.lpstrTitle = title;
	if (fDlg.DoModal() == IDOK)
	{
		m_EDIT_FilePath = fDlg.GetPathName();
		switch (fDlg.m_ofn.nFilterIndex)
		{
			case 1: 
				m_RADIO_ExportFormat = 0;
				break;
			case 2: 
				m_RADIO_ExportFormat = 1;
				break;
		}
	}
	UpdateData(FALSE);
}

void CElsExportTI::OnStartExport() 
{
	CFile fExport;
	CFileException e;
	CString s;

	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	
	s = m_ext;
	
	switch (m_RADIO_ExportFormat)
	{
		default:			// ASCII Format
			ExportASCII();
			break;
		case 0:				// ASCII Format
			if (s == "") 
			{
				s = ".txt";		
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportASCII();
			break;
		case 1: 			// Statistica Format
			if (s == "") 
			{
				s = ".sta";	
				m_EDIT_FilePath += s;
				UpdateData(FALSE);
			}
			ExportStat();
		break;
	}
}

void CElsExportTI::ExportASCII(void)
{
	CFile fExport;
	CFileException e;
	CExperiment exp;
	CString s, t, lastPath;
	int i, j, N, heat;
	int nPaths, nFiles;

	CElsDoc *pDoc = (CElsDoc *)m_pDoc;

	UpdateData();
	if (fExport.Open(m_EDIT_FilePath, CFile::modeRead, &e))
	{
		fExport.Close();
		s = "File " + m_EDIT_FilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES) 
			return;
	}
	if (!fExport.Open(m_EDIT_FilePath, CFile::modeCreate | CFile::modeWrite, &e))
	{
		s = "Unable to write indices\n to file " + m_EDIT_FilePath + "!";
		AfxMessageBox(s);
		return;
	}
	
	// Header of export file:
	s = "FILE;DATE;HEAT";
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		t.Format(";TI%i", i + 1);
		s += t;
	}
	s += "\r\n";
	fExport.Write(s, s.GetLength());
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
	nFiles = pDoc->m_fileList.GetSize();
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
		s = exp.m_ExpName;
		m_STATIC_ExportMessage.Format("Writing indices: %2i%%...\r\nExperiment: %s - ",
			i * 100 / nFiles, s);
		UpdateData(FALSE);
		if (exp.IsValid())
		{
			m_STATIC_ExportMessage += "ok!";
			N++;
			exp.CalcTorqueIndices();
			if (exp.m_iHeat == HEAT_0_180) heat = 1;
			else heat = -1;
			t.Format(";%i/%i/%i;%i", exp.m_Day, exp.m_Month, exp.m_Year, heat);
			s += t;
			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				t.Format(";%.3f", exp.m_TI[j]);
				s += t;
			}
			s += "\r\n";
		}
		else
		{
			m_STATIC_ExportMessage += "error!";
			s += " - error!\r\n";
		}
		fExport.Write(s, s.GetLength());
		UpdateData(FALSE);
	}
	m_STATIC_ExportMessage.Format("Indices of %i out of %i experiments\r\nsuccessfully exported.",
		N, nFiles);
	UpdateData(FALSE);
	fExport.Close();
}

void CElsExportTI::ExportStat(void)
{
	HSTAFILE fExport;
	HRES res;
	CExperiment exp;
	CString s, t, lastPath;
	int i, j, N, heat, nVars, staCase, staYear;
	int nPaths, nFiles;
	double date;
	int mlen[] =
	{
		0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
	}; 
	
	CElsDoc *pDoc = (CElsDoc *)m_pDoc;

	UpdateData();
	fExport = StaOpenFile(m_EDIT_FilePath);
	if (fExport != 0)
	{
		StaCloseFile(fExport);
		s = "File " + m_EDIT_FilePath + " already exists!\r\n\nOverwrite?";
		if (AfxMessageBox(s, MB_YESNOCANCEL) != IDYES)
			return;
	}
	nVars = pDoc->m_nOfBlocks + 3;
	nFiles = pDoc->m_fileList.GetSize();
	fExport = StaCreateFile(nVars, nFiles, m_EDIT_FilePath);
	if (fExport == 0)
	{
		s = "Unable to write indices\n to file " + m_EDIT_FilePath + "!";
		AfxMessageBox(s);
		return;
	}
	// setting variable names and formats:
	res = StaSetVarName(fExport, 1, "FILE");
	res = StaSetVarFormat(fExport, 1, 8, 0, 0, 0);
	StaSetVarName(fExport, 2, "DATE");
	StaSetVarFormat(fExport, 2, 8, 0, 1, 5);
	StaSetVarName(fExport, 3, "HEAT");
	StaSetVarFormat(fExport, 3, 8, 0, 0, 0);
	for (i = 0; i < pDoc->m_nOfBlocks; i++)
	{
		s.Format("TI%i", i + 1);
		res = StaSetVarName(fExport, i + 4, s);
		res = StaSetVarFormat(fExport, i + 4, 8, 3, 0, 0);
	}
	nPaths = pDoc->m_pathList.GetSize();
	if (nPaths > 0) lastPath = pDoc->m_pathList[0];
	else lastPath = "";
//	nFiles = pDoc->m_fileList.GetSize();
	for (i = 0, N = 0; i < nFiles; i++)
	{
		staCase = i + 1;
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
		s = exp.m_ExpName;
		m_STATIC_ExportMessage.Format("Writing indices: %2i%%...\r\nExperiment: %s - ",
			i * 100 / nFiles, s);
		UpdateData(FALSE);
		if (exp.IsValid())
		{
			m_STATIC_ExportMessage += "ok!";
			N++;
			exp.CalcTorqueIndices();
			if (exp.m_iHeat == HEAT_0_180) heat = 1;
			else heat = -1;
			res = StaSetCaseNameLength (fExport, 8);
			res = StaSetCaseName(fExport, staCase, pDoc->m_fileList[i]);
			res = StaSetData(fExport, 1, staCase, staCase);
			s.Format("%i", staCase * 100);
			res = StaAddLabel(fExport, 1, staCase, pDoc->m_fileList[i], NULL); 
			staYear = exp.m_Year - 1900;
			date = exp.m_Day + mlen[exp.m_Month] + (staYear * 365) + (staYear / 4) + 1;
			res = StaSetData(fExport, 2, staCase, date);
			res = StaSetData(fExport, 3, staCase, heat);

			for (j = 0; j < exp.m_nOfBlocks; j++)
			{
				res = StaSetData(fExport, j + 4, staCase, exp.m_TI[j]);
			}
		}
		else
		{
			m_STATIC_ExportMessage += "error!";
			res = StaSetData(fExport, 1, i, 0);
		}
		UpdateData(FALSE);
	}
	m_STATIC_ExportMessage.Format("Indices of %i out of %i experiments\r\nsuccessfully exported.",
		N, nFiles);
	UpdateData(FALSE);

	StaCloseFile(fExport);
}

void CElsExportTI::OnExportFormat() 
{
	// ASCII data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".txt");
	UpdateData(FALSE);
}

void CElsExportTI::OnExportFormat2() 
{
	// Statistica data format
	UpdateData();
	_splitpath(m_EDIT_FilePath, m_drive, m_dir, m_fname, m_ext);
	m_EDIT_FilePath.Format("%s%s%s%s", m_drive, m_dir, m_fname, ".sta");
	UpdateData(FALSE);
}