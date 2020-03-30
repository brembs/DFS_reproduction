// DFSDoc.cpp : implementation of the CDFSDoc class
//

#include "stdafx.h"
#include "DFS.h"

#include "DFSDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDFSDoc

IMPLEMENT_DYNCREATE(CDFSDoc, CDocument)

BEGIN_MESSAGE_MAP(CDFSDoc, CDocument)
	//{{AFX_MSG_MAP(CDFSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDFSDoc construction/destruction

CDFSDoc::CDFSDoc()
{
	// TODO: add one-time construction code here

}

CDFSDoc::~CDFSDoc()
{
}

BOOL CDFSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDFSDoc serialization

void CDFSDoc::Serialize(CArchive& ar)
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
// CDFSDoc diagnostics

#ifdef _DEBUG
void CDFSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDFSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDFSDoc commands
