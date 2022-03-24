#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef STL
	#include <map>
	namespace ft = std;
#else
	#include "map.hpp"
#endif

#define	MAX_SIZE 2048
#define SEED 42

void	print_details(ft::map<int,int> &m)
{
	std::cout << "printing details: " << std::endl;
	for (ft::map<int,int>::iterator it = m.begin(); it != m.end(); it++)
		std::cout << "[" << it->first << "] [" << it->second << "]" << std::endl;
	std::cout << "size = " << m.size() << std::endl; 
}

void	testing_assign()
{
	std::srand(SEED);
	ft::map<int,int> m;

	std::cout << "\n********* testing_assign *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		m[rand() % RAND_MAX] = rand() % RAND_MAX;
	print_details(m);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_empty()
{
	ft::map<int,int> foo;
	ft::map<int,int> m;

	std::cout << "\n********* testing_empty *********\n" << std::endl;
	std::cout << "After calling map empty constructor:"<< std::endl;
	if (foo.empty())
		std::cout << "foo is empty" << std::endl;
	else
		std::cout << "foo is not empty" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		foo.insert(ft::make_pair(rand() % RAND_MAX, rand() % RAND_MAX));
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

void	testing_erase()
{
	std::srand(SEED);
	ft::map<int,int> m;
	ft::map<int,int> mbis;
	ft::pair<int, int> val;
	ft::pair<ft::map<int, int>::iterator, bool> ret;
	ft::map<int, int>::iterator it;

	std::cout << "\n********* testing_assign *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		m[rand() % RAND_MAX] = rand() % RAND_MAX;
	std::cout << "(1) single element:" << std::endl;
	it = m.begin();
	for (int i = 0; i < rand() % MAX_SIZE; i++)
		it++;
	
	print_details(mbis);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_insert()
{
	std::srand(SEED);
	ft::map<int,int> m1;
	ft::map<int,int> m2;
	ft::map<int,int> m3;
	ft::pair<int, int> val;
	ft::pair<ft::map<int, int>::iterator, bool> ret;
	ft::map<int, int>::iterator it;

	std::cout << "\n********* testing_assign *********\n" << std::endl;
	std::cout << "(1) single element:" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		val = ft::make_pair(rand() % RAND_MAX, rand() % RAND_MAX);
		ret = m1.insert(val);
		if (ret.second == false)
			std::cout << "pair [" << val.first << "] [" << val.second << "] already exists" << std::endl;
	}
	print_details(m1);
	std::cout << "(2) with key:" << std::endl;
	it = m2.begin();
	for (int i = 0; i < MAX_SIZE; i++)
		it = m2.insert(it, ft::make_pair(rand() % RAND_MAX, rand() % RAND_MAX));
	print_details(m2);
	std::cout << "(3) range:" << std::endl;
	m3.insert(m2.begin(), it);
	print_details(m3);
	std::cout << "\n-- 2nd test with reverse iterators --\n" << std::endl;
	m1.insert(m3.rbegin(), m3.rend());
	print_details(m1);
	std::cout << "\n************** END **************\n" << std::endl;
}

int main ()
{

	ft::map<int,int> m;
	// first thing to test: modifiers with basic constructors
	
	testing_insert();


	return (0);
}