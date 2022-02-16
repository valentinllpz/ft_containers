/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/16 12:41:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"
#include <list>

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

int main ()
{
  ft::vector<int> myvector;
  for (int i=1; i<5; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::vector_reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::vector_reverse_iterator<iter_type> rev_from (until);     //                     ^

  std::cout << "myvector:";
//   while (rev_from != rev_until)
//   {
//     std::cout << *rev_from << " " << *rev_until;
//   	std::cout << '\n';
// 	  *rev_from++;
//   }

	std::cout << *rev_until << std::endl;
  return 0;
}


