#ifndef _IS_TEST
# include <stack>
namespace ft = std;
#else
# include "stack.hpp"
#endif // _IS_TEST

typedef	ft::stack<int>				stack;

#include <iostream>
#include <vector>

int main()
{

	stack	foo;
	stack	bar;

	std::cout << std::boolalpha;

	std::cout << "foo.empty() » " << foo.empty() << '\n';
	std::cout << "bar.empty() » " << bar.empty() << '\n';

	std::cout << "----------------------------" << std::endl;

	std::cout << "foo == bar returns " << (foo == bar) << '\n';
	std::cout << "foo != bar returns " << (foo != bar) << '\n';
	std::cout << "foo <  bar returns " << (foo < bar) << '\n';
	std::cout << "foo <= bar returns " << (foo <= bar) << '\n';
	std::cout << "foo >  bar returns " << (foo > bar) << '\n';
	std::cout << "foo >= bar returns " << (foo >= bar) << '\n';

	std::cout << "----------------------------" << std::endl;

	foo.push(1);
	bar.push(1);
	bar.push(3);

	std::cout << "foo.size() » " << foo.size() << '\n';
	std::cout << "bar.size() » " << bar.size() << '\n';

	std::cout << "----------------------------" << std::endl;


	std::cout << "foo == bar returns " << (foo == bar) << '\n';
	std::cout << "foo != bar returns " << (foo != bar) << '\n';
	std::cout << "foo <  bar returns " << (foo < bar) << '\n';
	std::cout << "foo <= bar returns " << (foo <= bar) << '\n';
	std::cout << "foo >  bar returns " << (foo > bar) << '\n';
	std::cout << "foo >= bar returns " << (foo >= bar) << '\n';

	std::cout << "----------------------------" << std::endl;

	foo.push(2);

	std::cout << "foo == bar returns " << (foo == bar) << '\n';
	std::cout << "foo != bar returns " << (foo != bar) << '\n';
	std::cout << "foo <  bar returns " << (foo < bar) << '\n';
	std::cout << "foo <= bar returns " << (foo <= bar) << '\n';
	std::cout << "foo >  bar returns " << (foo > bar) << '\n';
	std::cout << "foo >= bar returns " << (foo >= bar) << '\n';

	std::cout << "----------------------------" << std::endl;

	foo.push(42);
	bar.push(42);

	std::cout << "foo.top() » " << foo.top() << '\n';
	std::cout << "bar.top() » " << bar.top() << '\n';

	std::cout << "----------------------------" << std::endl;

	foo.pop();
	bar.pop();

	std::cout << "foo.pop() (than tpop to show value) » " << foo.top() << '\n';
	std::cout << "bar.pop() (than tpop to show value) » " << bar.top() << '\n';


	return 0;
}
