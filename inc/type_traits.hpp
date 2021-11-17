#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <cwchar>

namespace ft {

	// https://www.cplusplus.com/reference/type_traits/integral_constant/

	template< class T, T v >
	struct integral_constant {

		typedef T 						value_type;
		typedef integral_constant<T,v>	type;

		static const T value = v;

		operator T() {
			return v;
		}

	};

	// https://www.cplusplus.com/reference/type_traits/true_type/

	typedef integral_constant< bool, true >		true_type;

	// https://www.cplusplus.com/reference/type_traits/false_type/

	typedef integral_constant< bool, false >	false_type;

	// https://www.cplusplus.com/reference/type_traits/is_integral/

	template< class T >
	struct is_integral : false_type {};

	template<>
	struct is_integral< bool > : true_type {};

	template<>
	struct is_integral< char > : true_type {};

	template<>
	struct is_integral< wchar_t > : true_type {};

	template<>
	struct is_integral< signed char > : true_type {};

	template<>
	struct is_integral< short int > : true_type {};

	template<>
	struct is_integral< int > : true_type {};

	template<>
	struct is_integral< long int > : true_type {};

	template<>
	struct is_integral< long long int > : true_type {};

	template<>
	struct is_integral< unsigned char > : true_type {};

	template<>
	struct is_integral< unsigned short int > : true_type {};

	template<>
	struct is_integral< unsigned int > : true_type {};

	template<>
	struct is_integral< unsigned long int > : true_type {};

	template<>
	struct is_integral< unsigned long long int > : true_type {};

	// https://www.cplusplus.com/reference/type_traits/enable_if/

	template< bool Cond, class T = void >
	struct enable_if {};

	template< class T >
	struct enable_if<true, T> {

		typedef T 				type;

	};

	// https://www.cplusplus.com/reference/type_traits/is_same/

	template< class T, class U >
	struct is_same : false_type {};

	template< class T >
	struct is_same<T, T> : true_type {};

}


#endif // TYPE_TRAITS_HPP
