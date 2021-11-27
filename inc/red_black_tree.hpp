#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>

namespace ft
{

	enum RBTcolor
	{
		red,
		black
	};

	template <class T>
	struct RBTnode
	{
		typedef T value_type;
		typedef T *pointer;

		explicit RBTnode(RBTcolor c = red) : color(c),
											 data(0),
											 parent(0),
											 left(0),
											 right(0) {}

		explicit RBTnode(pointer v) : color(red),
									  data(v),
									  parent(0),
									  left(0),
									  right(0) {}

		~RBTnode() {}

		RBTcolor color;
		pointer data;
		RBTnode *parent;
		RBTnode *left;
		RBTnode *right;
	};

	// (1)	Every node in T is either red or black.
	// (2)	The root node of T is black.
	// (3)	Every NULL node is black. (NULL nodes are the leaf nodes. They do not contain any keys. When we search for a key that is not present in the tree, we reach the NULL node.)
	// (4)	If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
	// (5)	Every path from a root node to a NULL node has the same number of black nodes.

	template <
		class T,
		class CompSort = std::less<T>,
		class CompEqual = std::equal_to<T>,
		class Alloc = std::allocator<T> >
	class RedBlackTree
	{

		/* ************************************** Member types ************************************** */

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef RBTnode<T> node;
		typedef node *node_pointer;

	private:
		allocator_type _alloc;
		node_pointer _nil;
		node_pointer _root;

	public:
		explicit RedBlackTree(const allocator_type &alloc = allocator_type()) : _alloc(alloc),
																				_nil(new node(black)),
																				_root(_nil) {}

		~RedBlackTree()
		{
			// later do some tree clear function;
			delete (_nil);
		}

		void insert(const value_type &key)
		{

			node_pointer n = newNode(key);

			rbtInsert(n);
			fixInsert(n);
		}

		node_pointer findKey(const value_type &key)
		{
			node_pointer x = _root;
			node_pointer z = _nil;
			CompEqual equal;
			CompSort comp;

			while (x != _nil)
			{
				if (equal(*x->data, key))
				{
					z = x;
				}

				if (comp(*x->data, key))
				{
					x = x->right;
				}
				else
				{
					x = x->left;
				}
			}
			return (z);
		}

		void fixDelete(node_pointer x)
		{
			node_pointer w;

			while (x != _root && x->color == black)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						leftRotate(x->parent);
						w = x->parent->right;
					}

					if (w->left->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->right->color == black)
						{
							w->left->color = black;
							w->color = red;
							rightRotate(w);
							w = x->parent->right;
						}

						w->color = x->parent->color;
						x->parent->color = black;
						w->right->color = black;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						rightRotate(x->parent);
						w = x->parent->left;
					}

					if (w->right->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->left->color == black)
						{
							w->right->color = black;
							w->color = red;
							leftRotate(w);
							w = x->parent->left;
						}

						w->color = x->parent->color;
						x->parent->color = black;
						w->left->color = black;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = black;
		}

		void freeNode(node_pointer n)
		{
			_alloc.destroy(n->data);
			_alloc.deallocate(n->data, 1);
			delete n;
		}

		void rbtDelete(node_pointer node)
		{
			RBTcolor orig = node->color;
			node_pointer x;
			node_pointer y;

			if (node == _nil)
			{
				return;
			}

			if (node->left == _nil)
			{
				x = node->right;
				transplant(node, x);
			}
			else if (node->right == _nil)
			{
				x = node->left;
				transplant(node, x);
			}
			else
			{
				y = min(node);
				orig = y->color;
				x = y->right;
				if (y->parent == node)
				{
					x->parent = y;
				}
				else
				{
					transplant(y, y->right);
					y->right = node->right;
					y->right->parent = y;
				}
				transplant(node, y);
				y->left = node->left;
				y->left->parent = y;
				y->color = orig;
			}
			freeNode(node);
			if (orig == black)
			{
				fixDelete(x);
			}
		}

		void remove(const value_type &key)
		{

			node_pointer node = findKey(key);

			if (node == _nil)
			{
				std::cout << "nil" << std::endl;
			}
			else
			{
				std::cout << *node->data << std::endl;
			}

			rbtDelete(node);
		}

		void clear()
		{
			node_pointer x = _root;
			while (x != _nil)
			{
				rbtDelete(x);
				x = _root;
			}
		}

		/* ************************************ Helper functions ************************************ */

	private:
		node_pointer newNode(const value_type &key)
		{
			node_pointer n = new node(_alloc.allocate(1));

			_alloc.construct(n->data, key);
			n->parent = 0;
			n->left = _nil;
			n->right = _nil;
			return (n);
		}

		void rbtInsert(node_pointer n)
		{
			node_pointer y = 0;
			node_pointer x = _root;

			while (x != _nil)
			{
				y = x;
				if (CompSort()(*n->data, *x->data))
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			n->parent = y;
			if (!y)
			{
				_root = n;
			}
			else if (CompSort()(*n->data, *y->data))
			{
				y->left = n;
			}
			else
			{
				y->right = n;
			}
		}

		void fixInsert(node_pointer k)
		{
			node_pointer u;

			if (k->parent == 0)
			{
				k->color = black;
				return;
			}
			if (k->parent->parent == 0)
			{
				return;
			}

			while (k->parent->color == red)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == red)
					{
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							rightRotate(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						leftRotate(k->parent->parent);
					}
				}
				else // mirror
				{
					u = k->parent->parent->right;

					if (u->color == red)
					{
						u->color = black;
						k->parent->color = black;
						k->parent->parent->color = red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color = black;
						k->parent->parent->color = red;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
				{
					break;
				}
			}
			_root->color = black;
		}

		void leftRotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _nil)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == 0)
			{
				_root = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		// rotate right at node x
		void rightRotate(node_pointer x)
		{
			node_pointer y = x->left;
			x->left = y->right;
			if (y->right != _nil)
			{
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == 0)
			{
				_root = y;
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y;
			}
			else
			{
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		void transplant(node_pointer x, node_pointer y)
		{
			if (x->parent == _nil)
			{
				_root = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->parent = x->parent;
		}

		node_pointer min(node_pointer x)
		{
			if (x == _nil)
			{
				return x;
			}

			while (x->left != _nil)
			{
				x = x->left;
			}
			return x;
		}

		node_pointer max(node_pointer x)
		{
			if (x == _nil)
			{
				return x;
			}

			while (x->right != _nil)
			{
				x = x->right;
			}
			return x;
		}

	public:
		void printHelper(node_pointer _root, std::string indent, bool last)
		{
			// print the tree structure on the screen
			if (_root != _nil)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "     ";
				}
				else
				{
					std::cout << "L----";
					indent += "|    ";
				}

				std::string sColor = (_root->color == red) ? "RED" : "BLACK";
				std::cout << *_root->data << "(" << sColor << ")" << std::endl;
				printHelper(_root->left, indent, false);
				printHelper(_root->right, indent, true);
			}
			// std::cout<<root->left->data<<std::endl;
		}
		void prettyPrint()
		{
			if (_root != _nil)
			{
				printHelper(_root, "", true);
			}
		}
	};

}

#endif // RED_BLACK_TREE_HPP
