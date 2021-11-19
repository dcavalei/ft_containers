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
	vector		vec_full;

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

	it = vec.insert(vec.begin(), 10);
	display(vec);
	it = vec.insert(vec.begin(), 20);
	display(vec);
	it = vec.insert(it, 30);
	display(vec);
	it = vec.insert(it, 40);
	display(vec);
	it = vec.insert(it, 50);
	display(vec);


	
	// std::cout << "[#### Testing insert() ####]" << std::endl;
	// display(vec);
	// it = vec.insert(it, 42);
	// it = vec.insert(it, 42);
	// it = vec.insert(it, 42);
	return 0;
}
