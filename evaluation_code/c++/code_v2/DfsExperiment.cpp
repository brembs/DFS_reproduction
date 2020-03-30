// DfsExperiment.cpp : implementation file
//
#include "stdafx.h"
#include "math.h"
#include "DfsExperiment.h"
#include "array_f.h"


/////////////////////////////////////////////////////////////////////////////
// CExperiment commands

CExperiment::CExperiment()
{
	Reset();
	m_Trq = NULL;	
	m_Pos = NULL;	
}

CExperiment::~CExperiment()
{
	// Speicher fuer Positions- und Torquedaten freigeben
	if (m_Trq != NULL) 
	{
		delete m_Trq;
		m_Trq = NULL;
	}
	if (m_Pos != NULL) 
	{
		delete m_Pos;
		m_Pos = NULL;
	}
	Reset();
}

void CExperiment::Reset()
{
	int i;

	m_INF_Valid = FALSE;
	m_DTA_Valid = FALSE;
	m_ArenaType = ARENA_2048;
	m_ExpName = "";
	m_iHeat = 0;
	m_sHeat = "";
	m_Fly = "";
	m_Remarks = "";
	m_Date = "";
	m_Time = "";
	m_Year = 0;
	m_Month = 0;
	m_Day = 0;
	m_Hour = 0;
	m_Minute = 0;
	m_Second = 0;
	m_nOfBlocks = 0;
	for (i = 0; i < MAX_EXP_BLOCKS; i++)
	{
		m_BlockType[i] = 0;
		m_BlockLen[i] = 0;
		m_BlockDur[i] = 0;
		m_BlockEnd[i] = 0;
		m_PosHistogram[i].SetSize(0); 
		m_DwellTimeHot[i].SetSize(0); 
		m_DwellTimeCold[i].SetSize(0); 
		m_meanDwellHot[i] = 0;
		m_meanDwellCold[i] = 0;
		m_FIh[i] = 0.0;
		m_FIc[i] = 0.0;
	}
	m_ExpDur = 0;
	m_nOfAllRecords = 0;
	m_nOfData = 0;
	m_nOfFiles = 0;
	for (i = 0; i < MAX_EXP_FILES; i++)
	{
		m_nOfRecs[i] = 0;
	}
	m_PIPreference = 0.0;
	m_PI.SetSize(0);
	m_TIPreference = 0.0;
	m_TI.SetSize(0);
}

CString CExperiment::MakeFullName(CString exppath, CString expname)
{
	char path_buffer[MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	if (exppath.Right(1) != '\\') exppath += '\\';
	strcpy(path_buffer, exppath);
	_splitpath(path_buffer, drive, dir, NULL, NULL);
	expname = expname.Left(7) + 'a';
	strcpy(fname, expname);
	strcpy(ext, ".inf");
	_makepath(path_buffer, drive, dir, fname, ext);
	return path_buffer;
}

BOOL CExperiment::FindAndLoadExperiment(CStringArray *pathlist, CString *lastpath, CString *expname)
{
	int i, nPaths;
	CString s;

	nPaths = pathlist->GetSize();

	s = MakeFullName(*lastpath, *expname);
	if (!LoadExperiment(s))
	{
		for (i = 0; i < nPaths; i++)
		{
			s = MakeFullName(pathlist->GetAt(i), *expname);
			if (LoadExperiment(s))
			{
				*lastpath = pathlist->GetAt(i);
				return TRUE;
			}
		}
	}
	else return TRUE;

	return FALSE;
}

BOOL CExperiment::LoadExperiment(CString pathName)
{
	// INF Dateien einlesen:
	Reset();
	if (!Read_INF_Files(pathName)) 
		return FALSE;
	// Speicher fuer Indices
	m_PI.SetSize(m_nOfBlocks);
	m_TI.SetSize(m_nOfBlocks);
	// Daten einlesen
	if (!Read_DTA_Files(pathName)) 
	{
		SetDataSize(0);
		return FALSE;
	}

	
	return TRUE;
}

BOOL CExperiment::Read_INF_Files(CString pathName)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	CString Name, s;
	CFileException e;
	CFile f;
	InfoFile_raw_t inf[MAX_EXP_FILES];
	int i, n;
	char c;
	BOOL lastblock;

	m_iError = 0;
	m_INF_Valid = FALSE;
	memset(inf, 0, sizeof(InfoFile_raw_t) * MAX_EXP_FILES);

	_splitpath(pathName, drive, dir, fname, ext);
	Name = fname;
	m_ExpName = Name.Left(7);
	m_nOfData = 0;
	m_nOfAllRecords = 0;
	for (i = 0, c = 'a'; i < MAX_EXP_FILES; i++, c++)
	{
		Name = m_ExpName + c;
		_makepath(path_buffer, drive, dir, Name, "inf");
		if (f.Open(path_buffer, CFile::modeRead, &e)) 
		{
			f.Read(&inf[i], sizeof(InfoFile_raw_t));
			f.Close();
			// INF Datei ueberpruefen 
			if (inf[i].HeatedPattern != HEAT_0_180)
				if (inf[i].HeatedPattern != HEAT_90_270) 
					return FALSE;
//			if ((inf[i].nOfRecords * 1200) != inf[i].nOfData)	// doesn't work!!!
//				return FALSE;
			if (inf[i].nOfRecords < 0 || inf[i].nOfRecords > 54) 
				return FALSE;
			m_nOfData += inf[i].nOfData;
			m_nOfRecs[i] = inf[i].nOfRecords;
			m_nOfAllRecords += m_nOfRecs[i];
		}
		else break;
	}
	m_nOfFiles = inf[0].nOfFiles;
	if ((m_nOfFiles == 0) || (m_nOfFiles != i)) 
		return FALSE;
	
	m_iHeat = inf[0].HeatedPattern;
	if (m_iHeat == HEAT_0_180) m_sHeat = "0°/180°";
	else if  (m_iHeat == HEAT_90_270) m_sHeat = "90°/270°";
	else 
	{
		m_sHeat = "error";
		return FALSE;
	}

	s = inf[0].Fly.s;
	m_Fly = s.Left(inf[0].Fly.l);
	s = inf[0].Remarks.s;
	m_Remarks = s.Left(inf[0].Remarks.l);
	ConvDateTime(inf[0].Date.s, inf[0].DayTime.s);
	
	m_ExpDur = 0;
	m_nOfBlocks = 0;
	lastblock = FALSE;
	n = 0;
	for (i = 0; i < MAX_EXP_BLOCKS; i++)
	{
		s = inf[0].ExpType[i].s;
		s = s.Left(inf[0].ExpType[i].l);
		m_BlockType[i] = GetBlockType(s);
		if (m_BlockType[i] == EXPTYPE_END)
		{
			if (!lastblock) 
			{
				m_nOfBlocks = i;
				lastblock = TRUE;
			}
		}
		if (!lastblock)
		{
			m_BlockDur[i] = inf[0].Duration[i];
			m_ExpDur += m_BlockDur[i];
			m_BlockLen[i] = m_BlockDur[i] * SAMPLE_FREQ;
			n += m_BlockDur[i] * SAMPLE_FREQ;
			m_BlockEnd[i] = n;
		}
	}
	if (!lastblock) m_nOfBlocks = MAX_EXP_BLOCKS;
	
	m_INF_Valid = TRUE;
	return TRUE;
}

// Einlesen der Experimentdaten aus den Datenfiles. Die Daten
// sollten eigentlich in Records von 1200 Werten vorliegen. Das
// Originalprogramm wurde jedoch in Pascal programmiert und das
// entsprechende Array mit [0..1200] dimensioniert. Daher enthaelt
// ein Record 1201 Werte, von denen der erste unbenutzt ist und 
// ignoriert werden muss.
//
BOOL CExperiment::Read_DTA_Files(CString pathName)
{
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	
	short recbuf[PAS_RECSIZE];
	short *pTrq, *pPos;
	int nLargeValues;
	CString Name, s;
	CFileException e;
	CFile f;
	int i, j, k, recbytesize, n;
	char c;

	if (!m_INF_Valid) return FALSE;

	m_DTA_Valid = FALSE;

	n = m_nOfAllRecords * 1200;
	if (!SetDataSize(n)) return FALSE;

	_splitpath(pathName, drive, dir, fname, ext);
	
	Name = fname;
	m_ExpName = Name.Left(7);

	recbytesize = PAS_RECSIZE * sizeof(short);
	pPos = m_Pos;
	pTrq = m_Trq;
	for (i = 0, c = 'a'; i < m_nOfFiles; i++, c++)
	{
		Name = m_ExpName + c;
		_makepath(path_buffer, drive, dir, Name, "dta");
		if (!f.Open(path_buffer, CFile::modeRead, &e))
			return FALSE;
		
		for (j = 0; j < m_nOfRecs[i]; j++)
		{
			// reading Torque data:
			try
			{
				n = f.Read(recbuf, recbytesize);
			}
			catch (CException* e)
			{
				e->Delete();
			}
			if (n != recbytesize) 
			{
				f.Close();
				return FALSE;
			}
			for (k = 1; k < PAS_RECSIZE; k++) *pTrq++ = recbuf[k];

			// reading Position data:
			try
			{
				n = f.Read(recbuf, recbytesize);
			}
			catch (CException* e)
			{
				e->Delete();
			}
			if (n != recbytesize)
			{
				f.Close();
				return FALSE;
			}
			for (k = 1; k < PAS_RECSIZE; k++) *pPos++ = recbuf[k];
		}
		f.Close();
	}

	// Positionswertebereich automatisch bestimmen:
	nLargeValues = 0;
	for (i = 0; i < m_nOfData; i++)
	{
		if (m_Pos[i] > 1810 || m_Pos[i] < -1810) nLargeValues++;
	}
	if (nLargeValues > 10) m_ArenaType = ARENA_2048;
	else m_ArenaType = ARENA_2048;
// auskommentiert wegen sw-mode!!
/*	{
		m_ArenaType = ARENA_1800;
		// transform range of position values from +/1800 to +/- 2048:
	 	for (i = 0; i < m_nOfData; i++)
		{
			m_Pos[i] = m_Pos[i] * 2048 / 1800;
		}
	}
*/

	m_DTA_Valid = TRUE;
	return TRUE;
}

BOOL CExperiment::SetDataSize(int size)
{
	if (m_Pos != NULL) 
	{
		delete m_Pos;
		m_Pos = NULL;
	}
	if (m_Trq != NULL) 
	{
		delete m_Trq;
		m_Trq = NULL;
	}
	m_Pos = new short[size];
	if (m_Pos == NULL) 
		return FALSE;

	m_Trq = new short[size];
	if (m_Trq == NULL) 
	{
		delete m_Pos;
		m_Pos = NULL;
		return FALSE;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		m_Trq[i] = i;
		m_Pos[i] = i;
	}

	return TRUE;
}


int CExperiment::GetExpType(short pos)
{
	int i, n;

	if (pos < 0 || pos > m_nOfData) return EXPTYPE_UNDEF;
	n = 0;
	for (i = 0; i < m_nOfBlocks; i++)
	{
		n += m_BlockLen[i];
		if (pos < n) return m_BlockType[i];
	}
	return EXPTYPE_UNDEF;	// falls pos nicht innerhalb des Experiments
}

BOOL CExperiment::ConvDateTime(char *INFdate, char *INFtime)
{
	int i, z, nd;
	BOOL err, quit;
	char *p;
	char s[256];
	char *monE[] =
	{
		// english names of months
		"JAN", "FEB", "MAR", "APR", "MAI", "JUN",
		"JUL", "AUG", "SEP", "OCT", "NOV", "DEC",
		"",
	};
	char *monD[] =
	{
		// german names of months
		"Jan", "Feb", "M\x84r", "Apr", "Mai", "Jun",
		"Jul", "Aug", "Sep", "Okt", "Nov", "Dez",
		"",
	};
	m_Year = 0;
	m_Month = 0;
	m_Day = 0;
	m_Hour = 0;
	m_Minute = 0;
	m_Second = 0;

	p = INFdate;
	p[40] = '\0';
	err = FALSE;
	quit = FALSE;
	z = 0;
	while (!quit)
	{
		switch (z)
		{
			case 0:
				i = 0;
				if (isdigit(*p)) z = 1;
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 1:
			if (isdigit(*p)) s[i++] = *(p++);
			else
			if (*p == '\0') z = 99;
			else
			{
				s[i] = '\0';
				m_Day = atoi(s);
				i = 0;
				z = 2;
			}
			break;
			case 2:
				if (isalpha(*p)) z = 3;
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 3:
				if (isalpha(*p) || *p == (char)0x84) s[i++] = *(p++);
				else
				if (*p == '\0') z = 99;
				else
				{
					s[i] = '\0';
					for (i = 0; i < 12; i++) 
						if (strnicmp(s, monE[i], 3) == 0)
							break;
						else 
						if (memcmp(s, monD[i], 3) == 0)
							break;
					if (i < 12) m_Month = i + 1;
					else m_Month = 0;
					i = 0;
					z = 4;
				}
			break;
			case 4:
				if (isdigit(*p)) 
				{
					nd = 1;		// Stellen der Jahreszahl zaehlen, wg. Fehler in Datei
					z = 5;
				}
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 5:
				if (isdigit(*p) && nd < 5) 
				{
					nd++;		// Stellen der Jahreszahl zaehlen, wg. Fehler in Datei
					s[i++] = *(p++);
				}
				else
				{
					s[i] = '\0';
					m_Year = atoi(s);
					m_Date.Format("%02i.%02i.%04i", m_Day, m_Month, m_Year);
					s[0] = '\0';
					p = INFtime;
					p[40] = '\0';
					i = 0;
					z = 6;
				}
			break;
			case 6:		// Zeitstring einlesen
				if (isdigit(*p)) z = 7;
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 7:
				if (isdigit(*p)) s[i++] = *(p++);
				else
				if (*p == '\0') z = 99;
				else
				{
					s[i] = '\0';
					m_Hour = atoi(s);
					i = 0;
					z = 8;
				}
			break;
			case 8:
				if (isdigit(*p)) z = 9;
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 9:
			if (isdigit(*p)) s[i++] = *(p++);
			else
			if (*p == '\0') z = 99;
			else
			{
				s[i] = '\0';
				m_Minute = atoi(s);
				i = 0;
				z = 10;
			}
			break;
			case 10:
				if (isdigit(*p)) z = 11;
				else
				if (*p == '\0') z = 99;
				else p++;
			break;
			case 11:
				if (isdigit(*p)) s[i++] = *(p++);
				else
				if (*p == '\0') z = 99;
				else
				{
					s[i] = '\0';
					m_Second = atoi(s);
					m_Time.Format("%02i:%02i:%02i", m_Hour, m_Minute, m_Second);
					i = 0;
					z = 99;
				}
			break;
			case 99:
				quit = 1;
				break;
			default:
				quit = 1;
				err = TRUE;
			break;
		}
	}

	return err;
}

int CExperiment::GetSector(short pos)
{
	//  Sector berechnen, in dem ein bestimmter Positionswert liegt
	//  -45deg..  45deg = 0
	//   45deg.. 135deg = 1
	//  135deg..-135deg = 2
	// -135deg.. 135deg = 3

	if (pos >= -1536 && pos < -512) return 3;
	else if (pos >= -512 && pos < 512) return 0;
	else if (pos > 512 && pos < 1536) return 1;
	else return 2;
}

BOOL CExperiment::IsHeatedSector(int sector)
{
	if (m_iHeat == HEAT_0_180)
	{
		if (sector == 0 || sector == 2) return TRUE;
		else return FALSE;
	}
	else
	{
		if (sector == 1 || sector == 3) return TRUE;
		else return FALSE;
	}
	
}

BOOL CExperiment::CalcPerfIndices(BOOL subPref, BOOL artanh)
{
	int i, j, k, n, z, sector;
	int s_0_180, s_90_270;
	int s_0, s_90, s_180, s_270;
	double index;

	if (!IsValid()) return FALSE;

	z = 0;
	n = 0;
	k = 0;
	m_PIPreference = 0.0;
	for (i = 0; i < m_nOfBlocks; i++)
	{
		s_0_180 = 0;
		s_90_270 = 0;
		s_0 = s_90 = s_180 = s_270 = 0;
		for (j = 0; j < m_BlockLen[i]; j++, k++)
		{
			switch (sector = GetSector(m_Pos[k]))
			{
				case 0: 
					s_0++;
					break;
				case 1: 
					s_90++;
					break;
				case 2: 
					s_180++;
					break;
				case 3: 
					s_270++;
					break;
			}			
		}
		s_0_180 = s_0 + s_180;
		s_90_270 = s_90 + s_270;
		index = (double)(s_0_180 - s_90_270) / (double)j;
		if (m_iHeat == HEAT_0_180) index *= -1.0;

		if (artanh) index = TransformArtanh(index);

		m_PI[i] = index;
		if (z == 0)
		{
			if (m_BlockType[i] == EXPTYPE_TEST) 
			{
				n++;
				m_PIPreference += index;
			}
			else z = 1;
		}
	}
	if (n > 0) m_PIPreference /= n;
	if (subPref)
	{
		for (i = 0; i < m_nOfBlocks; i++) 
			m_PI[i] -= m_PIPreference;
	}
	return TRUE;
}

void CExperiment::CalcFixationIndices()
{
	int block, pos, sec, k;
	int hotMid, hotEdge, coldMid, coldEdge;
	double hotSum, coldSum;

	for (block = 0, pos = 0; block < m_nOfBlocks; block++)
	{
		hotMid = 0;
		hotEdge = 0;
		coldMid = 0;
		coldEdge = 0;
		m_FIh[block] = 0.0;
		m_FIc[block] = 0.0;
		for (k = 0; k < m_BlockLen[block]; k++, pos++)
		{
			sec = (m_Pos[pos] + 2048) / 256;
			if (m_iHeat == HEAT_0_180)
			{
				switch (sec)
				{
					// centers of reinforced quadrants:
					case 0: case 7: case 8: case 15:
						hotMid++;
						break;
					// borders of reinforced quadrants:
					case 1: case 6: case 9: case 14:
						hotEdge++;
						break;
					// centers of not reinforced quadrants:
					case 3: case 4: case 11: case 12:
						coldMid++;
						break;
					// borders of not reinforced quadrants:
					case 2: case 5: case 10: case 13:
						coldEdge++;
						break;
					default:
						break;
				}
			}
			else
			{
				switch (sec)
				{
					// centers of non reinforced quadrants:
					case 0: case 7: case 8: case 15:
						coldMid++;
						break;
					// borders of non reinforced quadrants:
					case 1: case 6: case 9: case 14:
						coldEdge++;
						break;
					// centers of reinforced quadrants:
					case 3: case 4: case 11: case 12:
						hotMid++;
						break;
					// borders of reinforced quadrants:
					case 2: case 5: case 10: case 13:
						hotEdge++;
						break;
					default:
						break;
				}
			}
		}
 		hotSum = hotMid + hotEdge;
		coldSum = coldMid + coldEdge;
		if (hotSum == 0.0) m_FIh[block] = 0.0;
		else m_FIh[block] = (hotMid - hotEdge) / hotSum;
		if (coldSum == 0.0) m_FIc[block] = 0.0;
		else m_FIc[block] = (coldMid - coldEdge) / coldSum;
	}
}

BOOL CExperiment::CalcTorqueIndices(BOOL subPref, BOOL artanh)
{
	int i, j, k, n, z;
	int loTorque,hiTorque;
	double TorqueIndex;

	if (!IsValid()) return FALSE;

	z = 0;
	n = 0;
	k = 0;
	m_TIPreference = 0.0;
	for (i = 0; i < m_nOfBlocks; i++)
	{
		loTorque = 0;
		hiTorque = 0;
		for (j = 0; j < m_BlockLen[i]; j++, k++)
		{
			if (m_Trq[k] < 0) loTorque++; else hiTorque++;
		
		}
		TorqueIndex = (double)(loTorque - hiTorque) / (double)j;
		if (m_iHeat == HEAT_0_180) TorqueIndex *= -1.0;

		if (artanh) TorqueIndex = TransformArtanh(TorqueIndex);

		m_TI[i] = TorqueIndex;
		if (z == 0)
		{
			if (m_BlockType[i] == EXPTYPE_TEST) 
			{
				n++;
				m_TIPreference += TorqueIndex;
			}
			else z = 1;
		}
	}
	if (n > 0) m_TIPreference /= n;
	if (subPref)
	{
		for (i = 0; i < m_nOfBlocks; i++) 
			m_TI[i] -= m_TIPreference;
	}
	return TRUE;
}


BOOL CExperiment::CalcDwellingTimes(int samplesPerUnit)
{
	int i, j, k, size; 
	int sector, oldsector, dur;
	int thot, tcold, durhot, durcold, nhot, ncold;
	double f;
	BOOL ok;

	if (!IsValid()) return FALSE;

	m_DwellUnit = (double)samplesPerUnit / SAMPLE_FREQ;
	ok = TRUE;
	for (i = 0; i < m_nOfBlocks; i++)
	{
		size = m_BlockLen[i] / samplesPerUnit;
		m_DwellTimeHot[i].SetSize(size);
		m_DwellTimeCold[i].SetSize(size);
		if ((m_DwellTimeHot[i].GetSize() != size) ||
			(m_DwellTimeCold[i].GetSize() != size)) 
		{
			for (j = 0; j < m_nOfBlocks; j++) 
			{
				m_DwellTimeHot[j].SetSize(0);
				m_DwellTimeCold[j].SetSize(0);
			}
			return FALSE;
		}
		else
		{
			for (j = 0; j < size; j++) 
			{
				m_DwellTimeHot[i][j] = 0;
				m_DwellTimeCold[i][j] = 0;
			}
		}
	}

	for (i = 0, k = 0; i < m_nOfBlocks; i++)
	{
		thot = 0; tcold = 0;
		durhot = 0; durcold = 0;
		nhot = 0; ncold = 0;
		size = m_BlockLen[i] / samplesPerUnit;
		oldsector = GetSector(m_Pos[k]);
		if (IsHeatedSector(oldsector)) thot++;
		else tcold++;
		k++;
		dur = 1;
		for (j = 1; j < m_BlockLen[i]; j++, k++)
		{
			sector = GetSector(m_Pos[k]);
			if (IsHeatedSector(sector)) thot++;
			else tcold++;
			if (sector == oldsector) dur++;
			else
			{
				if (IsHeatedSector(oldsector)) durhot += dur;
				else durcold += dur;
				f = ((double)dur - 0.1) / samplesPerUnit;
				dur = (int)f;
				if (IsHeatedSector(oldsector)) 
				{
					m_DwellTimeHot[i][dur]++;
					nhot++;
				}
				else
				{
					m_DwellTimeCold[i][dur]++;
					ncold++;
				}
				dur = 1;
			}
			oldsector = sector;
		}
		if (IsHeatedSector(oldsector)) durhot += dur;
		else durcold += dur;
		dur /= samplesPerUnit;
		if (IsHeatedSector(oldsector)) 
		{
			m_DwellTimeHot[i][dur]++;
			nhot++;
		}
		else 
		{
			m_DwellTimeCold[i][dur]++;
			ncold++;
		}
		if (nhot > 0) 
			m_meanDwellHot[i] = (double)durhot / nhot / SAMPLE_FREQ;
		else m_meanDwellHot[i] = 0.0;
		if (ncold > 0) 
			m_meanDwellCold[i] = (double)durcold / ncold / SAMPLE_FREQ;
		else m_meanDwellCold[i] = 0.0;
	}
	return TRUE;
}

int	GetBlockType(CString typeString)
{
	if (typeString == "test") return EXPTYPE_TEST;
	else
	if (typeString == " tr ") return EXPTYPE_TRAIN;
	else
	if (typeString == "repl") return EXPTYPE_REPL;
	else
	if (typeString == "    ") return EXPTYPE_END;
	else return EXPTYPE_UNDEF;
}

CString GetBlockType(int blockType)
{
	CString s;

	if (blockType == EXPTYPE_TEST) s = "Test";
	else
	if (blockType == EXPTYPE_TRAIN) s = "Training";
	else
	if (blockType == EXPTYPE_REPL) s = "Replay";
	else
	if (blockType == EXPTYPE_END) s = "End";
	else s = "?";

	return s;
}

double TransformArtanh(double val)
{
	// Gewichtung mit area tanh, Begrenzung der Ausgangswerte
	// auf +/- 0.99991 begrenzt gewichtete Indices auf +/- 5.0
	double f;
	if (val > .99991) val = .99991;
	if (val < -.99991) val = -.99991;
	f = log((1.0 + val) / (1.0 - val)) / 2.0;
	return f;
}