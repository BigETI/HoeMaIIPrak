#ifndef __CMYMATRIX_H__
#	define __CMYMATRIX_H__
#	include "CMyVektor.h"

class CMyMatrix
{
private:
	std::vector<CMyVektor> m;
public:
	CMyMatrix();
	CMyMatrix(const CMyMatrix &mat);
	CMyMatrix(double **mat, size_t x_sz, size_t y_sz);
	~CMyMatrix();

	CMyMatrix & operator = (const CMyMatrix &mat);
	CMyVektor & operator[](size_t index);
	CMyMatrix & operator += (CMyMatrix mat);
	CMyMatrix & operator *= (double lambda);
	CMyMatrix & operator /= (double lambda);
	CMyMatrix operator + (const CMyMatrix &mat);
	CMyMatrix operator * (double lambda);
	CMyVektor operator * (CMyVektor vect);
	CMyMatrix operator / (double lambda);

	CMyMatrix inverse();
	std::pair<size_t, size_t> getSize();
};

#endif
