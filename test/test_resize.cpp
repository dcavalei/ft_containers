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

void	test_resize( size_type initial_size, size_type to_resize, int val ) {
	static int	n = 0;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;
	std::cout << "[initial size] " << initial_size << std::endl;
	std::cout << "[expected size] " << to_resize << std::endl;

	ft::vector<int>	foo(initial_size);
	size_type		size;

	size = foo.size();
	for (size_type	i = 0; i < size; i++) {
		foo[i] = rand() % MAX_RANGE;
	}


	foo.resize(to_resize, val);
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
	srand(SEED);
	for (size_t i = 0; i < NUMBER_OF_TESTS; i++) {
		test_resize(rand() % MAX_RANGE, rand() % MAX_RANGE, rand() % MAX_RANGE);
	}

	return (0);
}
