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
		class value_equal;
		typedef std::equal_to<Key> key_equal;
		typedef RedBlackTree<pair<const Key, T>, value_compare, value_equal, Alloc> RedBlackTree;

	public:
		// https://www.cplusplus.com/reference/map/map/

		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef pair<const Key, T> value_type;
		typedef Alloc allocator_type;
		typedef typename RedBlackTree::const_iterator const_iterator;
		typedef typename RedBlackTree::iterator iterator;
		typedef typename RedBlackTree::const_reverse_iterator const_reverse_iterator;
		typedef typename RedBlackTree::reverse_iterator reverse_iterator;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

	public:
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type()) : _rbt(value_compare(comp),
																			alloc,
																			value_equal(key_equal())),
																	   _size(0) {}
		template <class InputIterator>
		map(InputIterator first,
			InputIterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _rbt(value_compare(comp),
																   alloc,
																   value_equal(key_equal())),
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
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			value_compare(){};
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		/* ************************************** Iterator ************************************** */

		iterator begin() { return (iterator(_rbt.start())); }

		const_iterator begin() const { return (const_iterator(_rbt.start())); }

		iterator end() { return (iterator(NULL)); }

		const_iterator end() const { return (const_iterator(NULL)); }

		reverse_iterator rbegin() { return (reverse_iterator(_rbt.last())); }

		const_reverse_iterator rbegin() const { return (const_reverse_iterator(_rbt.last())); }

		reverse_iterator rend() { return (reverse_iterator(NULL)); }

		const_reverse_iterator rend() const { return (const_reverse_iterator(NULL)); }

		/* ************************************** Capacity ************************************** */

		bool empty() const { return (_size == 0); }

		size_type size() const { return (_size); }

		size_type max_size() const { return (_rbt._alloc.max_size()); }

		/* *********************************** Element access *********************************** */

		mapped_type &operator[](const key_type &k)
		{
			value_type pair(k, mapped_type());
			typename RedBlackTree::node_pointer node = _rbt.findKey(_rbt._root, pair);

			if (!node)
			{
				_rbt.insert(pair);
				node = _rbt.findKey(_rbt._root, pair);
				_size++;
			}
			return (*node->data).second;
		}

		/* ************************************************************************************** */

		// pair<iterator,bool> insert (const value_type& val)
		// {

		// }

		pair<iterator, bool> insert(const value_type &val)
		{
			pair<iterator, bool> p;
			typename RedBlackTree::node_pointer node;

			node = _rbt.findKey(_rbt._root, val);
			if (node)
			{
				p.first = iterator(node);
				p.second = false;
			}
			else
			{
				_size++;
				_rbt.insert(val);
				node = _rbt.findKey(_rbt._root, val);
				p.first = iterator(node);
				p.second = true;
			}
			return p;
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			_rbt.insert(val);
			_size++;
			return (iterator(_rbt.findKey(_rbt._root, val)));
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_rbt.insert(*first++);
				_size++;
			}
		}

	private:
		class value_equal
		{
			friend class map;

		protected:
			std::equal_to<key_type> comp;
			value_equal(std::equal_to<key_type> c) : comp(c) {}

		public:
			value_equal(){};
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		RedBlackTree _rbt;
		size_type _size;
	};

}

#endif // MAP_HPP
