#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft {

	template<
		class T,
		class Alloc = std::allocator<T>
	> class vector {

	/* ************************************** Member types ************************************** */

		public:

		// https://www.cplusplus.com/reference/vector/vector/?kw=vector

		typedef T											value_type;			// T
		typedef Alloc										allocator_type;		// Alloc
		typedef typename allocator_type::const_reference	const_reference;	// const T&
		typedef typename allocator_type::reference			reference;			// T&
		typedef typename allocator_type::const_pointer		const_pointer;		// const T*
		typedef typename allocator_type::pointer			pointer;			// T*
		typedef typename allocator_type::difference_type	difference_type;	// std::ptrdiff_t
		typedef typename allocator_type::size_type			size_type;			// std::size_t
		typedef random_access_iterator<const value_type>	const_iterator;
		typedef random_access_iterator<value_type>			iterator;
		typedef reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;

	/* ********************************** Private data members ********************************** */

		private:

		allocator_type	_alloc;
		size_type		_size;
		pointer			_start;
		size_type		_capacity;

	/* ************************************** Constructors ************************************** */

		public:

		// (1)	empty container constructor (default constructor)
		// Constructs an empty container, with no elements.
		explicit vector( const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(0),
			_start(NULL),
			_capacity(0) {}

		// (2)	fill constructor
		// Constructs a container with n elements. Each element is a copy of val.
		explicit vector( size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(n),
			_start(_alloc.allocate(n)),
			_capacity(n) {
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_start + i, val);
			}
		}

		// (3)	range constructor
		// Constructs a container with as many elements as the range [ first, last [
		// with each element constructed from its corresponding element in that range,
		// in the same order.
		//
		// If Cond is true, enable_if has a public member typedef type, equal to T;
		// otherwise, there is no member typedef
		template< class InputIterator >
		vector( typename ft::enable_if<
					!ft::is_integral<InputIterator>::value,	// Cond
					InputIterator							// T
				>::type first,
				InputIterator last,
		 		const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(last - first),
			_start(_alloc.allocate(last - first)),
			_capacity(last - first) {
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_start + i, *(first + i));
			}
		}

		// (4)	copy constructor
		// Constructs a container with a copy of each of the elements in x, in the same order.
		vector( const vector& other ) :
			_alloc(other._alloc),
			_size(0),
			_start(NULL),
			_capacity(0) {
			*this = other;
		}

		~vector() {
			destruct_all();
			_alloc.deallocate(_start, _capacity);
		}

		// Assignment operator
		vector&	operator=( const vector& other ) {
			if (this == &other) {
				return (*this);
			}

			if (_capacity < other._size) {
				this->~vector();
				_start = _alloc.allocate(other._size);
				_capacity = other._size;
			} else {
				destruct_all();
			}

			for (size_type i = 0; i < other._size; i++) {
				copy_construct(_start, other[i], i);
			}
			_size = other._size;
			return (*this);
		}

	/* **************************************** Iterator **************************************** */

		// Returns an iterator pointing to the first element in the vector.
		iterator	begin() { return (iterator(_start)); }

		const_iterator	begin() const { return (const_iterator(_start)); }

		// Returns an iterator referring to the past-the-end element in the vector container.
		iterator	end() { return (iterator(_start + _size)); }

		const_iterator	end() const { return (const_iterator(_start + _size)); }


		// Returns an reverse iterator referring to the end element in the vector container.
		reverse_iterator	rbegin() { return (reverse_iterator(end())); }

		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }

		// Returns a reverse iterator pointing to the theoretical element preceding
		// the first element in the vector (which is considered its reverse end).
		reverse_iterator	rend() { return (reverse_iterator(begin())); }

		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

	/* *************************************** Modifiers **************************************** */

		// Assign vector content
		template< class InputIterator >
		void	assign( typename ft::enable_if<
							!ft::is_integral<InputIterator>::value,	// Cond
							InputIterator							// T
						>::type first,
						InputIterator last ) {
			destruct_all();
			_size = 0;
			reserve(last - first);
			copy_construct(_start, first, last);
			_size = last - first;
		}

		// Assign vector content
		void	assign( size_type n, const value_type& val ) {
			destruct_all();
			_size = 0;
			reserve(n);
			for (size_type i = 0; i < n; i++) {
				copy_construct(_start, val, i);
			}
			_size = n;
		}

		// Add element at the end
		void	push_back( const value_type& val ) {
			if (empty()) {
				reserve(1);
			} else if (_size == _capacity) {
				(_size * 2 < max_size()) ? reserve(_size * 2) : reserve(max_size());
			}
			copy_construct(_start, val, _size++);
		}

		// Delete last element
		void	pop_back() {
			destruct(_start, --_size);
		}

		// single element (1)
		iterator	insert( iterator position, const value_type& val ) {
			if (empty()) {
				if (position == begin()) {
					reserve(1);
					copy_construct(_start, val);
					position = iterator(_start);
				}
			} else if (_size == _capacity) {
				size_type		new_cap;
				pointer			tmp;
				size_type		pos;

				(_size * 2 < max_size()) ? (new_cap = _size * 2) : (new_cap = max_size());
				tmp = _alloc.allocate(new_cap);
				pos = position - begin();

				copy_construct(tmp, begin(), position);
				copy_construct(tmp + pos, val);
				copy_construct(tmp + pos + 1, position, end());

				this->~vector();
				_capacity = new_cap;
				_start = tmp;
				position = iterator(_start + pos);
			} else {
				iterator	end(this->end());
				size_type	i = _size;

				do
				{
					copy_construct(_start + i, _start[i - 1]);
					destruct(_start, --i);
				} while (position != --end);
				copy_construct(_start + (position - begin()), val);
			}
			_size++;
			return (position);
		}

		// fill (2)
		void	insert( iterator position, size_type n, const value_type& val ) {
			if (!n) {
				return;
			} else if (empty()) {
				if (position == begin()) {
					reserve(n);
					for (size_type i = 0; i < n; i++) {
						copy_construct(_start, val, i);
					}
				}
			} else if (_size + n > _capacity) {
				size_type	pos = position - begin();
				size_type	new_cap;
				pointer		tmp;

				// correct capacity
				if (_size * 2 > max_size() && _size + n <= max_size()) {
					new_cap = max_size();
				} else {
					(_size + n < _size * 2) ? (new_cap = _size * 2) : (new_cap = _size + n);
				}
				tmp = _alloc.allocate(new_cap);

				//copy construct content
				copy_construct(tmp, begin(), position);
				for (size_type i = 0; i < n; i++) {
					copy_construct(tmp, val, pos + i);
				}
				copy_construct(tmp + pos + n, position, end());

				//replace ptr for new ptr
				this->~vector();
				_capacity = new_cap;
				_start = tmp;
			} else {
				iterator	ite(end());
				size_type	last_index = _size - 1;
				size_type	pos = position - begin();

				do
				{
					copy_construct(_start + last_index + n, _start[last_index]);
					destruct(_start, last_index--);
				} while (position != --ite);
				for (size_type i = 0; i < n; i++) {
					copy_construct(_start + pos++, val);
				}
			}
			_size += n;
		}

		// range (3)
		template< class InputIterator >
		void	insert( iterator position,
						typename ft::enable_if<
							!ft::is_integral<InputIterator>::value,	// Cond
							InputIterator							// T
						>::type first,
						InputIterator last ) {
			difference_type	range = last - first;

			if (empty()) {
				if (position == begin()) {
					reserve(range);
					copy_construct(_start, first, last);
				}
			}
			_size += range;
		}


// insert
//     Insert elements (public member function )

// erase
//     Erase elements (public member function )

// swap
//     Swap content (public member function )

// clear
//     Clear content (public member function )


	/* **************************************** Capacity **************************************** */

		// Returns the number of elements in the vector.
		size_type	size() const { return (_size); }

		// Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const { return (_alloc.max_size()); }

		// Requests that the vector capacity be at least enough to contain n elements.
		//
		// If n is greater than the current vector capacity,the function causes
		// the container to reallocate its storage increasing its capacity to n (or greater).
		//
		// In all other cases, the function call does not cause a reallocation and
		// the vector capacity is not affected.
		//
		// This function has no effect on the vector size and cannot alter its elements.
		void	reserve( size_type n ) {
			if (n <= _capacity) {
				return;
			} else if (n > max_size()) {
				throw std::length_error("vector::reserve");
			}

			pointer	tmp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(tmp + i, _start[i]);
			}
			this->~vector();
			_start = tmp;
			_capacity = n;
		}

		// [Resizes the container so that it contains n elements]
		//
		// If n is smaller than the current container size, the content is reduced
		// to its first n elements, removing those beyond (and destroying them).
		//
		// If n is greater than the current container size, the content is expanded by inserting
		// at the end as many elements as needed to reach a size of n. If val is specified,the new
		// elements are initialized as copies of val, otherwise, they are value-initialized.
		//
		// If n is also greater than the current container capacity,
		// an automatic reallocation of the allocated storage space takes place.
		//
		// Notice that this function changes the actual content of the container
		// by inserting or erasing elements from it.
		void	resize( size_type n, const value_type& val = value_type() ) {
			if (n < _size) {
				for (size_type i = n; i < _size; i++) {
					_alloc.destroy(_start + i);
				}
			} else if (n > _capacity) {
				(n / 2 < _size) ? reserve(_size * 2) : reserve(n);
			}

			for (size_type i = _size; i < n; i++) {
				_alloc.construct(_start + i, val);
			}
			_size = n;
		}

		size_type	capacity() const { return (_capacity); }

		bool	empty() const { return (_size == 0); };

	/* ************************************* Element access ************************************* */

		// Element access (no-throw guarantee)
		reference	operator[]( size_type n ) { return (_start[n]); }

		const_reference	operator[]( size_type n ) const { return (_start[n]); }

		// Access element (public member function)
		reference	at( size_type n ) { _M_range_check(n); return (_start[n]); }

		const_reference	at( size_type n ) const { _M_range_check(n); return (_start[n]); }

		reference	front() { return (*_start); }

		const_reference	front() const { return (*_start); }

		reference	back() { return (*(_start + _size - 1)); }

		const_reference	back() const { return (*(_start + _size - 1)); }

	/* ************************************ Helper functions ************************************ */

		private:

		// Destroy objects in range (0, size), doesn't free memory
		void	destruct_all() {
			for (size_type i = 0; i < _size; i++) {
				destruct(_start, i);
			}
		}

		void	destruct( pointer ptr, size_type index ) {
				_alloc.destroy(ptr + index);
		}

		void	copy_construct( pointer dst, iterator start, iterator end ) {
			for (; start != end; ++start) {
				_alloc.construct(dst++ , *start);
			}
		}

		void	copy_construct( pointer dst, const value_type& val, size_type i = 0 ) {
				_alloc.construct(dst + i, val);
		}

		static std::string	atol( size_type rhs ) {
			std::string		str;
			int				n = 0;

			for (size_type i = rhs; i != 0; i /= 10) {
				n++;
			}

			for (; rhs != 0; rhs /= 10) {
				str.insert(0, 1, (rhs % 10) + '0');
			}
			return (str);
		}

		void	_M_range_check( size_type __n ) {

			if ( __n >= _size ) {
			std::string		buffer;

			buffer = "vector::_M_range_check: __n (which is " + atol(__n)
					+ ") >= this->size() (which is " + atol(_size) + ")";

			throw std::out_of_range(buffer);
			}
		}

	};

};

#endif // VECTOR_HPP
