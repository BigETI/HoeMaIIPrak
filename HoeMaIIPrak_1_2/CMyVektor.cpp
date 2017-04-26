#include "CMyVektor.h"
#include <string>
#include <stdexcept>

static const double H(0.00000001);

CMyVektor::CMyVektor()
{
	v.assign(1, 0.0);
}

CMyVektor::CMyVektor(const CMyVektor & cmv) : v(cmv.v)
{
	//
}

CMyVektor::CMyVektor(const std::vector<double>& vec) : v(vec)
{
	//
}

CMyVektor::CMyVektor(size_t size, double val)
{
	v.assign(size, val);
}

CMyVektor::CMyVektor(double * arr, size_t size)
{
	resize(size);
	for (size_t i = 0U; i != size; i++)
		v[i] = arr[i];
}


CMyVektor::~CMyVektor()
{
	v.clear();
}

CMyVektor & CMyVektor::operator=(const CMyVektor & cmv)
{
	v = cmv.v;
	return (*this);
}

double & CMyVektor::operator[](size_t index)
{
	if (getSize() <= index)
		throw std::out_of_range("index at " + std::to_string(index) + " is invalid.");
	return v[index];
}

CMyVektor & CMyVektor::operator()(const std::vector<double>& vect)
{
	v = vect;
	return (*this);
}

CMyVektor & CMyVektor::operator+=(CMyVektor cmv)
{
	size_t sz(getSize());
	if (cmv.getSize() == sz)
	{
		for (size_t i = 0; i != sz; i++)
			v[i] += cmv.v[i];
	}
	return (*this);
}

CMyVektor & CMyVektor::operator*=(double lambda)
{
	size_t sz(getSize());
	for (size_t i = 0; i != sz; i++)
		v[i] *= lambda;
	return (*this);
}

CMyVektor CMyVektor::operator+(CMyVektor cmv)
{
	return CMyVektor(*this) += cmv;
}

CMyVektor CMyVektor::operator*(double lambda)
{
	return CMyVektor(*this) *= lambda;
}

void CMyVektor::resize(size_t size)
{
	size_t lsz(v.size());
	v.resize(size);
	if (lsz < size)
	{
		for (size_t i(lsz); i != size; i++)
			v[i] = 0.0;
	}
}

size_t CMyVektor::getSize()
{
	return v.size();
}

CMyVektor CMyVektor::gradient(double(*funktion)(CMyVektor x))
{
	CMyVektor ret(getSize());
	CMyVektor vh(*this);
	size_t sz(getSize());
	double f(funktion(*this));
	for (size_t i = 0U; i != sz; i++)
	{
		vh[i] += H;
		ret[i] = (funktion(vh) - f) / H;
		vh[i] = (*this)[i];
	}
	return ret;
}

std::string CMyVektor::toString()
{
	std::string ret("( ");
	bool first(true);
	for (std::vector<double>::iterator it(v.begin()), end(v.end()); it != end; ++it)
	{
		if (first)
			first = false;
		else
			ret += ", ";
		ret += std::to_string(*it);
	}
	ret += " )";
	return ret;
}

std::ostream & operator << (std::ostream & stream, CMyVektor & cmv)
{
	return (stream << cmv.toString());
}
