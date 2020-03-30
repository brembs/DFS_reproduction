// V_TimeTr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewTimeTrace form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewTimeTrace : public CFormView
{
protected:
	CViewTimeTrace();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTimeTrace)

// Form Data
public:
	CDocument *m_pDoc;
	//{{AFX_DATA(CViewTimeTrace)
	enum { IDD = IDD_VIEW_TIMETRACE };
	CScrollBar	m_SB_Time;
	BOOL	m_CHECK_PositionTrace;
	BOOL	m_CHECK_TorqueTrace;
	int		m_ED_Debug;
	//}}AFX_DATA

	int		m_SB_TimePos;
	int		m_SB_TimeLine;
	int		m_SB_TimePage;
	int		m_SB_TimeMin;
	int		m_SB_TimeMax;

	int		m_PosRange;
	int		m_MaxPosValue;
	int		m_MinPosValue;

// Attributes
public:
	CRect	m_TraceRect;
	CDC		*m_pTraceDC;
	COLORREF	m_PosTraceColor;
	COLORREF	m_TrqTraceColor;


// Operations
public:
	void DrawAxes();
	void DrawScales();
	void DrawExpType();
	void DrawTrace();
	void DrawColorBox();
	void GetDiagramFrame();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTimeTrace)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewTimeTrace();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewTimeTrace)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckPositionTrace();
	afx_msg void OnCheckTorqueTrace();
	afx_msg void OnUpdateViewTimetraces(CCmdUI* pCmdUI);
	afx_msg void OnPostraceColor();
	afx_msg void OnTrqtraceColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
