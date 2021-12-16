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
typedef mapp::iterator iterator;
typedef mapp::const_iterator const_iterator;

static unsigned int n;

void	printMap(mapp const & map)
{
	std::cout << "[# Test " << ++n << " #]" << std::endl;
	for (const_iterator it = map.cbegin(); it != map.cend(); ++it)
	{
		std::cout << (*it).first << " - " << (*it).second << std::endl;
	}
}

int main()
{
	mapp map;
	pair p(42, 'A');
	ft::pair<iterator, bool> ret_pair;

	std::cout << std::boolalpha;

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	ret_pair = map.insert(p);
	std::cout << "Successfully inserted? " << ret_pair.second << std::endl;
	std::cout << "Pair values: " << ret_pair.first->first << " - " << ret_pair.first->second << std::endl;

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	p = pair(42, 'X');
	ret_pair = map.insert(p);
	std::cout << "Successfully inserted? " << ret_pair.second << std::endl;
	std::cout << "Pair values: " << ret_pair.first->first << " - " << ret_pair.first->second << std::endl;

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	p = pair(21, 'Z');
	ret_pair = map.insert(p);
	std::cout << "Successfully inserted? " << ret_pair.second << std::endl;
	std::cout << "Pair values: " << ret_pair.first->first << " - " << ret_pair.first->second << std::endl;

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	p = pair(43, 'F');
	iterator it = map.insert(ret_pair.first, p);
	std::cout << it->first << " - " << it->second << std::endl;
	p.second = 'G';
	it = map.insert(it, p);
	std::cout << it->first << " - " << it->second << std::endl;

	p = pair(4, 'O');

	it = map.insert(map.begin(), p);
	std::cout << it->first << " - " << it->second << std::endl;

	it = map.rbegin().base();
	p = pair(5, 'O');

	it = map.insert(it, p);


	map[0] = 'X';
	map[1] = 'X';
	map[2] = 'X';
	map[3] = 'X';
	// map[4] = 'X';
	// map[5] = 'X';
	map[6] = 'X';
	map[7] = 'X';
	map[8] = 'X';
	map[9] = 'X';
	map[10] = 'X';
	printMap(map);

	pair pa[10];
	for (size_t i = 0; i < 10; i++)
	{
		pa[i].first = i;
		pa[i].second = '0' + i;
	}

	map.insert(pa, pa + 10);
	printMap(map);

	for (size_t i = 0; i < 10; i++)
	{
		pa[i].first = i + 100;
		pa[i].second = '0' + i;
	}


	map.insert(pa, pa + 10);
	printMap(map);

	std::cout << "[# Test " << ++n << " #]" << std::endl;
	std::cout << "N erased: " << map.erase(103) << std::endl;
	std::cout << "N erased: " << map.erase(7) << std::endl;
	std::cout << "N erased: " << map.erase(109) << std::endl;
	printMap(map);

	map.erase(map.begin());
	printMap(map);

	map.erase(map.begin(), ++(++(++map.begin())));
	printMap(map);

	mapp map_other;

	for (size_t i = 0; i < 20; i++)
	{
		map_other[i] = 'a' + i;
	}
	printMap(map_other);

	map.swap(map_other);
	printMap(map);
	printMap(map_other);

	map.clear();
	map_other.clear();
	printMap(map);
	printMap(map_other);

	return 0;
}
