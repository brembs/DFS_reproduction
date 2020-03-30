// This code is a part of the NanoSoft NSViews C++ Library.
// Copyright (C) 1996 NanoSoft Corporation. All rights reserved.

class CDfsDoc : public CDocument
{
protected: // create from serialization only
	CDfsDoc();
	DECLARE_DYNCREATE(CDfsDoc)

// Attributes
public:
/*
	CString	m_csEdit1;
	CString	m_csList1;
	CString	m_csCombo1;
	CString	m_csCombo2;
	CString	m_csCombo3;
	CString m_csTab2Edit1;
	CString m_csIntroduction;
*/
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDfsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDfsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDfsDoc)
	afx_msg void OnDemoFlexibleFormView();
	afx_msg void OnDemoFlexiblePropertySheet();
	afx_msg void OnDemoFlexiblePropertySheetView();
	afx_msg void OnDemoIntroduction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
