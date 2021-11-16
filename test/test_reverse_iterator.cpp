#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>

# define SIZE 42

typedef ft::reverse_iterator<ft::vector<int>::iterator> 			iterator;

typedef ft::reverse_iterator<ft::vector<int>::iterator>				reverse_iterator;

struct Test {
	Test() {}
	~Test() {}
	const char*	annouce() const {
		return "Hello";
	}
};

int main() {

	ft::vector<int>	vec(SIZE);
	static int		n = 0;

	for (std::size_t i = 0; i < SIZE; i++) {
		vec[i] = (i + 1) * 42;
	}

	{
		std::cout << "[#### Testing iterator ####]" << std::endl;

		reverse_iterator	rit_begin(vec.end());
		reverse_iterator	rit_end(vec.begin());

		std::cout << "[original values]";
		for (reverse_iterator it(vec.end()); it != rit_end; it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[copy values]";
		for (reverse_iterator it(rit_begin); it != rit_end; it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[operator test]" << std::endl;
		std::cout << std::boolalpha;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin == rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin == rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin == rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin != rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin != rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin != rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin < rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin < rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin < rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin > rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin > rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin > rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin <= rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin <= rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin <= rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin >= rit_begin - 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin >= rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin >= rit_begin + 1) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin == rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) == rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) != rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) < rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) > rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) <= rit_begin) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((rit_begin + 10) >= rit_begin) << std::endl;
		{
			ft::vector<Test>			tmp;
			ft::reverse_iterator<ft::vector<Test>::iterator>	it;
			std::cout << "[ Test " << ++n << " ] " << it->annouce() << std::endl;
		}
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin = 123) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin++ = 456) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*++rit_begin = 789) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin-- = 111) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*--rit_begin = 222) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin++ = 333) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin++ = 444) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*rit_begin++ = 555) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(rit_begin + 2) = 666) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(rit_begin - 2) = 777) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(rit_begin += 3) = 888) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(rit_begin -= 3) = 999) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin[3] = 42) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (rit_begin[-1] = 42) << std::endl;

		std::cout << "[values]";
		for (reverse_iterator it(vec.end()); it != rit_end; it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[base function values]";
		for (reverse_iterator it(vec.end() - 1); it != rit_end + 1; it++) {
			std::cout << ' ' << *(it.base());
		}
	}
	return 0;
}
