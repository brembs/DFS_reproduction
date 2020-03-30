// ElsDoc.h : header file
//

#include "DfsExperiment.h"

/////////////////////////////////////////////////////////////////////////////
// CElsDoc document

class CElsDoc : public CDocument
{
protected:
	CElsDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CElsDoc)

// Attributes
public:

// Operations
public:
	double	m_PI_Mean[MAX_EXP_BLOCKS];	// Performance Index (PI) Mittelwerte
	double	m_PI_SEM[MAX_EXP_BLOCKS];	// Standardfehler der PI
	double	m_TI_Mean[MAX_EXP_BLOCKS];	// Torque Performance Index (PI) Mittelwerte
	double	m_TI_SEM[MAX_EXP_BLOCKS];	// Standardfehler der torque-PI
	PI_ARRAY	*m_PIArray;				// Array der PIs der Einzelexperimente
	
	double	m_FIh_Mean[MAX_EXP_BLOCKS];	// Fixation Index hot (FIh) Mittelwerte
	double	m_FIh_SEM[MAX_EXP_BLOCKS];	// Standardfehler der FIh
	double	m_FIc_Mean[MAX_EXP_BLOCKS];	// Fixation Index cold (FIc) Mittelwerte
	double	m_FIc_SEM[MAX_EXP_BLOCKS];	// Standardfehler der FIc

	int		m_nExpOk;					// Anzahl der gemittelten Einzelexp.
	int		m_nOfBlocks;				// Anzahl der Bloecke
	int		m_nHeat_0_180;				// Anzahl der bei 0/180 deg bestr. Exp.
	int		m_nHeat_90_270;				// Anzahl der bei 90/270 deg bestr. Exp.
	int		m_BlockType[MAX_EXP_BLOCKS];// Typ des jew. Blocks
	int		m_BlockDur[MAX_EXP_BLOCKS];	// Dauer des jew. Blocks in sec.
	int		m_BlockLen[MAX_EXP_BLOCKS];	// Anzahl der Samples des jew. Blocks 
	int		m_ExpDur;					// Dauer des gesamten Experiments
	BOOL	m_ScriptIsCompiled;
	CString			m_Script;			// String mit Experimentscript
	CStringArray	m_fileList;			// Liste der zu mittelnden Experimente
	CStringArray	m_pathList;			// Liste der Datenpfade

	BOOL ParseExpScript(CEdit *pEd);
	void CalcPIs(BOOL subPref, BOOL weightedInd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElsDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CElsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CElsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
