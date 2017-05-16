#include "CMyMatrix.h"
#include <string>

CMyMatrix::CMyMatrix()
{
	m.resize(1);
}

CMyMatrix::CMyMatrix(const CMyMatrix & mat) : m(mat.m)
{
	//
}


CMyMatrix::CMyMatrix(double ** mat, size_t x_sz, size_t y_sz)
{
	m.resize(x_sz);
	for (size_t i(0U), j; i != x_sz; i++)
	{
		m[i].resize(y_sz);
		for (j = 0U; j != y_sz; j++)
			m[i][j] = mat[i][j];
	}
}

CMyMatrix::~CMyMatrix()
{
	m.clear();
}

CMyMatrix & CMyMatrix::operator=(const CMyMatrix & mat)
{
	m = mat.m;
	return (*this);
}

CMyVektor & CMyMatrix::operator[](size_t index)
{
	if (index >= m.size())
		throw std::out_of_range("Index " + std::to_string(index) + " is not valid!");
	return m[index];
}

CMyMatrix & CMyMatrix::operator+=(CMyMatrix mat)
{
	std::pair<size_t, size_t> msz(mat.getSize());
	if (m.size() == msz.first)
	{
		if (m[0].getSize() == msz.second)
		{
			for (size_t i(0U), j, x_sz(msz.first), y_sz(msz.second); i != x_sz; i++)
			{
				for (j = 0U; j != y_sz; j++)
					m[i][j] += mat[i][j];
			}
		}
	}
	return (*this);
}

CMyMatrix & CMyMatrix::operator*=(double lambda)
{
	for (size_t i(0U), j, x_sz(m.size()), y_sz(m[0].getSize()); i != x_sz; i++)
	{
		for (j = 0U; j != y_sz; j++)
			m[i][j] *= lambda;
	}
	return (*this);
}

CMyMatrix & CMyMatrix::operator/=(double lambda)
{
	for (size_t i(0U), j, x_sz(m.size()), y_sz(m[0].getSize()); i != x_sz; i++)
	{
		for (j = 0U; j != y_sz; j++)
			m[i][j] /= lambda;
	}
	return (*this);
}

CMyMatrix CMyMatrix::operator+(const CMyMatrix & mat)
{
	return CMyMatrix(*this) += mat;
}

CMyMatrix CMyMatrix::operator*(double lambda)
{
	return CMyMatrix(*this) *= lambda;
}

CMyVektor CMyMatrix::operator*(CMyVektor vect)
{
	CMyVektor ret;
	std::pair<size_t, size_t> sz(getSize());
	double t;
	ret.resize(sz.second);
	if (sz.second == vect.getSize())
	{
		for (size_t i(0U), j; i != sz.second; i++)
		{
			t = 1.0;
			for (j = 0U; j != sz.first; j++)
				t += vect[i] * m[j][i];
			ret[i] = t;
		}
	}
	else
		throw std::out_of_range("Matrix dimension is not compatible to vector. " + std::to_string(sz.second) + " != " + std::to_string(vect.getSize()));
	return ret;
}

CMyMatrix CMyMatrix::operator/(double lambda)
{
	return CMyMatrix(*this) /= lambda;
}

CMyMatrix CMyMatrix::invers()
{
	CMyMatrix ret;
	std::pair<size_t, size_t> sz(getSize());
	if ((sz.first == 2) && (sz.second == 2))
	{
		double mat[2][2] = { { m[1][1], -m[1][0] },{ -m[0][1], m[0][0] } };
		ret = CMyMatrix(reinterpret_cast<double **>(mat), 2, 2) *= 1.0 / ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
	}
	else
		throw std::out_of_range("Matrix isn't 2x2, instead " + std::to_string(sz.first) + "x" + std::to_string(sz.second) + "!");
	return ret;
}

std::pair<size_t, size_t> CMyMatrix::getSize()
{
	return std::pair<size_t, size_t>(m.size(), m[0].getSize());
}
