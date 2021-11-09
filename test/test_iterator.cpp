#ifndef _IS_TEST
# include <vector>
namespace ft = std;
#else
# include "vector.hpp"
#endif

# include "test.hpp"

int main() {

	ft::vector<int>	vec(42);

	for (size_t i = 0; i < 42; i++)
		vec[i] = i * 42;

	{
		// Is default-constructible, copy-constructible, copy-assignable and destructible
		ft::vector<int>::iterator			default_ctor;
		ft::vector<int>::iterator			copy_ctor(default_ctor);
		ft::vector<int>::const_iterator		it = vec.begin();
		(void)default_ctor;
		(void)copy_ctor;

		it++;
		std::cout << *it << std::endl;
		++it;
		std::cout << *it << std::endl;
		it--;
		std::cout << *it << std::endl;
		--it;

		it++;
		it++;
		it++;

		std::cout << *(it + 1) << std::endl;
		std::cout << *(it - 1) << std::endl;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 2) << std::endl;

		std::cout << it[-1] << std::endl;
		std::cout << it[3] << std::endl;

	}

	return 0;
}
