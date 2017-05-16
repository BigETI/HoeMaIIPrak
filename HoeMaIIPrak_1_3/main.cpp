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
		ret = -((2.0 * (x[0] * x[0])) - (2.0 * x[0] * x[1]) + (x[1] * x[1]) + (x[2] * x[2]) - (2.0 * x[0]) - (4.0 * x[2]));
	return ret;
}

int main(int argc, char *argv[])
{
	double fa[] = { 3.0, 2.0 };
	double ga[] = { 0.0, 0.0, 0.0 };
	//CMyVektor f(CMyVektor(fv, sizeof(fv) / sizeof(double)).maximierung(fFunktion)), g(CMyVektor(gv, sizeof(gv) / sizeof(double)).maximierung(gFunktion, 0.1));
	//cout << f << endl << g << endl;
	//double vals[] = { 1.0, -1.0 };
	CMyVektor ff(fa, sizeof(fa) / sizeof(double)), gf(ga, sizeof(ga) / sizeof(double));
	//cout << ff.maximierung(fFunktion) << endl;
	
	cout << gf.maximierung(gFunktion, 0.1) << endl;

	getchar();
	return 0;
}