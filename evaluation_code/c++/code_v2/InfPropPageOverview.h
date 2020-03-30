// InfPropPageOverview.h : header file
//
#include "NSViews/NSFlexPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// CInfPropPageOverview dialog

class CInfPropPageOverview : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CInfPropPageOverview)

// Construction
public:
	CInfPropPageOverview();
	~CInfPropPageOverview();

// Dialog Data
	//{{AFX_DATA(CInfPropPageOverview)
	enum { IDD = IDD_PP_INF_OVERVIEW };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInfPropPageOverview)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInfPropPageOverview)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
