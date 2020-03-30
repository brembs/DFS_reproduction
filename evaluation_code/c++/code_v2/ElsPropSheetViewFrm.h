// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexMDIChildWnd.h"

class CElsPropSheetViewFrm : public CNSFlexMDIChildWnd
{
	DECLARE_DYNCREATE(CElsPropSheetViewFrm)
public:
	CElsPropSheetViewFrm();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsPropSheetViewFrm)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation

public:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

public:

	virtual void OnUpdateFrameTitle(BOOL bAddToTitle);


public:
	virtual ~CElsPropSheetViewFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CElsPropSheetViewFrm)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

