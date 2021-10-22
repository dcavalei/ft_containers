#ifndef TEST_HPP
# define TEST_HPP

# include <vector>
# include <csignal>
# include <iostream>
# include <cstdlib>
# include "color.hpp"

namespace test {

	struct Base {

		std::string*	base_ptr;
		static int		base_leak;

		Base() {
			base_ptr = new std::string("Base Default C/tor");	base_leak++;
		}

		Base( const Base& other ) {
			(void)other;
			base_ptr = new std::string("Base Copy C/tor");	base_leak++;
		}

		virtual ~Base() {
			std::cout << "Base D/tor [" << *base_ptr << "]" << std::endl;	base_leak--;
			delete base_ptr;
		}
	};

	struct Derived : public Base {

		std::string*	derived_ptr;
		static int		derived_leak;

		Derived() {
			derived_ptr = new std::string("Derived Default C/tor");	derived_leak++;
		}

		Derived( const Derived& other ) {
			(void)other;
			derived_ptr = new std::string("Derived Copy C/tor");	derived_leak++;
		}

		~Derived() {
			std::cout << "Derived D/tor [" << *derived_ptr << "]" << std::endl;	derived_leak--;
			delete derived_ptr;
		}
	};

	int Derived::derived_leak = 0;
	int Base::base_leak = 0;

	void	sigsegv( int signal );
	void	test_instances();

}

#endif
