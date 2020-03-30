// DgExpInd.h : header file
//
//#include "D_ELS.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgExportIndices dialog

class CDlgExportIndices : public CDialog
{
// Construction
public:
	CDlgExportIndices(CWnd* pParent = NULL);   // standard constructor

	CDocument	*m_pDoc;
	CEdit		*m_pEd;
	
	// Dialog Data
	//{{AFX_DATA(CDlgExportIndices)
	enum { IDD = IDD_EXPORT_INDICES };
	CStatic	m_STATIC_Message;
	BOOL	m_CHECK_WeightAreaTanh;
	int		m_RADIO_ExportFormat;
	CString	m_ED_ExportFilePath;
	BOOL	m_CHECK_ExportPerformance;
	BOOL	m_CHECK_ExportDwellings;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExportIndices)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExportIndices)
	virtual BOOL OnInitDialog();
	afx_msg void OnStartExport();
	afx_msg void OnBtnExportDestination();
	afx_msg void OnWeightAreaTanh();
	afx_msg void OnExportDwellings();
	afx_msg void OnExportPerformance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
