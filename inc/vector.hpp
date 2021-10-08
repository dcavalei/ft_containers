#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template<
    	class T,
    	class Allocator = std::allocator<T>
	> class vector	{
		private:
			T							value_type;
			Allocator					allocator_type;
			std::size_t					size_type;
			T&							reference = value_type;
			const T&					const_reference = value_type;
			Allocator::pointer			pointer;
			Allocator::const_pointer	const_pointer;

			// https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator

			// iterator 				LegacyRandomAccessIterator to value_type
			// const_iterator 			LegacyRandomAccessIterator to const value_type
			// reverse_iterator 		std::reverse_iterator<iterator>
			// const_reverse_iterator 	std::reverse_iterator<const_iterator>

		public:
			Vector(/* args */);
			~Vector();
	};
}

#endif