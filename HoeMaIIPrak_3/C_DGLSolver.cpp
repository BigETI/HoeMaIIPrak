#include "C_DGLSolver.h"
#ifdef C_DGLSOLVER_VERBOSE
#include <iostream>
#endif

size_t m1(~((size_t)0));

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
	CMyVektor ret;
	size_t sz;
	if (dgl_system)
		ret = _f_DGL_System(y, x);
	else
	{
		sz = y.getSize();
		ret.resize(sz);
		ret[sz - 1] = _f_DGL_nterOrdnung(y, x);
		for (size_t i(sz - 1); (i != 0) && (i != m1); i--)
			ret[i - 1] = y[i];
	}
	return ret;
}

C_DGLSolver::C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x)) : _f_DGL_System(f_DGL_System), dgl_system(true)
{
	//
}

C_DGLSolver::C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x)) : _f_DGL_nterOrdnung(f_DGL_nterOrdnung), dgl_system(false)
{
	//
}

C_DGLSolver::~C_DGLSolver()
{
	//
}

// Implizites Euler Verfahren
// Runge Kutta 1-er Ordnung
// y1 = y0 + h * f(y0, x0)
CMyVektor C_DGLSolver::euler(double x_start, double x_end, size_t schritte, CMyVektor y_start)
{
	CMyVektor ret(y_start);
	double hd, h, t, xe;
	if (x_end < x_start)
	{
		xe = x_start;
		x_start = x_end;
		x_end = xe;
	}
	hd = x_end - x_start;
	if (schritte > 1)
	{
		h = (hd / (double)schritte);
#ifdef C_DGLSOLVER_VERBOSE
		std::cout << "h = " << h;
#endif
		for (size_t k(0U); k != (schritte + 1U); k++)
		{
#ifdef C_DGLSOLVER_VERBOSE
			std::cout << std::endl << std::endl << std::endl;
#endif
			t = ((hd * (double)k) / (double)schritte) + x_start;
#ifdef C_DGLSOLVER_VERBOSE
			if (k == schritte)
				std::cout << "Ende bei";
			else
				std::cout << "Schritt " << k;
			std::cout << "\r\n\tx = " << t << "\r\n\ty = " << ret;
			if (k != schritte)
				std::cout << "\r\n\ty' = " << ableitungen(ret, t);
#endif
			ret += ableitungen(ret, t) * h;
		}
	}
	else
		throw std::invalid_argument("Argument \"schritte\" has to be > 1.");
	return ret;
}

// Heun Verfahren
// Runge Kutta 2-er Ordnung
// y1 = y0 + 1/2 * h * ( f(y0, x0) + f(y1, x0 + h) )
CMyVektor C_DGLSolver::heun(double x_start, double x_end, size_t schritte, CMyVektor y_start)
{
	CMyVektor ret(y_start), yso, yt, yst;
	double hd, h, t, xe;
	if (x_end < x_start)
	{
		xe = x_start;
		x_start = x_end;
		x_end = xe;
	}
	hd = x_end - x_start;
	if (schritte > 1)
	{
		h = (hd / (double)schritte);
#ifdef C_DGLSOLVER_VERBOSE
		std::cout << "h = " << h;
#endif
		for (size_t k(0U); k != (schritte + 1U); k++)
		{
#ifdef C_DGLSOLVER_VERBOSE
			std::cout << std::endl << std::endl << std::endl;
#endif
			t = ((hd * (double)k) / (double)schritte) + x_start;
#ifdef C_DGLSOLVER_VERBOSE
			if (k == schritte)
				std::cout << "Ende bei";
			else
				std::cout << "Schritt " << k;
			std::cout << "\r\n\tx = " << t << "\r\n\ty = " << ret;
#endif
			yso = ableitungen(ret, t);
			yt = ret + ableitungen(ret, t) * h;
			yst = ableitungen(yt, t + h);
#ifdef C_DGLSOLVER_VERBOSE
			if (k != schritte)
				std::cout << "\r\n\ty'_orig = " << yso << "\r\n\r\n\ty_Test" << yt << "\r\n\ty'_Test" << yst << "\r\n\r\n\ty'_Mittel = " << ((yso + yst) * 0.5);
#endif
			ret += ((yso + yst) * (0.5 * h));
		}
	}
	else
		throw std::invalid_argument("Argument \"schritte\" has to be > 1.");
	return ret;
}
