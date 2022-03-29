#include "map.hpp"

#include <iostream>

int main()
{
    ft::map<int, int> mymap;
    srand(0);

    for (size_t i = 0; i != 10000000; i++)
    {
        mymap.insert(ft::map<int, int>::value_type(rand(), rand()));
    }
}
