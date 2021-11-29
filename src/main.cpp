#include <iostream>
#include <vector>
#include <iterator>
#include <memory>

#include "vector.hpp"
#include "iterator.hpp"
#include "test.hpp"
#include "red_black_tree.hpp"
#include "map.hpp"

typedef ft::pair<std::string, int> pair;
typedef ft::map<std::string, int> map;
int main () {

	ft::RedBlackTree<int>	rbt;


for (size_t i = 0; i < 20; i++)
{
	rbt.insert(i);
}

std::cout << "start " << *rbt.start()->data << std::endl;
std::cout << "last " << *rbt.last()->data << std::endl;

ft::RedBlackTree<int>::iterator it = rbt.start();
ft::RedBlackTree<int>::iterator ite = rbt.last();
for ( ; it != 0; it++)
{
	std::cout << "data " << *(it) << std::endl;
}
// --it;


for (size_t i = 0; i < 20; i++)
{
	std::cout << "-----------" << std::endl;

	ft::RBTnode<int> *data;
	data = rbt.successor(rbt.findKey(rbt._root, i));
	if (data) {
		std::cout << "next " << *data->data << std::endl;
	} else {
		std::cout << "next " << data << std::endl;
	}
	data = rbt.predecessor(rbt.findKey(rbt._root, i));
	if (data) {
		std::cout << "prev " << *data->data << std::endl;
	} else {
		std::cout << "prev p " << data << std::endl;
	}
	rbt.remove(i);
}


	rbt.prettyPrint();



	rbt.clear();

	rbt.prettyPrint();

	// map map;
	// map.insert(pair("ola", 42));

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
