/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/14 17:19:05 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"

int main ()
{
  std::vector<int> foo (3,100);   // three ints with a value of 100
  std::vector<int> bar (4,200);   // five ints with a value of 200

	bar.reserve(50);
	std::cout << "foo.size() = " << foo.size() << " foo.capacity() = " << foo.capacity() <<  std::endl; 
	std::cout << "bar.size() = " << bar.size() << " bar.capacity() = " << bar.capacity() << std::endl;
	foo = bar;
	std::cout << "AFTER\nfoo.size() = " << foo.size() << " foo.capacity() = " << foo.capacity() << std::endl;
	std::cout << "bar.size() = " << bar.size() << " bar.capacity() = " << bar.capacity() << std::endl;

  return 0;
}


