#include <iostream>
#include "CMyMatrix.h"

CMyVektor TestFunktion(CMyVektor x)
{
	CMyVektor ret(3);
	if (x.getSize() == 4)
	{
		ret[0] = x[0] * x[1] * x[2];
		ret[1] = x[1] * x[2] * x[3];
		ret[2] = x[3];
	}
	return ret;
}

int main(int argc, char *argv[])
{
	/*double vals[4] = { 1.0, 2.0, 0.0, 3.0 };
	CMyVektor x(vals, sizeof(vals) / sizeof(double)), res(TestFunktion(x));
	std::cout << "(x1 * x2 * x3, x2 * x3 * x4, x4) = " << res << "\r\n'(x1 * x2 * x3, x2 * x3 * x4, x4) = " << x.jacobi(TestFunktion);*/
	getchar();
	return 0;
}