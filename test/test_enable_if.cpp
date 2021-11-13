#include "type_traits.hpp"
#include <iostream>

template <class T>
typename ft::enable_if< ft::is_integral<T>::value, bool >::type	is_odd (T i) {
	return (i % 2);
}

int main() {

	short int i = 1;

	std::cout << std::boolalpha;
 	std::cout << "i is odd: " << is_odd(i) << std::endl;

	// float i = 1;

	// std::cout << std::boolalpha;
 	// std::cout << "i is odd: " << is_odd(i) << std::endl;


	return 0;
}
