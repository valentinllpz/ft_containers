#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef STL
	#include <map>
	namespace ft = std;
else
	#include "map.hpp"

#define	MAX_SIZE 2048
#define SEED 42

void	testing_assign(ft::map<int,int> &m)
{
	std::srand(SEED);

	std::cout << "\n********* testing_assign *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		m[rand() % RAND_MAX] = rand() % RAND_MAX;
	std::cout << "m.size() = " << m.size() << std::endl;
	for (ft::map<int,int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << "m [" << it->first << "] [" << it->second << "]" << std::endl;
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_empty(ft::map<int,int> &m)
{
	ft::map<int,int> foo;

	std::cout << "\n********* testing_empty *********\n" << std::endl;
	std::cout << "After calling map empty constructor:"<< std::endl;
	if (foo.empty())
		std::cout << "foo is empty" << std::endl;
	else
		std::cout << "foo is not empty" << std::endl;
	foo = m;
	std::cout << "After foo = m:"<< std::endl;
	if (foo.empty())
		std::cout << "foo is empty" << std::endl;
	else
		std::cout << "foo is not empty" << std::endl;
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_size(ft::map<int,int> &m)
{
	ft::map<int,int> foo;

	std::cout << "\n********* testing_size *********\n" << std::endl;
	std::cout << "After calling map empty constructor:"<< std::endl;
	std::cout << "foo.size() = " << foo.size() << std::endl;
	foo = m;
	std::cout << "After foo = m: "<< std::endl;
	std::cout << "foo.size() = " << foo.size() << std::endl;
	std::cout << "\n************** END **************\n" << std::endl;
}

int main ()
{

	ft::map<int,int> m1;
	// first thing to test: modifiers with basic constructors
	


	return (0);
}