#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"

template <class T>
typename ft::enable_if< ft::is_integral<T>::value, bool >::type	is_odd (T i) {
	return (i % 2);
}

int main () {

	ft::vector<int> foo (2,100);
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

	std::cout << ft::is_integral<int>::value << std::endl;

	short int i = 1;

	std::cout << std::boolalpha;
 	std::cout << "i is odd: " << is_odd(i) << std::endl;
	// std::cout << "i is even: " << is_even(i) << std::endl;

	return 0;
}
