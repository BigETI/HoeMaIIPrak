#ifndef __CLOTTO_H__
#	define __CLOTTO_H__
#	include "CZufall.h"
#	include <set>

class CLotto
{
private:
	CLotto();
	CLotto(const CLotto &);
	CLotto & operator = (const CLotto &);

	CZufall z;
	std::vector<std::set<int>> tippzettel, gezogen;
	void simuliere();
	bool verify(std::vector<std::vector<int>> & t);
public:
	static const size_t fields;
	static const size_t entries;
	static const size_t tip_count;
	CLotto(int n = -1);
	~CLotto();

	void tippen(std::vector<std::vector<int>> & t);
	size_t ziehen(bool sim = true);
};

#endif