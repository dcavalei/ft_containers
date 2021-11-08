#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif

# include "test.hpp"

void	test_instances() {
	std::cout << "[Object Creation/Destruction] ";
	{
		ft::vector<int>				int_vector(10);
		ft::vector<test::Base>		base_vector(10);
		ft::vector<test::Derived>	derived_vector(10);
	}

	{
		ft::vector<int>				int_vector(10, 42);
		ft::vector<test::Base>		base_vector(10, test::Base());
		ft::vector<test::Derived>	derived_vector(10, test::Derived());
	}

	if (test::Base::base_leak || test::Derived::derived_leak) {
		std::cout << "KO" << std::endl;
	} else {
		std::cout << "OK" << std::endl;
	}
}

void	show_capacity() {
	std::cout << "[Capacity] ";

	ft::vector<int>				int_vector(10, 42);
	ft::vector<test::Base>		base_vector(10, test::Base());
	ft::vector<test::Derived>	derived_vector(10, test::Derived());

	std::cout
		<< int_vector.capacity() << ' '
		<< base_vector.capacity() << ' '
		<< derived_vector.capacity()
	<< std::endl;
}

void	show_size() {
	std::cout << "[Size] ";

	ft::vector<int>				int_vector(10, 42);
	ft::vector<test::Base>		base_vector(10, test::Base());
	ft::vector<test::Derived>	derived_vector(10, test::Derived());

	std::cout
		<< int_vector.size() << ' '
		<< base_vector.size() << ' '
		<< derived_vector.size()
	<< std::endl;
}

void	show_max_size() {
	std::cout << "[Max Size] ";

	ft::vector<int>				int_vector(10, 42);
	ft::vector<test::Base>		base_vector(10, test::Base());
	ft::vector<test::Derived>	derived_vector(10, test::Derived());

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

	std::cout << "* Testing fill Constructor *" << std::endl;
	test_instances();
	show_capacity();
	show_size();
	show_max_size();
	return 0;
}
