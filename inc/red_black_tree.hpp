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

		RBTcolor color;
		pointer data;
		RBTnode *parent;
		RBTnode *left;
		RBTnode *right;

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
	};

	template <
		class T,
		class Compare = std::less<T>,
		class Equal = std::equal_to<T>,
		class Alloc = std::allocator<T> >
	class RedBlackTree
	{

		/* ************************************ Member types ************************************ */

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef Compare key_compare;
		typedef Equal key_equal;
		typedef RBTnode<T> node;
		typedef node *node_pointer;

	public:
		explicit RedBlackTree(
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			const key_equal &equal = key_equal()) : _alloc(alloc),
													_equal(equal),
													_comp(comp),
													_nil(new node(black)),
													_root(_nil) {}

		~RedBlackTree()
		{
			clear();
			delete (_nil);
		}

		void insert(const value_type &key)
		{

			node_pointer n = newNode(key);

			rbtInsert(n);
			fixInsert(n);
		}

		node_pointer findKey(node_pointer x, const value_type &key)
		{
			node_pointer z = _nil;

			while (x != _nil)
			{
				if (_equal(*x->data, key))
				{
					z = x;
				}

				if (_comp(*x->data, key))
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

		void remove(const value_type &key)
		{
			node_pointer node = findKey(_root, key);

			if (node == _nil)
			{
				return;
			}

			rbtDelete(node);
		}

		void clear()
		{
			for (node_pointer x = _root; x != _nil; x = _root)
			{
				rbtDelete(x);
			}
		}

		/* ************************************ Helper functions ************************************ */

	private:
		node_pointer min(node_pointer x)
		{
			while (x->left != _nil)
			{
				x = x->left;
			}
			return x;
		}

		node_pointer max(node_pointer x)
		{
			while (x->right != _nil)
			{
				x = x->right;
			}
			return x;
		}

		node_pointer successor(node_pointer x)
		{
			if (x->right != _nil)
			{
				return min(x->right);
			}

			node_pointer y = x->parent;
			while (y != _nil && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		node_pointer predecessor(node_pointer x)
		{
			if (x->left != _nil)
			{
				return max(x->left);
			}

			node_pointer y = x->parent;
			while (y != _nil && x == y->left)
			{
				x = y;
				y = y->parent;
			}

			return y;
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

	private:
		void freeNode(node_pointer n)
		{
			_alloc.destroy(n->data);
			_alloc.deallocate(n->data, 1);
			delete n;
		}

		void fixDelete(node_pointer x)
		{
			node_pointer s;
			while (x != _root && x->color == black)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == red)
					{
						// case 3.1
						s->color = black;
						x->parent->color = red;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == black && s->right->color == black)
					{
						// case 3.2
						s->color = red;
						x = x->parent;
					}
					else
					{
						if (s->right->color == black)
						{
							// case 3.3
							s->left->color = black;
							s->color = red;
							rightRotate(s);
							s = x->parent->right;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = black;
						s->right->color = black;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == red)
					{
						// case 3.1
						s->color = black;
						x->parent->color = red;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == black && s->right->color == black)
					{
						// case 3.2
						s->color = red;
						x = x->parent;
					}
					else
					{
						if (s->left->color == black)
						{
							// case 3.3
							s->right->color = black;
							s->color = red;
							leftRotate(s);
							s = x->parent->left;
						}

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = black;
						s->left->color = black;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = black;
		}

		void rbtDelete(node_pointer z)
		{
			RBTcolor ori;
			node_pointer x, y;

			y = z;
			ori = y->color;
			if (z->left == _nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == _nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = min(z->right);
				ori = y->color;
				x = y->right;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			freeNode(z);
			if (ori == black)
			{
				fixDelete(x);
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

		void rbtInsert(node_pointer n)
		{
			node_pointer y = 0;
			node_pointer x = _root;

			while (x != _nil)
			{
				y = x;
				if (_comp(*n->data, *x->data))
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
			else if (_comp(*n->data, *y->data))
			{
				y->left = n;
			}
			else
			{
				y->right = n;
			}
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

		void transplant(node_pointer u, node_pointer v)
		{
			if (u->parent == 0)
			{
				_root = v;
			}
			else if (u == u->parent->left)
			{
				u->parent->left = v;
			}
			else
			{
				u->parent->right = v;
			}
			v->parent = u->parent;
		}

		node_pointer newNode(const value_type &key)
		{
			node_pointer n = new node(_alloc.allocate(1));

			_alloc.construct(n->data, key);
			n->parent = 0;
			n->left = _nil;
			n->right = _nil;
			return (n);
		}

		allocator_type _alloc;
		Equal _equal;
		Compare _comp;
		node_pointer _nil;
		node_pointer _root;
	};

}

#endif // RED_BLACK_TREE_HPP
