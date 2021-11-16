#ifndef _IS_TEST
# include <utility>
namespace ft = std;
#else
# include "utility.hpp"
#endif

#include <iostream>

int main () {
	ft::pair<int,int>	foo;
	ft::pair<int,int>	bar;

	foo = ft::make_pair(10, 20);
	bar = ft::make_pair(10.5, 'A');

	std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
	std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;

	return 0;
}
