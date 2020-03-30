// InfDoc.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "InfDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfDoc

IMPLEMENT_DYNCREATE(CInfDoc, CDocument)

CInfDoc::CInfDoc()
{
}

BOOL CInfDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CInfDoc::~CInfDoc()
{
}


BEGIN_MESSAGE_MAP(CInfDoc, CDocument)
	//{{AFX_MSG_MAP(CInfDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfDoc diagnostics

#ifdef _DEBUG
void CInfDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInfDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfDoc serialization

void CInfDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInfDoc commands
