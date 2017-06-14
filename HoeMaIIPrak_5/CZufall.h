#ifndef __CZUFALL_H__
#	define __CZUFALL_H__
#	include <vector>

class CZufall
{
private:
	CZufall(const CZufall &);
	CZufall & operator = (const CZufall &);
public:
	CZufall();
	~CZufall();

	int wert(int a, int b);
	void initialisiere(int n);
	std::vector<int> test(int a, int b, int N);
	std::vector<int> test_falsch(int a, int b, int N);
};

#endif
