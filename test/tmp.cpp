#include "test.hpp"
#include <vector>
#include <csignal>



void	sigsegv( int signal ) {
	// std::cout << 
}

int main() {
{
	std::signal(SIGSEGV, sigsegv);

	std::vector<int>	vector;

}

	return 0;
}
