// Exprimnt.h : header file
//

#include "array_f.h"

#if !defined _EXPRIMNT_H_
#define _EXPRIMNT_H_

/////////////////////////////////////////////////////////////////////////////
//

#define EXPTYPE_END		0
#define EXPTYPE_TEST	1
#define EXPTYPE_TRAIN	2
#define EXPTYPE_REPL	3
#define EXPTYPE_UNDEF	99

#define HEAT_0_180		0xC2	/* 194 */
#define HEAT_90_270		0xC1	/* 193 */

#define	MAX_FILES		5
#define MAX_BLOCKS		15

#define SAMPLE_FREQ		20	/* Hz */

#define ARENA_2048		1	/* Arena mit Wertebereich +/- 2048 */
#define ARENA_1800		2	/* Arena mit Wertebereich +/- 1800 */

// string definitions to convert pascal strings into c strings
typedef struct { char l; char s[4]; } 	str4;
typedef struct { char l; char s[20];} 	str20;
typedef struct { char l; char s[40];}	str40;
typedef struct { char l; char s[80];}	str80;

// INF file raw data structure
typedef struct
{
	unsigned char	HeatedPattern;
	str20			Fly;
	str40			Date;
	str40			DayTime;
	str80			Remarks;
	str4			ExpType[MAX_BLOCKS];
	short			Duration[MAX_BLOCKS];
	short			nOfRecords;
	short			nOfData;
	short			nOfFiles;
}	InfoFile_raw_t;


/////////////////////////////////////////////////////////////////////////////
// CExperiment

class CExperiment : public CObject
{
public:
	CExperiment();

// Attributes
public:
	int		m_iError;
	CString	m_sError;

	// INF Daten
	BOOL	m_INF_Valid;	// INF-Dateien vollstaendig und fehlerfrei 
							//  eingelesen, Plausibilitaetspruefung ok 
	BOOL	m_DTA_Valid;	// DTA-Dateien vollstaendig und fehlerfrei
							//  eingelesen, Plausibilitaetspruefung ok
	int		m_ArenaType;	// Positionswerte von +/-2047 bzw. +/-1800
	CString	m_ExpName;		// die ersten 7 Zeichen des Dateinamerns des Exp.
	int		m_iHeat;		// bestrafte Sektoren als int
	CString	m_sHeat;		// bestrafte Sektoren als string
	CString	m_Fly;			// Fliege
	CString	m_Remarks;		// Bemerkungen
	CString	m_Date;			// Datum als string
	CString	m_Time;			// Zeit als string
	int		m_Year;			// Jahr
	int		m_Month;		// Monat
	int		m_Day;			// Tag
	int		m_Hour;			// Stunde
	int		m_Minute;		// Minute
	int		m_Second;		// Sekunde
	short	m_nOfBlocks;	// Anzahl der Bloecke
	short	m_BlockType[MAX_BLOCKS];// Typ des jew. Blocks
	int		m_BlockDur[MAX_BLOCKS];	// Dauer des jew. Blocks in sec.
	int		m_BlockLen[MAX_BLOCKS];	// Anzahl der Samples des jew. Blocks 
	int		m_BlockEnd[MAX_BLOCKS];	// Endposition des jew. Blocks 
	int		m_ExpDur;		// Dauer des gesamten Experiments
	int		m_nOfAllRecords;// Anzahl der Records des ges. Exp.
	int		m_nOfData;		// Anzahl der Samples des ges. Exp.
	int		m_nOfFiles;		// Anzahl der Dateien des ges. Exp.
	int		m_nOfRecs[5];	// Anzahl der Records pro Datei
	
	// DTA Daten
	short	*m_Trq;			// Drehmomentdaten 
	short	*m_Pos;			// Positionsdaten
	
	// berechnete Indizees und Histogramme
	double			m_PrefIndex;				// Preference Index
	CDoubleArray	m_PerfIndex;				// Performance Indices
	CWordArray		m_PosHistogram[MAX_BLOCKS];	// Position Histograms
	CWordArray		m_DwellTimeHot[MAX_BLOCKS];	// Dwelling Times hot sectors
	CWordArray		m_DwellTimeCold[MAX_BLOCKS];// Dwelling Times cold sectors
	double			m_DwellUnit;				// Kleinste Einheit f. Berechnung von
												//  Aufenthaltsdauern
	double			m_meanDwellHot[MAX_BLOCKS];	// mittlere Aufenthaltsdauer hot 
	double			m_meanDwellCold[MAX_BLOCKS];// mittlere Aufenthaltsdauer cold 

// Operations
public:

// Overrides

// Implementation
public:
	virtual ~CExperiment();
	void	Reset();
	CString MakeFullName(CString exppath, CString expname);
	BOOL	Read_INF_Files(CString pathName);
	BOOL	Read_DTA_Files(CString pathName);
	BOOL	LoadExperiment(CString pathName);
	BOOL	IsValid() { return (m_INF_Valid && m_DTA_Valid); }
	BOOL	SetDataSize(int size);
	BOOL	ConvDateTime(char *INFdate, char *INFtime);
	int		GetExpType(short pos);
	int		GetSector(short pos);
	BOOL	IsHeatedSector(int sector);
	BOOL	CalcPerfIndices(BOOL subPref = FALSE, BOOL weightedInd = FALSE);
	BOOL	CalcPosHistograms();
	BOOL	CalcDwellingTimes(int samplesPerUnit);
};

int	GetBlockType(CString typeString);
CString	GetBlockType(int blockType);

#endif	// _EXPRIMNT_H_