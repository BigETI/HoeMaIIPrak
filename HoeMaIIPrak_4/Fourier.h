#ifndef __FOURIER_H__
#	define __FOURIER_H__
#include <vector>
#include "CKomplex.h"

namespace Fourier
{
	extern std::vector<CKomplex> hin(std::vector<CKomplex> werte);
	extern std::vector<CKomplex> zurueck(std::vector<CKomplex> werte);
}

#endif
