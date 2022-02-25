/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avltest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:32:00 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/25 15:04:25 by vlugand-         ###   ########.fr       */
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
	

	for (int i = 1; i < 15; i++)
		tree.add(i);

	tree.print(tree.getRoot(), 5);

	return 0;
}


