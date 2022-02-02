/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/02 16:08:48 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"

int main ()
{
  std::vector<int>::size_type sz;

 
    ft::vector<int> foo;
	foo.reserve(42);
  sz = foo.capacity();
//   std::cout << "making foo grow:\n";
  for (int i=0; i<20; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
   	sz = foo.capacity();
      std::cout << "capacity : " << sz << '\n';
    }
  }
  foo.insert(foo.begin() + 10, 3, 42);


  for (int i=0; i< foo.size(); i++)
  {
	  std::cout << foo[i] << std::endl;
  }

//   std::vector<int> bar;
//   sz = bar.capacity();
//   bar.reserve(100);   // this is the only difference with foo above
//   std::cout << "making bar grow:\n";
//   for (int i=0; i<100; ++i) {
//     bar.push_back(i);
//     if (sz!=bar.capacity()) {
//       sz = bar.capacity();
//       std::cout << "capacity changed: " << sz << '\n';
//     }
//   }

// std::cout << "test : " << bar[sz - 1] << std::endl;
//    bar.resize(120); 
//    sz = bar.size(); // cap
//    std::cout << "resize: " << sz << '\n';


//    bar.reserve(220); 
//    sz = bar.size(); // cap
//    std::cout << "reserve: " << sz << '\n';

// 	bar.assign(foo.begin(), foo.end());
// 	   sz = bar.size(); // cap
//    std::cout << "assign: " << sz << '\n';


  return 0;
}