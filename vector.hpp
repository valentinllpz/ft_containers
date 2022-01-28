/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:16:39 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/28 17:19:47 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "common.hpp"
#include "vector_iterator.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:

			/* ************************************************************************** */
			/*                     			   ALIASES                                    */
			/* ************************************************************************** */

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::const_pointer		const_pointer;
			
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			typedef vector_iterator<value_type>              	iterator;

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			// Empty container constructor (default constructor): Constructs an empty container, with no elements ( = a vector of size 0)
			explicit vector (const allocator_type& alloc = allocator_type()) : _data(NULL), _size(0), _max_size(alloc.max_size()), _alloc(alloc), _capacity(0)
			{
				return ;
			}

			// Fill constructor: Constructs a container with n elements. Each element is a copy of val.
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _max_size(alloc.max_size()), _alloc(alloc), _capacity(n)
			{
				_data = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_data[i], val);
				return ;
			};

			// Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{
				size_t	i;

				for (InputIterator it = first; it != last; it++)
					i++;
				
				return ;
			}

			// Copy constructor: Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _max_size(x.max_size())
			{
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_data = _alloc.construct(&_data[i], x[i]);
				return ;
			};

			/* ************************************************************************** */
			/*                     			  ITERATORS                                   */
			/* ************************************************************************** */


			iterator begin() { return iterator(_data); }
			iterator end() { return iterator(_data + size); }


		private:
		
			/* ************************************************************************** */
			/*                     			  VARIABLES                                   */
			/* ************************************************************************** */

			value_type				*_data;
			allocator_type			_alloc;
			size_type				_size;
			size_type				_capacity;
			const static size_type	_max_size;
	};

	
};

#endif
