// V_PerfIndex.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewPerfIndex form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewPerfIndex : public CFormView
{
protected:
	CViewPerfIndex();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewPerfIndex)

// Form Data
public:
	void DrawDiagram();
	//{{AFX_DATA(CViewPerfIndex)
	enum { IDD = IDD_VIEW_PERFINDEX };
	CStatic	m_BMP_Heat;
	CStatic	m_BMP_Heat_90_270;
	CStatic	m_BMP_Heat_0_180;
	CListBox	m_LB_Index;
	BOOL	m_CHECK_SubPref;
	BOOL	m_CHECK_WeightedIndices;
	double	m_ED_Preference;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPerfIndex)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewPerfIndex();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewPerfIndex)
	afx_msg void OnCheckSubPref();
	afx_msg void OnCheckWeightedIndices();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
