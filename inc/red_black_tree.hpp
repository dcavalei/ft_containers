#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <functional>

namespace ft
{

	template <class T> class RBTiterator;
	template <class T> class RBTreverse_iterator;

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
		typedef RBTiterator<value_type> iterator;
		typedef RBTiterator<const value_type> const_iterator;
		typedef RBTreverse_iterator<value_type> reverse_iterator;
		typedef RBTreverse_iterator<const value_type> const_reverse_iterator;

		/* ************************************ Constructors ************************************ */

	public:
		explicit RedBlackTree(
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			const key_equal &equal = key_equal()) : _alloc(alloc),
													_equal(equal),
													_comp(comp),
													_nil(new node(black)),
													_root(_nil) {}

		RedBlackTree(const RedBlackTree &other) : _nil(0), _root(0)
		{
			*this = other;
		}

		~RedBlackTree()
		{
			clear();
			delete (_nil);
		}

		RedBlackTree &operator=(const RedBlackTree &rhs)
		{
			node_pointer last = rhs.last();

			this->~RedBlackTree();
			_alloc = rhs._alloc;
			_equal = rhs._equal;
			_comp = rhs._comp;
			_nil = new node(black);
			_root = _nil;

			for (node_pointer i = rhs.start(); i != last; i = successor(i))
			{
				insert(*(i->data));
			}
			if (last)
			{
				insert(*(last->data));
			}
			return (*this);
		}

		void insert(const value_type &key)
		{
			node_pointer n = newNode(key);

			bstInsert(n, _root);
			fixInsert(n);
		}

		node_pointer findKey(node_pointer x, const value_type &key)
		{
			node_pointer z = NULL;

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

		bool remove(const value_type &key)
		{
			node_pointer node = findKey(_root, key);

			if (node)
			{
				rbtDelete(node);
				return true;
			}
			return false;
		}

		void clearHelper(node_pointer n)
		{
			if (n == _nil)
			{
				return;
			}
			clearHelper(n->left);
			clearHelper(n->right);

			freeNode(n);
		}

		void clear()
		{
			clearHelper(_root);
			_root = _nil;
		}

		/* ********************************** Helper functions ********************************** */

	public:
		static node_pointer min(node_pointer x)
		{
			if (!x && !x->left)
			{
				return (NULL);
			}
			while (x->left->parent)
			{
				x = x->left;
			}
			return x;
		}

		static node_pointer max(node_pointer x)
		{
			if (!x || !x->right)
			{
				return (NULL);
			}
			while (x->right->parent) // while != _nil
			{
				x = x->right;
			}
			return x;
		}

		static node_pointer successor(node_pointer x)
		{
			if (x->right && x->right->parent) // if right != _nil
			{
				return min(x->right);
			}

			node_pointer y = x->parent;
			while (y && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		static node_pointer predecessor(node_pointer x)
		{
			if (x->left && x->left->parent) // if left != _nil
			{
				return max(x->left);
			}

			node_pointer y = x->parent;
			while (y && x == y->left)
			{
				x = y;
				y = y->parent;
			}

			return y;
		}

		node_pointer start() const
		{
			return (min(_root));
		}

		node_pointer last() const
		{
			return (max(_root));
		}

	private:
		void freeNode(node_pointer n)
		{
			// std::cout << *n->data << std::endl;
			_alloc.destroy(n->data);
			_alloc.deallocate(n->data, 1);
			delete n;
		}

		void fixDelete(node_pointer x)
		{
			node_pointer s;
			while (x != _root && x != _nil && x->color == black)
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

					if (s->left->color == black && s->right->color == black)
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
				if (y->parent == z && x != _nil)
				{
					x->parent = y;
				}
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					if (y->right != _nil)
						y->right->parent = y;
				}

				transplant(z, y);
				y->left = z->left;
				if (y->left != _nil)
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

		void bstInsert(node_pointer n, node_pointer start)
		{
			node_pointer parent = NULL;
			node_pointer x = start;

			while (x != _nil)
			{
				parent = x;
				if (_comp(*n->data, *x->data))
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			n->parent = parent;
			if (!parent)
			{
				_root = n;
			}
			else if (_comp(*n->data, *parent->data))
			{
				parent->left = n;
			}
			else
			{
				parent->right = n;
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

		void transplant(node_pointer dst, node_pointer src)
		{
			if (dst->parent == 0)
			{
				_root = src;
			}
			else if (dst == dst->parent->left)
			{
				dst->parent->left = src;
			}
			else
			{
				dst->parent->right = src;
			}
			if (src->parent)
				src->parent = dst->parent;
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

	public:
		allocator_type _alloc;
		Equal _equal;
		Compare _comp;
		node_pointer _nil;
		node_pointer _root;
	};

	template <class T>
	class RBTiterator
	{

	public:
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef RBTnode<value_type> *node_pointer;

	private:
		node_pointer _node;

	public:
		// Default constructor
		RBTiterator() {}

		// Copy constructor
		RBTiterator(const RBTiterator &other)
		{
			*this = other;
		}

		// Pointer constructor
		RBTiterator(node_pointer ptr) : _node(ptr) {}

		// Destructor
		~RBTiterator() {}

		// Assignment operator
		RBTiterator &operator=(const RBTiterator &other)
		{
			_node = other._node;

			return (*this);
		}

		// Conversion operator to const_iterator
		operator RBTiterator<const value_type>() const
		{
			return (_node);
		}

		// Comparison operator, const compatible
		bool operator==(const RBTiterator &rhs) const
		{
			return (_node == rhs._node);
		}

		// Comparison operator, const compatible
		bool operator!=(const RBTiterator &rhs) const
		{
			return (!(*this == rhs));
		}

		// Dereference operator, const compatible
		reference operator*() const
		{
			return (*(_node->data));
		}

		// Member access operator, const compatible
		pointer operator->() const
		{
			return (_node->data);
		}

		// Prefix increment
		RBTiterator &operator++()
		{
			_node = RedBlackTree<value_type>::successor(_node);
			return (*this);
		}

		// Postfix increment
		RBTiterator operator++(int)
		{
			RBTiterator old = *this;
			operator++();
			return (old);
		}

		// Prefix decrement
		RBTiterator &operator--()
		{
			_node = RedBlackTree<value_type>::predecessor(_node);
			return (*this);
		}

		// Postfix decrement
		RBTiterator operator--(int)
		{
			RBTiterator old = *this;
			operator--();
			return (old);
		}

		node_pointer	getNode()
		{
			return (_node);
		}
	};

	template <class T>
	class RBTreverse_iterator
	{

	public:
		typedef T value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef RBTnode<value_type> *node_pointer;

	private:
		node_pointer _node;

	public:
		// Default constructor
		RBTreverse_iterator() {}

		// Copy constructor
		RBTreverse_iterator(const RBTreverse_iterator &other)
		{
			*this = other;
		}

		// Pointer constructor
		RBTreverse_iterator(node_pointer ptr) : _node(ptr) {}

		// Destructor
		~RBTreverse_iterator() {}

		// Assignment operator
		RBTreverse_iterator &operator=(const RBTreverse_iterator &other)
		{
			_node = other._node;

			return (*this);
		}

		// Conversion operator to const_iterator
		operator RBTreverse_iterator<const value_type>() const
		{
			return (_node);
		}

		// Comparison operator, const compatible
		bool operator==(const RBTreverse_iterator &rhs) const
		{
			return (_node == rhs._node);
		}

		// Comparison operator, const compatible
		bool operator!=(const RBTreverse_iterator &rhs) const
		{
			return (!(*this == rhs));
		}

		// Dereference operator, const compatible
		reference operator*() const
		{
			return (*(_node->data));
		}

		// Member access operator, const compatible
		pointer operator->() const
		{
			return (_node->data);
		}

		// Prefix increment
		RBTreverse_iterator &operator++()
		{
			_node = RedBlackTree<value_type>::predecessor(_node);
			return (*this);
		}

		// Postfix increment
		RBTreverse_iterator operator++(int)
		{
			RBTreverse_iterator old = *this;
			operator++();
			return (old);
		}

		// Prefix decrement
		RBTreverse_iterator &operator--()
		{
			_node = RedBlackTree<value_type>::successor(_node);
			return (*this);
		}

		// Postfix decrement
		RBTreverse_iterator operator--(int)
		{
			RBTreverse_iterator old = *this;
			operator--();
			return (old);
		}

		node_pointer	getNode()
		{
			return (_node);
		}
	};

}

#endif // RED_BLACK_TREE_HPP
