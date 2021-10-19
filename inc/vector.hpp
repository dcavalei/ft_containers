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

		private:
			allocator_type	_alloc;
			pointer			_start;
			size_type		_size;
			size_type		_capacity;
			size_type		_max_size;

		public:
			class iterator : public std::iterator<std::random_access_iterator_tag, value_type> {

				private:
					value_type*	_ptr;

				public:
					// Default constructor
					iterator() : _ptr(NULL) {}
					// Copy constructor
					iterator(const iterator& other) { *this = other; }
					// Destructor
					~iterator() {}

					iterator&	operator=(const iterator& rhs) {
						_ptr = rhs._ptr;
						return *this;
					}
			};

		public:


// begin
//     Return iterator to beginning (public member function )

// end
//     Return iterator to end (public member function )

// rbegin
//     Return reverse iterator to reverse beginning (public member function )

// rend
//     Return reverse iterator to reverse end (public member function )


			// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

			// iterator 				LegacyRandomAccessIterator to value_type
			// const_iterator 			LegacyRandomAccessIterator to const value_type
			// reverse_iterator 		std::reverse_iterator<iterator>
			// const_reverse_iterator 	std::reverse_iterator<const_iterator>


		// (1)	empty container constructor (default constructor)
		// Constructs an empty container, with no elements.
			explicit vector( const allocator_type& alloc = allocator_type() ) :
				_alloc(alloc),
				_start(NULL),
				_size(0),
				_capacity(0),
				_max_size(alloc.max_size()) {}

		// (2)	fill constructor
		// Constructs a container with n elements. Each element is a copy of val.
			explicit vector( size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type() ) :
				_alloc(alloc),
				_start(NULL),
				_size(n),
				_capacity(n),
				_max_size(alloc.max_size())
			{
				// if ()
				_start = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_start + i, val);
				}
			}

		// (3)	range constructor
		// Constructs a container with as many elements as the range [first,last),
		// with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type());

		// (4)	copy constructor
		// 	Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x) {
				std::cout << "Copy C/tor" << std::endl;
				(void)x;
			}

			~vector() {
				std::cout << "Default D/tor" << std::endl;
			}

			// ###---------------- Capacity ----------------###

			size_type	size() const { return _size; }
			size_type	max_size() const { return _max_size; }
			// void		resize (size_type n, value_type val = value_type());
			size_type	capacity() const { return _capacity; }
			bool		empty() const { return _size == 0; };
			// void		reserve (size_type n);

			// ###---------------- Capacity ----------------###
	};
};

#endif
