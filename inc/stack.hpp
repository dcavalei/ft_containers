#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

	template<
		class T,
		class Container = vector<T>
	> class stack {

	/* ************************************** Member types ************************************** */

		public:

		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	/* ********************************** Private data members ********************************** */

		protected:

		container_type	_c;

	/* ************************************** Constructors ************************************** */

		public:

		explicit stack( const container_type& cont = container_type() ) : _c(cont) {}

		~stack() {};

		stack&	operator=( const stack& other ) { _c = other._c; return *this; }

	/* ************************************* Element access ************************************* */

		reference	top() { return _c.back(); }

		const_reference	top() const { return _c.back(); }

	/* **************************************** Capacity **************************************** */

		bool	empty() const { return _c.empty(); }

		size_type	size() const { return _c.size(); }

	/* *************************************** Modifiers **************************************** */

		void	push( const value_type& value ) { _c.push_back(value); }

		void	pop() { _c.pop_back(); }

		friend bool	operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c == rhs._c;
		}

		friend bool	operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c != rhs._c;
		}

		friend bool	operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c < rhs._c;
		}

		friend bool	operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c <= rhs._c;
		}

		friend bool	operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c > rhs._c;
		}

		friend bool	operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c >= rhs._c;
		}

	};

	/* ********************************** Non-member functions ********************************** */

	template< class T, class Container >
	bool	operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs == rhs;
	}

	template< class T, class Container >
	bool	operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs != rhs;
	}

	template< class T, class Container >
	bool	operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs < rhs;
	}

	template< class T, class Container >
	bool	operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs <= rhs;
	}

	template< class T, class Container >
	bool	operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs > rhs;
	}

	template< class T, class Container >
	bool	operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
		return lhs >= rhs;
	}

}

#endif // STACK_HPP
