#ifndef _IS_TEST
# include <type_traits>
namespace ft = std;
#else
# include "type_traits.hpp"
#endif

#include <iostream>
#include <typeinfo>

static int	n = 0;

template< typename T >
void	test_is_integral() {

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

 	std::cout << typeid(T).name() << ' ' << ft::is_integral<T>::value << std::endl;
}

int main() {
	std::cout << "[* Testing is_integral *]" << std::endl;

	std::cout << std::boolalpha;
	ft::is_integral<void>::value_type value;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	value = ft::true_type();
	std::cout << value << std::endl;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	value = ft::false_type();
	std::cout << value << std::endl;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	std::cout << (ft::is_integral<int>::type() == ft::true_type()) << std::endl;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	std::cout << (ft::is_integral<int>::type() == ft::false_type()) << std::endl;

	test_is_integral<bool>();
	test_is_integral<char>();
	test_is_integral<wchar_t>();
	test_is_integral<signed char>();
	test_is_integral<short int>();
	test_is_integral<int>();
	test_is_integral<long int>();
	test_is_integral<long long int>();
	test_is_integral<unsigned char>();
	test_is_integral<unsigned short int>();
	test_is_integral<unsigned int>();
	test_is_integral<unsigned long int>();
	test_is_integral<unsigned long long int>();
	test_is_integral<float>();
	test_is_integral<double>();
	test_is_integral<void>();
	test_is_integral<void *>();
	test_is_integral<std::string>();
	return 0;
}
