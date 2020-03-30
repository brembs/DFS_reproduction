// ElsPropPageTorquePI.cpp : implementation file
//

#include "stdafx.h"
#include "dfs.h"
#include "ElsPropPageTorquePI.h"
#include "stadev/32BIT/stadev32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageTorquePI property page

IMPLEMENT_DYNCREATE(CElsPropPageTorquePI, CNSFlexPropertyPage)

CElsPropPageTorquePI::CElsPropPageTorquePI() : CNSFlexPropertyPage(CElsPropPageTorquePI::IDD)
{
	//{{AFX_DATA_INIT(CElsPropPageTorquePI)
	//}}AFX_DATA_INIT
}

CElsPropPageTorquePI::~CElsPropPageTorquePI()
{
}

void CElsPropPageTorquePI::DoDataExchange(CDataExchange* pDX)
{
	CNSFlexPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElsPropPageTorquePI)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CElsPropPageTorquePI, CNSFlexPropertyPage)
	//{{AFX_MSG_MAP(CElsPropPageTorquePI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageTorquePI message handlers

