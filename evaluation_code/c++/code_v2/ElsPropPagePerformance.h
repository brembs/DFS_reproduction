// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexPropertyPage.h"

class CElsPropPagePerformance : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CElsPropPagePerformance)

// Construction
public:
	CElsPropPagePerformance();
	~CElsPropPagePerformance();

// Dialog Data
	//{{AFX_DATA(CElsPropPagePerformance)
	enum { IDD = IDD_PP_ELS_PERFORMANCE };
	CStatic	m_FRAME_ElsPIs;
	CListBox	m_LIST_ElsPIs;
	BOOL	m_CHECK_ElsPreferenceSubstracted;
	BOOL	m_CHECK_ElsInclPosPreference;
	BOOL	m_CHECK_ElsInclNegPreference;
	BOOL	m_CHECK_ElsInclReinf0180;
	BOOL	m_CHECK_ElsInclReinf90270;
	BOOL	m_CHECK_ElsTransformArtanh;
	UINT	m_EDIT_ElsNPosPref;
	UINT	m_EDIT_ElsNNegPref;
	UINT	m_EDIT_ElsNReinf0180;
	UINT	m_EDIT_ElsNReinf90270;
	UINT	m_EDIT_ElsNAllFiles;
	//}}AFX_DATA

	UINT	m_DialogInitialized;

	void DrawPerformanceHistogram();

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CElsPropPagePerformance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
protected:

	void UpdateDocumentData();

	// Generated message map functions
	//{{AFX_MSG(CElsPropPagePerformance)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckElsHeat0180();
	afx_msg void OnCheckElsHeat90270();
	afx_msg void OnCheckElsNegpref();
	afx_msg void OnCheckElsPospref();
	afx_msg void OnCheckElsSubpref();
	afx_msg void OnCheckElsTransformartanh();
	afx_msg void OnPaint();
	afx_msg void OnButtonElsExportPI();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
