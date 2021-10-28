#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#endif

#ifdef _IS_TEST
# include "vector.hpp"
#endif

#include "test.hpp"

void	test_instances() {
	std::cout << "[Object Creation/Destruction] ";
	{
		ft::vector<int>				int_vector;
		ft::vector<test::Base>		base_vector;
		ft::vector<test::Derived>	derived_vector;
	}
	if (test::Base::base_leak || test::Derived::derived_leak) {
		test::ko();
	} else {
		test::ok();
	}
}

void	show_capacity() {
	std::cout << "[Capacity] ";

	ft::vector<int>				int_vector;
	ft::vector<test::Base>		base_vector;
	ft::vector<test::Derived>	derived_vector;

	std::cout
		<< int_vector.capacity() << ' '
		<< base_vector.capacity() << ' '
		<< derived_vector.capacity()
	<< std::endl;
}

void	show_size() {
	std::cout << "[Size] ";

	ft::vector<int>				int_vector;
	ft::vector<test::Base>		base_vector;
	ft::vector<test::Derived>	derived_vector;

	std::cout
		<< int_vector.size() << ' '
		<< base_vector.size() << ' '
		<< derived_vector.size()
	<< std::endl;
}

void	show_max_size() {
	std::cout << "[Max Size] ";

	ft::vector<int>				int_vector;
	ft::vector<test::Base>		base_vector;
	ft::vector<test::Derived>	derived_vector;

	std::cout
		<< int_vector.max_size() << ' '
		<< base_vector.max_size() << ' '
		<< derived_vector.max_size()
	<< std::endl;
}

int test::Derived::derived_leak = 0;
int test::Base::base_leak = 0;

int main() {
	std::signal(SIGSEGV, test::sigsegv);

	std::cout << "* Testing Default Constructor *" << std::endl;
	test_instances();
	show_capacity();
	show_size();
	show_max_size();

	return 0;
}
