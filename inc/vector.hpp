/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:42:55 by dcavalei          #+#    #+#             */
/*   Updated: 2021/11/10 20:13:49 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <stdexcept>

namespace ft {

	template<
		class T,
		class Alloc = std::allocator<T>
	> class vector {

	/* ************************************** Member types ************************************** */

		public:

		typedef Alloc										allocator_type;		//	Alloc
		typedef T											value_type;			//	T
		typedef typename allocator_type::reference			reference;			//	T&
		typedef typename allocator_type::const_reference	const_reference;	//	const T&
		typedef typename allocator_type::pointer			pointer;			//	T*
		typedef typename allocator_type::const_pointer		const_pointer;		//	const T*
		typedef typename allocator_type::size_type			size_type;			//	std::size_t
		typedef typename allocator_type::difference_type	difference_type;	//	std::ptrdiff_t

		class 												iterator;
		typedef iterator const								const_iterator;

	/* ********************************** Private data members ********************************** */

		private:

		allocator_type	_alloc;
		size_type		_size;
		pointer			_start;
		size_type		_capacity;

	/* ************************************** Constructors ************************************** */

		public:

		/*
			(1)	empty container constructor (default constructor)
			Constructs an empty container, with no elements.
		*/
		explicit vector( const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(0),
			_start(NULL),
			_capacity(0) {
			// std::cout << "Default C/tor" << std::endl;
			}

		/*
			(2)	fill constructor
			Constructs a container with n elements. Each element is a copy of val.
		*/
		explicit vector( size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(n),
			_start(_alloc.allocate(n)),
			_capacity(n) {
			// std::cout << "Fill C/tor" << std::endl;
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_start + i, val);
			}
		}

		/*
			(3)	range constructor
			Constructs a container with as many elements as the range (first,last),
			with each element constructed from its corresponding element in that range,
			in the same order.
		*/
		vector( const iterator& first, const iterator& last,
			const allocator_type& alloc = allocator_type() ) :
			_alloc(alloc),
			_size(last - first),
			_start(_alloc.allocate(last - first)),
			_capacity(last - first) {
			// std::cout << "Range C/tor" << std::endl;
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_start + i, first[i]);
			}
		}

		/*
			(4)	copy constructor
			Constructs a container with a copy of each of the elements in x, in the same order.
		*/
		vector( const vector& other ) :
			_alloc(other._alloc),
			_size(0),
			_start(NULL),
			_capacity(0) {
			// std::cout << "Copy C/tor" << std::endl;
			*this = other;
		}

		~vector() {
			// std::cout << "Default D/tor" << std::endl;
			destroy();
			deallocate();
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
				destroy();
			}

			_size = other._size;
			copy(other);
			return (*this);
		}

	/* **************************************** Iterator **************************************** */

		class iterator {

			private:

			pointer	_ptr;

			public:

			// Default constructor
			iterator() : _ptr(NULL) {}

			// Copy constructor
			iterator( const iterator& other ) {
				*this = other;
			}

			// Pointer constructor
			iterator( const pointer& ptr ) : _ptr(ptr) {}

			// Destructor
			~iterator() {}

			// Assignment operator
			iterator&			operator=( const iterator& rhs ) {
				_ptr = rhs._ptr;
				return (*this);
			}

			// Comparison operator, const compatible
			bool				operator==( const iterator& rhs ) const {
				return (_ptr == rhs._ptr);
			}

			// Comparison operator, const compatible
			bool				operator!=( const iterator& rhs ) const {
				return (!(*this == rhs));
			}

			// Comparison operator, const compatible
			bool				operator<( const iterator& rhs ) const {
				return (_ptr < rhs._ptr);
			}

			// Comparison operator, const compatible
			bool				operator>( const iterator& rhs ) const {
				return (rhs < *this);
			}

			// Comparison operator, const compatible
			bool				operator<=( const iterator& rhs ) const {
				return (!(*this > rhs));
			}

			// Comparison operator, const compatible
			bool				operator>=( const iterator& rhs ) const {
				return (!(*this < rhs));
			}

			// Dereference operator
			reference			operator*() {
				return (*_ptr);
			}

			// Dereference operator, const only
			const_reference		operator*() const {
				return (*_ptr);
			}

			// Member access operator
			pointer				operator->() {
				return (_ptr);
			}

			// Member access operator, const only
			const_pointer		operator->() const {
				return (_ptr);
			}

			// Prefix increment
			iterator&			operator++() {
				_ptr++;
				return (*this);
			}

			// Prefix increment, const only
			const_iterator&		operator++() const {
				const_cast<iterator*>(this)->_ptr++;
				return (*this);
			}

			// Postfix increment
			iterator			operator++( int ) {
				iterator old = *this;
				operator++();
				return (old);
			}

			// Postfix increment, const only
			const_iterator		operator++( int ) const {
				iterator old = *this;
				operator++();
				return (old);
			}

			// Prefix decrement
			iterator&			operator--() {
				_ptr--;
				return (*this);
			}

			// Prefix decrement, const only
			const_iterator&		operator--() const {
				const_cast<iterator*>(this)->_ptr--;
				return (*this);
			}

			// Postfix decrement
			iterator			operator--( int ) {
				iterator old = *this;
				operator--();
				return (old);
			}

			// Postfix decrement, const only
			const_iterator		operator--( int ) const {
				iterator old = *this;
				operator--();
				return (old);
			}

			iterator			operator+( int n ) {
				return (_ptr + n);
			}

			// Addition operator, const only
			const_iterator		operator+( int n ) const {
				return (_ptr + n);
			}

			// Subtraction operator
			iterator			operator-( int n ) {
				return (_ptr - n);
			}

			// Subtraction operator, const only
			const_iterator		operator-( int n ) const {
				return (_ptr - n);
			}

			// Difference operator, const compatible
			difference_type		operator-( const iterator& rhs ) const {
				return (_ptr - rhs._ptr);
			}

			// Addition assignment operator
			iterator&			operator+=( int n ) {
				_ptr += n;
				return (*this);
			}

			// Addition assignment operator, const only
			const_iterator&		operator+=( int n ) const {
				const_cast<iterator*>(this)->_ptr += n;
				return (*this);
			}

			// Subtraction assignment operator
			iterator&			operator-=( int n ) {
				_ptr -= n;
				return (*this);
			}

			// Subtraction assignment operator, const only
			const_iterator&		operator-=( int n ) const {
				const_cast<iterator*>(this)->_ptr -= n;
				return (*this);
			}

			// Member access operator
			reference			operator[]( size_type n ) {
				return (_ptr[n]);
			}

			// Member access operator, const only
			const_reference		operator[]( size_type n ) const {
				return (_ptr[n]);
			}
		};

		// Returns an iterator pointing to the first element in the vector.
		iterator	begin() {
			return (_start);
		}

		// Returns an iterator referring to the past-the-end element in the vector container.
		iterator	end() {
			return (_start + _size);
		}
		// iterator 				LegacyRandomAccessIterator to value_type
		// const_iterator 			LegacyRandomAccessIterator to const value_type
		// reverse_iterator 		std::reverse_iterator<iterator>
		// const_reverse_iterator 	std::reverse_iterator<const_iterator>

	/* **************************************** Capacity **************************************** */

		// [Returns the number of elements in the vector]
		size_type	size() const {
			return (_size);
		}

		// [Returns the maximum number of elements that the vector can hold]
		size_type	max_size() const {
			return (_alloc.max_size());
		}

		/*
			[Requests that the vector capacity be at least enough to contain n elements]

			If n is greater than the current vector capacity,the function causes
			the container to reallocate its storage increasing its capacity to n (or greater).

			In all other cases, the function call does not cause a reallocation and
			the vector capacity is not affected.

			This function has no effect on the vector size and cannot alter its elements.
		*/
		void		reserve( size_type n ) {
			if (n <= _capacity) {
				return;
			} else if (n > max_size()) {
				throw std::length_error("can't reserve more than max_size()");
			}

			pointer	tmp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(tmp + i, _start[i]);
			}
			this->destroy();
			_start = tmp;
			_capacity = n;
		}


		/*
			[Resizes the container so that it contains n elements]

			If n is smaller than the current container size, the content is reduced
			to its first n elements, removing those beyond (and destroying them).

			If n is greater than the current container size, the content is expanded by inserting
			at the end as many elements as needed to reach a size of n. If val is specified,the new
			elements are initialized as copies of val, otherwise, they are value-initialized.

			If n is also greater than the current container capacity,
			an automatic reallocation of the allocated storage space takes place.

			Notice that this function changes the actual content of the container
			by inserting or erasing elements from it.
		*/
		void		resize( size_type n, const value_type& val = value_type() ) {
			if (n < _size) {
				for (size_type i = n; i < _size; i++) {
					_alloc.destroy(_start + i);
				}
			} else if (n > _capacity) {
				reserve(n);
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(_start + i, val);
				}
			} else {
				for (size_type i = _size; i < n; i++) {
					_alloc.construct(_start + i, val);
				}
			}
			_size = n;
		}

		size_type	capacity() const {
			return (_capacity);
		}

		bool		empty() const {
			return (_size == 0);
		};

		// void		reserve (size_type n);

		// ###---------------- Capacity ----------------###
		// ###------------------------------------------###
		// ###------------- Element access -------------###

		// Element access
		reference		operator[](size_type n) {
			return _start[n];
		}

		// Element access, const only
		const_reference	operator[](size_type n) const {
			return _start[n];
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

	/* ************************************ Helper functions ************************************ */

		private:

		// Destroy objects in range (0, size), doesn't free memory
		void	destroy() {
			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_start + i);
			}
		}

		// Free allocated memory
		void	deallocate() {
			_alloc.deallocate(_start, _capacity);
		}

		void	copy( const vector& other ) {
			size_type	size = other._size;
			for (size_type i = 0; i < size; i++) {
				_alloc.construct(_start + i, other[i]);
			}
		}

		// Range, copy val from range (start, end)
		void	copy( size_type start, size_type end, const value_type& val = value_type() ) {
			for (size_type i = start; i < end; i++) {
				_alloc.construct(_start + i, val);
			}
		}

	};
};

#endif
