#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "utility.hpp"
#include "iterator.hpp"
#include "red_black_tree.hpp"

namespace ft
{

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
		/* ************************************ Member types ************************************ */
	public:
		class value_compare;

	private:
		typedef RedBlackTree<pair<const Key, T>, value_compare, Alloc> RedBlackTree;

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef pair<const Key, T> value_type;
		typedef Alloc allocator_type;
		typedef typename RedBlackTree::iterator iterator;
		typedef typename RedBlackTree::const_iterator const_iterator;
		typedef typename RedBlackTree::reverse_iterator reverse_iterator;
		typedef typename RedBlackTree::const_reverse_iterator const_reverse_iterator;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _rbt(value_compare(comp), alloc),
																	   _comp(comp),
																	   _size(0) {}
		template <class InputIterator>
		map(InputIterator first,
			InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _rbt(value_compare(comp), alloc),
															  _size(0)
		{
			while (first != last)
			{
				_rbt.insert(*first++);
				_size++;
			}
		}

		map(const map &other)
		{
			*this = other;
		}

		map &operator=(const map &rhs)
		{
			_rbt = rhs._rbt;
			_size = rhs._size;
			return *this;
		}

		// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		class value_compare : std::binary_function<value_type, value_type, bool>
		{
		protected:
			key_compare comp;

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
			value_compare(const key_compare &c = key_compare()) : comp(c) {}
		};

		/* ************************************** Iterator ************************************** */

		iterator begin() { return (iterator(_rbt.start())); }

		const_iterator cbegin() const { return (const_iterator(_rbt.start())); }

		iterator end() { return (iterator(NULL)); }

		const_iterator cend() const { return (const_iterator(NULL)); }

		reverse_iterator rbegin() { return (reverse_iterator(_rbt.last())); }

		const_reverse_iterator crbegin() const { return (const_reverse_iterator(_rbt.last())); }

		reverse_iterator rend() { return (reverse_iterator(NULL)); }

		const_reverse_iterator crend() const { return (const_reverse_iterator(NULL)); }

		/* ************************************** Capacity ************************************** */

		bool empty() const { return (_size == 0); }

		size_type size() const { return (_size); }

		size_type max_size() const { return (_rbt.alloc.max_size()); }

		/* *********************************** Element access *********************************** */

		mapped_type &operator[](const key_type &k)
		{
			value_type pair(k, mapped_type());
			typename RedBlackTree::node_pointer node = _rbt.findKey(_rbt.root, pair);

			if (!node)
			{
				_rbt.insert(pair);
				node = _rbt.findKey(_rbt.root, pair);
				_size++;
			}
			return (*node->data).second;
		}

		/* ************************************* Modifiers ************************************** */

		pair<iterator, bool> insert(const value_type &val)
		{
			pair<iterator, bool> p;
			typename RedBlackTree::node_pointer node;

			node = _rbt.findKey(_rbt.root, val);
			if (node)
			{
				p.second = false;
			}
			else
			{
				_size++;
				_rbt.insert(val);
				node = _rbt.findKey(_rbt.root, val);
				p.second = true;
			}
			p.first = iterator(node);
			return p;
		}

		iterator insert(iterator position, const value_type &val)
		{
			typename RedBlackTree::node_pointer target, node;

			node = _rbt.findKey(_rbt.root, val);
			if (node)
			{
				return (iterator(node));
			}
			target = position.getNode();
			node = _rbt.newNode(val);
			value_compare comp;
			while (target->parent)
			{
				if (target->parent->left == target)
				{
					if (comp(*target->parent->data, val))
					{
						target = target->parent;
						continue;
					}
					break;
				}
				else
				{
					if (comp(val, *target->parent->data))
					{
						target = target->parent;
						continue;
					}
					break;
				}
			}

			_rbt.bstInsert(node, target);
			_rbt.fixInsert(node);
			_size++;
			return (iterator(node));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first++);
			}
		}

		void erase(iterator position)
		{
			_rbt.rbtDelete(position.getNode());
			_size--;
		}

		size_type erase(const key_type &k)
		{
			size_type i = 0;
			value_type pair(k, mapped_type());

			while (_rbt.remove(pair))
			{
				i++;
			}
			_size -= i;
			return (i);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				erase(first++);
			}
		}

		void swap(map &other)
		{
			size_type tmp_size;
			typename RedBlackTree::node_pointer tmp_nil, tmp_root;

			tmp_size = this->_size;
			tmp_nil = this->_rbt.nil;
			tmp_root = this->_rbt.root;

			this->_size = other._size;
			this->_rbt.nil = other._rbt.nil;
			this->_rbt.root = other._rbt.root;

			other._size = tmp_size;
			other._rbt.nil = tmp_nil;
			other._rbt.root = tmp_root;
		}

		void clear()
		{
			_rbt.clear();
			_size = 0;
		}

		/* ************************************* Observers ************************************** */

		key_compare key_comp() const { return (_comp); }

		value_compare value_comp() const { return (_comp); }

		/* ************************************* Operations ************************************* */

		iterator find(const key_type &k)
		{
			value_type p(k, mapped_type());
			return (iterator(_rbt.findKey(_rbt.root, p)));
		}

		const_iterator find(const key_type &k) const
		{
			value_type p(k, mapped_type());
			return (const_iterator(_rbt.findKey(_rbt.root, p)));
		}

		size_type count(const key_type &k) const
		{
			value_type p(k, mapped_type());
			return (countHelper(_rbt.root, p));
		}

		iterator lower_bound(const key_type &key)
		{
			typename RedBlackTree::node_pointer n, p;

			n = _rbt.root;
			p = NULL;
			while (n != _rbt.nil)
			{
				if (_comp(n->data->first, key))
				{
					n = n->right;
				}
				else
				{
					p = n;
					n = n->left;
				}
			}
			return (p);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			typename RedBlackTree::node_pointer n, p;

			n = _rbt.root;
			p = NULL;
			while (n != _rbt.nil)
			{
				if (_comp(n->data->first, key))
				{
					n = n->right;
				}
				else
				{
					p = n;
					n = n->left;
				}
			}
			return (p);
		}

		iterator upper_bound(const key_type &key)
		{
			typename RedBlackTree::node_pointer n;

			n = lower_bound(key).getNode();
			if (n && !_comp(key, n->data->first))
			{
				return (RedBlackTree::successor(n));
			}
			return (n);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			typename RedBlackTree::node_pointer n;

			n = lower_bound(key).getNode();
			if (n && !_comp(key, n->data->first))
			{
				return (RedBlackTree::successor(n));
			}
			return (n);
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		/* ************************************** Allocator ************************************* */

		allocator_type get_allocator() const { return (_rbt.alloc); }

		/* ********************************** Private data members ****************************** */

	private:
		size_type countHelper(typename RedBlackTree::node_pointer n, const value_type &val) const
		{
			size_type ret;

			if (n == _rbt.nil)
			{
				return 0;
			}

			!(_rbt.comp(val, *n->data) || _rbt.comp(*n->data, val)) == true ? ret = 1 : ret = 0;
			return (countHelper(n->left, val) + countHelper(n->right, val) + ret);
		}

		RedBlackTree _rbt;
		key_compare _comp;
		size_type _size;
	};

}

#endif // MAP_HPP
