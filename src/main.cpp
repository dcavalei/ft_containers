#include "map.hpp"

#include <iostream>

int main()
{
	ft::map<char, int> mymap;

	mymap['a'] = 1;

	ft::map<char, int>::iterator it = mymap.cbegin();

	std::cout << it->second << std::endl;
}
