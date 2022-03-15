#include "vector.hpp"
// #include <vector>
#include <iostream>

int main()
{
	ft::vector<int> v(7);
	// std::vector<int> v2;
	
	for (unsigned long int i = 0; i < v.size(); ++i)
		v[i] = (v.size() - i) * 3;
	
	// for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
	// 	std::cout << "[" << *it << "] ";
	std::cout << std::endl;
	v.insert(v.begin(), 2, 42);
	return 0;
}