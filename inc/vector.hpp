#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template<
    	class T,
    	class Alloc = std::allocator<T>
	> class vector {

		public:

			T							value_type;
			Alloc						allocator_type;
			std::size_t					size_type;
			T&							reference = value_type;
			const T&					const_reference = value_type;
			Allocator::pointer			pointer;
			Allocator::const_pointer	const_pointer;

			// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

			// iterator 				LegacyRandomAccessIterator to value_type
			// const_iterator 			LegacyRandomAccessIterator to const value_type
			// reverse_iterator 		std::reverse_iterator<iterator>
			// const_reverse_iterator 	std::reverse_iterator<const_iterator>


//	(1)	empty container constructor (default constructor)
//		Constructs an empty container, with no elements.
			explicit vector( const allocator_type& alloc = allocator_type() );

//	(2)	fill constructor
//		Constructs a container with n elements. Each element is a copy of val.
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type());

//	(3)	range constructor
//		Constructs a container with as many elements as the range [first,last),
//		with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());

//	(4)	copy constructor
//		Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x);

			~vector();
	};

}

#endif
