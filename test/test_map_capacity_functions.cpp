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

	map map1(p, p + 10);
	map::iterator itr = map1.end();

	for (map::iterator it = map1.begin(); it != itr; ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
	std::cout << "-----" << std::endl;

	std::cout << "size() - " << map1.size() << std::endl;
	std::cout << "max_size() - " << map1.max_size() << std::endl;
	std::cout << "empty() - " << std::boolalpha << map1.empty() << std::endl;



	return 0;
}
