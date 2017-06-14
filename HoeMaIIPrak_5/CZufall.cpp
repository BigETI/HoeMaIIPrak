#include "CZufall.h"
#include <random>
#include <ctime>
#include <map>

using namespace std;

CZufall::CZufall()
{
	initialisiere(time(nullptr));
}

CZufall::~CZufall()
{
	//
}

int CZufall::wert(int a, int b)
{
	return (rand() % ((b + 1) - a)) + a;
}

void CZufall::initialisiere(int n)
{
	srand((time_t)n);
}

vector<int> CZufall::test(int a, int b, int N)
{
	vector<int> ret;
	map<int, int> m;
	int r;
	for (int i(0); i < N; i++)
	{
		r = wert(a, b);
		if (m.find(r) != m.end())
			++m[r];
		else
			m[r] = 0;
	}
	for (map<int, int>::iterator it(m.begin()), end(m.end()); it != end; ++it)
		ret.push_back(it->second);
	return ret;
}

vector<int> CZufall::test_falsch(int a, int b, int N)
{
	vector<int> ret;
	map<int, int> m;
	int r;
	for (int i(0); i < N; i++)
	{
		initialisiere(time(nullptr));
		r = wert(a, b);
		if (m.find(r) != m.end())
			++m[r];
		else
			m[r] = 0;
	}
	for (map<int, int>::iterator it(m.begin()), end(m.end()); it != end; ++it)
		ret.push_back(it->second);
	return ret;
}
