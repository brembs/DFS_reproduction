// V_ELS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewELS view

class CViewELS : public CEditView
{
protected:
	CViewELS();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewELS)

	CFont m_screenFont;

// Attributes
public:

// Operations
public:
	int ParseExpScript();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewELS)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewELS();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewELS)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewSetFont();
	afx_msg void OnFileExportIndices();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
