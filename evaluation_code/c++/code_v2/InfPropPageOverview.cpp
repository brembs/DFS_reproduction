// InfPropPageOverview.cpp : implementation file
//

#include "stdafx.h"
#include "Dfs.h"
#include "InfPropPageOverview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfPropPageOverview property page

IMPLEMENT_DYNCREATE(CInfPropPageOverview, CNSFlexPropertyPage)

CInfPropPageOverview::CInfPropPageOverview() : CNSFlexPropertyPage(CInfPropPageOverview::IDD)
{
	//{{AFX_DATA_INIT(CInfPropPageOverview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInfPropPageOverview::~CInfPropPageOverview()
{
}

void CInfPropPageOverview::DoDataExchange(CDataExchange* pDX)
{
	CNSFlexPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfPropPageOverview)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfPropPageOverview, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CInfPropPageOverview)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfPropPageOverview message handlers
