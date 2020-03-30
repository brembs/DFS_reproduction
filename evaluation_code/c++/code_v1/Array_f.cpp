
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
//
// Implementation of parameterized Array
//
/////////////////////////////////////////////////////////////////////////////
// NOTE: we allocate an array of 'm_nMaxSize' elements, but only
//  the current size 'm_nSize' contains properly constructed
//  objects.

#include "stdafx.h"
#include "array_f.h"

/////////////////////////////////////////////////////////////////////////////
// CFloatArray

CFloatArray::CFloatArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CFloatArray::~CFloatArray()
{
	delete[] (BYTE*)m_pData;
}

void CFloatArray::SetSize(int nNewSize, int nGrowBy)
{
	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
		m_pData = (float*) new BYTE[nNewSize * sizeof(float)];
		memset(m_pData, 0, nNewSize * sizeof(float));  // zero fill
		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(float));
		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		float* pNewData = (float*) new BYTE[nNewMax * sizeof(float)];

		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(float));

		// construct remaining elements
		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(float));

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CFloatArray::Append(const CFloatArray& src)
{
	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

	memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(float));

	return nOldSize;
}

void CFloatArray::Copy(const CFloatArray& src)
{
	SetSize(src.m_nSize);
	memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(float));
}

void CFloatArray::FreeExtra()
{
	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
		float* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (float*) new BYTE[m_nSize * sizeof(float)];
			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(float));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CFloatArray::SetAtGrow(int nIndex, float newElement)
{
	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}

void CFloatArray::InsertAt(int nIndex, float newElement, int nCount)
{
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size
		// shift old data up to fill gap
		memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
			(nOldSize-nIndex) * sizeof(float));

		// re-init slots we copied from

		memset(&m_pData[nIndex], 0, nCount * sizeof(float));

	}

	// insert new value in the gap
	while (nCount--) m_pData[nIndex++] = newElement;
}

void CFloatArray::RemoveAt(int nIndex, int nCount)
{
	// just remove a range
	int nMoveCount = m_nSize - (nIndex + nCount);

	if (nMoveCount)
		memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
			nMoveCount * sizeof(float));
	m_nSize -= nCount;
}

void CFloatArray::InsertAt(int nStartIndex, CFloatArray* pNewArray)
{
	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDoubleArray

CDoubleArray::CDoubleArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

CDoubleArray::~CDoubleArray()
{
	delete[] (BYTE*)m_pData;
}

void CDoubleArray::SetSize(int nNewSize, int nGrowBy)
{
	if (nGrowBy != -1)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		delete[] (BYTE*)m_pData;
		m_pData = NULL;
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create one with exact size
		m_pData = (double*) new BYTE[nNewSize * sizeof(double)];
		memset(m_pData, 0, nNewSize * sizeof(double));  // zero fill
		m_nSize = m_nMaxSize = nNewSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(double));
		}

		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow array
		int nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = min(1024, max(4, m_nSize / 8));
		}
		int nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		double* pNewData = (double*) new BYTE[nNewMax * sizeof(double)];

		// copy new data from old
		memcpy(pNewData, m_pData, m_nSize * sizeof(double));

		// construct remaining elements
		memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(double));

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

int CDoubleArray::Append(const CDoubleArray& src)
{
	int nOldSize = m_nSize;
	SetSize(m_nSize + src.m_nSize);

	memcpy(m_pData + nOldSize, src.m_pData, src.m_nSize * sizeof(double));

	return nOldSize;
}

void CDoubleArray::Copy(const CDoubleArray& src)
{
	SetSize(src.m_nSize);
	memcpy(m_pData, src.m_pData, src.m_nSize * sizeof(double));
}

void CDoubleArray::FreeExtra()
{
	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
		double* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (double*) new BYTE[m_nSize * sizeof(double)];
			// copy new data from old
			memcpy(pNewData, m_pData, m_nSize * sizeof(double));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

/////////////////////////////////////////////////////////////////////////////

void CDoubleArray::SetAtGrow(int nIndex, double newElement)
{
	if (nIndex >= m_nSize)
		SetSize(nIndex+1);
	m_pData[nIndex] = newElement;
}

void CDoubleArray::InsertAt(int nIndex, double newElement, int nCount)
{
	if (nIndex >= m_nSize)
	{
		// adding after the end of the array
		SetSize(nIndex + nCount);  // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the array
		int nOldSize = m_nSize;
		SetSize(m_nSize + nCount);  // grow it to new size
		// shift old data up to fill gap
		memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
			(nOldSize-nIndex) * sizeof(double));

		// re-init slots we copied from

		memset(&m_pData[nIndex], 0, nCount * sizeof(double));

	}

	// insert new value in the gap
	while (nCount--) m_pData[nIndex++] = newElement;
}

void CDoubleArray::RemoveAt(int nIndex, int nCount)
{
	// just remove a range
	int nMoveCount = m_nSize - (nIndex + nCount);

	if (nMoveCount)
		memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
			nMoveCount * sizeof(double));
	m_nSize -= nCount;
}

void CDoubleArray::InsertAt(int nStartIndex, CDoubleArray* pNewArray)
{
	if (pNewArray->GetSize() > 0)
	{
		InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
		for (int i = 0; i < pNewArray->GetSize(); i++)
			SetAt(nStartIndex + i, pNewArray->GetAt(i));
	}
}

/////////////////////////////////////////////////////////////////////////////
