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
		ft::vector<test::Base>		base_vector(10);
		ft::vector<test::Derived>	derived_vector(10);
	}

	if (test::Base::base_leak || test::Derived::derived_leak) {
		test::ko();
	} else {
		test::ok();
	}
}

int test::Derived::derived_leak = 0;
int test::Base::base_leak = 0;

int main() {
	std::signal(SIGSEGV, test::sigsegv);

	std::cout << "* Testing fill Constructor *" << std::endl;
	test_instances();

	return 0;
}
