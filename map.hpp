/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:06:34 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/03 22:39:47 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "common.hpp"

// https://cplusplus.com/reference/map/map/

namespace ft
{
	template < class Key,                                  		// map::key_type
			class T,                                       		// map::mapped_type
			class Compare = std::less<Key>,               		// map::key_compare
			class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		public :

			/* ************************************************************************** */
			/*                     		    MEMBER TYPES                                  */
			/* ************************************************************************** */

			typedef	Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef ft::Node<value_type>					node_type;
      		typedef ft::Node<value_type>*					node_pointer;
			typedef Compare									key_compare;
			
			class	value_compare //: public ft::binary_function<value_type, value_type, bool >
			{ 
				friend class	map;

				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};
			
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef ft::map_iterator<value_type>				iterator;
			// typedef ft::map_iterator<value_type const>		const_iterator;
			// typedef ft::reverse_iterator<iterator>        	reverse_iterator;
      		// typedef ft::reverse_iterator<const_iterator>  	const_reverse_iterator;

			typedef std::ptrdiff_t								difference_type; //iterator_traits<iterator>::difference_type
			typedef size_t										size_type;

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			// Empty container constructor (default constructor): Constructs an empty container, with no elements ( = a map of size 0)
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _comp(comp), _alloc(alloc), _size(0), _max_size(alloc.max_size()) {}

			// // Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			// template <class InputIterator>
			// map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _comp(comp)
			// {
			// 		insert(first, last);
					//  size ?
			// }

			// Copy constructor: Constructs a container with a copy of each of the elements in x.
			map(const map & x) : _root(x.root), _alloc(x.alloc), _comp(x.comp), _size(x.size), _max_size(x.max_size) {}

			~map() {}

			// map& operator= (const map& x)
			// {
			// 	clear_from_node(_root);
			// 	insert(x.begin(), x.end());
			// 	return *this;
			// }

			/* ************************************************************************** */
			/*                     			  ITERATORS                                   */
			/* ************************************************************************** */

			iterator			begin()
			{
				if (_size == 0)
					return (_root);
				return iterator(minimum(_root));				
			}

			const_iterator		begin() const
			{
				if (_size == 0)
					return (_root);
				return const_iterator(minimum(_root));
			}

			iterator			end()
			{
				if (_size == 0)
					return (_root);
				return iterator(maximum(_root));				
			}

			const_iterator		end() const
			{
				if (_size == 0)
					return (_root);
				return const_iterator(maximum(_root));
			}
		
			// reverse_iterator rbegin() {return reverse_iterator(end()--);}
			// const_reverse_iterator rbegin() const {return const_reverse_iterator(end()--);}
			// reverse_iterator rend() {return reverse_iterator(begin());}
			// const_reverse_iterator rend() const {return const_reverse_iterator(begin());}


			/* ************************************************************************** */
			/*                     			   CAPACITY                                   */
			/* ************************************************************************** */

			bool			empty() const { return (_size == 0 ? true : false); }
			size_type		size() const { return (_size); }
			size_type		max_size() const { return (_max_size); }

			/* ************************************************************************** */
			/*                     		    ELEMENT ACCESS                                */
			/* ************************************************************************** */

			// mapped_type& operator[] (const key_type& k)
			// {
			// 		???
			// }

		private :

			node_pointer						_root;
			allocator_type						_alloc;
			key_compare							_comp;
			size_type							_size;
			const size_type						_max_size;

			/* ************************************************************************** */
			/*                   UNDERLAYING AVL TREE INTERNAL FUNCTIONS                  */
			/* ************************************************************************** */

			node_pointer	new_node(const value_type& v, node_pointer parent)
			{
				node_pointer n = _alloc_type.allocate(1);
				_alloc.construct(n, node_type(v, parent));
				_size++;
				return (n);
			}

			node_pointer	minimum(node_pointer n) const
			{
				if (n->l_child)
					return (minimum(n->l_child));
				return (n);
			}

			node_pointer	maximum(node_pointer n) const
			{
				if (n->r_child)
					return (maximum(n->r_child));
				return (n);
			}

			node_pointer	findKey(const key_type & k)
			{
				node_pointer	n = _root;

				while (n && (key_compare(k, n->value.first) || key_compare(n->value.first, k))) // while n && k != n->value.first
				{
					if (key_compare(k, n->value.first))
						n = n->l_child;
					else
						n = n->r_child;
				}
				return (n);
			}

			node_pointer	findValue(const value_type & v)
			{
				node_pointer	n = _root;

				while (n && (value_compare(key_compare(v, n->value)) || value_compare(key_compare(n->value), v))) // while n && n != v
				{
					if (value_compare(key_compare(v, n->value)))
						n = n->l_child;
					else
						n = n->r_child;
				}
				return (n);
			}

			int		add(const T v)
			{
				if (findValue(v)) // If value already exists we cannot add it
					return (0); 
				node_pointer parent = _root;
				if (parent)
				{
					while (1) // We need first to find which node will become parent of new value v
					{
						if (v < parent->value && parent->l_child)
							parent = parent->l_child;
						else if (parent->value < v && parent->r_child)
							parent = parent->r_child;
						else
							break ;
					}
				}
				node_pointer n = new Node<T>(v, parent);

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
				node_pointer n = findValue(v);
				if (n == NULL)
					return (0);
				node_pointer parent = n->parent;					// Backing up parent address
				node_pointer substitute = maximum(n->l_child);		// finding smallest value bigger than n->value
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

			void	eraseFrom(node_pointer node)
			{
				if (node != NULL)
				{
					eraseFrom(node->l_child);
					eraseFrom(node->r_child);
					delete node; // et size--?
				}
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

			// AVL tree balancing related function

			void	balance(node_pointer tree)
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
				balance(tree->parent);
			}

			int		depth(node_pointer tree) const
			{
				if (tree == NULL)
					return (0);
				int	lh = depth(tree->l_child);
				int	rh = depth(tree->r_child);
				return (lh > rh ? lh + 1 : rh + 1);
			}
			
			void	leftRotate(node_pointer tree)
			{
				if (tree == NULL)
					return ;
				node_pointer  r_child = tree->r_child;		// Linking tree's parent to tree's right child
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

			void	rightRotate(node_pointer tree)
			{
				if (tree == NULL)
					return;
				node_pointer l_child = tree->l_child;		// Linking tree's parent to tree's left child
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

			// DEBUG
			void		print(node_pointer  r, int space)
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
