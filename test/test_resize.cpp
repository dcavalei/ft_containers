#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif

# include <iostream>
# include <cstdlib>

typedef	ft::vector<int>::size_type	size_type;

void	test_resize( size_type initial_size, size_type to_resize, int val ) {
	static int	n = 0;

	std::cout << "[##### Test " << ++n << " #####]" << std::endl;

	ft::vector<int>				foo(initial_size);
	ft::vector<int>				bar(foo);
	ft::vector<int>::size_type	size;


	foo.resize(to_resize, val);
	size = foo.size();

	int	trigger = 0;
	for (ft::vector<int>::size_type	i = 0; i < size; i++) {
		if (foo[i] != bar[i]) {
			trigger = 1;
			break;
		}
	}

	if (trigger) {
		std::cout << "[values] KO" << std::endl;
	} else {
		std::cout << "[values] OK" << std::endl;
	}
	std::cout << "[size] " << foo.size() << std::endl;
	std::cout << "[capacity] " << foo.capacity() << std::endl;

}

int main ()
{
	size_t	number_of_tests = 10;
	size_t	max_range = 100;
	size_t	seed = 42;

	srand(seed);
	for (size_t i = 0; i < number_of_tests; i++) {
		test_resize(rand() % max_range, rand() % max_range, rand() % max_range);
	}

	return (0);
}
