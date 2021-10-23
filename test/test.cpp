#include "test.hpp"

void	test::sigsegv( int signal ) {
	(void)signal;
	std::cout << _BLUE_ << "SIGSEGV" << _RESET_ << std::endl;
	exit(EXIT_SUCCESS);
}

void	test::ok() {
	std::cout << _GREEN_ << "OK" << _RESET_ << std::endl;
}

void	test::ko() {
	std::cout << _RED_ << "KO" << _RESET_ << std::endl;
}
