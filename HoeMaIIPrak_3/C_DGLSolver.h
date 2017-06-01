#ifndef __C_DGLSOLVER_H__
#	define __C_DGLSOLVER_H__
#	include "CMyVektor.h"
//#	define C_DGLSOLVER_VERBOSE
class C_DGLSolver
{
private:
	CMyVektor(*_f_DGL_System)(CMyVektor y, double x);
	double(*_f_DGL_nterOrdnung)(CMyVektor y, double x);
	bool dgl_system;

	C_DGLSolver();
	C_DGLSolver(const C_DGLSolver &);
	C_DGLSolver & operator = (const C_DGLSolver &);

	CMyVektor ableitungen(CMyVektor y, double x);
public:
	C_DGLSolver(CMyVektor (*f_DGL_System)(CMyVektor y, double x));
	C_DGLSolver(double(*f_DGL_nterOrdnung)(CMyVektor y, double x));
	~C_DGLSolver();

	CMyVektor euler(double x_start, double x_end, size_t schritte, CMyVektor y_start);
	CMyVektor heun(double x_start, double x_end, size_t schritte, CMyVektor y_start);
};

#endif
