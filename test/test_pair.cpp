#ifndef _IS_TEST
#include <utility>      // std::pair
namespace ft = std;
#else
#include "utility.hpp"      // std::pair
#endif

#include <iostream>

int main () {
	ft::pair<int,char>	foo(10,'z');
	ft::pair<int,char>	bar(90,'a');

	if (foo == bar) std::cout << "foo and bar are equal" << std::endl;
	if (foo != bar) std::cout << "foo and bar are not equal" << std::endl;
	if (foo <  bar) std::cout << "foo is less than bar" << std::endl;
	if (foo >  bar) std::cout << "foo is greater than bar" << std::endl;
	if (foo <= bar) std::cout << "foo is less than or equal to bar" << std::endl;
	if (foo >= bar) std::cout << "foo is greater than or equal to bar" << std::endl;

  return 0;
}