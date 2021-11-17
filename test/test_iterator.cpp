#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>

# define SIZE 42

typedef ft::vector<int>::iterator 			iterator;
typedef ft::vector<int>::const_iterator		const_iterator;

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

		iterator	iter;
		iter = vec.begin();

		std::cout << "[original values]";
		for (iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[copy values]";
		for (iterator it(iter); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[operator test]" << std::endl;
		std::cout << std::boolalpha;
		std::cout << "[ Test " << ++n << " ] " << (iter == vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter != vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter < vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter > vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter <= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter >= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter == vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter != vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter < vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter > vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter <= vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter >= vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) == vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) != vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) < vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) > vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) <= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter + 10) >= vec.begin()) << std::endl;
		{
			ft::vector<Test>			tmp;
			ft::vector<Test>::iterator	it;
			std::cout << "[ Test " << ++n << " ] " << it->annouce() << std::endl;
		}
		std::cout << "[ Test " << ++n << " ] " << (*iter = 123) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*iter++ = 456) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*++iter = 789) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*iter-- = 111) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*--iter = 222) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*iter++ = 333) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*iter++ = 444) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*iter++ = 555) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(iter + 2) = 666) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(iter - 2) = 777) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(iter += 3) = 888) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (*(iter -= 3) = 999) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter[3] = 42) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter[-1] = 42) << std::endl;

		std::cout << "[values]";
		for (iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;
	}
	{
		std::cout << std::endl << "[#### Testing const_iterator ####]" << std::endl;

		const_iterator	iter_const(vec.begin());

		const ft::vector<int> name(vec);

		ft::vector<int>::const_iterator i = name.begin();
		i = name.end();
		iter_const = vec.begin();

		std::cout << "[original values]";
		for (const_iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[copy values]";
		for (const_iterator it(iter_const); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;

		std::cout << "[operator test]" << std::endl;
		std::cout << std::boolalpha;
		std::cout << "[ Test " << ++n << " ] " << (iter_const == vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const != vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const < vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const > vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const <= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const >= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const == vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const != vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const < vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const > vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const <= vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << (iter_const >= vec.end()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) == vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) != vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) < vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) > vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) <= vec.begin()) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << ((iter_const + 10) >= vec.begin()) << std::endl;
		{
			ft::vector<Test>					tmp;
			ft::vector<Test>::const_iterator	it;
			std::cout << "[ Test " << ++n << " ] " << it->annouce() << std::endl;
		}
		std::cout << "[ Test " << ++n << " ] " << *iter_const << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *iter_const++ << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *++iter_const << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *iter_const-- << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *--iter_const << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *iter_const++ << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *iter_const++ << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *iter_const++ << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *(iter_const + 2) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *(iter_const - 2) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *(iter_const += 3) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << *(iter_const -= 3) << std::endl;
		std::cout << "[ Test " << ++n << " ] " << iter_const[3] << std::endl;
		std::cout << "[ Test " << ++n << " ] " << iter_const[-1] << std::endl;

		std::cout << "[values]";
		for (const_iterator it = vec.begin(); it != vec.end(); it++) {
			std::cout << ' ' << *it;
		}
		std::cout << std::endl;
	}
	return 0;
}
