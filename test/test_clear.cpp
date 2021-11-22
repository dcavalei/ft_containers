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

void	display( vector& vec ) {
	static int n;

	std::cout << "[# Test " << ++n << " #]" << "[values]";
	for (iterator i = vec.begin(); i != vec.end(); ++i) {
		std::cout << ' ' << *i;
	}
	std::cout << std::endl;
	std::cout << "[# Test " << ++n << " #]" << "[size] "<< vec.size() << std::endl;
	std::cout << "[# Test " << ++n << " #]" << "[capacity] "<< vec.capacity() << std::endl;

}

int main() {

	vector		vec_full;

	for (size_type i = 0; i < SIZE; i++) {
		vec_full.push_back(rand() % 100);
	}

	display(vec_full);
	vec_full.clear();
	display(vec_full);

	return 0;
}
