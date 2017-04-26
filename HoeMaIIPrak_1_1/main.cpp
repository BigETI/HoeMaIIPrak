#include <iostream>
#include "CMyVektor.h"

using namespace std;

int main(int argc, char *argv[])
{
	double vals[] = { 1.0, 2.0, 3.0 };
	CMyVektor cmv(vals, sizeof(vals) / sizeof(double));
	cout << cmv << endl;
	getchar();
	return 0;
}