/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:06:34 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/29 23:25:33 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "common.hpp"

// https://cplusplus.com/reference/map/map/

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

			Node() : parent(NULL), l_child(NULL), r_child(NULL) {}
			Node(const T & v, Node<T> *n) : value(v), parent(n), l_child(NULL), r_child(NULL) {}
			~Node() {}
	};

	template < class Key,                                  		// map::key_type
			class T,                                       		// map::mapped_type
			class Compare = std::less<Key>,               		// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		public :

			/* ************************************************************************** */
			/*                     		    MEMBER TYPES                                  */
			/* ************************************************************************** */

			typedef	Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
		
		private :

			typedef ft::Node<value_type>											node_type;
      		typedef ft::Node<value_type>*											node_pointer;

		public :

			class	value_compare //: public std::binary_function<value_type, value_type, bool >
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
			
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

		private :

			typedef typename allocator_type::template rebind<node_type>::other		node_allocator;
			// we need to use alloc for both our pair and the node, see doc: https://alp.developpez.com/tutoriels/templaterebinding/

		public :

			typedef ft::map_iterator<value_type, node_pointer>				iterator;
			typedef ft::map_iterator<const value_type, node_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
      		typedef ft::reverse_iterator<const_iterator>  					const_reverse_iterator;

			typedef std::ptrdiff_t											difference_type; 	//iterator_traits<iterator>::difference_type
			typedef size_t													size_type;


		private :

			/* ************************************************************************** */
			/*                     			 VARIABLES                                    */
			/* ************************************************************************** */

			node_pointer						_root;
			node_pointer						_end;	// _root's parent node
			node_allocator						_alloc;
			key_compare							_comp;
			size_type							_size;

		public:

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _comp(comp), _size(0)
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node_type());
			}
			
			template <class InputIterator>
			map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _comp(comp), _size(0)
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node_type());
				insert(first, last);
			}

			map(const map & x) : _root(NULL), _alloc(x._alloc), _comp(x._comp), _size(0)
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node_type());
				insert(x.begin(), x.end());			
			}

			~map() { clear(); }

			map& operator= (const map& x)
			{
				if (this != &x)
				{
					clear();
					_end = _alloc.allocate(1);
					_alloc.construct(_end, node_type());
					insert(x.begin(), x.end());
				}
				return (*this);
			}

			/* ************************************************************************** */
			/*                     			  ITERATORS                                   */
			/* ************************************************************************** */

			iterator			begin()
			{
				if (_size == 0)
					return iterator(_end);
				return iterator(minimum(_root));				
			}

			const_iterator		begin() const
			{
				if (_size == 0)
					return const_iterator(_end);
				return const_iterator(minimum(_root));
			}

			iterator			end() { return iterator(_end); }

			const_iterator		end() const	{ return const_iterator(_end); }
		
			reverse_iterator 		rbegin()
			{
				if (_size == 0)
					return reverse_iterator(_end);
				return reverse_iterator(end()--);
			}

			const_reverse_iterator 	rbegin() const
			{
				if (_size == 0)
					return const_reverse_iterator(_end);
				return const_reverse_iterator(end()--);
			}

			reverse_iterator 		rend() { return reverse_iterator(begin()); }
			
			const_reverse_iterator 	rend() const { return const_reverse_iterator(begin()); }


			/* ************************************************************************** */
			/*                     			   CAPACITY                                   */
			/* ************************************************************************** */

			bool			empty() const { return (_size == 0 ? true : false); }

			size_type		size() const { return (_size); }
			
			size_type		max_size() const { return _alloc.max_size(); }

			/* ************************************************************************** */
			/*                     		    ELEMENT ACCESS                                */
			/* ************************************************************************** */

			mapped_type& operator[](const key_type& k)
			{
				node_pointer	n = findKey(k);

				if (n)
					return (n->value.second);
				ft::pair<iterator,bool> ret = insert(value_type(k, mapped_type()));
				return ((*ret.first).second);
			}

			/* ************************************************************************** */
			/*                     		       MODIFIERS                                  */
			/* ************************************************************************** */

			ft::pair<iterator, bool>	insert(const value_type& val)
			{
				bool added = addFrom(_root, val);
				ft::pair<iterator, bool> ret = ft::make_pair(iterator(findValue(val)), added);
				return (ret);
			}

			iterator	insert(iterator position, const value_type& val)
			{
				if (position != end())
				{
					iterator next = position;
					++next;
					if (value_comp()(*position, val) && (next == end() || value_comp()(val, *next)))
					{
						addFrom(position.base(), val);
						return (--next);
					}
				}
				(void)position;
				return (insert(val).first);
			}

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}

			void		erase(iterator position)
			{
				remove(*position);
			}

			size_type	erase(const key_type & k)
			{
				node_pointer	n = findKey(k);

				if (n)
					return (remove(n->value));
				return (0);
			}

			void 		erase(iterator first, iterator last)
			{
				iterator tmp;
				
				while (first != last)
				{
					tmp = first;
					++tmp;
					remove(*first);
					first = tmp;
				}
			}

			void		swap(map & x)
			{
				node_pointer	tmp_root = _root;
				node_pointer	tmp_end = _end;
				node_allocator	tmp_alloc = _alloc;
				key_compare		tmp_comp = _comp;
				size_type		tmp_size = _size;	
				
				_root = x._root;
				_end = x._end;
				_alloc = x._alloc;
				_comp = x._comp;
				_size = x._size;
				x._root = tmp_root;
				x._end = tmp_end;
				x._alloc = tmp_alloc;
				x._comp = tmp_comp;
				x._size = tmp_size;
			}

			void		clear()
			{
				eraseFrom(_root);
			}

			/* ************************************************************************** */
			/*                     		       OBSERVERS                                  */
			/* ************************************************************************** */

			key_compare key_comp() const { return (key_compare()); }

			value_compare value_comp() const { return (value_compare(key_compare())); }

			/* ************************************************************************** */
			/*                     		      OPERATIONS                                  */
			/* ************************************************************************** */

			iterator	find(const key_type& k)
			{
				node_pointer	n = findKey(k);

				if (n)
					return iterator(n);
				return end();
			}

			const_iterator	find(const key_type& k) const
			{
				node_pointer	n = findKey(k);

				if (n)
					return const_iterator(n);
				return end();
			}

			size_type	count(const key_type& k) const
			{
				const_iterator	it = find(k);
	
				if (it != end())
					return (1);
				return (0);
			}

			iterator	lower_bound(const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); it++)
				{
					if (key_comp()(it->first, k) == false)
						break ;
				}
				return (it);
			}

			const_iterator		lower_bound(const key_type& k) const
			{
				const_iterator it = begin();
				
				for (; it != end(); it++)
				{
					if (key_comp()(it->first, k) == false)
						break ;
				}
				return (it);
			}

			iterator	upper_bound(const key_type& k)
			{
				iterator it = begin();

				for (; it != end(); it++)
				{
					if (key_comp()(k, it->first) == true)
						break ;
				}
				return (it);
			}

			const_iterator	upper_bound(const key_type& k) const
			{
				const_iterator it = begin();

				for (; it != end(); it++)
				{
					if (key_comp()(k, it->first) == true)
						break ;
				}
				return (it);
			}

			ft::pair<iterator,iterator>		equal_range(const key_type& k) { return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			ft::pair<const_iterator,const_iterator>		equal_range(const key_type& k) const { return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			allocator_type		get_allocator() const { return (allocator_type()); }

			// DEBUG -----------------------------------
			// void		printTree()	{ printFrom(_root, 5); }
			
			// void		printFrom(node_pointer r, int space)
			// {
			// 	if (r == NULL)
			// 		return ;
			// 	space += 5; 
			// 	printFrom(r->r_child, space);
			// 	std::cout << std::endl;
			// 	for (int i = 5; i < space; i++)
			// 		std::cout << " ";
			// 	std::cout << r->value.first << "\n"; 
			// 	printFrom(r->l_child, space); 
			// }
			// -----------------------------------------

		private :

			/* ************************************************************************** */
			/*                   UNDERLAYING AVL TREE INTERNAL FUNCTIONS                  */
			/* ************************************************************************** */

			node_pointer	new_node(const value_type& v, node_pointer parent)
			{
				node_pointer n = _alloc.allocate(1);
				_alloc.construct(n, node_type(v, parent));
				return (n);
			}

			node_pointer	minimum(node_pointer n) const
			{
				if (n && n->l_child)
					return (minimum(n->l_child));
				return (n);
			}

			node_pointer	maximum(node_pointer n) const
			{
				if (n && n->r_child)
					return (maximum(n->r_child));
				return (n);
			}

			node_pointer	findKey(const key_type & k) const
			{
				node_pointer	n = _root;

				while (n && n->value.first != k)
				{
					if (key_compare()(k, n->value.first))
						n = n->l_child;
					else
						n = n->r_child;
				}
				return (n);
			}

			node_pointer	findValue(const value_type & v) const { return (findKey(v.first)); }

			void	updateEnd()
			{
				if (!_end)
				{
					_end = _alloc.allocate(1);
					_alloc.construct(_end, node_type());
				}
				if (_root)
				{
					_end->l_child = _root;
					_end->r_child = _root;
					_root->parent = _end;
				}
			}

			bool	addFrom(node_pointer parent, const value_type & v)	// returns 1 if value was added, 0 if exists already
			{
				if (parent != _root && findValue(v)) // If value already exists we cannot add it
					return (0); 
				if (parent)
				{
					while (1) // Finding which node will become parent of new value v
					{
						if (value_comp()(v, parent->value) && parent->l_child)
							parent = parent->l_child;
						else if (value_comp()(parent->value, v) && parent->r_child)
							parent = parent->r_child;
						else
							break ;
					}
				}
				node_pointer n = new_node(v, parent);
				
				if (parent == NULL)			// Now linking new node to parent 
					_root = n;
				else if (value_comp()(v, parent->value))
					parent->l_child = n;
				else
					parent->r_child = n;
				++_size;
				balance(n);
				updateEnd();
				return (1);
			}

			void	replaceValue(node_pointer n, const value_type & v) // since key is const the only way to replace a node's value is to replace the whole node + connections
			{
				node_pointer nbis = new_node(v, n->parent);

				nbis->l_child = n->l_child;
				nbis->r_child = n->r_child;
				if (n->parent->l_child == n)
					n->parent->l_child = nbis;
				if (n->parent->r_child == n)
					n->parent->r_child = nbis;
				if (n->l_child)
					n->l_child->parent = nbis;
				if (n->r_child)
					n->r_child->parent = nbis;
				if (n == _root)
					_root = nbis;
				_alloc.destroy(n);
				_alloc.deallocate(n, 1);
			}

			bool	remove(const value_type & v)
			{

				node_pointer n = findValue(v);
				if (n == NULL)
					return (0);
				node_pointer parent = n->parent;					// Backing up parent address
				node_pointer substitute = maximum(n->l_child);		// checking left subtree for next smallest value bigger than n->value
				if (substitute == NULL) 							// if we didn't find the substitute ( = no left subtree)
				{
					if (n == _root)
					{												// if n is _root, its right subtree will replace it
						_root = n->r_child;
						updateEnd();
					}
					else if (n->parent->l_child == n)				// if next smallest value bigger than n->value is n->parent 
						n->parent->l_child = n->r_child;			// we know there is no left subtree so we can replace n->parent->l_child (= n) by n->r_child subtree
					else
						n->parent->r_child = n->r_child;			// if next smallest value bigger than n->value is n->r_child, let's replace n by its right subtree 
					if (n->r_child != NULL)
						n->r_child->parent = n->parent;				// now setting r_child->parent pointer 
					_alloc.destroy(n);
					_alloc.deallocate(n, 1);
				}
				else												// if we found the subtitute ( = left subtree exists)
				{
					replaceValue(n, substitute->value); // we replace n->value by the new value
					if (substitute->parent->l_child == substitute)				// if n->l_child has no right subtree
						substitute->parent->l_child = substitute->l_child;
					else
						substitute->parent->r_child = substitute->l_child;
					if (substitute->l_child != NULL)
						substitute->l_child->parent = substitute->parent; 		// now setting l_child->parent pointer 
					_alloc.destroy(substitute);
					_alloc.deallocate(substitute, 1);
				}
				--_size;
				if (_size == 0)
				{
					_alloc.destroy(_end);
					_alloc.deallocate(_end, 1);
					_end = NULL;
					_root = NULL;
					parent = NULL;
				}
				balance(parent);
				updateEnd();
				return (1);
			}

			void	eraseFrom(node_pointer node)
			{
				if (node)
				{
					eraseFrom(node->l_child);
					eraseFrom(node->r_child);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					--_size;
					if (node == _root)
					{
						_alloc.destroy(_end);
						_alloc.deallocate(_end, 1);
						_end = NULL;
						_root = NULL;
					}
				}
			}

			// AVL tree balancing related function (see https://cours.etsmtl.ca/SEG/FHenri/inf145/Suppl%C3%A9ments/arbres%20AVL.htm)
			// *** Note that using an AVL will reduce speed at both insertion and removal, but it will find elements quicker ***
			// *** Map is implemented using a Red Black Tree, which is way more efficient - if I had to redo the project I would go for this option instead ***

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
	};

	/* ************************************************************************** */
	/*                     		  NON-MEMBER OVERLOADS		                      */
	/* ************************************************************************** */

	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (0);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return !(lhs == rhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return !(rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return (rhs < lhs); }

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs) { return !(lhs < rhs); }

	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs) { lhs.swap(rhs); }
}

#endif
