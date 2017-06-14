#include <iostream>
#include <ctime>
#include "CLotto.h"

using namespace std;

template <class _T> void print_vec(vector<typename _T> & vec)
{
	bool first(true);
	for (vector<typename _T>::iterator it(vec.begin()), end(vec.end()); it != end; ++it)
	{
		if (first)
			first = false;
		else
			cout << ", ";
		cout << *it;
	}
	cout << endl;
}

static bool const dreiVonVergleich(size_t gezogen)
{
	return (gezogen == 3U);
}

double monte_carlo_simulation(size_t n, size_t ziehungen = 1U, bool const (*cmp)(size_t gezogen) = dreiVonVergleich)
{
	CZufall z;
	int r;
	vector<int> t;
	vector<vector<int>> tips;
	set<int> s;
	CLotto lotto(-1);
	size_t d(0U);
	for (size_t i(0U), j, k, l, m; i != ziehungen; i++)
	{
		for (j = 0U; j != n; j++)
		{
			tips.clear();
			for (k = 0U; k != CLotto::fields; k++)
			{
				s.clear();
				t.clear();
				for (l = 0U; l != CLotto::tip_count; l++)
				{
					while (true)
					{
						r = z.wert(1, 49);
						if (s.find(r) == s.end())
						{
							s.insert(r);
							t.push_back(r);
							break;
						}
					}
				}
				tips.push_back(t);
			}
			lotto.tippen(tips);
			m = lotto.ziehen(false);
			if (cmp(m))
				++d;
		}
	}
	return (((double)d * 100.0) / (double)(n * ziehungen));
}

int main(int argc, char *argv[])
{
	/*CZufall z;
	vector<int> werte;
	cout << "test() : einmal\r\n\"n\" gleich 10";
	z.initialisiere(10);
	werte = z.test(3, 7, 10000);
	print_vec(werte);
	cout << "test() : mehrmals\r\n\"n\" immer gleich\r\n";
	for (int i(0); i < 10; i++)
	{
		cout << "n = 0\r\n";
		z.initialisiere(0);
		werte = z.test(3, 7, 10000);
		print_vec(werte);
	}
	cout << "test() : mehrmals\r\n\"n\" immer verschieden\r\n";
	for (int i(0); i < 10; i++)
	{
		cout << "n = 0\r\n";
		z.initialisiere(i);
		werte = z.test(3, 7, 10000);
		print_vec(werte);
	}
	cout << "test() : mehrmals\r\n\"n\" = \"time(nullptr)\"\r\n";
	for (int i(0); i < 10; i++)
	{
		cout << "n = 0\r\n";
		z.initialisiere(time(nullptr));
		werte = z.test(3, 7, 10000);
		print_vec(werte);
	}
	cout << "test_falsch() : einmal\r\n\"n\" gleich 10";
	z.initialisiere(10);
	werte = z.test_falsch(3, 7, 10000);
	print_vec(werte);
	getchar();*/

	cout << "Monte-Carlo-Simulation mit 100000 Ziehungen in einer Ziehung 3 identisch Wahrscheinlichkeit: " << round(monte_carlo_simulation(10000U)) << "%\r\nMonte-Carlo-Simulation mit 1000000 Ziehungen in einer Ziehung 3 identisch Wahrscheinlichkeit: " << round(monte_carlo_simulation(100000U)) << "%\r\nMonte-Carlo-Simulation mit 100000 Ziehungen in 2 Ziehungen 3 identisch Wahrscheinlichkeit: " << round(monte_carlo_simulation(10000U, 2U)) << "%\r\nMonte-Carlo-Simulation mit 1000000 Ziehungen in 2 Ziehungen 3 identisch Wahrscheinlichkeit: " << round(monte_carlo_simulation(100000U, 2U)) << "%\r\n";
	getchar();
	return 0;
}