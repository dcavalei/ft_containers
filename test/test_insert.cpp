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

/*
	This test is done according to macOS version of vector,
	the capacity will differ from linux to macOS.
*/

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

	vector		vec;
	vector		vec_full(3);

	for (size_type i = 0; i < SIZE; i++) {
		vec_full.push_back(rand() % 100);
	}

	iterator it(vec.begin());

	for (size_type i = 0; i < 100; i++) {
		display(vec);
		it = vec.insert(it, rand() % 100);
		display(vec);
		it = vec.insert(vec.begin() + (rand() % vec.size()), rand() % 100);
	}
	display(vec);

	it = vec_full.begin();
	for (size_type i = 0; i < 100; i++) {
		display(vec_full);
		it = vec_full.insert(it, rand() % 100);
		display(vec_full);
		it = vec_full.insert(vec_full.begin() + (rand() % vec_full.size()), rand() % 100);
	}
	display(vec_full);

	vec.insert(vec.begin(), 2, 1);
	for (size_type i = 0; i < 100; i++) {
		display(vec);
		vec.insert(vec.begin(), rand() % 10, rand() % 100);
		display(vec);
		vec.insert(vec.begin() + (rand() % vec.size()), rand() % 10, rand() % 100);
	}
	display(vec);

	vector vec2;
	vec2.insert(vec2.begin(), vec_full.begin(), vec_full.end());
	for (size_type i = 0; i < 100; i++) {
		display(vec2);
		vec2.insert(vec2.begin() , vec_full.begin(), vec_full.begin() + 10);
		display(vec2);
		vec2.insert(vec2.begin() + (rand() % vec2.size()), vec_full.begin(), vec_full.begin() + 10);
	}
	display(vec);

	return 0;
}
