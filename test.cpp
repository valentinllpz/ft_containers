/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/23 17:56:55 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// vector::reserve
#include <iostream>
#include <vector>
#include <stdexcept>
#include "vector.hpp"
#include <list>
#include "AVL.hpp"

#define TESTED_NAMESPACE ft
#define TESTED_TYPE int

int main ()
{
	AVLTree<int> tree;
	Node<int> * new_node = new Node<int>();

	for (int i = 0; i < 15; i++)
	{
		new_node->value = i;
		tree.insert(tree.root, new_node);
	}
	tree.print(tree.root, 5);
	return 0;
}


