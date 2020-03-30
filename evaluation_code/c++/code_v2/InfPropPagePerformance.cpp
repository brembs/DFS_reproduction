// InfPropPagePerformance.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "InfPropPagePerformance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfPropPagePerformance property page

IMPLEMENT_DYNCREATE(CInfPropPagePerformance, CNSFlexPropertyPage)

CInfPropPagePerformance::CInfPropPagePerformance() : CNSFlexPropertyPage(CInfPropPagePerformance::IDD)
{
	//{{AFX_DATA_INIT(CInfPropPagePerformance)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInfPropPagePerformance::~CInfPropPagePerformance()
{
}

void CInfPropPagePerformance::DoDataExchange(CDataExchange* pDX)
{
	CNSFlexPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfPropPagePerformance)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfPropPagePerformance, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CInfPropPagePerformance)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfPropPagePerformance message handlers
