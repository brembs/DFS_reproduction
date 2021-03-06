// D_ELS.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "D_ELS.h"
#include "V_ELS.h"
#include "Exprimnt.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocELS

IMPLEMENT_DYNCREATE(CDocELS, CDocument)

CDocELS::CDocELS()
{
	int i;
	
	for (i = 0; i < MAX_BLOCKS; i++)
	{
		m_perfIndex[i] = 0.0;
		m_SEM[i] = 0.0;
		m_BlockType[i] = EXPTYPE_UNDEF;
		m_BlockDur[i] = 0;
		m_BlockLen[i] = 0;
	}
	m_ExpDur = 0;
	m_nHeat_0_180 = 0;
	m_nHeat_90_270 = 0;
}

BOOL CDocELS::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDocELS::~CDocELS()
{
}


BEGIN_MESSAGE_MAP(CDocELS, CDocument)
	//{{AFX_MSG_MAP(CDocELS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocELS diagnostics

#ifdef _DEBUG
void CDocELS::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocELS::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocELS serialization

void CDocELS::Serialize(CArchive& ar)
{
	CEditView* pView = (CEditView *)m_viewList.GetHead();
	ASSERT_KINDOF(CEditView, pView);
	pView->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CDocELS commands

BOOL CDocELS::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	return TRUE;
}

BOOL CDocELS::ParseExpScript(CEdit *pEd)
{
	int	z, m, n, nmax;
	BOOL done = FALSE;
	char line[260], *p;
	CString expname, meta, param;
	
	m_fileList.SetSize(0, 5);
	m_pathList.SetSize(0, 5);

	nmax = pEd->GetLineCount();
	n = 0;
	z = 0;
	while (!done)
	{
		switch (z)
		{
			case 0:			// Zeile einlesen
				m = pEd->GetLine(n, line, 256);
				line[m] = '\0';
				p = line;
				if (n < nmax)				// fuer alle Zeilen
					{ n++; z = 50; }
				else 
					{ done = TRUE; }
				break;
			case 50:		// Zeilenanfang absuchen
				if (*p == '\0')				// Zeilenende
					{ z = 0; }
				else 
				if (*p == '\t' || *p == ' ')// Leerzeichen
					{ p++; }
				else
				if (*p == ';')				// Kommentar beginnt
					{ p++; z = 100; }
				else
				if (isalnum(*p))			// Experimentnamen beginnt
					{ expname = ""; z = 200; }
				else
				if (*p == '#')				// Direktive beginnt
					{ p++; z = 300; }
				else
					z = 0;
				break;
			case 100:		// Kommentar
				if (*p == '\0') 
					{ z = 0; }
				else p++; 
				break;
			case 200:		// Experimentnamen einlesen
				if (isalnum(*p) || *p == '-' || *p == '_') 
					{ expname += *p; p++; }
				else
					{ m_fileList.Add(expname); z = 210; }
				break;
			case 210:
				if (*p == '\0')
					{ z = 0; }
				else
				if (*p == ';')		// Kommentar nach Experimentnamen
					{ p++; z = 100; }
				else
					{ p++; }
				break;
			case 300:		// Direktive einlesen
				meta = "";
				param = "";
				z = 310;
				break;
			case 310:
				if (*p == '\0')
					{ z = 398; }		// vorzeitiges Zeilenende
				else
				if (isspace(*p))
					{ p++; }
				else
				if (isalnum(*p))
					{ meta += *p; p++; z = 320; }
				else 
					{ z = 395; }
				break;
			case 320:		
				if (*p == '\0')
					{ z = 398; }		// vorzeitiges Zeilenende
				else
				if (isalnum(*p))
					{ meta += *p; p++; }
				else 
				if (isspace(*p))		// Direktive Befehlsteil komplett
					{ p++; z = 330; }
				else
				if (*p == '=')
					{ p++; z = 350; }
				else
					{ z = 395; }		// unerwartetes Zeichen 
				break;
			case 330:
				if (*p == '\0')
					{ z = 398; }		// vorzeitiges Zeilenende
				else
				if (isspace(*p))		// Leerzeichen ueberspringen
					{ p++; }
				else
				if (*p == '=')
					{ p++; }
				else
				if (*p == '\"')
					{ p++; z = 360; }
				else					// erstes Parameterzeichen
					{ param += *p; p++; z = 340; }
				break;
			case 340:
				if (*p == '\0')
					{ z = 398; }		// tolerierbares vorzeitiges Zeilenende
				else
				if (*p == '\t' || *p == ' ')
					{ p++; z = 370; }	// Parameter komplett
				else
					{ param += *p; p++; }
				break;
			case 350:		// mit '=' eingeleitete Parameter
				if (*p == '\0')
					{ z = 398; }		// tolerierbares vorzeitiges Zeilenende
				else
				if (isspace(*p))		// Leerzeichen ueberspringen
					{ p++; }
				else
				if (*p == '\"')			// Parameter beginnt mit '"'
					{ p++; z = 360; }
				else					// Parameter beginnt
					{ z = 340; }
				break;
			case 360:
				if (*p == '\0')
					{ z = 398; }		// tolerierbares vorzeitiges Zeilenende
				else
				if (*p == '\"')			// Parameter komplett
					{ z = 370; }
				else
					{ param += *p; p++; }
				break;
			case 370:
				if (meta == "path")	
				{
					if (param.Right(1) != '\\') param += '\\';
					m_pathList.Add(param);
				}
				if (*p == '\0')
					{ z = 398; }		// tolerierbares vorzeitiges Zeilenende
				else					// Rest der Zeile ignorieren
					{ p++; }
				break;
			case 395:		// unerwartetes Zeichen aufgetreten
				z = 0;
				break;
			case 397:		// nicht tolerierbares vorzeitiges Zeilenende 
				z = 0;
				break;
			case 398:		// tolerierbares vorzeitiges Zeilenende 
			case 399:		// Direktive korrekt eingelesen
				z = 0;
				break;
			default:
				done = TRUE;
				break;
		}
	}
	return TRUE;
}
BOOL CDocELS::ParseExpScript()
{
	CEdit ed;
	CFile f;
	CFileException e;
	CString s;
	char b[256];
	int length, l;

	s = "";
	for (l = 0; l < length; l++)
	{
		if (!f.Open(GetPathName(), CFile::modeRead, &e)) return FALSE;
		length = f.GetLength();
		l += f.Read(b, sizeof(char) * 255);
		b[l] = '\0';
		s += b;
	}
	ed.SetWindowText(s);
	return TRUE;
}

void CDocELS::CalcIndices(BOOL subPref, BOOL weightedInd)
{
	CExperiment exp;
	CString s, lastPath;
	int i, j, N, nFiles, nPaths;
	double s_x2[MAX_BLOCKS], sx[MAX_BLOCKS], sx_2[MAX_BLOCKS];

	for (i = 0; i < MAX_BLOCKS; i++)
	{
		m_perfIndex[i] = 0.0;
		m_SEM[i] = 0.0;
		s_x2[i] = 0.0;
		sx[i] = 0.0;
		sx_2[i] = 0.0;
	}
	nPaths = m_pathList.GetSize();
	if (nPaths > 0) lastPath = m_pathList[0];
	else lastPath = "";
	nFiles = m_fileList.GetSize();
	m_nHeat_0_180 = 0;
	m_nHeat_90_270 = 0;
	for (i = 0, N = 0; i < nFiles; i++)
	{
		CWaitCursor wait;
		s = exp.MakeFullName(lastPath, m_fileList[i]);
		if (!exp.LoadExperiment(s))
		{
			for (j = 0; j < nPaths; j++)
			{
				s = exp.MakeFullName(m_pathList[j], m_fileList[i]);
				if (exp.LoadExperiment(s))
				{
					lastPath = s;
					break;
				}
			}
		}

		if (!exp.IsValid()) continue; 

		N++;
		if (exp.m_iHeat == HEAT_0_180) m_nHeat_0_180++;
		else m_nHeat_90_270++;
	
		exp.CalcPerfIndices(subPref, weightedInd);
		for (j = 0; j < exp.m_nOfBlocks; j++)
		{
			m_perfIndex[j] += exp.m_PerfIndex[j];
			s_x2[j] += exp.m_PerfIndex[j] * exp.m_PerfIndex[j];
			sx[j] += exp.m_PerfIndex[j];
			sx_2[j] = sx[j] * sx[j];
			if (N < 2) continue;
			m_SEM[j] = s_x2[j] - (sx_2[j] / N);
			m_SEM[j] /= N * (N - 1);
			m_SEM[j] = sqrt(m_SEM[j]);
		}
	}
	
	m_ExpDur = exp.m_ExpDur;
	m_nOfBlocks = exp.m_nOfBlocks;
	for (i = 0; i < m_nOfBlocks; i++)
	{
		m_BlockDur[i] = exp.m_BlockDur[i];
		m_BlockLen[i] = exp.m_BlockLen[i];
		m_BlockType[i] = exp.m_BlockType[i];
		m_perfIndex[i] /= N;
	}
}
