#include <iostream>
#include "CMyVektor.h"
#include <math.h>

using namespace std;


double fFunktion(CMyVektor x)
{
	double ret(0.0);
	if (x.getSize() == 2)
		ret = sin(x[0] + (x[1] * x[1])) + (x[1] * x[1] * x[1]) - ((x[1] * x[1]) * 6.0) + (x[1] * 9.0);
	return ret;
}

double gFunktion(CMyVektor x)
{
	double ret(0.0);
	if (x.getSize() == 3)
		ret = -((x[0] * x[0]) - (2.0 * x[0] * x[1]) + (x[1], x[1]) + (x[2], x[2]) - (2.0 * x[0]) - (4.0 * x[2]));
	return ret;
}

double testFunktion(CMyVektor x)
{
	return (-x[0] * x[1] * x[1]);
}

int main(int argc, char *argv[])
{
	double fv[] = { 3.0, 2.0 };
	//double gv[] = { 0.0, 0.0, 0.0 };
	//CMyVektor f(CMyVektor(fv, sizeof(fv) / sizeof(double)).maximierung(fFunktion)), g(CMyVektor(gv, sizeof(gv) / sizeof(double)).maximierung(gFunktion, 0.1));
	//cout << f << endl << g << endl;
	//double vals[] = { 1.0, -1.0 };
	CMyVektor v(fv, sizeof(fv) / sizeof(double)), g(v.gradient(testFunktion));
	cout << v.maximierung(fFunktion) << endl;

	getchar();
	return 0;
}