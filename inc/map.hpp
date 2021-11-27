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
		// https://www.cplusplus.com/reference/map/map/

		typedef Key key_type;
		typedef T mapped_type;
		typedef Compare key_compare;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Alloc allocator_type;
		typedef bidirectional_iterator<const value_type> const_iterator;
		typedef bidirectional_iterator<value_type> iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

	private:
		typedef std::equal_to<key_type> key_equal;
	public:

		explicit map(
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : _rbt(value_compare(comp),
																   alloc,
																   value_equal(key_equal())) {}

		// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
		class value_compare : std::binary_function<value_type,value_type,bool>
		{
			friend class map;

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		// pair<iterator,bool> insert (const value_type& val)
		// {

		// }

		void insert(const value_type& val)
		{
			_rbt.insert(val);
			// _rbt.findKey("ola");
		}


	private:

		class value_equal
		{
			friend class map;

		protected:
			std::equal_to<key_type> comp;
			value_equal(std::equal_to<key_type> c) : comp(c) {}

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

		RedBlackTree<value_type, value_compare, value_equal, allocator_type> _rbt;
	};

}

#endif // MAP_HPP
