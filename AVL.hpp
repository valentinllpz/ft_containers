/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:59:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/25 17:42:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
# define AVL_HPP

#include "common.hpp"

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


template <class T>
class AVLTree
{
	public :

		Node<T>		*root;		// root de l'arbre.
		int			nodeNb;		// Nombre de noeuds de l'arbre.

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

		Node<T>		*findValue(const T & v) const
		{
			Node<T>	*n = root;

			while (n && n->value != v)
			{
				if (v < n->value)
					n = n->l_child;
				else
					n = n->r_child;
			}
			return (n);
		}

		Node<T>		*findParent(const T & v) const
		{
			if (nodeNb == 0)
				return (NULL);
			Node<T>	*parent = root;
			while (1)
			{
				std::cout << "LOOP\n";
				if (v < parent->value && parent->l_child)
					parent = parent->l_child;
				else if (parent->value < v && parent->r_child)
					parent = parent->r_child;
				else
					break ;
			}
			std::cout << parent->value << " is the parent of " << v << std::endl;
			return (parent);
		}

		void eraseFrom(Node<T> *node)
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

		void balanceTree(Node<T> *tree)
		{
			if (tree == NULL)
				return;
			int bf = depth(tree->r_child) - depth(tree->l_child);
			if (bf == 2) // if the tree is left heavy.
			{
				int balance_r_child = depth(tree->r_child->r_child) - depth(tree->r_child->l_child);
				if (balance_r_child == -1)	// RL rotation required
					rightRotate(tree->r_child);
				leftRotate(tree);
			}
			else if (bf == -2)	// Debalancement vers la gauche.
			{
				int balance_l_child = depth(tree->l_child->r_child) - depth(tree->l_child->l_child);
				if (balance_l_child == 1)		// Cas de rotation gauche-droite.
					leftRotate(tree->l_child);
				rightRotate(tree);
			}
			balanceTree(tree->parent);
		}
		
		void leftRotate(Node<T> *tree)
		{
			if (tree == NULL)
				return;
			Node<T> * r_child = tree->r_child; // On attache le parent de tree au fils droit de tree.
			if (tree->parent != NULL)
			{
				if (tree->parent->r_child == tree)
					tree->parent->r_child = r_child;
				else
					tree->parent->l_child = r_child;
			}
			r_child->parent = tree->parent; // On lie tree et le sous tree gauche du fils droit.
			if (r_child->l_child != NULL)
				r_child->l_child->parent = tree;
			tree->r_child = r_child->l_child; // On place le fils droit comme sommet de tree.
			tree->parent = r_child;
			r_child->l_child = tree;
			if (tree == root)
				root = r_child;
		}

		void rightRotate(Node<T> *tree)
		{
			if (tree == NULL) // Si l'arbre est vide, on ne fait rien.
				return;
			Node<T> * l_child = tree->l_child; // On attache le parent de tree au fils gauche de tree.
			if (tree->parent != NULL)
			{
				if (tree->parent->l_child == tree)
					tree->parent->l_child = l_child;
				else
					tree->parent->r_child = l_child;
			}
			l_child->parent = tree->parent; // On lie tree et le sous tree droit du fils gauche.
			if (l_child->r_child != NULL)
				l_child->r_child->parent = tree;
			tree->l_child = l_child->r_child; // On place le fils droit comme sommet de tree.
			tree->parent = l_child;
			l_child->r_child = tree;
			if (tree == root)
				root = l_child;
		}

		
		// Retourne l'adresse du parent d'un v que l'on ajoutera.
		// Retourne l'adresse du parent HYPOTHETIQUE d'un v A AJOUTER
		// (non present dans l'arbre). Si l'arbre est vide, on retourne NULL.

 public :
	// CONSTRUCTEUR
	AVLTree() : root(NULL), nodeNb(0) {}

	// DESTRUCTEUR
	~AVLTree() {}

	// METHODES DE MODIFICATION
	// Permettent d'ajouter et de retirer un v dans l'arbre.
	bool	isEmpty() { return (root == NULL ? true : false); }
//	size_type size() const;

	Node<T>		*getRoot() { return (root); }

	int add(const T);
	int remove(const T &);
	void clear()
	{
		if (nodeNb > 0)
		{
			eraseFrom(root->l_child);
			eraseFrom(root->r_child);
			delete root;
			nodeNb = 0;
		}
	}


	// DEBUG
	void	print(Node<T> * r, int space)
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





//-----------------------------------------------------------------------
// 					METHODES PUBLIQUES DE AVLTree
//-----------------------------------------------------------------------
template <class T>
int AVLTree<T>::add(const T v)
{
// Si la valeur est deja la, on ne l'ajoute pas une seconde fois.
	if (findValue(v))
		return 0;

	// On trouve le parent, on cree le noeud et on verifie la memoire.
	Node<T> * parent = findParent(v);
	Node<T> * nouveau = new Node<T>(v, parent);
	if (nouveau == NULL)
		return 0;

	// On attache le parent et le fils.
	if (parent == NULL)
		root = nouveau;
	else if (v < parent->value)
		parent->l_child = nouveau;
	else
		parent->r_child = nouveau;
	++nodeNb;

	// On garde l'arbre equilibre en balacant a partir du nouveau.
	balanceTree(findValue(v));
	return 1;
}


template <class T>
int AVLTree<T>::remove(const T & v)
{
	// On conserve l'adresse du parent.
	Node<T> * parent = findValue(v);
	parent = parent->parent;

	// On retire l'v.
// On trouve l'v.
	Node<T> * noeud = findValue(v);
	if (noeud == NULL)
		return 0;

	// On trouve le plus grand des plus petits.
	Node<T> * remplacant = maximum(noeud->l_child);

	// S'il n'y a pas de remplacant, on escamote le noeud.
	if (remplacant == NULL)
	{
		if (noeud == root)
			root = noeud->r_child;
		else if (noeud->parent->l_child == noeud)
			noeud->parent->l_child = noeud->r_child;
		else
			noeud->parent->r_child = noeud->r_child;
		if (noeud->r_child != NULL)
			noeud->r_child->parent = noeud->parent;
	}
	else	// J'ai un maximum des minima.
	{
		noeud->value = remplacant->value;
		if (remplacant->parent->l_child == remplacant)
			remplacant->parent->l_child = remplacant->l_child;
		else
			remplacant->parent->r_child = remplacant->l_child;
		if (remplacant->l_child != NULL)
			remplacant->l_child->parent = remplacant->parent;
		noeud = remplacant;
	}
	delete noeud;
	--nodeNb;

	// On rebalance l'arbre a partir du parent.
	balanceTree(parent);
	return 1;
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//						FIN DE LA CLASSE AVLTree
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------


#endif

