// V_MPerfIndex.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewMPerfIndex form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewMPerfIndex : public CFormView
{
protected:
	CViewMPerfIndex();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewMPerfIndex)

// Form Data
public:
	void DrawDiagram();
	void CalcIndices();
	//{{AFX_DATA(CViewMPerfIndex)
	enum { IDD = IDD_VIEW_M_PERFINDEX };
	CStatic	m_STATIC_Message;
	CListBox	m_LB_PerfIndices;
	CListBox	m_LB_ExpNames;
	BOOL	m_CHECK_SubPref;
	BOOL	m_CHECK_WeightedIndices;
	UINT	m_ED_nHeat_0_180;
	UINT	m_ED_nHeat_90_270;
	UINT	m_ED_nOfFiles;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewMPerfIndex)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewMPerfIndex();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewMPerfIndex)
	afx_msg void OnCheckWeightedIndices();
	afx_msg void OnCheckSubPref();
	afx_msg void OnFileExportIndices();
	afx_msg void OnRecalc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
