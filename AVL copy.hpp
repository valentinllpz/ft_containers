/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL copy.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:59:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/03 19:29:27 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP

#include "common.hpp"

namespace ft
{
	template <class T>
	class Node
	{
		public :

			T 		value;
			Node	*parent;
			Node	*l_child;
			Node	*r_child;

			Node() : value(0), parent(NULL), l_child(NULL), r_child(NULL) {}
			Node(const T & v) : value(v), parent(NULL), l_child(NULL), r_child(NULL) {}
			Node(const T & v, Node<T> *n) : value(v), parent(n), l_child(NULL), r_child(NULL) {}
	};


	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> >	>
	class AVLTree
	{
		private :

			Node<T>		*_root;
			size_t		_size;

			/* ************************************************************************** */
			/*                       PRIVATE MEMBER FUNCTIONS                             */
			/* ************************************************************************** */

			Node<T>		*minimum(Node<T> *n) const
			{
				if (n->l_child)
					return (minimum(n->l_child));
				return (n);
			}

			Node<T>		*maximum(Node<T> *n) const
			{
				if (n->r_child)
					return (maximum(n->r_child));
				return (n);
			}

			void	eraseFrom(Node<T> *node)
			{
				if (node != NULL)
				{
					eraseFrom(node->l_child);
					eraseFrom(node->r_child);
					delete node;
				}
			}

			int		depth(Node<T> *n) const
			{
				if (n == NULL)
					return (0);
				int	lh = depth(n->l_child);
				int	rh = depth(n->r_child);
				return (lh > rh ? lh + 1 : rh + 1);
			}

			void	balanceTree(Node<T> *tree)
			{
				if (tree == NULL)
					return;
				int bf = depth(tree->r_child) - depth(tree->l_child);
				if (bf == 2)		// if the tree is left heavy
				{
					int balance_r_child = depth(tree->r_child->r_child) - depth(tree->r_child->l_child);
					if (balance_r_child == -1)		// RL rotation required
						rightRotate(tree->r_child);
					leftRotate(tree);
				}
				else if (bf == -2)		// if the tree is right heavy
				{
					int balance_l_child = depth(tree->l_child->r_child) - depth(tree->l_child->l_child);
					if (balance_l_child == 1)		// LR rotation required
						leftRotate(tree->l_child);
					rightRotate(tree);
				}
				balanceTree(tree->parent);
			}
			
			void	leftRotate(Node<T> *tree)
			{
				if (tree == NULL)
					return ;
				Node<T> * r_child = tree->r_child;		// Linking tree's parent to tree's right child
				if (tree->parent != NULL)
				{
					if (tree->parent->r_child == tree)
						tree->parent->r_child = r_child;
					else
						tree->parent->l_child = r_child;
				}
				r_child->parent = tree->parent;			// Linking tree to right child's left subtree
				if (r_child->l_child != NULL)
					r_child->l_child->parent = tree;
				tree->r_child = r_child->l_child;		// Placing right child as head of tree
				tree->parent = r_child;
				r_child->l_child = tree;
				if (tree == _root)
					_root = r_child;
			}

			void	rightRotate(Node<T> *tree)
			{
				if (tree == NULL)
					return;
				Node<T> * l_child = tree->l_child;		// Linking tree's parent to tree's left child
				if (tree->parent != NULL)
				{
					if (tree->parent->l_child == tree)
						tree->parent->l_child = l_child;
					else
						tree->parent->r_child = l_child;
				}
				l_child->parent = tree->parent;			// Linking tree and left child's right subtree
				if (l_child->r_child != NULL)
					l_child->r_child->parent = tree;
				tree->l_child = l_child->r_child;		// Placing left child as head of tree
				tree->parent = l_child;
				l_child->r_child = tree;
				if (tree == _root)
					_root = l_child;
			}



	public :

		AVLTree() : _root(NULL), _size(0) {}
		~AVLTree() {}

		bool		isEmpty() { return (_root == NULL ? true : false); }
		
		size_t		get_size() const {return (_size); };

		Node<T>		*get_root() { return (_root); }

		Node<T>		*findValue(const T & v) const
			{
				Node<T>	*n = _root;

				while (n && n->value != v)
				{
					if (v < n->value)
						n = n->l_child;
					else
						n = n->r_child;
				}
				return (n);
			}


		int		add(const T v)
		{
			if (findValue(v))
				return (0); 			// If value already exists we cannot add it
			Node<T> *parent = _root;
			if (parent)
			{
				while (1)					// We need first to find which node will become parent of new value v
				{
					if (v < parent->value && parent->l_child)
						parent = parent->l_child;
					else if (parent->value < v && parent->r_child)
						parent = parent->r_child;
					else
						break ;
				}
			}
			Node<T> *n = 
			
			new Node<T>(v, parent);

			if (n == NULL)
				return (0);
			if (parent == NULL)			// Now linking new node to parent 
				_root = n;
			else if (v < parent->value)
				parent->l_child = n;
			else
				parent->r_child = n;
			++_size;
			balanceTree(findValue(v));
			return (1);
		}

		int		remove(const T & v)
		{
			Node<T> *n = findValue(v);
			if (n == NULL)
				return (0);
			Node<T> *parent = n->parent;					// Backing up parent address
			Node<T> *substitute = maximum(n->l_child);		// finding smallest value bigger than n->value
			if (substitute == NULL) 						// if no substitute found
			{
				if (n == _root)
					_root = n->r_child;
				else if (n->parent->l_child == n)
					n->parent->l_child = n->r_child;
				else
					n->parent->r_child = n->r_child;
				if (n->r_child != NULL)
					n->r_child->parent = n->parent;
			}
			else
			{
				n->value = substitute->value;
				if (substitute->parent->l_child == substitute)
					substitute->parent->l_child = substitute->l_child;
				else
					substitute->parent->r_child = substitute->l_child;
				if (substitute->l_child != NULL)
					substitute->l_child->parent = substitute->parent;
				n = substitute;
			}
			delete n;
			--_size;
			balanceTree(parent);
			return 1;
		}

		void		clear()
		{
			if (_size > 0)
			{
				eraseFrom(_root->l_child);
				eraseFrom(_root->r_child);
				delete _root;
				_size = 0;
			}
		}

		// DEBUG
		void		print(Node<T> * r, int space)
		{
			if (r == NULL)
				return ;
			space += 5; 
			print(r->r_child, space);
			std::cout << std::endl;
			for (int i = 5; i < space; i++)
				std::cout << " ";
			std::cout << r->value << "\n"; 
			print(r->l_child, space); 
		}
	};
}

#endif

