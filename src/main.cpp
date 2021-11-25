#include <iostream>
#include <vector>
#include <iterator>
#include <memory>

#include "vector.hpp"
#include "iterator.hpp"
#include "test.hpp"
#include "red_black_tree.hpp"

int main () {

	std::cout << std::boolalpha;

	ft::bidirectional_iterator<int>::value_type name;
	name = 1;

	std::cout << name << std::endl;
	std::cout << ft::is_same< ft::bidirectional_iterator<int>::iterator_category, std::bidirectional_iterator_tag >::value << std::endl;

	ft::bidirectional_iterator<test::Base> yo;

	yo->announce();
	ft::node<int> asdadname;

	return 0;
}
