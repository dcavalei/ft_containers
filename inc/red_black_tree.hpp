#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <functional>

namespace ft {

	enum RBTcolor { red, black };

	template< class T >
	struct node {

		typedef T		value_type;
		typedef T*		pointer;

		explicit node() :
			color(red),
			content(NULL),
			parent(NULL),
			left(NULL),
			right(NULL) {};

		explicit node( pointer v ) :
			color(red),
			content(v),
			parent(NULL),
			left(NULL),
			right(NULL) {}

		~node() {}

		RBTcolor	color;
		pointer		content;
		node*		parent;
		node*		left;
		node*		right;

	};

	// (1)	Every node in T is either red or black.
	// (2)	The root node of T is black.
	// (3)	Every NULL node is black. (NULL nodes are the leaf nodes. They do not contain any keys. When we search for a key that is not present in the tree, we reach the NULL node.)
	// (4)	If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
	// (5)	Every path from a root node to a NULL node has the same number of black nodes.

	template<
		class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T>
	> class RedBlackTree {

	/* ************************************** Member types ************************************** */

		public:

		typedef T			value_type;
		typedef Alloc		allocator_type;
		typedef node<T>*	node_pointer;

		static const node_pointer nil = NULL;

		private:

		allocator_type	_alloc;
		node_pointer	_root;

		public:

		explicit RedBlackTree( const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_root(NULL) {}

		~RedBlackTree() {
			// later do some tree clear function;
		}

		void	insert( const value_type& value ) {

			node_pointer node = new_node(value);

			node_pointer parent = NULL;
			node_pointer current = _root;

			while (current != nil) {
				parent = current;
				if (Compare(*node->content, *current->content)) {
					current = current->left;
				} else {
					current = current->right;
				}
			}

			// 'parent' is parent of 'node'
			node->parent = parent;
			if (parent == NULL) {
				_root = node;
			} else if (Compare(*node->content, *parent->content)) {
				parent->left = node;
			} else {
				parent->right = node;
			}

			// if 'node' is a root node, simply return
			if (node->parent == NULL){
				node->color = black;
				return;
			}

			// if the grandparent is null, simply return
			if (node->parent->parent == NULL) {
				return;
			}

			// fixInsert(node); PLEASEASDADSASDASD
		}

		void	remove( const value_type& value );

		private:

		node_pointer	new_node( const value_type& value ) {
			node_pointer	ptr = new node<T>(_alloc.allocate(1));

			_alloc.construct(ptr->content, value);
			return (ptr);
		}

	// fix the red-black tree

	// void fixInsert(NodePtr k){
	// 	NodePtr u;
	// 	while (k->parent->color == 1) {
	// 		if (k->parent == k->parent->parent->right) {
	// 			u = k->parent->parent->left; // uncle
	// 			if (u->color == 1) {
	// 				// case 3.1
	// 				u->color = 0;
	// 				k->parent->color = 0;
	// 				k->parent->parent->color = 1;
	// 				k = k->parent->parent;
	// 			} else {
	// 				if (k == k->parent->left) {
	// 					// case 3.2.2
	// 					k = k->parent;
	// 					rightRotate(k);
	// 				}
	// 				// case 3.2.1
	// 				k->parent->color = 0;
	// 				k->parent->parent->color = 1;
	// 				leftRotate(k->parent->parent);
	// 			}
	// 		} else {
	// 			u = k->parent->parent->right; // uncle
	//
	// 			if (u->color == 1) {
	// 				// mirror case 3.1
	// 				u->color = 0;
	// 				k->parent->color = 0;
	// 				k->parent->parent->color = 1;
	// 				k = k->parent->parent;
	// 			} else {
	// 				if (k == k->parent->right) {
	// 					// mirror case 3.2.2
	// 					k = k->parent;
	// 					leftRotate(k);
	// 				}
	// 				// mirror case 3.2.1
	// 				k->parent->color = 0;
	// 				k->parent->parent->color = 1;
	// 				rightRotate(k->parent->parent);
	// 			}
	// 		}
	// 		if (k == root) {
	// 			break;
	// 		}
	// 	}
	// 	root->color = 0;
	// }

	/* ************************************ Helper functions ************************************ */


	};

}

#endif // RED_BLACK_TREE_HPP
