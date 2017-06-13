#ifndef __CKOMPLEX_H__
#	define __CKOMPLEX_H__

class CKomplex
{
private:
	double a, b;
public:
	CKomplex();
	CKomplex(double _a, double _b);
	CKomplex(double phi);
	CKomplex(const CKomplex & complex);
	~CKomplex();
	CKomplex & operator = (const CKomplex & complex);
	CKomplex & operator += (const CKomplex & complex);
	CKomplex & operator += (double _a);
	CKomplex & operator -= (const CKomplex & complex);
	CKomplex & operator -= (double _a);
	CKomplex & operator *= (const CKomplex & complex);
	CKomplex & operator *= (double _a);
	CKomplex & operator /= (const CKomplex & complex);
	CKomplex & operator /= (double _a);

	CKomplex operator + (const CKomplex & complex);
	CKomplex operator + (double _a);
	CKomplex operator - (const CKomplex & complex);
	CKomplex operator - (double _a);
	CKomplex operator * (const CKomplex & complex);
	CKomplex operator * (double _a);
	CKomplex operator / (const CKomplex & complex);
	CKomplex operator / (double _a);

	double re();
	double im();
	CKomplex conjugate();
	double absSquared();
	double abs();
};

#endif
