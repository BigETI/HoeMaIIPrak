#include "CMyMatrix.h"
#include <iostream>
#include <string>
#include <stdexcept>

static const double H(1e-4);

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

CMyVektor CMyVektor::maximierung(double(*funktion)(CMyVektor x), double lambda, size_t s)
{
	CMyVektor ret(*this), vn, gv;
	double f, fn, ft;
	bool c(false);
	for (size_t i(0U); i != s; i++)
	{
		f = funktion(ret);
		gv = ret.gradient(funktion);
		vn = ret + (gv * lambda);
		fn = funktion(vn);
		if (gv.getMagnitude() < 0.00001)
		{
			c = true;
			break;
		}
		std::cout << "Schritt " << i << std::endl <<
			"x = " << ret << std::endl <<
			"lambda = " << lambda << std::endl <<
			"f(x) = " << f << std::endl <<
			"grad f(x) = " << gv << std::endl <<
			"||grad f(x)|| = " << gv.getMagnitude() << std::endl <<
			"x_neu = " << vn << std::endl <<
			"f(x_neu) = " << fn << std::endl;
		if (fn > f)
		{
			
			CMyVektor vt(ret + (gv * (2.0 * lambda)));
			ft = funktion(vt);
			std::cout << "Teste eine doppelte Schrittweite.\nx_test = " << vt << std::endl <<
				"f(x_test) = " << ft << std::endl;
			if (ft > fn)
			{
				ret = vt;
				lambda *= 2.0;
				std::cout << "verdoppele Schrittweite\n\n";
			}
			else
			{
				ret = vn;
				std::cout << "behalte alte Schrittweite\n\n";
			}
		}
		else
		{
			double l(lambda);
			do
			{
				l *= 0.5;
				std::cout << "halbiere Schrittweite(lambda = " << l << ") : " << std::endl;
				vn = ret + (gv * l);
				fn = funktion(vn);
				std::cout << "x_neu = " << vn << std::endl <<
					"f(x_neu) = " << fn << std::endl << std::endl;
			} while (!(fn > f));
			ret = vn;
			lambda = l;
		}
		std::cout << std::endl;
	}
	f = funktion(ret);
	gv = ret.gradient(funktion);
	if (c)
		std::cout << "Abruchbedingung durch ||grad f(x)|| < 10^-5\n\n";
	else
		std::cout << "Abruchbedingung wegen Durchlauf = 50\n\n";
	std::cout << "x = " << ret << std::endl <<
		"lambda = " << lambda << std::endl <<
		"f(x) = " << fn << std::endl <<
		"grad f(x) = " << gv << std::endl <<
		"||grad f(x)|| = " << gv.getMagnitude() << std::endl << std::endl << std::endl;
	return ret;
}

double CMyVektor::getMagnitudeSquared()
{
	double ret(0.0);
	for (std::vector<double>::iterator it(v.begin()), end(v.end()); it != end; ++it)
		ret += (*it) * (*it);
	return ret;
}

double CMyVektor::getMagnitude()
{
	return sqrt(getMagnitudeSquared());
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
		std::string s(16, '\0');
		int w = std::snprintf(&s[0], s.size(), "%.5e", *it);
		s.resize(w);
		ret += s;
	}
	ret += " )";
	return ret;
}

CMyMatrix CMyVektor::jacobi(CMyVektor(*funktion)(CMyVektor x))
{
	CMyVektor r(funktion(*this)), vh(*this);
	size_t xsz(getSize()), ysz(r.getSize());
	CMyMatrix ret(xsz, ysz);
	double f;
	for (size_t i(0U), j; i != ysz; i++)
	{
		f = r[i];
		for (j = 0U; j != xsz; j++)
		{
			vh[j] += H;
			ret[i][j] = (funktion(vh)[i] - f) / H;
			vh[j] = (*this)[j];
		}
	}
	return ret;
}

CMyVektor CMyVektor::newton(CMyVektor (*funktion)(CMyVektor x))
{
	static const int sz = 2;
	CMyVektor ret(*this), fkwert(funktion(ret)), dx(sz);
	double epsilon = 1e-3;
	CMyMatrix jac(sz, getSize());
	int c = 0;
	while ((fkwert.getMagnitude() > epsilon) && (c < 50))
	{
		std::cout << "Schritt " << c << "\r\nx = " << ret << "\r\nf(x) = " << fkwert;
		// Berechnung der Jakobimatrix
		jac = ret.jacobi(funktion);
		std::cout << "\r\nf'(x) = " << std::endl << jac;
		// Inverse von Jacobi
		jac = jac.invers();
		std::cout << "\r\n(f'(x))^(-1) = " << jac;
		dx = jac * fkwert * -1.0;
		//std::cout << "\r\njac = " << jac << " fkwert = " << fkwert << " dx = " << dx;
		std::cout << "\r\ndx = " << dx;
		// Neues x berechnen
		ret += dx;
		std::cout << "\r\nNeues x = " << ret << std::endl;
		std::cout << "\r\n||f(x)|| = " << fkwert.getMagnitude() << std::endl;
		fkwert = funktion(ret);
		++c;
		getchar();
	}
	if (c >= 50)
		std::cout << "Ende wegen Schritt = 50 bei x = " << ret << "\r\nf(x) = " << fkwert;
	else
		std::cout << "Ende wegen ||f(x)|| < 1e-5 bei " << std::endl << "\r\nx= " << ret << "\r\nf(x) = " << fkwert << "\r\n||f(x)|| = " << fkwert.getMagnitude() << std::endl;
	return ret;
}

std::ostream & operator << (std::ostream & stream, CMyVektor & cmv)
{
	return (stream << cmv.toString());
}
