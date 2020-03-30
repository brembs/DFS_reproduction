// D_INF.h : header file
//

#if !defined _EXPRIMNT_H_
#include "exprimnt.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocINF document

class CDocINF : public CDocument
{
protected:
	CDocINF();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDocINF)

// Attributes
public:
	CString		m_ExpName;
	CExperiment	m_Experiment;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocINF)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);


// Implementation
public:
	virtual ~CDocINF();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	



	// Generated message map functions
protected:
	//{{AFX_MSG(CDocINF)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
