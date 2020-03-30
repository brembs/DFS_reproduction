// ElsPropPageTorquePI.h : header file
//
#include "NSViews/NSFlexPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageTorquePI dialog

class CElsPropPageTorquePI : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CElsPropPageTorquePI)

// Construction
public:
	CElsPropPageTorquePI();
	~CElsPropPageTorquePI();

// Dialog Data
	//{{AFX_DATA(CElsPropPageTorquePI)
	enum { IDD = IDD_PP_ELS_TORQUEPI };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CElsPropPageTorquePI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CElsPropPageTorquePI)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
