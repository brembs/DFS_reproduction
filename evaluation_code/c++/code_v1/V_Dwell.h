// V_Dwell.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewDwell form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewDwell : public CFormView
{
protected:
	CViewDwell();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewDwell)

// Form Data
public:
	//{{AFX_DATA(CViewDwell)
	enum { IDD = IDD_VIEW_DWELL };
	CSpinButtonCtrl	m_SPIN_Resolution;
	CSpinButtonCtrl	m_SPIN_BlockNo;
	CString	m_ED_BlockNo;
	int		m_RADIO_HotCold;
	CString	m_ED_MeanDwellHot;
	CString	m_ED_MeanDwellCold;
	int		m_RADIO_XLinLog;
	CString	m_ED_TimeResolution;
	int		m_SpinBuddyBlockNo;
	int		m_SpinBuddyTimeResolution;
	//}}AFX_DATA

// Attributes
public:
	int	m_curBlock;
	int m_maxBlock;

// Operations
public:
	double GetDiv(double range);
	void DrawDiagram();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewDwell)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewDwell();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewDwell)
	afx_msg void OnRadioHotCold();
	afx_msg void OnChangeSpinbuddyBlockNo();
	afx_msg void OnChangeSpinbuddyTimeResolution();
	afx_msg void OnRadioXLinLog();
	afx_msg void OnRadioHotCold1();
	afx_msg void OnRadioXLinLog2();
	afx_msg void OnRadioHotCold2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
