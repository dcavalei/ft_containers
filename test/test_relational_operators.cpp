#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif // _IS_TEST

#include <iostream>

typedef	ft::vector<int>				vector;

#include <iostream>

int main ()
{
	vector foo(3, 100);
	vector foo_copy(foo);
	vector bar(2, 200);

	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

	std::cout << "-----------------------------------------------" << std::endl;

	if (foo==foo_copy) std::cout << "foo and foo_copy are equal\n";
	if (foo!=foo_copy) std::cout << "foo and foo_copy are not equal\n";
	if (foo< foo_copy) std::cout << "foo is less than foo_copy\n";
	if (foo> foo_copy) std::cout << "foo is greater than foo_copy\n";
	if (foo<=foo_copy) std::cout << "foo is less than or equal to foo_copy\n";
	if (foo>=foo_copy) std::cout << "foo is greater than or equal to foo_copy\n";

	return 0;
}