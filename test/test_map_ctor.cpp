#ifndef _IS_TEST
# include <map>
namespace ft = std;
#else
# include "map.hpp"
#endif

#include <iostream>

typedef std::string string;
typedef ft::map<int,string> map;
typedef ft::pair<int, string> pair;


int main() {

	map map_d;

	pair p[10];
	for (size_t i = 0; i < 10; i++)
	{
		p[i].first = i;
		p[i].second = 'a' + i;
	}

	map map_r(p, p + 10);
	map map_c(map_r);

	return 0;
}
