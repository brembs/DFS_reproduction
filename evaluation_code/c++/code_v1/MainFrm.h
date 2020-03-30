// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	int m_nTimePaneNo;
	CMainFrame();

// Attributes
public:

// Operations
public:
	void CreateOrActivateFrame(CDocTemplate* pTemplate,
		CRuntimeClass* pViewClass);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewTimetraces();
	afx_msg void OnViewPerformanceindices();
	afx_msg void OnViewExperimentoverview();
	afx_msg void OnViewMultiExpLstOv();
	afx_msg void OnViewDwellingTimes();
	afx_msg void OnViewELSDwellings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
};

/////////////////////////////////////////////////////////////////////////////
