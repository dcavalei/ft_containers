#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

	template <
		class T,
		class Container = vector<T> >
	class stack
	{
		/* ************************************ Member types ************************************ */

	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		/* ************************************ Constructors ************************************ */

		explicit stack(container_type const &cont = container_type()) : _c(cont) {}

		~stack(){};

		stack &operator=(stack const &other)
		{
			_c = other._c;
			return *this;
		}

		/* *********************************** Element access *********************************** */

		reference top() { return _c.back(); }

		const_reference top() const { return _c.back(); }

		/* ************************************** Capacity ************************************** */

		bool empty() const { return _c.empty(); }

		size_type size() const { return _c.size(); }

		/* ************************************* Modifiers ************************************** */

		void push(value_type const &value) { _c.push_back(value); }

		void pop() { _c.pop_back(); }

		/* ******************************** Non-member functions ******************************** */

		friend bool operator==(stack const &lhs, stack const &rhs) { return lhs._c == rhs._c; }

		friend bool operator!=(stack const &lhs, stack const &rhs) { return lhs._c != rhs._c; }

		friend bool operator<(stack const &lhs, stack const &rhs) { return lhs._c < rhs._c; }

		friend bool operator<=(stack const &lhs, stack const &rhs) { return lhs._c <= rhs._c; }

		friend bool operator>(stack const &lhs, stack const &rhs) { return lhs._c > rhs._c; }

		friend bool operator>=(stack const &lhs, stack const &rhs) { return lhs._c >= rhs._c; }

		/* ******************************* Protected data members ******************************* */

	protected:
		container_type _c;
	};
}

#endif // STACK_HPP
