#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft {

	template< class T1, class T2 > struct pair {

		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

		pair() :
			first(T1()),
			second(T2()) {}

		pair( const pair& pr ) :
			first(pr.first),
			second(pr.second) {}

		pair( const first_type& a, const second_type& b ) :
			first(a),
			second(b) {}

		pair&	operator=( const pair& pr ) {
			if (this == &pr) {
				return (*this);
			}

			first = pr.first;
			second = pr.second;
			return (*this);
		}

		bool	operator==( const pair& rhs ) const {
				return ( first == rhs.first && second == rhs.second);
			}

		bool	operator!=( const pair& rhs ) const {
			return (!(*this == rhs));
		}

		bool	operator<( const pair& rhs ) const {
			return ( first < rhs.first || (!(rhs.first < first) && second < rhs.second));
		}

		bool	operator<=( const pair& rhs ) const {
			return (!(rhs < *this));
		}

		bool	operator>( const pair& rhs ) const {
			return (rhs < *this);
		}

		bool	operator>=( const pair& rhs ) const {
			return (!(*this < rhs));
		}

	};

}

#endif // UTILITY_HPP
