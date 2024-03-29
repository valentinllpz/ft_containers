/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:45:04 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/10 16:45:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "common.hpp"

// https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
// https://www.boost.org/sgi/stl/RandomAccessIterator.html

namespace ft
{
	template < typename T >
	class vector_iterator
	{
		public:

		/* ************************************************************************** */
		/*                     		    MEMBER TYPES                                  */
		/* ************************************************************************** */
			
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef value_type *						pointer;
			typedef value_type &						reference;
			typedef std::random_access_iterator_tag		iterator_category;
		
		protected: 

		/* ************************************************************************** */
		/*                     			  VARIABLE                                    */
		/* ************************************************************************** */

			pointer											_ptr;

		public:
		
		/* ************************************************************************** */
		/*                     			CONSTRUCTORS                                  */
		/* ************************************************************************** */

			vector_iterator() : _ptr(NULL) {}

			vector_iterator(pointer ptr) : _ptr(ptr) {}

			vector_iterator(const vector_iterator & src) : _ptr(src._ptr) {}
			
			~vector_iterator() {}

		/* ************************************************************************** */
		/*                     		  BASE PTR GETTER                                 */
		/* ************************************************************************** */

			pointer base() const { return _ptr; }

		/* ************************************************************************** */
		/*                     		OPERATORS OVERLOADS                               */
		/* ************************************************************************** */

		// Implicit conversion to const: (https://en.cppreference.com/w/cpp/language/cast_operator)
			operator vector_iterator<value_type const>() const { return vector_iterator<value_type const>(_ptr); }

		// Dereferencement operators:

			reference operator*() const { return *_ptr; }

			pointer operator->() const { return _ptr; }

			reference operator[](size_t i) { return *(_ptr + i); }

		// Increment / decrement operators:

			vector_iterator & operator++() // Prefix increment
			{ 
				_ptr++;
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}
	
			vector_iterator operator++(int) // Postfix increment
			{
				vector_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp); // value before incrementation is returned
			}
			
			vector_iterator & operator--() // Prefix decrement
			{ 
				_ptr--;
				return (*this); // decremented value is returned (hence the use of reference in prototype)
			}
			
			vector_iterator operator--(int) // Postfix decrement
			{
				vector_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp); // value before decrementation is returned
			}

		// Comparison operators:

			// bool operator==(const vector_iterator & rhs) const { return (_ptr == rhs._ptr); }
			// bool operator!=(const vector_iterator & rhs) const { return (_ptr != rhs._ptr); }
			// bool operator<=(const vector_iterator & rhs) const { return (_ptr <= rhs._ptr); }
			// bool operator>=(const vector_iterator & rhs) const { return (_ptr >= rhs._ptr); }
			// bool operator<(const vector_iterator & rhs) const { return (_ptr < rhs._ptr); }
			// bool operator>(const vector_iterator & rhs) const { return (_ptr > rhs._ptr); }

		// Arithmetics operators:  (a and b are objects of this iterator type, n is a value of its difference type)

			/* here we need the "friend" keyword because the (+) operator comes from [n] which is not a member of this class) */
			friend vector_iterator<T> operator+(difference_type n, const vector_iterator & rhs) { return (n + rhs._ptr); } // [n + a]

			vector_iterator<T> operator+(difference_type n) const { return (_ptr + n); } // [a + n]

			vector_iterator<T> operator-(difference_type n) const { return (_ptr - n); } // [a - n]
			
			difference_type operator-(const vector_iterator & rhs) const { return (_ptr - rhs._ptr); } // [a - b]

			/* when (=) is involved we need to return a pointer to the current modified instance (allows chaining a = b = c) */
			vector_iterator & operator=(vector_iterator const & rhs) // [a = b]
			{
				_ptr = rhs._ptr;
				return (*this);
			}

			vector_iterator<T> & operator+=(difference_type n) // [a += n]
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
			
			vector_iterator<T> & operator-=(difference_type n) // [a -= n]
			{
				_ptr += (-n);
				return (*this);
			}

		// Redirection operator

			/* here again we need the "friend" keyword because our class instance comes on the right hand side of the (<<) operator */
			friend std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs)
			{
				o << *rhs._ptr;
				return (o);
			}
	};

	/* ************************************************************************** */
	/*                     	 NON-MEMBER FUNCTION OVERLOADS                        */
	/* ************************************************************************** */

	template<typename it1, typename it2>
	bool operator==(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() == b.base()); }

	template<typename it1, typename it2>
	bool operator!=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() != b.base()); }

	template<typename it1, typename it2>
	bool operator<(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() < b.base()); }

	template<typename it1, typename it2>
	bool operator<=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() <= b.base()); }

	template<typename it1, typename it2>
	bool operator>(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() > b.base()); }
	
	template<typename it1, typename it2>
	bool operator>=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) { return (a.base() >= b.base()); }

}

#endif
