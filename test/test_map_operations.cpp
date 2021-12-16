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
		ft::map<char, int>::iterator it;

		mymap['a'] = 50;
		mymap['b'] = 100;
		mymap['c'] = 150;
		mymap['d'] = 200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase(it);

		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}
	{
		ft::map<char, int> mymap;
		char c;

		mymap['a'] = 101;
		mymap['c'] = 202;
		mymap['f'] = 303;

		for (c = 'a'; c < 'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c) > 0)
				std::cout << " is an element of mymap.\n";
			else
				std::cout << " is not an element of mymap.\n";
		}
	}
	{
		ft::map<char, int> mymap;
		ft::map<char, int>::iterator itlow, itup;

		mymap['a'] = 1;
		mymap['b'] = 2;
		mymap['c'] = 3;
		mymap['d'] = 4;
		// mymap['e'] = 5;
		mymap['f'] = 6;
		mymap['g'] = 7;
		mymap['h'] = 8;
		// mymap['i'] = 9;
		mymap['j'] = 10;

		itlow = mymap.lower_bound('e'); // itlow points to b
		itup = mymap.upper_bound('i');	// itup points to e (not d!)

		mymap.erase(itlow, itup); // erases [itlow,itup)

		// print content:
		for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	return 0;
}
