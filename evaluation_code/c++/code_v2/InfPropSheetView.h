// InfPropSheetView.h : header file
//
#include "NSViews/NSFlexPropertySheetView.h"
#include "NSViews/NSFlexPropertySheet.h"

#include "InfPropPageOverview.h"
#include "InfPropPagePerformance.h"

/////////////////////////////////////////////////////////////////////////////
// CInfPropSheetView view

class CInfPropSheetView : public CNSFlexPropertySheetView
{
protected:
	CInfPropSheetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfPropSheetView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfPropSheetView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInfPropSheetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CInfPropSheetView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CInfPropPageOverview m_pInfPropPageOverview;
	CInfPropPagePerformance m_pInfPropPagePerformance;

};

/////////////////////////////////////////////////////////////////////////////
