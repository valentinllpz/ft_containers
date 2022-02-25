/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:06:34 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/24 20:01:52 by vlugand-         ###   ########.fr       */
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
			class Compare = less<Key>,                     // map::key_compare
			class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
			>
	class map
	{
		typedef	Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		
		class	value_compare//: public ft::binary_function<value_type, value_type, bool >
		{ 
			friend class map;

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
		}
		
		typedef Alloc									allocator_type;
		typedef allocator_type::reference				reference;
		typedef allocator_type::const_reference			const_reference;
		typedef allocator_type::pointer					pointer;
		typedef allocator_type::const_pointer			const_pointer;
							


	};
}

#endif
