/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:19:36 by vlugand-          #+#    #+#             */
/*   Updated: 2022/04/07 23:53:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef STL
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

#define	MAX_SIZE 2048 // INT VALUE ONLY

void	print_details(ft::vector<int> &v) // uses size, max_size, capacity, empty and []
{
	std::cout << "printing details: " << std::endl;
	std::cout << "size = " << v.size() << std::endl;
	if (v.empty())
		std::cout << "v is empty" << std::endl;
	else
		std::cout << "v is not empty" << std::endl;
	std::cout << "max size = " << v.max_size() << std::endl;
	std::cout << "capacity = " << v.capacity() << std::endl;	
	std::cout << "printing content: " << std::endl;
	for (size_t i = 0; i < v.size(); i++)
		std::cout << "v[" << i << "] = "<< v[i] << std::endl;
}

void	testing_clear()
{
	ft::vector<int> v;

	std::cout << "\n********* testing_erase *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v.push_back(rand() % RAND_MAX);
	v.clear();
	print_details(v);
	for (int i = 0; i < MAX_SIZE; i++)
		v.push_back(rand() % RAND_MAX);
	print_details(v);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_swap()
{
	ft::vector<int> v1;
	ft::vector<int> v2;

	std::cout << "\n********* testing_swap *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v1.push_back(rand() % RAND_MAX);
	for (int i = 0; i < MAX_SIZE; i++)
		v2.push_back(rand() % RAND_MAX);
	v1.swap(v2);
	v1.erase(v1.begin());
	v2.assign(rand() % MAX_SIZE, rand() % RAND_MAX);
	print_details(v1);
	print_details(v2);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_erase()
{
	ft::vector<int> v;
	ft::vector<int>::iterator it;

	std::cout << "\n********* testing_erase *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v.push_back(rand() % RAND_MAX);
	it = v.begin() + v.size() / 2;
	it = v.erase(it);
	std::cout << "*it = " << *it << std::endl;
	print_details(v);
	v.erase(v.begin(), v.end());
	v.erase(v.begin(), v.end());
	print_details(v);
	for (int i = 0; i < MAX_SIZE; i++)
		v.push_back(rand() % RAND_MAX);
	print_details(v);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_insert()
{
	ft::vector<int> v1;
	ft::vector<int> v2;
	ft::vector<int>::iterator it;

	std::cout << "\n********* testing_insert *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v1.push_back(rand() % RAND_MAX);
	std::cout << "(1) single element:" << std::endl;
	it = v1.begin() + v1.size() / 2;
  	it = v1.insert(it, rand() % RAND_MAX);
	std::cout << "*it = " << *it << std::endl;
	it = v1.end();
  	it = v1.insert(it , rand() % RAND_MAX);
	std::cout << "*it = " << *it << std::endl;
	print_details(v1);
	std::cout << "(2) fill:" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v2.push_back(rand() % RAND_MAX);
	it = v2.begin() + v2.size() / 2;
	v2.insert(it, rand() % MAX_SIZE, rand() % RAND_MAX);
	print_details(v2);
	std::cout << "(3) range:" << std::endl;
	it = v2.begin() + v2.size() / 2;
	v2.insert(it, v1.rbegin(), v1.rend());
	print_details(v2);
	int myarray [] = {501,502,503};
  	v1.insert (v1.begin() + v1.size() / 2, myarray, myarray + 3);
	print_details(v1);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_push_pop_back()
{
	ft::vector<int> v;

	std::cout << "\n********* testing_push_pop_back *********\n" << std::endl;
	for (int i = 0; i < MAX_SIZE; i++)
		v.push_back(rand() % RAND_MAX);
	if (!v.empty())
		v.pop_back();
	print_details(v);
	while (!v.empty())
		v.pop_back();
	print_details(v);
	std::cout << "\n************** END **************\n" << std::endl;
}

void	testing_assign()
{
	ft::vector<int> v1;
	ft::vector<int> v2;
	ft::vector<int> v3;

	std::cout << "\n********* testing_assign *********\n" << std::endl;
	v1.assign(0, 0);
	v2.assign(v1.begin(), v1.end());
	print_details(v1);
	print_details(v2);
	v1.assign(rand() % RAND_MAX, rand() % MAX_SIZE);
	v2.assign(v1.begin(), v1.end());
	print_details(v1);
	print_details(v2);
	int myints[] = {1776,7,4};
  	v3.assign(myints,myints+3);
	v2.assign(v3.rbegin(), v3.rend());
	print_details(v1);
	print_details(v2);
	print_details(v3);
	std::cout << "\n************** END **************\n" << std::endl;
}

int main ()
{

	ft::vector<int> m; // just testing ints here
	// first thing to test: modifiers with basic constructors // faire des try catch ?
	
	std::cout << ">>>>>>>>>>>>>>>> TESTING vector <<<<<<<<<<<<<<<<<" << std::endl;
	// from now on size(), iterator, reverse iterator and basic constructor are required
	// size, max_size, capacity, empty and []
	testing_assign();
	testing_push_pop_back();
	testing_insert();
	testing_erase();
	testing_swap();
	std::cout << ">>>>>>>>>>>>>>>> END vector TESTS <<<<<<<<<<<<<<<<<" << std::endl;

	return (0);
}