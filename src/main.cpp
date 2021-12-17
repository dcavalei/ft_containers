#include "map.hpp"

#include <iostream>

int main()
{
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator itlow, itup;

	mymap['a'] = 1;
	mymap['b'] = 2;
	mymap['c'] = 3;
	// mymap['d'] = 4;
	mymap['e'] = 5;
	mymap['f'] = 6;
	mymap['g'] = 7;
	mymap['h'] = 8;
	mymap['i'] = 9;
	mymap['j'] = 10;

	itlow = mymap.lower_bound(100);
	itup = mymap.upper_bound('i');

	if (itlow == mymap.end())
	{
		std::cout << "HELLO\n";
		return 0;
	}
	mymap.erase(itlow, itup); // erases [itlow,itup)

	// print content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	return 0;
}
