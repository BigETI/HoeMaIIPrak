#define _USE_MATH_DEFINES
#include <math.h>
#include "Fourier.h"

using namespace std;

vector<CKomplex> Fourier::hin(vector<CKomplex> werte)
{
	vector<CKomplex> ret;
	for (size_t n(0U), k, bn(werte.size()); n != bn; n++)
	{
		CKomplex v;
		for (k = 0U; k != bn; k++)
			v += werte[k] * CKomplex((-2.0 * M_PI * k * n) / (double)bn);
		v *= (1 / sqrt(bn));
		ret.push_back(v);
	}
	return ret;
}

vector<CKomplex> Fourier::zurueck(vector<CKomplex> werte)
{
	vector<CKomplex> ret;
	for (size_t k(0U), n, bn(werte.size()); k != bn; k++)
	{
		CKomplex v;
		for (n = 0U; n != bn; n++)
			v += werte[n] * CKomplex((2.0 * M_PI * k * n) / (double)bn);
		v *= (1 / sqrt(bn));
		ret.push_back(v);
	}
	return ret;
}
