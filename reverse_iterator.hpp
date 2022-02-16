/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:10:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/16 12:59:42 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "utils.hpp"
#include "vector_iterator.hpp"

// http://www.cplusplus.com/reference/iterator/reverse_iterator/
// https://en.cppreference.com/w/cpp/iterator/reverse_iterator

namespace ft
{
	template <typename Iterator>
	class reverse_iterator
	{
		public:

		/* ************************************************************************** */
		/*                     			   ALIASES                                    */
		/* ************************************************************************** */

			typedef Iterator														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;
			typedef typename iterator_traits<iterator_type>::reference           	reference;
			typedef typename iterator_traits<iterator_type>::pointer             	pointer;
			typedef typename iterator_traits<iterator_type>::difference_type     	difference_type;
			typedef typename iterator_traits<iterator_type>::value_type          	value_type;
		
		protected: 

		/* ************************************************************************** */
		/*                     			  VARIABLE                                    */
		/* ************************************************************************** */

			iterator_type		_ptr;
			// we want the pointer to be "protected" because we want to allow children classes to access it
			// _ptr is also accessible between different instances of the same class

		public:
		
		/* ************************************************************************** */
		/*                     			CONSTRUCTORS                                  */
		/* ************************************************************************** */

			reverse_iterator() : _ptr() {}
			reverse_iterator(iterator_type ptr) : _ptr(ptr) {}
			template <typename AnyIter>
			reverse_iterator(const reverse_iterator<AnyIter>& src) : _ptr(src.base()) {}
			~reverse_iterator() {}

		/* ************************************************************************** */
		/*                     		  BASE PTR GETTER                                 */
		/* ************************************************************************** */

			iterator_type		base() const { return _ptr; }

		/* ************************************************************************** */
		/*                     		OPERATORS OVERLOADS                               */
		/* ************************************************************************** */

			reverse_iterator & operator=(reverse_iterator const & rhs) { _ptr = rhs._ptr; return *this; }

		// Implicit conversion to const: (https://en.cppreference.com/w/cpp/language/cast_operator)

			operator reverse_iterator<vector_iterator<value_type> >() { return reverse_iterator<vector_iterator<value_type> >(_ptr); }
			operator reverse_iterator<vector_iterator<value_type const> >() const { return reverse_iterator<vector_iterator<value_type const> >(_ptr); }

		// Dereferencement operators:
			
			reference operator*() const
			{
				iterator_type tmp = _ptr;
				tmp--;
				return (*tmp); 
				// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it
				// Why ? https://devblogs.microsoft.com/oldnewthing/20211112-00/?p=105908
			}

			pointer operator->() const { return &(operator*()); }
			reference operator[](int index) { return *(_ptr - index - 1); }

		// Increment / decrement operators:

			reverse_iterator & operator++() // Prefix increment
			{ 
				_ptr--;
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}
	
			reverse_iterator operator++(int) // Postfix increment
			{
				reverse_iterator tmp;

				tmp = *this;
				--_ptr;
				return (tmp); // value before incrementation is returned
			}
			
			reverse_iterator & operator--() // Prefix decrement
			{ 
				_ptr++;
				return (*this); // decremented value is returned (hence the use of reference in prototype)
			}
			
			reverse_iterator operator--(int) // Postfix decrement
			{
				reverse_iterator tmp;

				tmp = *this;
				++_ptr;
				return (tmp); // value before decrementation is returned
			}

		// Arithmetics operators:  (a and b are objects of this iterator type, n is a value of its difference type)
			
			friend reverse_iterator<Iterator> operator+(difference_type n, const reverse_iterator& rhs) {return rhs._ptr - n;} //n + a
			reverse_iterator<Iterator> operator+(difference_type n) const {return _ptr - n;} //a + n
			reverse_iterator<Iterator> operator-(difference_type n) const {return _ptr + n;} //a - n
			difference_type operator-(const reverse_iterator& rhs) const {return rhs._ptr - _ptr;} //a - b
			reverse_iterator<Iterator> & operator+=(difference_type n) {_ptr -= n; return *this;}
			reverse_iterator<Iterator> & operator-=(difference_type n) {_ptr += n; return *this;}
		
		// Redirection operator

			/* here again we need the "friend" keyword because our class instance comes on the right hand side of the (<<) operator */
			friend std::ostream & operator<<(std::ostream & o, reverse_iterator<iterator_type> & rhs)
			{
				o << *rhs._ptr;
				return (o);
			}
	};

	/* ************************************************************************** */
	/*                     		  NON MEMBER OVERLOADS                            */
	/* ************************************************************************** */

	template <typename T>
	reverse_iterator<T> & operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& it) { return it + n; }
	template <typename T>
	reverse_iterator<T> & operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& it) { return it - n; }

	template< class Iter1, class Iter2 >
	bool operator==( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() == rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator!=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() != rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator<( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() > rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator<=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() >= rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator>( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() < rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator>=( const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs ){ return (lhs.base() <= rhs.base()); }

}

#endif
