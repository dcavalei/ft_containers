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
		ft::vector<int>				int_vector(10, 42);
		ft::vector<test::Base>		base_vector(10, test::Base());
		ft::vector<test::Derived>	derived_vector(10, test::Derived());

		ft::vector<int>				int_vector_range(int_vector.begin(), int_vector.end());
		ft::vector<test::Base>		base_vector_range(base_vector.begin(), base_vector.end());
		ft::vector<test::Derived>	derived_vector_range(derived_vector.begin(), derived_vector.end());
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

	ft::vector<int>				int_vector_range(int_vector.begin(), int_vector.end());
	ft::vector<test::Base>		base_vector_range(base_vector.begin(), base_vector.end());
	ft::vector<test::Derived>	derived_vector_range(derived_vector.begin(), derived_vector.end());

	std::cout
		<< int_vector_range.capacity() << ' '
		<< base_vector_range.capacity() << ' '
		<< derived_vector_range.capacity()
	<< std::endl;
}

void	show_size() {
	std::cout << "[Size] ";

	ft::vector<int>				int_vector(10, 42);
	ft::vector<test::Base>		base_vector(10, test::Base());
	ft::vector<test::Derived>	derived_vector(10, test::Derived());

	ft::vector<int>				int_vector_range(int_vector.begin(), int_vector.end());
	ft::vector<test::Base>		base_vector_range(base_vector.begin(), base_vector.end());
	ft::vector<test::Derived>	derived_vector_range(derived_vector.begin(), derived_vector.end());

	std::cout
		<< int_vector_range.size() << ' '
		<< base_vector_range.size() << ' '
		<< derived_vector_range.size()
	<< std::endl;
}

void	show_max_size() {
	std::cout << "[Max Size] ";

	ft::vector<int>				int_vector(10, 42);
	ft::vector<test::Base>		base_vector(10, test::Base());
	ft::vector<test::Derived>	derived_vector(10, test::Derived());

	ft::vector<int>				int_vector_range(int_vector.begin(), int_vector.end());
	ft::vector<test::Base>		base_vector_range(base_vector.begin(), base_vector.end());
	ft::vector<test::Derived>	derived_vector_range(derived_vector.begin(), derived_vector.end());

	std::cout
		<< int_vector_range.max_size() << ' '
		<< base_vector_range.max_size() << ' '
		<< derived_vector_range.max_size()
	<< std::endl;
}

void	show_values() {
	std::cout << "[Values]";

	ft::vector<int>				int_vector(10);

	for (size_t i = 0; i < 10; i++) {
		int_vector[i] = i * 42;
	}

	ft::vector<int>				int_vector_range(int_vector.begin(), int_vector.end());

	for (size_t i = 0; i < 10; i++) {
		std::cout << ' ' << int_vector_range[i];
	}
	std::cout << std::endl;
}

int test::Derived::derived_leak = 0;
int test::Base::base_leak = 0;

int main() {
	std::signal(SIGSEGV, test::sigsegv);

	std::cout << "* Testing range Constructor *" << std::endl;
	test_instances();
	show_capacity();
	show_size();
	show_max_size();
	show_values();
	return 0;
}
