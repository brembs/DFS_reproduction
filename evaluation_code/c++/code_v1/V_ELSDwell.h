// V_ELSDwell.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewELSDwell form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CViewELSDwell : public CFormView
{
protected:
	CViewELSDwell();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewELSDwell)

// Form Data
public:
	//{{AFX_DATA(CViewELSDwell)
	enum { IDD = IDD_VIEW_ELS_DWELL };
	CButton	m_BTN_Test;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewELSDwell)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewELSDwell();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CViewELSDwell)
	afx_msg void OnButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
