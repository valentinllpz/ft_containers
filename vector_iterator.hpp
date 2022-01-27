/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:45:04 by vlugand-          #+#    #+#             */
/*   Updated: 2022/01/27 18:47:41 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace ft
{
	template <typename T>
	class vector_iterator
	{
		public:
			typedef T         								value_type;
			typedef std::random_access_iterator_tag  		iterator_category;
			typedef std::ptrdiff_t 							difference_type;
			typedef value_type *							pointer;
			typedef value_type & 							reference;
	
		protected:
			pointer											_pointer;

		public:
			vector_iterator() : _ptr(NULL) {}
			vector_iterator(pointer ptr) : _ptr() {}
			vector_iterator(const vector_iterator src) : _ptr(src._ptr) {}

			reference operator*() const { return *_ptr; }
			pointer operator->() { return _ptr; }
			value_type operator[](size_t i) { return *(_ptr + i); } //use signed type instead?

			//Prefix increment
			vector_iterator & operator++()
			{ 
				_ptr++;
				return (*this);
			}
			//Postfix increment
			vector_iterator operator++(int)
			{
				vector_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp);
			}
			//Prefix decrement
			vector_iterator & operator--()
			{ 
				_ptr--;
				return (*this);
			}
			//Postfix decrement
			vector_iterator operator--(int)
			{
				vector_iterator tmp;

				tmp = *this;
				--(*this);
				return (tmp);
			}

			bool operator==(const vector_iterator& rhs) const { return _ptr == rhs._ptr; } //protected variable _ptr is accessible between instances of the same class
			bool operator!=(const vector_iterator& rhs) const { return _ptr != rhs._ptr; }
			bool operator<=(const vector_iterator& rhs) const { return _ptr <= rhs._ptr; }
			bool operator>=(const vector_iterator& rhs) const { return _ptr >= rhs._ptr; }
			bool operator==(const vector_iterator& rhs) const { return _ptr == rhs._ptr; }
			bool operator<(const vector_iterator& rhs) const { return _ptr < rhs._ptr; }
			bool operator>(const vector_iterator& rhs) const { return _ptr > rhs._ptr; }

			

	};

}

#endif
