/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:06:34 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/02 18:41:08 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "common.hpp"

// https://cplusplus.com/reference/map/map/

namespace ft
{
	template < class Key,                                  // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                // map::key_compare
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
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
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
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(NULL), _comp(comp), _alloc(alloc), _size(0), _max_size(alloc.max_size()) {}

			// // Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			// template <class InputIterator>
			// map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(NULL), _alloc(alloc), _comp(comp)
			// {
			// 		insert(first, last);
					//  size ?
			// }

			// Copy constructor: Constructs a container with a copy of each of the elements in x.
			map(const map & x) : _tree(x.tree), _alloc(x.alloc), _comp(x.comp), _size(x.size), _max_size(x.max_size) {}

			~map() {}

		private :

			AVLTree<value_type>		_tree;
			allocator_type			_alloc;
			key_compare				_comp;
			size_type				_size;
			const size_type			_max_size;


	};
}

#endif
