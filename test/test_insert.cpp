#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>
# include <vector>

# define SIZE 42

typedef	std::vector<int>::size_type	size_type;
typedef	std::vector<int>				vector;
typedef	std::vector<int>::iterator	iterator;

void	display( vector& vec ) {
	std::cout << "[# Display #]" << std::endl;
	std::cout << "[values]";
	for (iterator i = vec.begin(); i != vec.end(); ++i) {
		std::cout << ' ' << *i;
	}
	std::cout << std::endl;
	std::cout << "[size] "<< vec.size() << std::endl;
	std::cout << "[capacity] "<< vec.capacity() << std::endl;


}

int main() {

	vector		vec(3);
	vector		vec_full;

	for (size_type i = 0; i < SIZE; i++)
	{
		vec_full.push_back(rand() % 100);
	}

	iterator itB(vec_full.begin());
	iterator itE(vec_full.begin() + 7);

	vec.insert(vec.begin(), itB, itE);

	display(vec_full);
	display(vec);
	iterator	it = vec.insert(vec.begin(), 42);
	display(vec);
	it = vec.insert(it, 43);
	display(vec);
	it = vec.insert(it, 44);
	display(vec);

	
	// std::cout << "[#### Testing insert() ####]" << std::endl;
	// display(vec);
	// it = vec.insert(it, 42);
	// it = vec.insert(it, 42);
	// it = vec.insert(it, 42);
	return 0;
}
