#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_traits.hpp"

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
		typedef std::random_access_iterator_tag	iterator_category;

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

	template< class Iterator >
	class reverse_iterator {

	public:

	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	reverse_iterator() : _base(iterator_type()) {}

	explicit reverse_iterator( iterator_type it ) : _base(it - 1) {}

	template< class Iter >
	reverse_iterator( const reverse_iterator<Iter>& rev_it ) : _base(rev_it._base) {}

	// Returns a copy of the base iterator
	iterator_type	base() const {
		return (_base + 1);
	}

	reference	operator*() const {
		return (*_base);
	}

	reverse_iterator	operator+( difference_type n ) const {
		return (reverse_iterator(base() - n));
	}

	reverse_iterator	operator-( difference_type n ) const {
		return (reverse_iterator(base() + n));
	}

	reverse_iterator&	operator++() {
		--_base;
		return (*this);
	}

	reverse_iterator	operator++(int) {
		reverse_iterator	old = *this;

		operator++();
		return (old);
	}

	reverse_iterator&	operator--() {
		++_base;
		return (*this);
	}

	reverse_iterator	operator--(int) {
		reverse_iterator	old = *this;

		operator--();
		return (old);
	}

	reverse_iterator&	operator+=( difference_type n ) {
		_base -= n;
		return (*this);
	};

	reverse_iterator&	operator-=( difference_type n ) {
		_base += n;
		return (*this);
	};

	pointer				operator->() const {
		return (&(operator*()));
	}

	reference			operator[]( difference_type n ) const {
		return (base()[-n - 1]);
	}

	private:

	iterator_type	_base;

	};

	template< class Iterator >
	bool	operator==( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() == rhs.base());
	}
	template< class Iterator >
	bool	operator!=( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() != rhs.base());
	}
	template< class Iterator >
	bool	operator<( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() > rhs.base());
	}
	template< class Iterator >
	bool	operator<=( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() >= rhs.base());
	}
	template< class Iterator >
	bool	operator>( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() < rhs.base());
	}
	template< class Iterator >
	bool	operator>=( const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs ) {
		return (lhs.base() <= rhs.base());
	}

};

#endif // ITERATOR_HPP
