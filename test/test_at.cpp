#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>

# define SIZE 42

int main() {

	ft::vector<int>	vec(SIZE);

	std::cout << "[#### Testing at() ####]" << std::endl;

	std::cout << "[value atribution]" << std::endl;
	for (std::size_t i = 0; i < SIZE; i++) {
		vec.at(i) = (i + 1) * 42;
	}

	for (std::size_t i = 0; i < SIZE; i++) {
		std::cout << vec.at(i) << std::endl;
	}

	std::cout << vec.size() << std::endl;


	try
	{
		vec.at(-1);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	return 0;
}
