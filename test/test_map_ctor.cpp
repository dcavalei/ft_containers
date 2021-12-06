#ifndef _IS_TEST
#include <map>
namespace ft = std;
#else
#include "map.hpp"
#endif

#include <iostream>

typedef std::string string;
typedef ft::map<int, string> map;
typedef ft::pair<int, string> pair;

int main()
{

	pair p[10];
	for (size_t i = 0; i < 10; i++)
	{
		p[i].first = i;
		p[i].second = 'a' + i;
	}

	map map_d;
	map map_r(p, p + 10);
	map map_c(map_r);
	map::iterator itr = map_d.end();

	map_d.insert(p, p + 10);
	for (map::iterator it = map_d.begin(); it != itr; ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
	std::cout << "-----" << std::endl;

	itr = map_r.end();
	for (map::iterator it = map_r.begin(); it != itr; ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
	std::cout << "-----" << std::endl;

	itr = map_c.end();
	for (map::iterator it = map_c.begin(); it != itr; ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
	std::cout << "-----" << std::endl;

	map map_a;
	map_a = map_c;

	itr = map_a.end();
	for (map::iterator it = map_a.begin(); it != itr; ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
	std::cout << "-----" << std::endl;

	return 0;
}
