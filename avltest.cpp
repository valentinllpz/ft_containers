/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avltest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/07 21:46:26 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>

#include <list>
#include "AVL.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

int main ()
{
	AVLTree<int> tree;
	

	for (int i = 1; i < 50; i++)
		tree.add(i);

	tree.print(tree.getRoot(), 5);
	// Node<int> *n = tree.findParent(66);
	// std::cout << "\n parent is " << n->value;
	return 0;
}


