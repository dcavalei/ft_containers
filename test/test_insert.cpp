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

void	display( vector& vec ) {
	static int n;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;
	std::cout << "[values]";
	for (iterator i = vec.begin(); i != vec.end(); ++i) {
		std::cout << ' ' << *i;
	}
	std::cout << std::endl;
	std::cout << "[size] "<< vec.size() << std::endl;
	std::cout << "[capacity] "<< vec.capacity() << std::endl;


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

	return 0;
}
