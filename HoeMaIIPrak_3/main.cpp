#include <iostream>
#include "C_DGLSolver.h"

CMyVektor DGLSystem(CMyVektor y, double x)
{
	CMyVektor ret(2U);
	ret[0] = (2.0 * y[1]) - (x * y[0]);
	ret[1] = (y[0] * y[1]) - (2.0 * x * x * x);
	return ret;
}

double DGLDritterOrdnung(CMyVektor y, double x)
{
	return (2.0 * x * y[1] * y[2]) + (2.0 * y[0] * y[0] * y[1]);
}

int main(int argc, char *argv[])
{
	/*C_DGLSolver solver(DGLSystem);
	CMyVektor y(2U);
	y[0] = 0.0;
	y[1] = 1.0;
	//solver.euler(0.0, 2.0, 100, y);
	solver.heun(0.0, 2.0, 100, y);*/

	C_DGLSolver solver(DGLDritterOrdnung);
	CMyVektor y(3U);
	bool first(true);
	y[0] = 1.0;
	y[1] = -1.0;
	y[2] = 2.0;
	for (size_t i = 0U, j, s; i != 4; i++)
	{
		if (first)
			first = false;
		else
			std::cout << std::endl;
		s = 10U;
		for (j = 0U; j != i; j++)
			s *= 10;
		std::cout << "Abweichung bei Euler bei " << s << " Schritten: " << (solver.euler(1.0, 2.0, s, y)[0] - 0.5) << "\r\nAbweichung bei Heun bei " << s << " Schritten: " << (solver.heun(1.0, 2.0, s, y)[0] - 0.5);
	}
	getchar();
	return 0;
}