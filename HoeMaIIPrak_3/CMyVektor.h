#ifndef __CMYVEKTOR_H__
#	define __CMYVEKTOR_H__
#	include <vector>
#	include <functional>
//#	define CMYVEKTOR_SCIENTIFIC

class CMyMatrix;

class CMyVektor
{
private:
	std::vector<double> v;
public:
	CMyVektor();
	CMyVektor(const CMyVektor &cmv);
	CMyVektor(const std::vector<double> &vec);
	CMyVektor(size_t size, double val = 0.0);
	CMyVektor(double *arr, size_t size);
	~CMyVektor();

	CMyVektor & operator = (const CMyVektor &cmv);
	double & operator [] (size_t index);
	CMyVektor & operator () (const std::vector<double> &vect);
	CMyVektor & operator += (CMyVektor cmv);
	CMyVektor & operator *= (double lambda);
	CMyVektor operator + (CMyVektor cmv);
	CMyVektor operator * (double lambda);

	void resize(size_t size);
	size_t getSize();
	CMyVektor gradient(double(*funktion)(CMyVektor x));
	CMyVektor gradient(std::function<double (CMyVektor x)> funktion);
	CMyVektor maximierung(double(*funktion)(CMyVektor x), double lambda = 1.0, size_t s = 50);
	double getMagnitudeSquared();
	double getMagnitude();
	std::string toString();
	friend std::ostream & operator << (std::ostream & stream, CMyVektor & cmv);
	//CMyMatrix jacobi(CMyVektor (*funktion)(CMyVektor x));
	//CMyVektor newton(CMyVektor (*funktion)(CMyVektor x));
};

#endif
