/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reverse_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:10:27 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/10 15:57:24 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

// http://www.cplusplus.com/reference/iterator/reverse_iterator/

namespace ft
{
	template <typename iterator>
	class vector_reverse_iterator
	{
		public:

		/* ************************************************************************** */
		/*                     			   ALIASES                                    */
		/* ************************************************************************** */

			typedef iterator								iterator_type;
			typedef T         								value_type;
			typedef std::random_access_iterator_tag  		iterator_category;
			typedef std::ptrdiff_t 							difference_type;
			typedef value_type *							pointer;
			typedef value_type & 							reference;
		
		protected: 

		/* ************************************************************************** */
		/*                     			  VARIABLE                                    */
		/* ************************************************************************** */

			pointer											_ptr;
			// we want the pointer to be "protected" because we want to allow children classes to access it
			// _ptr is also accessible between different instances of the same class

		public:
		
		/* ************************************************************************** */
		/*                     			CONSTRUCTORS                                  */
		/* ************************************************************************** */

			vector_iterator() : _ptr() {}
			vector_iterator(pointer ptr) : _ptr(ptr) {}
			vector_iterator(const vector_iterator & src) : _ptr(src._ptr) {}
			~vector_iterator() {}

			iterator_type base() const { return _ptr; }

		/* ************************************************************************** */
		/*                     		OPERATORS OVERLOADS                               */
		/* ************************************************************************** */

		// Dereferencement operators:

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }	
			value_type operator[](size_t i) { return *(_ptr + i); }

		// Increment / decrement operators:

			vector_iterator & operator++() // Prefix increment
			{ 
				_ptr--;
				return (*this); // incremented value is returned (hence the use of reference in prototype)
			}
	
			vector_iterator operator++(int) // Postfix increment
			{
				vector_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp); // value before incrementation is returned
			}
			
			vector_iterator & operator--() // Prefix decrement
			{ 
				_ptr++;
				return (*this); // decremented value is returned (hence the use of reference in prototype)
			}
			
			vector_iterator operator--(int) // Postfix decrement
			{
				vector_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp); // value before decrementation is returned
			}

		// Comparison operators:
			bool operator==(const vector_iterator & rhs) const { return (_ptr == rhs._ptr); }
			bool operator!=(const vector_iterator & rhs) const { return (_ptr != rhs._ptr); }
			bool operator<=(const vector_iterator & rhs) const { return (_ptr >= rhs._ptr); }
			bool operator>=(const vector_iterator & rhs) const { return (_ptr <= rhs._ptr); }
			bool operator<(const vector_iterator & rhs) const { return (_ptr > rhs._ptr); }
			bool operator>(const vector_iterator & rhs) const { return (_ptr < rhs._ptr); }

		// Arithmetics operators:  (a and b are objects of this iterator type, n is a value of its difference type)

			/* here we need the "friend" keyword because the (+) operator comes from [n] which is not a member of this class) */
			friend vector_iterator<T> operator+(difference_type n, const vector_iterator & rhs) { return (n + rhs._ptr); } // [n + a]
			vector_iterator<T> operator+(difference_type n) const { return (_ptr + n); } // [a + n]
			vector_iterator<T> operator-(difference_type n) const { return (_ptr - n); } // [a - n]
			vector_iterator<T> operator-(const vector_iterator & rhs) const { return (_ptr - rhs._ptr); } // [a - b]

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

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() == rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() != rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() > rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() >= rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() < rhs.base()); }
	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ){ return (lhs.base() <= rhs.base()); }
}

#endif