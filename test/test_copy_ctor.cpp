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

		ft::vector<int>				copy_int_vector(int_vector);
		ft::vector<test::Base>		copy_base_vector(base_vector);
		ft::vector<test::Derived>	copy_derived_vector(derived_vector);
	}

	if (test::Base::base_leak || test::Derived::derived_leak) {
		std::cout << "KO" << std::endl;
	} else {
		std::cout << "OK" << std::endl;
	}
}

void	show_capacity() {
	std::cout << "[Capacity] ";

	ft::vector<int>				int_vector(10);
	ft::vector<test::Base>		base_vector(10);
	ft::vector<test::Derived>	derived_vector(10);

	ft::vector<int>				copy_int_vector(int_vector);
	ft::vector<test::Base>		copy_base_vector(base_vector);
	ft::vector<test::Derived>	copy_derived_vector(derived_vector);

	std::cout
		<< copy_int_vector.capacity() << ' '
		<< copy_base_vector.capacity() << ' '
		<< copy_derived_vector.capacity()
	<< std::endl;
}

void	show_size() {
	std::cout << "[Size] ";

	ft::vector<int>				int_vector(10);
	ft::vector<test::Base>		base_vector(10);
	ft::vector<test::Derived>	derived_vector(10);

	ft::vector<int>				copy_int_vector(int_vector);
	ft::vector<test::Base>		copy_base_vector(base_vector);
	ft::vector<test::Derived>	copy_derived_vector(derived_vector);

	std::cout
		<< copy_int_vector.size() << ' '
		<< copy_base_vector.size() << ' '
		<< copy_derived_vector.size()
	<< std::endl;
}

void	show_max_size() {
	std::cout << "[Max Size] ";

	ft::vector<int>				int_vector(10);
	ft::vector<test::Base>		base_vector(10);
	ft::vector<test::Derived>	derived_vector(10);

	ft::vector<int>				copy_int_vector(int_vector);
	ft::vector<test::Base>		copy_base_vector(base_vector);
	ft::vector<test::Derived>	copy_derived_vector(derived_vector);

	std::cout
		<< copy_int_vector.max_size() << ' '
		<< copy_base_vector.max_size() << ' '
		<< copy_derived_vector.max_size()
	<< std::endl;
}

void	show_values() {
	std::cout << "[Values]";

	ft::vector<int>				int_vector(10);

	for (size_t i = 0; i < 10; i++) {
		int_vector[i] = i * 42;
	}

	ft::vector<int>				copy_int_vector(int_vector);

	for (size_t i = 0; i < 10; i++) {
		std::cout << ' ' << copy_int_vector[i];
	}
	std::cout << std::endl;
}

int test::Derived::derived_leak = 0;
int test::Base::base_leak = 0;

int main() {
	std::signal(SIGSEGV, test::sigsegv);

	std::cout << "* Testing copy Constructor *" << std::endl;
	test_instances();
	show_capacity();
	show_size();
	show_max_size();
	show_values();
	return 0;
}
