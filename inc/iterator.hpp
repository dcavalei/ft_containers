#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft {

	template< class T >
	class iterator {

		public:

		typedef T								value_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef std::ptrdiff_t					difference_type;

		// Default constructor
		iterator() : _ptr(NULL) {}

		// Copy constructor
		iterator( const iterator& other ) {
			*this = other;
		}

		// Pointer constructor
		iterator( pointer ptr ) : _ptr(ptr) {}

		// Destructor
		~iterator() {}

		// Assignment operator
		iterator&			operator=( const iterator& rhs ) {
			_ptr = rhs._ptr;
			return (*this);
		}

		// Conversion operator to const_iterator
		operator	iterator<const value_type>() const {
			return (_ptr);
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

		// Dereference operator, const compatible
		reference			operator*() const {
			return (*_ptr);
		}

		// Member access operator, const compatible
		pointer				operator->() const {
			return (_ptr);
		}

		// Prefix increment
		iterator&			operator++() {
			_ptr++;
			return (*this);
		}

		// Postfix increment
		iterator			operator++( int ) {
			iterator old = *this;
			operator++();
			return (old);
		}

		// Prefix decrement
		iterator&			operator--() {
			_ptr--;
			return (*this);
		}

		// Postfix decrement
		iterator			operator--( int ) {
			iterator old = *this;
			operator--();
			return (old);
		}

		// Addition operator, const compatible
		iterator			operator+( difference_type n ) const {
			return (iterator(_ptr + n));
		}

		// Subtraction operator, const compatible
		iterator			operator-( difference_type n ) const {
			return (iterator(_ptr - n));
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

		// Subtraction assignment operator
		iterator&			operator-=( int n ) {
			_ptr -= n;
			return (*this);
		}

		// Member access operator, const compatible
		reference			operator[]( difference_type n ) const {
			return (_ptr[n]);
		}

		private:

		pointer	_ptr;

	};
};

#endif // ITERATOR_HPP
