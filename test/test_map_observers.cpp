#ifndef _IS_TEST
#include <map>
namespace ft = std;
#else
#include "map.hpp"
#endif

#include <iostream>

int main()
{
	{
		ft::map<char, int> mymap;

		ft::map<char, int>::key_compare mycomp = mymap.key_comp();

		mymap['a'] = 100;
		mymap['b'] = 200;
		mymap['c'] = 300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;

		ft::map<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mycomp((*it++).first, highest));

		std::cout << '\n';
	}
	{
		ft::map<char, int> mymap;

		mymap['x'] = 1001;
		mymap['y'] = 2002;
		mymap['z'] = 3003;

		std::cout << "mymap contains:\n";

		ft::pair<char, int> highest = *mymap.rbegin();

		ft::map<char, int>::iterator it = mymap.begin();
		do
		{
			std::cout << it->first << " => " << it->second << '\n';
		} while (mymap.value_comp()(*it++, highest));
	}
	return 0;
}
