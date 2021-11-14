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

	std::cout << std::boolalpha;

	std::cout << "ft::is_integral<float>::value_type value = ft::is_integral<float>::value;" << std::endl;
	

	std::cout << (ft::is_integral<int>::type() == ft::true_type()) << std::endl;


	short int i = 1;

 	std::cout << "i is odd: " << is_odd(i) << std::endl;

	ft::integral_constant<int, false>::value_type name = ft::integral_constant<int, true>();

 	std::cout << name << std::endl;

	return 0;
}
