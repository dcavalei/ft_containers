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

	vector		vec;
	vector		vec_full(3);

	for (size_type i = 0; i < SIZE; i++) {
		vec_full.push_back(rand() % 100);
	}

	vec = vec_full;
	display(vec);
	while (vec.size()) {
		vec.erase(vec.begin());
		display(vec);
	}

	iterator	it(vec.begin());

	vec = vec_full;
	display(vec);
	while (it != vec.end()) {
		it = vec.erase(it);
		display(vec);
	}

	vec = vec_full;
	it = vec.end();
	display(vec);
	while (--it != vec.begin() - 1) {
		it = vec.erase(it);
		display(vec);
	}

	vec = vec_full;
	display(vec);
	vec.erase(vec.begin(), vec.end());
	display(vec);

	vec = vec_full;
	display(vec);
	vec.erase(vec.begin(), vec.begin() + vec.size() / 2);
	display(vec);



	return 0;
}
