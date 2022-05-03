/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:19:36 by vlugand-          #+#    #+#             */
/*   Updated: 2022/05/03 12:56:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

#ifdef STL
	#include <stack>
    #include <vector>
	namespace ft = std;
#else
	#include "../stack.hpp"
    #include "../vector.hpp"
#endif

#define	MAX_SIZE 10000 // INT VALUE ONLY
#define SEED 42

template <typename T>
void	print_details(ft::stack<T> &s) // uses size, max_size, capacity, empty and []
{
	std::cout << "printing details: " << std::endl;
	
	while (!s.empty())
    {
        std::cout << "top() = [" << s.top() << "] | size = " << s.size() << std::endl;
        s.pop();
    }
	std::cout << "--------- details printed" << std::endl;
}

std::string		itoa_cpp(int nb)
{
	std::stringstream	out;

	out << nb;
	return (out.str());
}

void    testing_all()
{
    ft::stack<int> s;
    ft::stack<std::string> s2;
    ft::stack<int,ft::vector<int> > sv;
    ft::vector<int> v(MAX_SIZE, 42);
    ft::stack<int,ft::vector<int> > sv2(v);

    for (int i = 0; i < MAX_SIZE; ++i)
        s.push(i);
    for (int i = 0; i < MAX_SIZE; ++i)
        s2.push(itoa_cpp(i));
    for (int i = 0; i < MAX_SIZE; ++i)
        sv.push(i);
    print_details(s);
    print_details(s2);
}

int main ()
{
	srand(SEED);
	std::cout << ">>>>>>>>>>>>>>>> TESTING stack <<<<<<<<<<<<<<<<<" << std::endl;
	testing_all();
	std::cout << ">>>>>>>>>>>>>>>> END stack TESTS <<<<<<<<<<<<<<<<<" << std::endl;

	return (0);
}
