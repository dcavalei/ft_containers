#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"
#include "iterator_traits.hpp"

int main ()
{
	std::vector<int> foo (2,100);
	std::vector<int> bar (5,0);

	std::vector<int> tmp(bar);
		// std::cout << "wow" << std::endl;
	bar.resize(2);

	for (std::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << *it << '\n';

	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Capacity of foo: " << int(foo.capacity()) << '\n';
	std::cout << "-----------------------" << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
	std::cout << "Capacity of bar: " << int(bar.capacity()) << '\n';
	std::cout << "-----------------------" << '\n';
	std::cout << "Size of tmp: " << int(tmp.size()) << '\n';
	std::cout << "Capacity of tmp: " << int(tmp.capacity()) << '\n';

	ft::iterator<int> it(&tmp[0]);

	return 0;
}
