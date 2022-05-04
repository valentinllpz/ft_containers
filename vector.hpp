/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:16:39 by vlugand-          #+#    #+#             */
/*   Updated: 2022/05/02 21:36:00 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "common.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:

			/* ************************************************************************** */
			/*                     		    MEMBER TYPES                                  */
			/* ************************************************************************** */

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			
			typedef ft::vector_iterator<value_type>      	   	 	iterator;
			typedef ft::vector_iterator<value_type const>			const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			typedef std::ptrdiff_t									difference_type;
			typedef size_t											size_type;

			

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _alloc(alloc), _size(0), _capacity(0), _max_size(alloc.max_size()) {}

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _max_size(alloc.max_size())
			{
				_array = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], val);
			};

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc),  _size(0), _capacity(0), _max_size(alloc.max_size())
			{
				size_type	i = 0;

				for (InputIterator it = first; it != last; it++)
					i++;
				_array = _alloc.allocate(i);
				_size = i;
				_capacity = i;
				i = 0;
				for (InputIterator it = first; it != last; it++)
				{
					_alloc.construct(&_array[i], *it);
					i++;
				}
			}

			vector(const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._size), _max_size(x.max_size())
			{
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x[i]);
			};

			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _capacity);
			}

			/* ************************************************************************** */
			/*                     		  OPERATOR OVERLOADS                              */
			/* ************************************************************************** */

			vector & operator=(const vector & x)
			{
				if (_size < x._size)
				{
					reserve(x._size);
					resize(x._size);
				}
				else
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(&_array[i]);
					_size = x._size;
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
				return (*this);
			};

			/* ************************************************************************** */
			/*                     			  ITERATORS                                   */
			/* ************************************************************************** */


			iterator					begin() { return iterator(_array); }

			const_iterator				begin() const {return const_iterator(_array); }

			iterator					end() { return iterator(_array + _size); }

			const_iterator				end() const { return const_iterator(_array + _size); }

			reverse_iterator 			rbegin() { return reverse_iterator(end()); }

			const_reverse_iterator 		rbegin() const { return const_reverse_iterator(end()); }

			reverse_iterator 			rend() { return reverse_iterator(begin()); }

			const_reverse_iterator 		rend() const { return const_reverse_iterator(begin()); }

			/* ************************************************************************** */
			/*                     			   CAPACITY                                   */
			/* ************************************************************************** */

			size_type	size() const { return (_size); }

			size_type	max_size() const { return (_max_size); }

			void		resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
					erase(begin() + n, end());
				else if (n > _size)
					insert(end(), n - _size, val);
			}

			size_type	capacity() const { return (_capacity); }

			bool		empty() const {	return (_size == 0 ? true : false); }

			void		reserve(size_type n)
			{
				if (n > _capacity)
				{
					value_type *tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.construct(&tmp[i], _array[i]);
						_alloc.destroy(&_array[i]);
					}
					_alloc.deallocate(_array, _capacity);
					_capacity = n;
					_array = tmp;
				}
				else if (n > _max_size)
					throw (std::length_error("vector"));
			}

			/* ************************************************************************** */
			/*                     		    ELEMENT ACCESS                                */
			/* ************************************************************************** */

			reference operator[](size_type n) {	return (_array[n]);	}

			const_reference operator[](size_type n) const {	return (_array[n]);	}

			reference at(size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return (_array[n]);
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return (_array[n]);
			}

			reference front() { return (_array[0]); }

			const_reference front() const {	return (_array[0]);	}

			reference back() { return (_array[_size - 1]); }

			const_reference back() const { return (_array[_size - 1]); }


			/* ************************************************************************** */
			/*                     		       MODIFIERS                                  */
			/* ************************************************************************** */

			template <class InputIterator>
  			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type n = 0;
				size_type i = 0;

				for (InputIterator it = first; it != last; it++)
					n++;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				if (n > _capacity)
				{
					_alloc.deallocate(_array, _capacity);
					_array = _alloc.allocate(n);
					_capacity = n;
				}
				for (InputIterator it = first; it != last; it++)
				{
					_alloc.construct(&_array[i], *it);
					i++;
				}
				_size = n;
				return ;
			}

			void	assign(size_type n, const value_type& val)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				if (n > _capacity)
				{
					_alloc.deallocate(_array, _capacity);
					_array = _alloc.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
				return ;
			}

			void	push_back(const value_type &val)
			{
				if (_size == _capacity)
				{
					if (_capacity == 0)
						_capacity = 1;
					reserve(_capacity * 2);
				}
				_alloc.construct(&_array[_size], val);
				++_size;
			}

			void	pop_back()
			{
				_alloc.destroy(&_array[_size - 1]);
				--_size;
			}

			iterator insert(iterator position, const value_type& val)
			{
				difference_type diff;
				
				diff = position.base() - _array;
				insert(position, 1, val);
				return (begin() + diff);
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				size_type	pos_index = 0;
						
				for (iterator it = begin(); it != position; it++)
					pos_index++;
				if (_size +  n > _capacity && _size * 2 > _size + n)
					reserve(_size * 2);
				else
					reserve(_size + n);	
				for (size_type i = _size + n - 1; (i > pos_index && i >= n); i--)
				{
					_alloc.construct(&_array[i], _array[i - n]);
					_alloc.destroy(&_array[i - n]);
				}
				for (size_type i = pos_index; i < pos_index + n; i++)
					_alloc.construct(&_array[i], val);
				_size += n;
			}

			template <class InputIterator>
    		void	insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type		n = 0;
				size_type		pos_index = 0;
				InputIterator 	it;
				
				for (it = first; it != last; it++)
					n++;
				for (iterator it = begin(); it != position; it++)
					pos_index++;
				if (_size +  n > _capacity && _size * 2 > _size + n)
					reserve(_size * 2);
				else
					reserve(_size + n);
				for (size_type i = _size + n - 1; (i > pos_index && i >= n); i--)
				{
					_alloc.construct(&_array[i], _array[i - n]);
					_alloc.destroy(&_array[i - n]);
				}
				it = first;
				for (size_type i = pos_index; i < pos_index + n; i++)
				{
					_alloc.construct(&_array[i], *it);
					it++;
				}
				_size += n;
			}

			iterator	erase(iterator it)
			{
				iterator last = end();
				iterator tmp = it;

				while (tmp != (last - 1))
				{
					_array[tmp - begin()] = *(tmp + 1); 
					tmp++;
				}
				_alloc.destroy(&_array[tmp - begin()]);
				_size--;
				return it;
			}

			iterator	erase(iterator first, iterator last)
			{
				difference_type	range = last - first;

				for (difference_type i(0); i < range; i++)
					erase(first);
				return first;
			}

			void	swap(vector& x)
			{
				pointer					_array_tmp = x._array;
				allocator_type			_alloc_tmp = x._alloc;
				size_type				_size_tmp = x._size;
				size_type				_capacity_tmp = x._capacity;
				
				x._array = _array;
				x._alloc = _alloc;
				x._size = _size;
				x._capacity = _capacity;
				_array = _array_tmp;
				_alloc = _alloc_tmp;
				_size = _size_tmp;
				_capacity = _capacity_tmp;
			}

			void	clear() { resize(0); }

			/* ************************************************************************** */
			/*                     		       ALLOCATOR                                  */
			/* ************************************************************************** */

			allocator_type		get_allocator() const { return (_alloc); };

			private:
		
			/* ************************************************************************** */
			/*                     		       VARIABLES                                  */
			/* ************************************************************************** */

				pointer					_array;
				allocator_type			_alloc;
				size_type				_size;
				size_type				_capacity;
				const size_type			_max_size;
	};

	/* ************************************************************************** */
	/*                     		  NON-MEMBER OVERLOADS		                      */
	/* ************************************************************************** */

		template <class T, class Alloc>
		bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		
		template <class T, class Alloc>
		bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }

		template <class T, class Alloc>
		bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (lhs < rhs || lhs == rhs); }

		template <class T, class Alloc>
		bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
		
		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs > rhs || lhs == rhs);}
	
		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

}

#endif
