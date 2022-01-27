/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:23:07 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/27 15:19:53 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator
	{
		public:
			typedef	T*					pointer;
			typedef std::ptrdiff_t		difference_type;
		
			random_access_iterator(void) : _ptr(NULL) {}
			random_access_iterator(pointer ptr) : _ptr(ptr) {}
			random_access_iterator(const random_access_iterator &src) : _ptr(src.ptr) {}
			~random_access_iterator(void) {}

			random_access_iterator<T> & operator=(random_access_iterator const & rhs)
			{
				_ptr = rhs._ptr;
				return (*this);
			}
			

		protected:
			pointer _ptr;
		
	};
}

#endif
