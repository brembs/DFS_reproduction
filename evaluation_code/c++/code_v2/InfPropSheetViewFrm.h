// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexMDIChildWnd.h"

class CInfPropSheetViewFrm : public CNSFlexMDIChildWnd
{
	DECLARE_DYNCREATE(CInfPropSheetViewFrm)
public:
	CInfPropSheetViewFrm();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfPropSheetViewFrm)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation


virtual void OnUpdateFrameTitle(BOOL bAddToTitle);


public:
	virtual ~CInfPropSheetViewFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CInfPropSheetViewFrm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

