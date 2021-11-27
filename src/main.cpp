#include <iostream>
#include <vector>
#include <iterator>
#include <memory>

#include "vector.hpp"
#include "iterator.hpp"
#include "test.hpp"
#include "red_black_tree.hpp"

int main () {

	ft::RedBlackTree<int>	rbt;


for (size_t i = 0; i < 20; i++)
{
	rbt.insert(i);
}

	rbt.prettyPrint();

	// rbt.insert(12);
	// rbt.insert(15);
	// rbt.insert(13);
	// rbt.insert(4);
	// rbt.insert(3);
	// rbt.insert(2);
	// rbt.insert(6);
	// rbt.insert(11);
	// rbt.insert(5);
	// rbt.insert(14);
	// rbt.insert(7);
	return 0;
}
