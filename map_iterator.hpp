/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:42:12 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/07 23:39:49 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "common.hpp"

// https://www.cplusplus.com/reference/iterator/BidirectionalIterator/

namespace ft
{
	template < typename T >
	class map_iterator
	{
		public:

		/* ************************************************************************** */
		/*                     		    MEMBER TYPES                                  */
		/* ************************************************************************** */

			typedef T 									value_type;
			typedef value_type *						pointer;
			typedef value_type & 						reference;
			typedef	ft::Node<T> *						node_pointer;
			typedef std::bidirectional_iterator_tag		iterator_category;

		protected:

		/* ************************************************************************** */
		/*                     			  VARIABLE                                    */
		/* ************************************************************************** */
		
			node_pointer								_node;

		public:

		/* ************************************************************************** */
		/*                     			CONSTRUCTORS                                  */
		/* ************************************************************************** */

			map_iterator() : _node(NULL) {}
			map_iterator(node_pointer node) : _node(node) {}
			map_iterator(const map_iterator & src) : _node(src._node) {}
			~map_iterator() {}

		/* ************************************************************************** */
		/*                     		  BASE PTR GETTER                                 */
		/* ************************************************************************** */

			node_pointer base() const { return (_node); }

		/* ************************************************************************** */
		/*                     		OPERATORS OVERLOADS                               */
		/* ************************************************************************** */
		
		// Implicit conversion to const: (https://en.cppreference.com/w/cpp/language/cast_operator)
		
			operator map_iterator<value_type const>() const { return map_iterator<value_type const>(_node); }

		// Dereferencement operators:

			reference	operator*() const { return (_node->value); }
			pointer 	operator->() const { return &(_node->value); }	

		// Increment / decrement operators:

			map_iterator & operator++() // Prefix increment
			{
				if (_node->r_child)
				{
					_node = _node->r_child; // we know that _node->r_child->value > _node->value
					while (_node->l_child)
						_node = _node->l_child; // finding the smallest value bigger than _node->value
				}
				else
				{
					while (_node->parent && _node->parent->l_child != _node) // while our current node is not the left child of its parent (= while it's not smaller than its parent)
						_node = _node->parent;
					if (_node->parent) // if we are not in the case _root->_parent
						_node = _node->parent;
				}
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}

			map_iterator operator++(int) // Postfix increment
			{
				map_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp); // value before incrementation is returned
			}

			map_iterator & operator--() // Prefix decrement
			{
				if (_node->l_child)
				{
					_node = _node->l_child; // we know that _node->l_child->value < _node->value
					while (_node->r_child)
						_node = _node->r_child; // finding the biggest value smaller than _node->value
				}
				else
				{
					while (_node->parent && _node->parent->r_child != _node) // while our current node is not the right child of its parent (= while it's not bigger than its parent)
						_node = _node->parent;
					if (_node->parent) // if we are not in the case _root->_parent
						_node = _node->parent;
				}
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}

			map_iterator operator--(int) // Postfix decrement
			{
				map_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp); // value before decrementation is returned
			}

			map_iterator & operator=(const map_iterator& src)
			{
				_node = src._node;
				return (*this);
			}

		// Comparison operators:

			bool	operator==(const map_iterator& lhs) { return (_node == lhs.base()); };
			bool	operator!=(const map_iterator& lhs) { return (_node != lhs.base()); };

	};
}

#endif
