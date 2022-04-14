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
#define SEED 42

void	print_details(ft::vector<int> &v) // uses 
{

}

int main ()
{

	ft::vector<int> m; // just testing ints here
	// first thing to test: modifiers with basic constructors // faire des try catch ?
	
	std::cout << ">>>>>>>>>>>>>>>> TESTING vector <<<<<<<<<<<<<<<<<" << std::endl;
	// from now on size(), iterator, reverse iterator and basic constructor are required


	std::cout << ">>>>>>>>>>>>>>>> END vector TESTS <<<<<<<<<<<<<<<<<" << std::endl;

	return (0);
}