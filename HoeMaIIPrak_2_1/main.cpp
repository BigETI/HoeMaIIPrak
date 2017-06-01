#include <iostream>
#include "CMyMatrix.h"

int main(int argc, char *argv[])
{
	double vals[4] = { 1.0, 1.0, 2.0, 3.0 };
	const int sz = sizeof(vals) / sizeof(double);
	CMyMatrix v(vals, 2, 2);
	std::cout << "v = " << v << "\r\ninvers(v) = " << v.invers();
	getchar();
	return 0;
}