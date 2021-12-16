#ifndef _IS_TEST
#include <map>
namespace ft = std;
#else
#include "map.hpp"
#endif

#include <iostream>

typedef std::string string;
typedef ft::map<int, char> mapp;
typedef ft::pair<int, char> pair;
typedef mapp::const_iterator const_iterator;

void	printMap(mapp const & map)
{
	static unsigned int n;

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	for (const_iterator it = map.cbegin(); it != map.cend(); ++it)
	{
		std::cout << '\t' << (*it).first << " - " << (*it).second << std::endl;
	}
}

int main()
{

	pair p[10];
	for (size_t i = 0; i < 10; i++)
	{
		p[i].first = i;
		p[i].second = 'a' + i;
	}

{
	mapp map;

	std::cout << "empty() - " << std::boolalpha << map.empty() << std::endl;
	map[42];
	std::cout << "empty() - " << std::boolalpha << map.empty() << std::endl;
	map[42] = 'A';
	printMap(map);
	map[42] = 'B';
	printMap(map);
	map[42] = '@';
	map[1] = 'X';
	map[2] = 'Y';
	map[3] = 'Z';
	printMap(map);
	std::cout << "\nsize() - " << map.size() << std::endl;
}
	return 0;
}
