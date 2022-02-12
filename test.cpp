/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/12 17:11:33 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"

int main ()
{
  ft::vector<int> myvector (3,100);
  ft::vector<int>::iterator it;

  std::cout << "1 myvector contains:";
  for (ft::vector<int>::iterator it2 =myvector.begin(); it2<myvector.end(); it2++)
    std::cout << ' ' << *it2;
  std::cout << '\n';

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  std::cout << "2 myvector contains:";
  for (ft::vector<int>::iterator it2 =myvector.begin(); it2<myvector.end(); it2++)
    std::cout << ' ' << *it2;
  std::cout << '\n';

  myvector.insert (it,2,300);

  std::cout << "3 myvector contains:";
  for (ft::vector<int>::iterator it2 =myvector.begin(); it2<myvector.end(); it2++)
    std::cout << ' ' << *it2;
  std::cout << '\n';
  // "it" no longer valid, get a new one:
  it = myvector.begin();

  ft::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  std::cout << "4 myvector contains:";
  for (ft::vector<int>::iterator it2 =myvector.begin(); it2<myvector.end(); it2++)
    std::cout << ' ' << *it2;
  std::cout << '\n';

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "5 myvector contains:";
  for (ft::vector<int>::iterator it2 =myvector.begin(); it2<myvector.end(); it2++)
    std::cout << ' ' << *it2;
  std::cout << '\n';

  return 0;
}
