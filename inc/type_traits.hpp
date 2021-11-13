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
	struct is_integral : integral_constant< T, false > {};

	template<>
	struct is_integral< bool > : integral_constant< bool, true > {};

	template<>
	struct is_integral< char > : integral_constant< char, true > {};

	template<>
	struct is_integral< wchar_t > : integral_constant< wchar_t, true > {};

	template<>
	struct is_integral< signed char > : integral_constant< signed char, true > {};

	template<>
	struct is_integral< short int > : integral_constant< short int, true > {};

	template<>
	struct is_integral< int > : integral_constant< int, true > {};

	template<>
	struct is_integral< long int > : integral_constant< long int, true > {};

	template<>
	struct is_integral< long long int > : integral_constant< long long int, true > {};

	template<>
	struct is_integral< unsigned char > : integral_constant< unsigned char, true > {};

	template<>
	struct is_integral< unsigned short int > : integral_constant< unsigned short int, true > {};

	template<>
	struct is_integral< unsigned int > : integral_constant< unsigned int, true > {};

	template<>
	struct is_integral< unsigned long int > : integral_constant< unsigned long int, true > {};

	template<>
	struct is_integral< unsigned long long int > : integral_constant< unsigned long long int, true > {};

	// https://www.cplusplus.com/reference/type_traits/enable_if/

	template< bool Cond, class T = void >
	struct enable_if {};

	template< class T >
	struct enable_if<true, T> {

		typedef T 				type;

	};

}


#endif // TYPE_TRAITS_HPP
