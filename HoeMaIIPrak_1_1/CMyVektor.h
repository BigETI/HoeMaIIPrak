#ifndef __CMYVEKTOR_H__
#	define __CMYVEKTOR_H__
#	include <vector>

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
	std::string toString();
	friend std::ostream & operator << (std::ostream & stream, CMyVektor & cmv);
};

#endif
