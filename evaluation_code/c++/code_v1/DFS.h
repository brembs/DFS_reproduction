// DFS.h : main header file for the DFS application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDFSApp:
// See DFS.cpp for the implementation of this class
//

class CDFSApp : public CWinApp
{
public:
	CDFSApp();
	CMultiDocTemplate* m_pDFS_Template;
	CMultiDocTemplate* m_pINF_Template;
	CMultiDocTemplate* m_pINF_TimeTrace_Template;
	CMultiDocTemplate* m_pINF_PerfIndex_Template;
	CMultiDocTemplate* m_pINF_DwellingTimes_Template;

	CMultiDocTemplate* m_pELS_Template;
	CMultiDocTemplate* m_pELS_PerfIndex_Template;
	CMultiDocTemplate* m_pELS_Dwellings_Template;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDFSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
// Implementation

	//{{AFX_MSG(CDFSApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
