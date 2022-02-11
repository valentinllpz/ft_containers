/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reverse_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:10:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/11 13:16:42 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

#include "utils.hpp"
#include "vector_iterator.hpp"

// http://www.cplusplus.com/reference/iterator/reverse_iterator/

namespace ft
{
	template <typename Iterator>
	class vector_reverse_iterator
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

			pointer		_ptr;
			// we want the pointer to be "protected" because we want to allow children classes to access it
			// _ptr is also accessible between different instances of the same class

		public:
		
		/* ************************************************************************** */
		/*                     			CONSTRUCTORS                                  */
		/* ************************************************************************** */

			vector_reverse_iterator() : _ptr() {}
			explicit vector_reverse_iterator(pointer ptr) : _ptr(ptr) {}
			template <class Iter>
			vector_reverse_iterator(const vector_reverse_iterator<Iter>& src) : _ptr(src._ptr) {}
			~vector_reverse_iterator() {}

			iterator_type base() const { return _ptr; }

		/* ************************************************************************** */
		/*                     		OPERATORS OVERLOADS                               */
		/* ************************************************************************** */

		// Dereferencement operators:

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }	
			value_type operator[](size_t i) { return *(_ptr + i); }

		// Increment / decrement operators:

			vector_reverse_iterator & operator++() // Prefix increment
			{ 
				_ptr--;
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}
	
			vector_reverse_iterator operator++(int) // Postfix increment
			{
				vector_reverse_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp); // value before incrementation is returned
			}
			
			vector_reverse_iterator & operator--() // Prefix decrement
			{ 
				_ptr++;
				return (*this); // decremented value is returned (hence the use of reference in prototype)
			}
			
			vector_reverse_iterator operator--(int) // Postfix decrement
			{
				vector_reverse_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp); // value before decrementation is returned
			}

		// Comparison operators:

			// bool operator==(const vector_reverse_iterator & rhs) const { return (_ptr == rhs._ptr); }
			// bool operator!=(const vector_reverse_iterator & rhs) const { return (_ptr != rhs._ptr); }
			// bool operator<=(const vector_reverse_iterator & rhs) const { return (_ptr >= rhs._ptr); }
			// bool operator>=(const vector_reverse_iterator & rhs) const { return (_ptr <= rhs._ptr); }
			// bool operator<(const vector_reverse_iterator & rhs) const { return (_ptr > rhs._ptr); }
			// bool operator>(const vector_reverse_iterator & rhs) const { return (_ptr < rhs._ptr); }

		// Arithmetics operators:  (a and b are objects of this iterator type, n is a value of its difference type)
			vector_reverse_iterator<iterator_type> operator+(difference_type n) const { return (_ptr - n); } // [a + n]
			vector_reverse_iterator<iterator_type> operator-(difference_type n) const { return (_ptr + n); } // [a - n]
			difference_type operator-(const vector_reverse_iterator & rhs) const { return (_ptr + rhs._ptr); } // [a - b]

			/* when (=) is involved we need to return a pointer to the current modified instance (allows chaining a = b = c) */
			vector_reverse_iterator & operator=(vector_reverse_iterator const & rhs) // [a = b]
			{
				_ptr = rhs._ptr;
				return (*this);
			}

			vector_reverse_iterator<iterator_type> & operator+=(difference_type n) // [a += n]
			{ 
				// If n == 0, this is a null operation
				if (n < 0) // If n < 0, equivalent to executing --i n times. 
				{
					while (n < 0)
					{
						operator--();
						n++;
					}
				}
				else // If n > 0, equivalent to executing ++i n times.
				{
					while (n > 0)
					{
						operator++();
						n--;
					}
				}
				return (*this);
			}
			
			vector_reverse_iterator<iterator_type> & operator-=(difference_type n) // [a -= n]
			{
				_ptr += (-n);
				return (*this);
			}

		// Redirection operator

			/* here again we need the "friend" keyword because our class instance comes on the right hand side of the (<<) operator */
			friend std::ostream & operator<<(std::ostream & o, vector_reverse_iterator<iterator_type> & rhs)
			{
				o << *rhs._ptr;
				return (o);
			}
	};

	/* ************************************************************************** */
	/*                     		  NON MEMBER OVERLOADS                            */
	/* ************************************************************************** */

	template <typename T>
	vector_reverse_iterator<T> & operator+(typename vector_reverse_iterator<T>::difference_type n, const vector_reverse_iterator<T>& it) { return it + n; }
	template <typename T>
	vector_reverse_iterator<T> & operator-(typename vector_reverse_iterator<T>::difference_type n, const vector_reverse_iterator<T>& it) { return it - n; }

	template< class Iter1, class Iter2 >
	bool operator==( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() == rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator!=( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() != rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator<( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() > rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator<=( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() >= rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator>( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() < rhs.base()); }
	template< class Iter1, class Iter2 >
	bool operator>=( const ft::vector_reverse_iterator<Iter1>& lhs, const ft::vector_reverse_iterator<Iter2>& rhs ){ return (lhs.base() <= rhs.base()); }
}

#endif
