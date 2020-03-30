// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexMDIChildWnd.h"

class CIntroViewFrm : public CNSFlexMDIChildWnd
{
	DECLARE_DYNCREATE(CIntroViewFrm)
public:
	CIntroViewFrm();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntroViewFrm)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation


virtual void OnUpdateFrameTitle(BOOL bAddToTitle);


public:
	virtual ~CIntroViewFrm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CIntroViewFrm)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
