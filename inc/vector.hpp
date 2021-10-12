#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
namespace ft
{
	template<
    	class T,
    	class Alloc = std::allocator<T>
	> class vector
	{

		public:

			typedef Alloc										allocator_type;
			typedef T											value_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			

			// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

			// iterator 				LegacyRandomAccessIterator to value_type
			// const_iterator 			LegacyRandomAccessIterator to const value_type
			// reverse_iterator 		std::reverse_iterator<iterator>
			// const_reverse_iterator 	std::reverse_iterator<const_iterator>


		// (1)	empty container constructor (default constructor)
		// Constructs an empty container, with no elements.
			explicit vector( const allocator_type& alloc = allocator_type() ) {
				std::cout << "Default C/tor" << std::endl;
			}

		// (2)	fill constructor
		// Constructs a container with n elements. Each element is a copy of val.
			explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type());

		// (3)	range constructor
		// Constructs a container with as many elements as the range [first,last),
		// with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());

		// (4)	copy constructor
		// 	Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x);

			~vector() {
				std::cout << "Default D/tor" << std::endl;
			}
	};

};

#endif
