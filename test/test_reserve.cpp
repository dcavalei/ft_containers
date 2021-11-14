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

void	test_reserve( size_type initial_size, size_type to_reserve ) {
	static int	n = 0;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	ft::vector<int>	foo(initial_size);
	ft::vector<int>	bar(foo);
	size_type		size;

	size = foo.size();
	for (size_type	i = 0; i < size; i++) {
		foo[i] = rand() % MAX_RANGE;
	}

	foo.reserve(to_reserve);
	size = foo.size();

	std::cout << "[values]";
	for (size_type	i = 0; i < size; i++) {
		std::cout << ' ' << foo[i];
	}
	std::cout << std::endl;

	std::cout << "[size] " << foo.size() << std::endl;
	std::cout << "[capacity] " << foo.capacity() << std::endl;

}

int main ()
{
	test_reserve(10, 0);
	test_reserve(10, 1);
	test_reserve(10, 9);
	test_reserve(10, 10);
	test_reserve(10, 11);
	test_reserve(10, 20);

	srand(SEED);
	for (size_t i = 0; i < NUMBER_OF_TESTS; i++) {
		test_reserve(rand() % MAX_RANGE, rand() % MAX_RANGE);
	}

	return (0);
}
