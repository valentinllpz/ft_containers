/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:16:39 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/12 17:10:14 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "common.hpp"
#include "vector_iterator.hpp"
#include "vector_reverse_iterator.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
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
			
			typedef vector_iterator<T>      		        	iterator;
			typedef vector_iterator<T const>					const_iterator;
			typedef vector_reverse_iterator<T>					reverse_iterator;
			typedef vector_reverse_iterator<T const>			const_reverse_iterator;

			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			

			/* ************************************************************************** */
			/*                     			CONSTRUCTORS                                  */
			/* ************************************************************************** */

			// Empty container constructor (default constructor): Constructs an empty container, with no elements ( = a vector of size 0)
			explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _alloc(alloc), _size(0), _capacity(0), _max_size(alloc.max_size()) {}

			// Fill constructor: Constructs a container with n elements. Each element is a copy of val.
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _max_size(alloc.max_size())
			{
				_array = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], val);
				return ;
			};

			// Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _max_size(alloc.max_size())
			{
				size_type	i = 0;

				for (InputIterator it = first; it != last; it++)
					i++;
				_array = alloc.allocate(i);
				_size = i;
				_capacity = i;
				i = 0;
				for (InputIterator it = first; it != last; it++)
				{
					_alloc.construct(&_array[i], *it);
					i++;
				}
				return ;
			}

			// Copy constructor: Constructs a container with a copy of each of the elements in x, in the same order.
			vector(const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _max_size(x.max_size())
			{
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x[i]);
				return ;
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

			vector & operator=(const vector & x) // pas sur que ca soit good ici
			{
				~vector();
				*this = vector(x);
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

			size_type	size() const
			{
				return (_size);
			}

			size_type	max_size() const
			{
				return (_max_size);
			}

			void		resize(size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
					for (size_type i = n ; i < _size ; i++)	
						_alloc.destroy(&_array[i]);
				}
				else if (n > _size && n < _capacity)
				{
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_array[i], val);
				}
				else if (n > _size && n > _capacity)
				{
					if (n > _capacity * 2)
						reserve(n);
					else
						reserve(_capacity * 2);
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_array[i], val);
				}
				_size = n;
				return ;
			}

			size_type	capacity() const
			{
				return (_capacity);
			}

			bool		empty() const
			{
				return _size == 0 ? true : false;
			}

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
				return ;
			}

			/* ************************************************************************** */
			/*                     		    ELEMENT ACCESS                                */
			/* ************************************************************************** */

			reference operator[](size_type n)
			{
				return (_array[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (_array[n]);
			}

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

			reference front()
			{
				return (_array[0]);
			}

			const_reference front() const
			{
				return (_array[0]);
			}

			reference back()
			{
				return (_array[_size - 1]);
			}

			const_reference back() const
			{
				return (_array[_size - 1]);
			}


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
				_size++;
				return ;
			}

			void	pop_back()
			{
				_alloc.destroy(&_array[_size - 1]);
				--_size;
				return ;
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
				if (_size + n > _capacity)
				{
					if (_size + n < _capacity * 2)
						reserve(_capacity * 2);
					else
						reserve(_size + n);
				}
				for (size_type i = _size + n; i > pos_index; i--)
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
				if (_size + n > _capacity)
				{
					if (_size + n < _capacity * 2)
						reserve(_capacity * 2);
					else
						reserve(_size + n);
				}
				for (size_type i = _size + n; i > pos_index; i--)
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
				return ;
			}

			

		private:
		
			/* ************************************************************************** */
			/*                     		       VARIABLES                                  */
			/* ************************************************************************** */

			value_type				*_array;
			allocator_type			_alloc;
			size_type				_size;
			size_type				_capacity;
			const size_type			_max_size;
	};

	// MISSING NON MEMBER OVERLOADS + erase + swap + clear
	// LESS NOT UNDERSTOOD
};

#endif
