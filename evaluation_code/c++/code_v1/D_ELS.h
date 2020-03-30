// D_ELS.h : header file
//

#include "exprimnt.h"

/////////////////////////////////////////////////////////////////////////////
// CDocELS document

class CDocELS : public CDocument
{
protected:
	CDocELS();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDocELS)

// Attributes
public:

// Operations
public:

	double	m_perfIndex[MAX_BLOCKS];// Mittelwerte
	double	m_SEM[MAX_BLOCKS];		// Standardfehler der Mittelwerte
	int		m_nOfBlocks;			// Anzahl der Bloecke
	int		m_nHeat_0_180;			// Anzahl der bei 0/180 deg bestr. Exp.
	int		m_nHeat_90_270;			// Anzahl der bei 90/270 deg bestr. Exp.
	int		m_BlockType[MAX_BLOCKS];// Typ des jew. Blocks
	int		m_BlockDur[MAX_BLOCKS];	// Dauer des jew. Blocks in sec.
	int		m_BlockLen[MAX_BLOCKS];	// Anzahl der Samples des jew. Blocks 
	int		m_ExpDur;				// Dauer des gesamten Experiments
	CStringArray	m_fileList;		// Liste der zu mittelnden Experimente
	CStringArray	m_pathList;		// Liste der Datenpfade

	BOOL ParseExpScript(CEdit *pEd);
	BOOL ParseExpScript();
	void CalcIndices(BOOL subPref, BOOL weightedInd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocELS)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDocELS();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocELS)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
