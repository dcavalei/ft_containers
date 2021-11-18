#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif

# include <iostream>
# include <cstdlib>

# define MAX_RANGE 1000
# define NUMBER_OF_TESTS 1000
# define SEED 42

typedef	ft::vector<int>::size_type	size_type;
typedef	ft::vector<int>				vector;
typedef	ft::vector<int>::iterator	iterator;

void	test_assign( vector& vec, size_type initial_size, size_type range_size ) {
	static int	n = 0;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	vector	foo(initial_size);
	size_type		size;

	size = foo.size();

	iterator itBegin(vec.begin());
	iterator itEnd(vec.begin() + range_size);

	foo.assign(itBegin, itEnd);


	std::cout << "[values]";
	iterator ite(foo.end());
	for (iterator	it = foo.begin(); it != ite; ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << std::endl;

	std::cout << "[size] " << foo.size() << std::endl;
	std::cout << "[capacity] " << foo.capacity() << std::endl;

}

int main ()
{
	vector		vec(MAX_RANGE);

	for (size_type	i = 0; i < MAX_RANGE; i++) {
		vec[i] = rand() % MAX_RANGE;
	}

	test_assign(vec, 10, 0);
	test_assign(vec, 10, 1);
	test_assign(vec, 10, 9);
	test_assign(vec, 10, 10);
	test_assign(vec, 10, 11);
	test_assign(vec, 10, 20);

	srand(SEED);
	for (size_t i = 0; i < NUMBER_OF_TESTS; i++) {
		test_assign(vec, rand() % MAX_RANGE, rand() % MAX_RANGE);
	}

	return (0);
}
