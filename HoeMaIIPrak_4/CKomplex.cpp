#include "CKomplex.h"
#include <math.h>

CKomplex::CKomplex() : a(0.0), b(0.0)
{
	//
}

CKomplex::CKomplex(double _a, double _b) : a(_a), b(_b)
{
	//
}

CKomplex::CKomplex(double phi)
{
	a = cos(phi);
	b = sin(phi);
}

CKomplex::CKomplex(const CKomplex & complex) : a(complex.a), b(complex.b)
{
	//
}

CKomplex::~CKomplex()
{
	//
}

CKomplex & CKomplex::operator=(const CKomplex & complex)
{
	a = complex.a;
	b = complex.b;
	return (*this);
}

CKomplex & CKomplex::operator+=(const CKomplex & complex)
{
	a += complex.a;
	b += complex.b;
	return (*this);
}

CKomplex & CKomplex::operator+=(double _a)
{
	a += _a;
	return (*this);
}

CKomplex & CKomplex::operator-=(const CKomplex & complex)
{
	a -= complex.a;
	b -= complex.b;
	return (*this);
}

CKomplex & CKomplex::operator-=(double _a)
{
	a -= _a;
	return (*this);
}

CKomplex & CKomplex::operator*=(const CKomplex & complex)
{
	double r(a);
	a = (r * complex.a) + (b * complex.b * -1.0);
	b = (b * complex.a) + (r * complex.b);
	return (*this);
}

CKomplex & CKomplex::operator*=(double _a)
{
	a *= _a;
	b *= _a;
	return (*this);
}

CKomplex & CKomplex::operator/=(const CKomplex & complex)
{
	CKomplex con(conjugate());
	(*this) = ((*this) * con) / (CKomplex(complex) * con).a;
	return (*this);
}

CKomplex & CKomplex::operator/=(double _a)
{
	a /= _a;
	b /= a;
	return (*this);
}

CKomplex CKomplex::operator+(const CKomplex & complex)
{
	CKomplex ret(*this);
	return ret += complex;
}

CKomplex CKomplex::operator+(double _a)
{
	CKomplex ret(*this);
	return ret += _a;
}

CKomplex CKomplex::operator-(const CKomplex & complex)
{
	CKomplex ret(*this);
	return ret -= complex;
}

CKomplex CKomplex::operator-(double _a)
{
	CKomplex ret(*this);
	return ret -= _a;
}

CKomplex CKomplex::operator*(const CKomplex & complex)
{
	CKomplex ret(*this);
	return ret *= complex;
}

CKomplex CKomplex::operator*(double _a)
{
	CKomplex ret(*this);
	return ret *= _a;
}

CKomplex CKomplex::operator/(const CKomplex & complex)
{
	CKomplex ret(*this);
	return ret /= complex;
}

CKomplex CKomplex::operator/(double _a)
{
	CKomplex ret(*this);
	return ret /= _a;
}

double CKomplex::re()
{
	return a;
}

double CKomplex::im()
{
	return b;
}

CKomplex CKomplex::conjugate()
{
	return CKomplex(a, -b);
}

double CKomplex::absSquared()
{
	return (a * a) + (b * b);
}

double CKomplex::abs()
{
	return sqrt(absSquared());
}
