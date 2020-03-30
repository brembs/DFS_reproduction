// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "NSViews/NSFlexFormView.h"

class CIntroView : public CNSFlexFormView
{
protected:
	CIntroView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIntroView)

// Form Data
public:
	//{{AFX_DATA(CIntroView)
	enum { IDD = IDD_FORM2 };
	CString	m_csIntroduction;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntroView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIntroView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIntroView)
	afx_msg void OnButtonFormView();
	afx_msg void OnButtonPropSheet();
	afx_msg void OnButtonPropSheetView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
