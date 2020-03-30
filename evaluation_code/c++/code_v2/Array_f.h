#ifndef __ARRAY_F_H__
#define __ARRAY_F_H__

/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//CObject
	// Arrays
	class CFloatArray;			// array of float
	class CDoubleArray;			// array of double

////////////////////////////////////////////////////////////////////////////
// CFloatArray
class CFloatArray : public CObject
{

//	DECLARE_DYNAMIC(CFloatArray)
public:

// Construction
	CFloatArray();

// Attributes
	int GetSize() const	{ return m_nSize; }
	int GetUpperBound() const { return m_nSize-1; }
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll() { SetSize(0); }

	// Accessing elements
	float GetAt(int nIndex) const 
	{
		return m_pData[nIndex]; 
	}
	void SetAt(int nIndex, float newElement)
	{
		m_pData[nIndex] = newElement;
	}
	float& ElementAt(int nIndex)
	{
		return m_pData[nIndex];
	}

	// Direct Access to the element data (may return NULL)
	const float* GetData() const { return (const float*)m_pData; }
	float* GetData() { return (float*)m_pData; }

	// Potentially growing the array
	void SetAtGrow(int nIndex, float newElement);
	int Add(float newElement)
	{
		int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex;
	}
	int Append(const CFloatArray& src);
	void Copy(const CFloatArray& src);

	// overloaded operator helpers
	float operator[](int nIndex) const { return GetAt(nIndex); }
	float& operator[](int nIndex) { return ElementAt(nIndex); }


	// Operations that move elements around
	void InsertAt(int nIndex, float newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CFloatArray* pNewArray);

// Implementation
protected:
	float* m_pData;  // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CFloatArray();

protected:
	// local typedefs for class templates
	typedef float BASE_TYPE;
	typedef float BASE_ARG_TYPE;
};

/////////////////////////////////////////////////////////////////////////////
// CDoubleArray
class CDoubleArray : public CObject
{

//	DECLARE_DYNAMIC(CDoubleArray)
public:

// Construction
	CDoubleArray();

// Attributes
	int GetSize() const	{ return m_nSize; }
	int GetUpperBound() const { return m_nSize-1; }
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll() { SetSize(0); }

	// Accessing elements
	double GetAt(int nIndex) const 
	{
		return m_pData[nIndex]; 
	}
	void SetAt(int nIndex, double newElement)
	{
		m_pData[nIndex] = newElement;
	}
	double& ElementAt(int nIndex)
	{
		return m_pData[nIndex];
	}

	// Direct Access to the element data (may return NULL)
	const double* GetData() const { return (const double*)m_pData; }
	double* GetData() { return (double*)m_pData; }

	// Potentially growing the array
	void SetAtGrow(int nIndex, double newElement);
	int Add(double newElement)
	{
		int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex;
	}
	int Append(const CDoubleArray& src);
	void Copy(const CDoubleArray& src);

	// overloaded operator helpers
	double operator[](int nIndex) const { return GetAt(nIndex); }
	double& operator[](int nIndex) { return ElementAt(nIndex); }


	// Operations that move elements around
	void InsertAt(int nIndex, double newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CDoubleArray* pNewArray);

// Implementation
protected:
	double* m_pData; // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	~CDoubleArray();

protected:
	// local typedefs for class templates
	typedef double BASE_TYPE;
	typedef double BASE_ARG_TYPE;
};

#endif //!__ARRAY_F_H__

/////////////////////////////////////////////////////////////////////////////
