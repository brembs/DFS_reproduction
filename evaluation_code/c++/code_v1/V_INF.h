// INFView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewINF form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewINF : public CFormView
{
protected:
	CViewINF();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewINF)

// Form Data
public:
	//{{AFX_DATA(CViewINF)
	enum { IDD = IDD_VIEW_INF };
	CStatic	m_STATIC_Detected1800;
	CStatic	m_STATIC_Detected2048;
	UINT	m_ED_nOfFiles;
	CString	m_ED_Fly;
	CString	m_ED_HeatedSectors;
	CString	m_ED_Remarks;
	CString	m_ED_Time;
	UINT	m_ED_nOfRecords;
	UINT	m_ED_nOfData;
	CString	m_ED_ExperimentName;
	CString	m_ED_Date;
	UINT	m_ED_nOfPeriods;
	int		m_RADIO_ArenaPosRange;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewINF)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewINF();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewINF)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPosRange2048();
	afx_msg void OnPosRange1800();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
