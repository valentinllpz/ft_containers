/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:59:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/22 17:00:38 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"

template <class T>
class Node
{
	public:

		T 		value;
  		Node	*left;
		Node	*right;

 		Node() : value(0), left(NULL), right(NULL) {}
		Node(T & v) : value(v), left(NULL), right(NULL) {}
};

template <class T>
class AVLTree
{
	public:

		Node	*root;
	
		AVLTree() : root(NULL) {}

		bool	isEmpty() { return (root == NULL ? true : false); }

		int		height(Node *n)  // Get Tree's height from Node *n recursively
		{
			if (n == NULL)
				return (-1);
			int	lh = height(n->left);
			int	rh = height(n->right);
			return (lh > rh ? lh + 1 : rh + 1)
		}

		int		balance(Node *n) // Get Balance factor of Node *n
		{
			if (n == NULL)
				return (-1);
			return (height(n->left) - height(n->right));
		}

		Node	*rightRotate(Node *y) // Performs a right rotation if the tree is left heavy
		{
			Node *x = y->left;
			node *subtree = x->right;
			x->right = y;
			y->left = subtree;
			return (x);
		}

		Node	*leftRotate(Node *x)  // Performs a right rotation if the tree is right heavy
		{
			Node *y = x->right;
			node *subtree = y->left;
			y->left = x;
			x->right = subtree;
			return (y);
		}
		
		Node	*insert(Node *n, Node *new_node)
		{
			if (n == NULL)
			{
				n = new_node;
				return (n);
			}
			if (new_node->value < n->value)
				n->left = insert(n->left, new_node);
			else if (new_node->value > n->value)
				n->right = insert(n->right, new_node);
			else // no duplicate allowed
				return (n);
			
		}

}