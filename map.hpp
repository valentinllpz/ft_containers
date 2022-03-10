/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:06:34 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/10 23:00:50 by vlugand-         ###   ########.fr       */
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

			typedef	Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef ft::Node<value_type>						node_type;
      		typedef ft::Node<value_type>*						node_pointer;
			typedef Compare										key_compare;
			
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
			
			typedef Alloc															allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other		node_allocator;
			// we need to use alloc for both our pair and the node, see doc: https://alp.developpez.com/tutoriels/templaterebinding/

			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;

			typedef ft::map_iterator<value_type, node_pointer>				iterator;
			typedef ft::map_iterator<const value_type, node_pointer>		const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
      		typedef ft::reverse_iterator<const_iterator>  					const_reverse_iterator;

			typedef std::ptrdiff_t											difference_type; 	//iterator_traits<iterator>::difference_type
			typedef size_t													size_type;

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			// Empty container constructor (default constructor): Constructs an empty container, with no elements ( = a map of size 0)
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _comp(comp), _size(0), _max_size(alloc.max_size())
			{
				_end = _alloc.allocate(1);
				_alloc.construct(_end, node_type());
			}
			
			// Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _alloc(alloc), _comp(comp), _size(0), _max_size(alloc.max_size())
			{
				insert(first, last);
			}

			// Copy constructor: Constructs a container with a copy of each of the elements in x.
			map(const map & x) : _root(x._root), _end(x._end), _alloc(x._alloc), _comp(x._comp), _size(x._size), _max_size(x._max_size) {}

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
					return iterator(_root);
				return iterator(minimum(_root));				
			}

			const_iterator		begin() const
			{
				if (_size == 0)
					return const_iterator(_root);
				return const_iterator(minimum(_root));
			}

			iterator			end() { return iterator(_end); }

			const_iterator		end() const	{ return const_iterator(_end); }
		
			reverse_iterator 		rbegin() { return reverse_iterator(end()--); }

			const_reverse_iterator 	rbegin() const { return const_reverse_iterator(end()--); }

			reverse_iterator 		rend() { return reverse_iterator(begin()); }
			
			const_reverse_iterator 	rend() const { return const_reverse_iterator(begin()); }


			/* ************************************************************************** */
			/*                     			   CAPACITY                                   */
			/* ************************************************************************** */

			bool			empty() const { return (_size == 0 ? true : false); }

			size_type		size() const { return (_size); }
			
			size_type		max_size() const { return (_max_size); }

			/* ************************************************************************** */
			/*                     		    ELEMENT ACCESS                                */
			/* ************************************************************************** */

			mapped_type& operator[](const key_type& k)
			{
				node_pointer	n = findKey(k);

				if (n)
					return (n->value.second);
				ft::pair<iterator,bool> ret = insert(ft::make_pair(k, mapped_type()));
				return ((*ret.first).second);
			}

			/* ************************************************************************** */
			/*                     		       MODIFIERS                                  */
			/* ************************************************************************** */

			pair<iterator, bool>	insert(const value_type& val)
			{
				bool added = add(val);
				ft::pair<iterator, bool> ret = ft::make_pair(iterator(findValue(val)), added);
				return (ret);
			}

			iterator	insert(iterator position, const value_type& val)
			{
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

			void		erase(iterator position) { remove(*position); }

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
				// _size = 0; ?
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

			// DEBUG
			// void		print(node_pointer r, int space)
			// {
			// 	if (r == NULL)
			// 		return ;
			// 	space += 5; 
			// 	print(r->r_child, space);
			// 	std::cout << std::endl;
			// 	for (int i = 5; i < space; i++)
			// 		std::cout << " ";
			// 	std::cout << r->value << "\n"; 
			// 	print(r->l_child, space); 
			// }

		private :

			node_pointer						_root;
			node_pointer						_end;	// _root's parent node
			node_allocator						_alloc;
			key_compare							_comp;
			size_type							_size;
			size_type							_max_size;

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

			node_pointer	findValue(const value_type & v) const
			{
				node_pointer	n = _root;

				while (n && n->value != v)
				{
					if (value_comp()(v, n->value))
						n = n->l_child;
					else
						n = n->r_child;
				}
				return (n);
			}

			void	updateEnd()
			{
				_end->l_child = _root;
				_end->r_child = _root;
				_root->parent = _end;
			}

			bool	add(const value_type & v)	// returns 1 if value was added, 0 if exists already
			{
				if (findValue(v)) // If value already exists we cannot add it
					return (0); 
				node_pointer parent = _root;
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
				balance(findValue(v));
				++_size;
				return (1);
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
					if (n == _root)									// if n is _root, its right subtree will replace it
						_root = n->r_child;
					else if (n->parent->l_child == n)				// if next smallest value bigger than n->value is n->parent 
						n->parent->l_child = n->r_child;			// we know there is no left subtree so we can replace n->parent->l_child (= n) by n->r_child subtree
					else
						n->parent->r_child = n->r_child;			// if next smallest value bigger than n->value is n->r_child, let's replace n by its right subtree 
					if (n->r_child != NULL)
						n->r_child->parent = n->parent;				// now setting r_child->parent pointer 
				}
				else												// if we found the subtitute ( = left subtree exists)
				{
					node_pointer tmp = new_node(substitute->value, n->parent);
					tmp->l_child = n->l_child;
					tmp->r_child = n->r_child;
					_alloc.destroy(n);
					_alloc.deallocate(n, 1);
					// n->value = substitute->value;								// we replace n->value by the new value
					if (substitute->parent->l_child == substitute)				// if n->l_child has no right subtree
						substitute->parent->l_child = substitute->l_child;
					else
						substitute->parent->r_child = substitute->l_child;
					if (substitute->l_child != NULL)
						substitute->l_child->parent = substitute->parent; 		// now setting l_child->parent pointer 
					n = substitute;
				}
				_alloc.destroy(n);
				_alloc.deallocate(n, 1);
				balance(parent);
				--_size;
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
						_root = NULL;
				}
			}

			// AVL tree balancing related function (see https://cours.etsmtl.ca/SEG/FHenri/inf145/Suppl%C3%A9ments/arbres%20AVL.htm)

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
				updateEnd();
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
