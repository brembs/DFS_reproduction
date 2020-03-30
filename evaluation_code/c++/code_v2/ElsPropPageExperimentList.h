// ElsPropPageExperimentList.h : header file
//
#include "NSViews/NSFlexPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// CElsPropPageExperimentList dialog

class CElsPropPageExperimentList : public CNSFlexPropertyPage
{
	DECLARE_DYNCREATE(CElsPropPageExperimentList)

// Construction
public:
	CElsPropPageExperimentList();
	~CElsPropPageExperimentList();

	
// Dialog Data
	//{{AFX_DATA(CElsPropPageExperimentList)
	enum { IDD = IDD_PP_ELS_EXPERIMENTLIST };
	CEdit	m_EDIT_ElsExperimentScript;
	CListBox	m_LIST_ElsExperimentNames;
	UINT	m_EDIT_ElsNOfFiles;
	UINT	m_EDIT_ElsN0180;
	UINT	m_EDIT_ElsN90270;
	UINT	m_EDIT_ElsFilesOk;
	CString	m_STATIC_ElsPP1Message;
	//}}AFX_DATA

private:
	CFont	m_scriptFont;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CElsPropPageExperimentList)
	public:
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

// Implementation
protected:

	void UpdateDocumentData();
	
	// Generated message map functions
	//{{AFX_MSG(CElsPropPageExperimentList)
	afx_msg void OnChangeEditElsExperimentScript();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCompileScript();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
