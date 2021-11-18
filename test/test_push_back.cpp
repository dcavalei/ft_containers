#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>

# define SIZE 42

typedef	ft::vector<int>::size_type	size_type;
typedef	ft::vector<int>				vector;
typedef	ft::vector<int>::iterator	iterator;

int main() {

	vector	vec;
	static int n = 0;

	std::cout << "[#### Testing push_back() ####]" << std::endl;

	for (size_type i = 0; i < SIZE; i++) {
		std::cout << "[# Test " << ++n << " #]" << std::endl;
		vec.push_back((i + 1) * 42);

		std::cout << "[values]";
		iterator ite(vec.end());
		for (iterator it(vec.begin()); it != ite; ++it) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[size] "<< vec.size() << std::endl;
		std::cout << "[capacity] "<< vec.capacity() << std::endl;
	}
	std::cout << "[-----------------]" << std::endl;
	std::cout << "[size] "<< vec.size() << std::endl;
	std::cout << "[capacity] "<< vec.capacity() << std::endl;

	vector	vec1(3);
	vec = vec1;

	std::cout << "[size] "<< vec.size() << std::endl;
	std::cout << "[capacity] "<< vec.capacity() << std::endl;
	std::cout << "[-----------------]" << std::endl;

	for (size_type i = 0; i < SIZE; i++) {
		std::cout << "[# Test " << ++n << " #]" << std::endl;
		vec.push_back((i + 1) * 42);

		std::cout << "[values]";
		iterator ite(vec.end());
		for (iterator it(vec.begin()); it != ite; ++it) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[size] "<< vec.size() << std::endl;
		std::cout << "[capacity] "<< vec.capacity() << std::endl;
	}


	vector	vec2(42);
	vec = vec2;

	std::cout << "[size] "<< vec.size() << std::endl;
	std::cout << "[capacity] "<< vec.capacity() << std::endl;
	std::cout << "[-----------------]" << std::endl;

	for (size_type i = 0; i < SIZE; i++) {
		std::cout << "[# Test " << ++n << " #]" << std::endl;
		vec.push_back((i + 1) * 42);

		std::cout << "[values]";
		iterator ite(vec.end());
		for (iterator it(vec.begin()); it != ite; ++it) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[size] "<< vec.size() << std::endl;
		std::cout << "[capacity] "<< vec.capacity() << std::endl;
	}


	return 0;
}
