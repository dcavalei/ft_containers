#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>
#include <stdlib.h>

# define SIZE 42

typedef	ft::vector<int>::size_type	size_type;
typedef	ft::vector<int>				vector;
typedef	ft::vector<int>::iterator	iterator;

int main() {

	vector		vec(SIZE);

	for (size_type	i = 0; i < SIZE; i++) {
		vec[i] = rand() % 100;
	}

	static int n = 0;

	std::cout << "[#### Testing pop_back() ####]" << std::endl;

	for (size_type i = 0; i < SIZE; i++) {
		std::cout << "[# Test " << ++n << " #]" << std::endl;
		vec.pop_back();

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
