#include "CLotto.h"
#include <ctime>

using namespace std;

const size_t CLotto::fields(12U);
const size_t CLotto::entries(49U);
const size_t CLotto::tip_count(6U);

void CLotto::simuliere()
{
	int r;
	set<int> s;
	gezogen.clear();
	for (size_t i(0U), j; i != fields; i++)
	{
		s.clear();
		for (size_t j = 0U; j != tip_count; j++)
		{
			while (true)
			{
				r = z.wert(1, 49);
				if (s.find(r) == s.end())
				{
					s.insert(r);
					break;
				}
			}
		}
		gezogen.push_back(s);
	}
}

bool CLotto::verify(vector<vector<int>>& t)
{
	bool ret(false);
	set<int> s;
	if (t.size() == fields)
	{
		ret = true;
		for (vector<vector<int>>::iterator it(t.begin()), end(t.end()); it != end; ++it)
		{
			if (it->size() == tip_count)
			{
				s.clear();
				for (vector<int>::iterator it2(it->begin()), end2(it->end()); it2 != end2; ++it2)
				{
					if (s.find(*it2) == s.end())
						s.insert(*it2);
					else
					{
						ret = false;
						break;
					}
				}
				if (!ret)
					break;
			}
			else
			{
				ret = false;
				break;
			}
		}
	}
	return ret;
}

CLotto::CLotto(int n)
{
	if (n < 0)
		n = time(nullptr);
	z.initialisiere(n);
	tippzettel.resize(fields);
}

CLotto::~CLotto()
{
	//
}

void CLotto::tippen(vector<vector<int>>& t)
{
	set<int> s;
	if (verify(t))
	{
		tippzettel.clear();
		for (size_t i(0U), j; i != fields; i++)
		{
			s.clear();
			for (j = 0U; j != tip_count; j++)
				s.insert(t[i][j]);
			tippzettel.push_back(s);
		}
	}
}

size_t CLotto::ziehen(bool sim)
{
	size_t ret(0U);
	if (sim)
		simuliere();
	else
	{
		if (gezogen.size() < fields)
			simuliere();
	}
	for (size_t i(0U); i != fields; i++)
	{
		for (set<int>::iterator it(tippzettel[i].begin()), end(tippzettel[i].end()); it != end; ++it)
		{
			if (gezogen[i].find(*it) != gezogen[i].end())
				++ret;
		}
	}
	return ret;
}
