// InfPropPagePerformance.h : header file
//
#include "NSViews/NSFlexPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// CInfPropPagePerformance dialog

class CInfPropPagePerformance : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CInfPropPagePerformance)

// Construction
public:
	CInfPropPagePerformance();
	~CInfPropPagePerformance();

// Dialog Data
	//{{AFX_DATA(CInfPropPagePerformance)
	enum { IDD = IDD_PP_INF_PERFORMANCE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInfPropPagePerformance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInfPropPagePerformance)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
