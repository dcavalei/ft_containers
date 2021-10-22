#include "test.hpp"

void	sigsegv( int signal ) {
	(void)signal;
	std::cout << _BLUE_ << "SIGSEGV" << _RESET_ << std::endl;
	exit(EXIT_SUCCESS);
}

void	test_instances() {

}

int main() {
	std::signal(SIGSEGV, sigsegv);

	std::cout << "* Testing Default Constructor *" << std::endl;
{
	std::vector<int>			int_vector;
	std::vector<char>			char_vector;
	std::vector<test::Base>		base_vector;
	std::vector<test::Derived>	derived_vector;
}
	std::cout << "[CLASS INSTANCES] ";
	if (test::Base::base_leak || test::Derived::derived_leak) {
		std::cout << _RED_ << "KO" << _RESET_ << std::endl;
	} else {
		std::cout << _GREEN_ << "OK" << _RESET_ << std::endl;
	}

	return 0;
}
