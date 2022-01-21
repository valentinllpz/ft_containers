/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:16:39 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/21 17:07:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "common.hpp"

namespace ft
{
	template< typename T, typename Alloc = std::allocator<T> >
	class	vector
	{
		public:

			/* ************************************************************************** */
			/*                     			   ALIASES                                    */
			/* ************************************************************************** */

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;


			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			// 1. empty container constructor (default constructor): Constructs an empty container, with no elements.
			explicit vector (const allocator_type& alloc = allocator_type()); 
			// 2. fill constructor: Constructs a container with n elements. Each element is a copy of val.
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()); 
			// 3. range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			// 4. copy constructor: Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x);

		private:
			value_type				*_data;
			allocator_type			_alloc;
			size_type				_size;
			size_type				_capacity;
			const static size_type	_max_size;
	};

	
};

#endif
