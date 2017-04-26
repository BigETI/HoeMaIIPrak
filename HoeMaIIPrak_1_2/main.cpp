#include <iostream>
#include "CMyVektor.h"
#include <math.h>

using namespace std;

double fFunktion(CMyVektor x)
{
	double ret(0.0);
	if (x.getSize() == 3)
		ret = sin(x[0]);
	return ret;
}

int main(int argc, char *argv[])
{
	double vals[] = { 1.0, 2.0, 3.0 };
	CMyVektor cmv(vals, sizeof(vals) / sizeof(double));
	CMyVektor g(cmv.gradient(fFunktion));
	cout << cmv << endl << g << endl;
	getchar();
	return 0;
}