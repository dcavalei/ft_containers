#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "utility.hpp"
# include "iterator.hpp"

namespace ft {

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key,T> >
	> class map {

	/* ************************************** Member types ************************************** */

		public:

		// https://www.cplusplus.com/reference/map/map/

		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef pair<const key_type,mapped_type>					value_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef typename allocator_type::size_type					size_type;
		typedef bidirectional_iterator<const value_type>			const_iterator;
		typedef bidirectional_iterator<value_type>					iterator;
		typedef reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;

		template <class Key, class T, class Compare, class Alloc>
		class value_compare {

			public:

				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool	operator()( const value_type& x, const value_type& y ) const {
					return (comp(x.first, y.first));
				}

			protected:

				Compare comp;
				value_compare( Compare c ) : comp(c) {}	// constructed with map's comparison object
		};

	};

}

#endif // MAP_HPP
