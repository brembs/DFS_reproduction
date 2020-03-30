// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexPropertySheetView.h"
#include "NSViews/NSFlexPropertySheet.h"

#include "ElsPropPageExperimentList.h"
#include "ElsPropPagePerformance.h"
#include "ElsPropPageFixation.h"
#include "ElsPropPageTorquePI.h"

class CElsPropSheetView : public CNSFlexPropertySheetView
{
protected:
	CElsPropSheetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CElsPropSheetView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsPropSheetView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CElsPropSheetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CElsPropSheetView)
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	CElsPropPageExperimentList m_ElsPropPageExperimentList;
	CElsPropPagePerformance m_ElsPropPagePerformance;
	CElsPropPageFixation m_ElsPropPageFixation;
	CElsPropPageTorquePI m_ElsPropPageTorquePI;
};

/////////////////////////////////////////////////////////////////////////////
