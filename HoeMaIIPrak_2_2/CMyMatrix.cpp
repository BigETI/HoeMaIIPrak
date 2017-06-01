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

CMyMatrix::CMyMatrix(double *mat, size_t x_sz, size_t y_sz)
{
	m.resize(x_sz);
	for (size_t i(0U), j; i != x_sz; i++)
	{
		m[i].resize(y_sz);
		for (j = 0U; j != y_sz; j++)
			m[i][j] = mat[(y_sz * j) + i];
	}
}

CMyMatrix::CMyMatrix(size_t x_sz, size_t y_sz, double val)
{
	m.resize(x_sz);
	for (size_t i(0U), j; i != x_sz; i++)
	{
		m[i].resize(y_sz);
		for (j = 0U; j != y_sz; j++)
			m[i][j] = val;
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
	ret.resize(sz.first);
	if (sz.first == vect.getSize())
	{
		for (size_t j(0U), i; j != sz.second; j++)
		{
			for (i = 0U; i != sz.first; i++)
				ret[j] += vect[i] * m[j][i];
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
		double mat[4] = { m[1][1], -m[1][0], -m[0][1], m[0][0] }, d((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
		if ((d < std::numeric_limits<double>::epsilon()) && (d > -std::numeric_limits<double>::epsilon()))
			throw std::logic_error("Division by zero");
		ret = CMyMatrix(mat, 2, 2) *= 1.0 / d;
	}
	else
		throw std::out_of_range("Matrix isn't 2x2, instead " + std::to_string(sz.first) + "x" + std::to_string(sz.second) + "!");
	return ret;
}

std::pair<size_t, size_t> CMyMatrix::getSize()
{
	return std::pair<size_t, size_t>(m.size(), m[0].getSize());
}

std::string CMyMatrix::toString()
{
	std::string ret("( ");
	bool first(true);
	for (std::vector<CMyVektor>::iterator it(m.begin()), end(m.end()); it != end; ++it)
	{
		if (first)
			first = false;
		else
			ret += ", ";
		ret += it->toString();
	}
	ret += " )";
	return ret;
}

std::ostream & operator << (std::ostream & stream, CMyMatrix & cmm)
{
	return (stream << cmm.toString());
}
