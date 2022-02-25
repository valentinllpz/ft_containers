/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL_old.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:59:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/25 13:13:09 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.hpp"

template <class T>
class Node
{
	public:

		T 		value;
		Node	*parent;
  		Node	*left;
		Node	*right;

 		Node() : value(0), left(NULL), right(NULL) {}
		Node(T & v) : value(v), left(NULL), right(NULL) {}
};



template <class T>
class AVLTree
{
	public:

		Node<T>	*root;
	
		AVLTree() : root(NULL) {}

		bool	isEmpty() { return (root == NULL ? true : false); }

		int		height(Node<T> *n)  // Get the tree's height from Node *n recursively
		{
			if (n == NULL)
				return (-1);
			int	lh = height(n->left);
			int	rh = height(n->right);
			return (lh > rh ? lh + 1 : rh + 1);
		}

		int		balance(Node<T> *n) // Get the balance factor of Node *n
		{
			if (n == NULL)
				return (-1);
			return (height(n->left) - height(n->right));
		}

		Node<T>	*rightRotate(Node<T> *y)
		{
			Node<T> *x = y->left;
			Node<T> *subtree = x->right;
			x->right = y;
			y->left = subtree;
			return (x);
		}

		Node<T>	*leftRotate(Node<T> *x)
		{
			Node<T> *y = x->right;
			Node<T> *subtree = y->left;
			y->left = x;
			x->right = subtree;
			return (y);
		}

		Node<T>	*min(Node<T> *n)
		{
			if (n->left)
				return (min(n->left));
			return (n);
		}

		Node<T> *findParent(Node<T> *n, T & value)
		{
			if (n == NULL)
				return (NULL);
			if (n->left && value < n->left->value)
				return (findParent(n->left, value));
			else if (n->right && value > n->right->value)
				return (findParent(n->right, value));
			return (n);
		}
		
		Node<T>	*increment(Node<T> *n, T & value)
		{
			if (n == NULL)
				return (NULL);
			if (n->left && value < n->left->value)
				return (increment(n->left, value));
			else if (n->right && value > n->right->value)
				return (increment(n->right, value));
			if (n->right && value > n->right->value)
				return (min(n->right));
			return (n);
		}
		
		Node<T>	*insertNode(Node<T> *n, Node<T> *new_node)
		{
			if (n == NULL)
			{
				n = new_node;
				return (n);
			}
			if (new_node->value < n->value)
				n->left = insertNode(n->left, new_node);
			else if (new_node->value > n->value)
				n->right = insertNode(n->right, new_node);
			else // no duplicate allowed
				return (n);
			int	bf = balance(n);
			if (bf > 1 && new_node->value < n->left->value)  // if the tree is left heavy and our new_node->value was added after n->left
				return (rightRotate(n));
			if (bf < -1 && new_node->value > n->right->value) // if the tree is right heavy and our new->node value was added after n->right
				return (leftRotate(n));
			if (bf > 1 && new_node->value > n->left->value) // if the tree is left heavy and our new_node->value was added to n->right
			{
				n->left = leftRotate(n);
				return (rightRotate(n));
			}
			if (bf < -1 && new_node->value < n->right->value) // if the tree is right heavy and our new_node->value was added to n->left
			{
				n->right = rightRotate(n);
				return (leftRotate(n));
			}
			return (n);
		}

		Node<T>	*searchNode(Node<T> *n, T & value) // call with n = root the first time to search all the tree
		{
			if (n == NULL)
				return (NULL);
			if (value < n->value)
				return (searchNode(n->left, value));
			else if (value > n->value)
				return (searchNode(n->right, value));
			else // value == n->value
				return (n);
		}

		Node<T>	*deleteNode(Node<T> *n, T value)
		{
			if (n == NULL)
				return (NULL);
			if (value < n->value)
				n->left = deleteNode(n->left, value);
			else if (value > n->value)
				n->right = deleteNode(n->right, value);
			else
			{
				if (n->left == NULL) // node with only one child or no child
				{
					Node<T> *tmp = n->right;
					delete n;
					return (tmp);
				}
				else if (n->right == NULL) // node with only one child or no child
				{
					Node<T> *tmp = n->left;
					delete n;
					return (tmp);
				}
				else // node with 2 children
				{
					Node<T> *tmp = n->right; // Here we are going down to the smallest value of the n right descendants (= smallest value bigger than n->value)
					while (tmp->left)
						tmp = tmp->left;
					n->value = tmp->value; // we replace the value in node n
					n->right = deleteNode(n->right, n->value); // from the right child of n, we now delete the duplicate value
				}

				int bf = getBalanceFactor(n);
				if (bf == 2 && getBalanceFactor(n->left) >= 0) // Left Left Imbalance
					return rightRotate(n);
				else if (bf == 2 && getBalanceFactor(n->left) == -1) // Left Right Imbalance
				{
					n->left = leftRotate(n->left);
					return rightRotate(n);
				}
				else if (bf == -2 && getBalanceFactor(n->right) <= 0) // Right Right Imbalance	
					return leftRotate(n);
				else if (bf == -2 && getBalanceFactor(n->right) == 1) // Right Left Imbalance
				{
					n->right = rightRotate(n->right);
					return leftRotate(n);
    			}
			}
			return (n);
		}

		// DEBUG
		void	print(Node<T> * r, int space)
		{
			if (r == NULL)
				return ;
			space += 5; 
			print(r -> right, space);
			std::cout << std::endl;
			for (int i = 5; i < space; i++)
				std::cout << " ";
			std::cout << r -> value << "\n"; 
			print(r -> left, space); 
		}
		
};
