#include <iostream>
#include "CMyMatrix.h"

double P1Funktion(CMyVektor x)
{
	double x1(x[0]), y1(x[1]);
	return (x1 * x1 * x1 * y1 * y1 * y1) - (2.0 * y1);
}

double P2Funktion(CMyVektor x)
{
	return x[0] - 2.0;
}

CMyVektor FFunktion(CMyVektor x)
{
	CMyVektor ret(2U);
	ret[0] = P1Funktion(x);
	ret[1] = P2Funktion(x);
	return ret;
}

int main(int argc, char *argv[])
{
	/*CMyMatrix m(2, 2);
	m[0][0] = 1.0;
	m[1][0] = 2.0;
	m[0][1] = 3.0;
	m[1][1] = 4.0;
	CMyVektor v(2);
	v[0] = 5.0;
	v[1] = 6.0;
	std::cout << (m * v);*/
	
	double vals[2] = { 1.0, 1.0 };
	const int sz = sizeof(vals) / sizeof(double);
	CMyVektor p(vals, sz);
	p.newton(FFunktion);
	getchar();
	return 0;
}