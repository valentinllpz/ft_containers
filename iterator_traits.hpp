/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:58:05 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/26 14:55:13 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft 
{
	template <class Iter>
	struct iterator_traits
	{
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		public:
			typedef	std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag 	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t						difference_type;
			typedef T 									value_type;
			typedef const T* 							pointer;
			typedef const T& 							reference;
			typedef std::random_access_iterator_tag 	iterator_category;
	};
}

#endif
