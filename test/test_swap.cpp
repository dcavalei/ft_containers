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

	vector		vec1;
	vector		vec2;

	for (size_type i = 0; i < SIZE; i++) {
		vec1.push_back(rand() % 100);
	}

	for (size_type i = 0; i < SIZE * 2; i++) {
		vec2.push_back(rand() % 100);
	}

	std::cout << "[before swap]\n" << std::endl;

	std::cout << "------------------------" << std::endl;
	display(vec1);
	std::cout << "------------------------" << std::endl;
	display(vec2);
	std::cout << "------------------------" << std::endl;

	iterator	vec1_begin(vec1.begin());
	iterator	vec1_end(vec1.end());
	iterator	vec1_random(vec1.begin() + rand() % vec1.size());

	iterator	vec2_begin(vec2.begin());
	iterator	vec2_end(vec2.end());
	iterator	vec2_random(vec2.begin() + rand() % vec2.size());


	vec1.swap(vec2);

	std::cout << "\n[after swap]\n" << std::endl;

	std::cout << "------------------------" << std::endl;
	display(vec1);
	std::cout << "------------------------" << std::endl;
	display(vec2);
	std::cout << "------------------------" << std::endl;

	std::cout << "\n[iterators]\n" << std::endl;

	std::cout << "[values] "
		<< *vec1_begin << ' '
		<< *(vec1_end - 1) << ' '
		<< *vec1_random
	<< std::endl;

	std::cout << "[values] "
		<< *vec2_begin << ' '
		<< *(vec2_end - 1) << ' '
		<< *vec2_random
	<< std::endl;

	return 0;
}
