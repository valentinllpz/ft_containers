/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/26 14:44:11 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>     // std::cout
#include <iterator>     // std::iterator_traits
#include <typeinfo>     // typeid
#include "iterator_traits.hpp"

int main()
{
	// STD
	typedef std::iterator_traits<int *> stdtraits;
	if (typeid(stdtraits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "[std] int * is a random access iterator" << std::endl;
	// FT
		typedef ft::iterator_traits<int *> fttraits;
	if (typeid(fttraits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "[ft] int * is a random access iterator" << std::endl;
	return (0);
}