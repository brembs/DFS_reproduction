// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

#include "NSViews/NSFlexPropertyPage.h"
#include "DfsExperiment.h"

class CElsPropPageFixation : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CElsPropPageFixation)

#define MAX_POSRANGE	4096
// Construction
public:
	CElsPropPageFixation();
	~CElsPropPageFixation();

// Dialog Data
	//{{AFX_DATA(CElsPropPageFixation)
	enum { IDD = IDD_PP_ELS_FIXATION };
	CComboBox	m_COMBO_ElsDisplayResolution;
	CSpinButtonCtrl	m_SPIN_ElsDisplayedBlock;
	CListBox	m_LIST_ElsFixationIndices;
	UINT	m_EDIT_ElsNReinf0180;
	UINT	m_EDIT_ElsNReinf90270;
	UINT	m_EDIT_ElsNAllFiles;
	CString	m_EDIT_ElsDisplayedBlock;
	int		m_EDIT_ElsSpinBuddyBlock;
	int		m_RADIO_ElsSelectReinforcement;
	BOOL	m_CHECK_ElsSuperimposeHeat;
	BOOL	m_CHECK_ElsMirroredQuadrants;
	//}}AFX_DATA

	UINT			m_DialogInitialized;
	int				m_nDisplayedFiles;
	CStringArray	m_BlockDescr;
	UINT			m_PosCount0180[MAX_EXP_BLOCKS][MAX_POSRANGE];
	UINT			m_PosCount90270[MAX_EXP_BLOCKS][MAX_POSRANGE];
	UINT			m_PosCount[MAX_POSRANGE];
	UINT			m_PosCountHg[MAX_EXP_BLOCKS][360];
 	double			m_FIh[MAX_EXP_BLOCKS];
 	double			m_FIc[MAX_EXP_BLOCKS];
	double			m_DisplayResolution;
	CDoubleArray	m_DisplayRes;
	UINT			m_nDiv;
	double			m_UnitsPerDiv;

	void ResetPosArray();
	void DrawHistogram();
	void CalcRawFreqencies();
	void CalcHistogramValues();
	void CalcFixationIndices();
	
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CElsPropPageFixation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
protected:

	void UpdateDocumentData();

	// Generated message map functions
	//{{AFX_MSG(CElsPropPageFixation)
	afx_msg void OnPaint();
	afx_msg void OnChangeEditElsSpinbuddyBlock();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboElsDisplayResolution();
	afx_msg void OnRadioElsSelectHeat90270();
	afx_msg void OnRadioElsSelectHeat0180();
	afx_msg void OnRadioElsSelectHeatAll();
	afx_msg void OnCheckElsHalfArena();
	afx_msg void OnCheckElsSuperimposed();
	afx_msg void OnButtonElsExportFi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
