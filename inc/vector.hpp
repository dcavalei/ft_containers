#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>

namespace ft
{
	template<
		class T,
		class Alloc = std::allocator<T>
	> class vector
	{
		public:
			typedef Alloc										allocator_type;		//	Alloc
			typedef T											value_type;			//	T
			typedef typename allocator_type::reference			reference;			//	T&
			typedef typename allocator_type::const_reference	const_reference;	//	const T&
			typedef typename allocator_type::pointer			pointer;			//	T*
			typedef typename allocator_type::const_pointer		const_pointer;		//	const T*
			typedef typename allocator_type::size_type			size_type;			//	std::size_t
			typedef typename allocator_type::difference_type	difference_type;	//	std::ptrdiff_t

			class iterator;

		private:
			allocator_type	_alloc;
			size_type		_size;
			pointer			_start;
			size_type		_capacity;

		public:

			// ########################################################################################
			// (1)	empty container constructor (default constructor)
			// Constructs an empty container, with no elements.
			// 'explicit' keyword will deny this sort of initialization:
			// vector<value_type> vec = {} (error)
			explicit vector( const allocator_type& alloc = allocator_type() ) :
				_alloc(alloc),
				_size(0),
				_start(NULL),
				_capacity(0) {}

			// (2)	fill constructor
			// Constructs a container with n elements. Each element is a copy of val.
			// 'explicit' keyword will deny this sort of initialization:
			// vector<value_type> vec = {size_type, value_type} (error)
			explicit vector( size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type() ) :
				_alloc(alloc),
				_size(n),
				_start(_alloc.allocate(_size)),
				_capacity(_size)
			{
				// std::cout << "Fill C/tor" << std::endl;
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_start + i, val);
				}
			}

			// (3)	range constructor
			// Constructs a container with as many elements as the range [first,last),
			// with each element constructed from its corresponding element in that range, in the same order.
			vector(iterator first, const iterator& last,
				const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_size(last - first),
				_start(_alloc.allocate(_size)),
				_capacity(_size)
				{
					// std::cout << "Range C/tor" << std::endl;
					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(_start + i, *(first++));
					}
				}

			// (4)	copy constructor
			// Constructs a container with a copy of each of the elements in x, in the same order.
			vector( const vector& x )
			{
				std::cout << "Copy C/tor" << std::endl;
				*this = x;
			}

			~vector() {
				// std::cout << "Default D/tor" << std::endl;
				for (size_type i = 0; i < _size; i++) {
					_alloc.destroy(_start + i);
				}
				_alloc.deallocate(_start, _capacity);
			}

			// Assignment operator
			vector&	operator=( const vector& other ) {
				if (this == &other) {
					return (*this);
				}
				this->~vector();

				_alloc = other._alloc;
				_start = _alloc.allocate(other._capacity);

				for (size_type i = 0; i < other._size; i++) {
					_alloc.construct(_start + i, *(other._start + i));
				}
			}

			// ########################################################################################
			class iterator {
				private:
					pointer	_ptr;

				public:
					// Default constructor
					iterator() : _ptr(NULL) {}

					// Copy constructor
					iterator( const iterator& other ) { *this = other; }

					// Pointer constructor
					iterator( const pointer& ptr ) : _ptr(ptr) {}

					// Destructor
					~iterator() {}

					// Assignment operator
					iterator&		operator=( const iterator& rhs ) {
						_ptr = rhs._ptr;
						return *this;
					}

					// Comparison operator
					bool			operator==( const iterator& rhs ) const {
						return (_ptr == rhs._ptr);
					}

					// Comparison operator
					bool			operator!=( const iterator& rhs ) const {
						return (!(*this == rhs));
					}

					// Dereference operator
					value_type&		operator*() const {
						return *_ptr;
					}

					// Member access operator
					pointer			operator->() const {
						return _ptr;
					}

					// Prefix increment
					iterator&		operator++() {
						_ptr++;
						return *this;
					}

					// Postfix increment
					iterator		operator++(int) {
						iterator old = *this;
						operator++();
						return old;
					}

					// Prefix decrement
					iterator&		operator--() {
						_ptr--;
						return *this;
					}

					// Postfix decrement
					iterator		operator--(int) {
						iterator old = *this;
						operator--();
						return old;
					}

					// Addition operator
					iterator		operator+( int n ) const {
						return iterator(_ptr + n);
					}

					// Subtraction operator
					iterator		operator-( int n ) const {
						return iterator(_ptr - n);
					}

					// Difference operator
					difference_type	operator-( const iterator& rhs ) const {
						return _ptr - rhs._ptr;
					}

					// Comparison operator
					bool			operator<( const iterator& rhs ) const {
						return _ptr < rhs._ptr;
					}

					// Comparison operator
					bool			operator>( const iterator& rhs ) const {
						return rhs < *this;
					}

					// Comparison operator
					bool			operator<=( const iterator& rhs ) const {
						return !(*this > rhs);
					}

					// Comparison operator
					bool			operator>=( const iterator& rhs ) const {
						return !(*this < rhs);
					}

					// Assignment operator
					iterator&		operator+=( int n ) {
						_ptr += n;
						return *this;
					}

					// Assignment operator
					iterator&		operator-=( int n ) {
						_ptr -= n;
						return *this;
					}

					// Subscript operator
					value_type&		operator[]( size_type n ) {
						return *(_ptr + n);
					}

			};

			iterator	begin() {
				return (iterator(_start));
			}

			iterator	end() {
				return (iterator(_start + _size));
			}

		public:

			// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

			// iterator 				LegacyRandomAccessIterator to value_type
			// const_iterator 			LegacyRandomAccessIterator to const value_type
			// reverse_iterator 		std::reverse_iterator<iterator>
			// const_reverse_iterator 	std::reverse_iterator<const_iterator>


			// ###---------------- Capacity ----------------###

			size_type	size() const {
				return _size;
			}

			size_type	max_size() const {
				return _alloc.max_size();
			}

			// void		resize (size_type n, value_type val = value_type());

			size_type	capacity() const {
				return _capacity;
			}

			bool		empty() const {
				return _size == 0;
			};

			// void		reserve (size_type n);

			// ###---------------- Capacity ----------------###
			// ###------------------------------------------###
			// ###------------- Element access -------------###

			reference		operator[](size_type n) {
				return *(_start + n);
			}

			const_reference	operator[](size_type n) const {
				return *(_start + n);
			}

			//     Access element (public member function )

			// at
			//     Access element (public member function )

			// front
			//     Access first element (public member function )

			// back
			//     Access last element (public member function )

			// data
			//     Access data (public member function )

			// ###------------- Element access -------------###
			// ###------------------------------------------###


	};
};

#endif
