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
		typedef pair<const Key,T>									value_type;
		// typedef blablalbla										value_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef typename allocator_type::size_type					size_type;
		// iterator							a bidirectional iterator to value_type
		// const_iterator					a bidirectional iterator to const value_type
		// reverse_iterator					reverse_iterator<iterator>
		// const_reverse_iterator			reverse_iterator<const_iterator>
		
	};

}

#endif // MAP_HPP
