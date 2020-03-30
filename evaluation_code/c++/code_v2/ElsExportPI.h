// ElsExportPI.h : header file
//

#include "DfsExperiment.h"

/////////////////////////////////////////////////////////////////////////////
// CElsExportPI dialog

class CElsExportPI : public CDialog
{
// Construction
public:
	CElsExportPI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElsExportPI)
	enum { IDD = IDD_EXPORT_PI };
	CButton	m_BUTTON_Export;
	CButton	m_BUTTON_ExportPI;
	CString	m_EDIT_FilePath;
	int		m_RADIO_ExportFormat;
	CString	m_STATIC_ExportMessage;
	//}}AFX_DATA
	
	CDocument	*m_pDoc;
	char m_drive[_MAX_DRIVE];
	char m_dir[_MAX_DIR];
	char m_fname[_MAX_FNAME];
	char m_ext[_MAX_EXT];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsExportPI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ExportASCII(void);
	void ExportStat(void);

	// Generated message map functions
	//{{AFX_MSG(CElsExportPI)
	afx_msg void OnButtonExportDestination();
	afx_msg void OnStartExport();
	afx_msg void OnExportFormat();
	afx_msg void OnExportFormat2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CElsExportFI dialog

class CElsExportFI : public CDialog
{
// Construction
public:
	CElsExportFI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElsExportFI)
	enum { IDD = IDD_EXPORT_FI };
	CButton	m_BUTTON_Export;
	CButton	m_BUTTON_ExportFormat;
	CString	m_EDIT_FilePath;
	int		m_RADIO_ExportFormat;
	CString	m_STATIC_ExportMessage;
	//}}AFX_DATA

	CDocument	*m_pDoc;
	char m_drive[_MAX_DRIVE];
	char m_dir[_MAX_DIR];
	char m_fname[_MAX_FNAME];
	char m_ext[_MAX_EXT];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsExportFI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ExportASCII(void);
	void ExportStat(void);

	// Generated message map functions
	//{{AFX_MSG(CElsExportFI)
	afx_msg void OnStartExport();
	afx_msg void OnButtonExportDestination();
	virtual BOOL OnInitDialog();
	afx_msg void OnExportFormat();
	afx_msg void OnExportFormat2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CElsExportTI dialog

class CElsExportTI : public CDialog
{
// Construction
public:
	CElsExportTI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CElsExportTI)
	enum { IDD = IDD_EXPORT_TI };
	CButton	m_BUTTON_Export;
	CButton	m_BUTTON_ExportTI;
	CString	m_EDIT_FilePath;
	int		m_RADIO_ExportFormat;
	CString	m_STATIC_ExportMessage;
	//}}AFX_DATA
	
	CDocument	*m_pDoc;
	char m_drive[_MAX_DRIVE];
	char m_dir[_MAX_DIR];
	char m_fname[_MAX_FNAME];
	char m_ext[_MAX_EXT];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsExportTI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ExportASCII(void);
	void ExportStat(void);

	// Generated message map functions
	//{{AFX_MSG(CElsExportTI)
	afx_msg void OnButtonExportDestination();
	afx_msg void OnStartExport();
	afx_msg void OnExportFormat();
	afx_msg void OnExportFormat2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
