#include <iostream>
#include "vector.hpp"
#include <vector>
#include <memory>
#include <iomanip>

struct Animal {

	Animal(){}
	~Animal(){}

	void	function() {
		debug_msg("F called");
	}
};

template<class T>
void	print_table( const std::vector<T>& vector, const ft::vector<T>& ft_vector );

int main() {

	ft::vector<int>						ft_vector(10);
	std::vector<int>					vector(10);

	std::allocator< ft::vector<int> >	alloc;

	ft::vector<int>* ptr = alloc.allocate(10); //malloc

	alloc.construct(ptr, ft_vector); //ctor called

	print_table(vector, ft_vector);

	ft::vector<int>::iterator ft_it;
	ft::vector<int>::iterator it2(ft_it);
	ft_it = ft_vector.begin();

	std::cout << *ft_it << std::endl;


	std::cout << *ft_it << std::endl;

	std::vector<int>::iterator it123(&vector[0]);
	std::vector<int>::iterator it321(&vector[8]);

	std::cout << it123 - it321 << std::endl;

	std::cout << "=================" << std::endl;

	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);

	for (std::vector<int>::iterator it(&vector[0]); it != vector.end(); ++it)
		std::cout << "vec = " << *it << std::endl;
	return (0);

}

template<class T>
void	print_table( const std::vector<T>& vector, const ft::vector<T>& ft_vector ) {

	std::cout << "======================================================" << std::endl;
	std::cout << std::left << '|' << std::setw(10) << "##########" << '|' << std::setw(20) << "std::vector" << '|' << std::setw(20) << "ft::vector" << '|' << std::endl;
	std::cout << std::left << '|' << std::setw(10) << "size()" << '|' << std::setw(20) << vector.size() << '|' << std::setw(20) << ft_vector.size() << '|' << std::endl;
	std::cout << std::left << '|' << std::setw(10) << "max_size()" << '|' << std::setw(20) << vector.max_size() << '|' << std::setw(20) << ft_vector.max_size() << '|' << std::endl;
	std::cout << std::left << '|' << std::setw(10) << "capacity()" << '|' << std::setw(20) << vector.capacity() << '|' << std::setw(20) << ft_vector.capacity() << '|' << std::endl;

}




















//	##########################################################################################

// #include <iostream>
// #include <string>
// #include <deque>
// #if 1 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include <map.hpp>
// 	#include <stack.hpp>
// 	#include <vector.hpp>
// #endif

// #include <stdlib.h>

// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };


// #define COUNT (MAX_RAM / (int)sizeof(Buffer))

// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs)
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}

// 	typedef typename ft::stack<T>::container_type::iterator iterator;

// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{clang
// 	const int seed = atoi(argv[1]);
// 	srand(seed);

// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
// 	ft::map<int, int> map_int;

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}

// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);

// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}

// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;

// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }
