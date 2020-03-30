// D_INF.cpp : implementation file
//

#include "stdafx.h"
#include "DFS.h"
#include "D_INF.h"
#include "stdlib.h"

#if !defined _EXPRIMNT_H_
#include "exprimnt.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDocINF

IMPLEMENT_DYNCREATE(CDocINF, CDocument)

CDocINF::CDocINF()
{
}


BOOL CDocINF::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CDocINF::~CDocINF()
{
}


BEGIN_MESSAGE_MAP(CDocINF, CDocument)
	//{{AFX_MSG_MAP(CDocINF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocINF diagnostics

#ifdef _DEBUG
void CDocINF::AssertValid() const
{
	CDocument::AssertValid();
}

void CDocINF::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocINF serialization

void CDocINF::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// Hier wird nichts gemacht, das Laden der Daten
		// geschieht in einem Override von 'OnOpenDocument'
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDocINF commands

BOOL CDocINF::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// Laden der Experimentdaten
	if (!m_Experiment.LoadExperiment(lpszPathName))
		return FALSE;

	UpdateAllViews(NULL);

	return TRUE;
}
