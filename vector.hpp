/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:16:39 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/15 19:20:50 by vlugand-         ###   ########.fr       */
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

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			
			typedef ft::vector_iterator<value_type>      	   	 	iterator;
			typedef ft::vector_iterator<value_type const>			const_iterator;
			typedef ft::vector_reverse_iterator<iterator>			reverse_iterator;
			typedef ft::vector_reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef std::ptrdiff_t									difference_type;
			typedef size_t											size_type;

			

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
					erase(begin() + n, end());
				else if (n > _size)
					insert(end(), n - _size, val);
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
				erase(begin(), end());
				insert(begin(), first, last);
			}

			void	assign(size_type n, const value_type& val)
			{
				erase(begin(), end());
				insert(begin(), n, val);
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
				for (size_type i = _size + n - 1; i > pos_index; i--)
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
				for (size_type i = _size + n - 1; i > pos_index; i--)
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

			iterator	erase(iterator position) { return (erase(position, position + 1));	}

			iterator	erase(iterator first, iterator last)
			{
				size_type	first_index = 0;
				size_type	last_index = 0;
				size_type	last_to_end = 0;
				
				for (iterator it = begin(); it != first; it++)
					first_index++;
				for (iterator it = begin(); it != last; it++)
					last_index++;
				for (iterator it = last; it != end(); it++)
					last_to_end++;
				for (size_type i = first_index, j = 0; i < _size; i++, j++)
				{
					_alloc.destroy(&_array[i]);
					_alloc.construct(&_array[i], _array[last_index + j]);
				}
				for (size_type i = first_index + last_to_end; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size -= last_index - first_index;
				return (first);
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
				return ;
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
		/*                     	 NON-MEMBER FUNCTION OVERLOADS                        */
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
		bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){ return (lhs < rhs || lhs == rhs); }

		template <class T, class Alloc>
		bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
		
		template <class T, class Alloc>
		bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs > rhs || lhs == rhs);}
	
		template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

};

#endif


// #ifndef VECTOR_HPP
// #define VECTOR_HPP

// #include <memory>
// #include <iostream>
// #include <string>
// #include "vector_iterator.hpp"
// #include "vector_reverse_iterator.hpp"
// #include "utils.hpp"

// //vector is a sequence container that encapsulates dynamic size arrays
// namespace ft {

// template <class T, class Alloc = std::allocator<T> >
// class vector {

// public:
// 	//list of the typedef required: https://cplusplus.com/reference/vector/vector/
// 	typedef T                                        value_type;
// 	typedef value_type*                              pointer_type;
// 	typedef value_type&                              reference_type;
// 	typedef Alloc                                    allocator_type;
// 	typedef typename allocator_type::reference       reference;
// 	typedef typename allocator_type::const_reference const_reference;
// 	typedef typename allocator_type::size_type       size_type;
// 	typedef typename allocator_type::difference_type difference_type;
// 	typedef typename allocator_type::pointer         pointer;
// 	typedef typename allocator_type::const_pointer   const_pointer;
// 	typedef vector_iterator<value_type>              iterator;
// 	typedef vector_iterator<value_type const>        const_iterator;
// 	typedef ft::vector_reverse_iterator<iterator>           reverse_iterator;
// 	typedef ft::vector_reverse_iterator<const_iterator>     const_reverse_iterator;

// protected:
// 	allocator_type _alloc;
// 	pointer_type _array;
// 	size_type _size;
// 	size_type _capacity;
// 	size_type _max_size;

// public:
// //MEMBER FUNCTIONS
// 			// Empty container constructor (default constructor): Constructs an empty container, with no elements ( = a vector of size 0)
// 			explicit vector(const allocator_type& alloc = allocator_type()) : _array(NULL), _alloc(alloc), _size(0), _capacity(0), _max_size(alloc.max_size()) {}

// 			// Fill constructor: Constructs a container with n elements. Each element is a copy of val.
// 			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _max_size(alloc.max_size())
// 			{
// 				_array = _alloc.allocate(n);
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.construct(&_array[i], val);
// 				return ;
// 			};

// 			// Range constructor: Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
// 			template <class InputIterator>
// 			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc),  _size(0), _capacity(0), _max_size(alloc.max_size())
// 			{
// 				size_type	i = 0;

// 				for (InputIterator it = first; it != last; it++)
// 					i++;
// 				_array = _alloc.allocate(i);
// 				_size = i;
// 				_capacity = i;
// 				i = 0;
// 				for (InputIterator it = first; it != last; it++)
// 				{
// 					_alloc.construct(&_array[i], *it);
// 					i++;
// 				}
// 				return ;
// 			}

// 			// Copy constructor: Constructs a container with a copy of each of the elements in x, in the same order.
// 			vector(const vector& x) : _alloc(x._alloc), _size(x._size), _capacity(x._capacity), _max_size(x.max_size())
// 			{
// 				_array = _alloc.allocate(_capacity);
// 				for (size_type i = 0; i < _size; i++)
// 					_alloc.construct(&_array[i], x[i]);
// 				return ;
// 			};


// 	vector& operator= (const vector& x) {
// 		if (_size < x._size) {
// 			reserve(x._size);
// 			resize(x._size);
// 		}
// 		else
// 			for (size_type i = 0; i < _size; i++)
// 				_alloc.destroy(&_array[i]);
// 		_size = x._size;
// 		for (size_type i = 0; i < _size; i++)
// 			_alloc.construct(&_array[i], x._array[i]);
// 		return *this;
// 	}
// 	~vector() {
// 		for (size_type i = 0; i < _size; i++)
// 			_alloc.destroy(&_array[i]);
// 		_alloc.deallocate(_array, _capacity);
// 	}

// //ITERATORS
// // begin Return iterator to beginning (public member function )
// 	iterator begin() {return iterator(_array);}
// 	const_iterator begin() const {return const_iterator(_array);}
// // end Return iterator to end (public member function )
// 	iterator end() {return iterator(_array + _size);}
// 	const_iterator end() const {return const_iterator(_array + _size);}
// // rbegin Return reverse iterator to reverse beginning (public member function )
// 	reverse_iterator rbegin() {return reverse_iterator(end());}
// 	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
// // rend Return reverse iterator to reverse end (public member function )
// 	reverse_iterator rend() {return reverse_iterator(begin());}
// 	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

// //CAPACITY
// 	size_type size() const {return _size;}
// 	size_type max_size() const {return _alloc.max_size();}
// 	size_type capacity() const {return _capacity;}
// 	bool empty() const {return _size == 0 ? true : false;}
// 	void reserve(size_type n) {
// 		if (n > _capacity) {
// 			pointer_type update = _alloc.allocate(n);
// 			for (size_type i = 0; i < _size; i++) {
// 				_alloc.construct(&update[i], _array[i]);
// 				_alloc.destroy(&_array[i]);
// 			}
// 			_alloc.deallocate(_array, _capacity = n);
// 			_array = update;
// 			_capacity = n;
// 		}
// 	}
// 	void resize(size_type n, value_type val = value_type()) {
// 		if (n > _capacity) {
// 			if (n < _capacity * 2)
// 				reserve(_capacity * 2);
// 			else
// 				reserve(n);
// 		}
// 		for (size_type i = _size; i < n; i++)
// 			_alloc.construct(&_array[i], val);
// 		for (size_type i = n; i < _size; i++)
// 			_alloc.destroy(&_array[i]);
// 		_size = n;
// 	}

// //ELEMENT ACCESS
// 	reference operator[] (size_type n) {return _array[n];}
// 	const_reference operator[] (size_type n) const {return _array[n];}
// 	reference at (size_type n) {
// 		if (n >= _size)
// 			throw std::out_of_range("out of range");
// 		return _array[n];
// 	}
// 	const_reference at (size_type n) const {
// 		if (n >= _size)
// 			throw std::out_of_range("out of range");
// 		return _array[n];
// 	}
// 	reference front() {return _array[0];}
// 	const_reference front() const {return _array[0];}
// 	reference back() {return _array[_size - 1];}
// 	const_reference back() const {return _array[_size - 1];}

// //MODIFIERS
// 	template <class InputIterator>
// 	void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
// 		size_type n = 0;
// 		size_type i = 0;
// 		for (InputIterator it = first; it != last; it++)
// 			n++;
// 		reserve(n);
// 		resize(n);
// 		for (size_type i = 0; i < n && i < _size; i++)
// 			_alloc.destroy(&_array[i]);
// 		for (InputIterator it = first; it != last; it++, i++)
// 			_alloc.construct(&_array[i], *it);
// 		if (n > _size)
// 			_size = n;
// 	}
// 	void assign (size_type n, const value_type& val) {
// 		reserve(n);
// 		resize(n);
// 		for (size_type i = 0; i < n && i < _size; i++)
// 			_alloc.destroy(&_array[i]);
// 		for (size_type i = 0; i < n; i++)
// 			_alloc.construct(&_array[i], val);
// 		if (n > _size)
// 			_size = n;
// 	}
// 	void push_back(const value_type& val) {
// 		if (_size == _capacity) {
// 			if (_capacity == 0)
// 				reserve(1);
// 			else
// 				reserve(_capacity * 2);
// 		}
// 		_alloc.construct(&_array[_size], val);
// 		_size++;
// 	}
// 	void pop_back() {_alloc.destroy(&_array[--_size]);}
// 	iterator insert (iterator position, const value_type& val) {
// 		difference_type diff = position.get_ptr() - _array;
// 		insert(position, 1, val);
// 		return iterator(begin() + diff);
// 	}
// 	void insert (iterator position, size_type n, const value_type& val) {
// 		size_type begin_to_pos = 0;
// 		size_type pos_to_end = 0;
// 		iterator it = begin();
// 		for (; it != position; it++)
// 			begin_to_pos++;
// 		for (; it != end(); it++)
// 			pos_to_end++;
// 		if (_size + n > _capacity) {
// 			if (_size + n < _capacity * 2)
// 				reserve(_capacity * 2);
// 			else
// 				reserve(_size + n);
// 		}
// 		for (size_type i = 0; i < pos_to_end; i++) {
// 			_alloc.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
// 			_alloc.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
// 		}
// 		for (size_type i = 0; i < n; i++) {
// 			_alloc.construct(&_array[begin_to_pos + i], val);
// 		}
// 		_size += n;
// 	}
// 	template <class InputIterator>
// 	void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
// 		size_type n = 0;
// 		size_type begin_to_pos = 0;
// 		size_type pos_to_end = 0;
// 		for (InputIterator it = first; it != last; it++)
// 			n++;
// 		iterator it = begin();
// 		for (; it != position; it++)
// 			begin_to_pos++;
// 		for (;it != end(); it++)
// 			pos_to_end++;
// 		if (_size + n > _capacity) {
// 			if (_size + n < _capacity * 2)
// 				reserve(_capacity * 2);
// 			else
// 				reserve(_size + n);
// 		}
// 		for (size_type i = 0; i < pos_to_end; i++) {
// 			_alloc.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
// 			_alloc.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
// 		}
// 		InputIterator curs = first;
// 		for (size_type i = 0; i < n; i++) {
// 			_alloc.construct(&_array[begin_to_pos + i], *curs);
// 			curs++;
// 		}
// 		_size += n;
// 	}
// 	iterator erase(iterator position) {return erase(position, position + 1);}
// 	iterator erase(iterator first, iterator last) {
// 		size_type begin_to_first = 0;
// 		size_type first_to_last = 0;
// 		size_type last_to_end = 0;
// 		for (iterator it = begin(); it != first; it++)
// 			begin_to_first++;
// 		for (iterator it = first; it != last; it++)
// 			first_to_last++;
// 		for (iterator it = last; it != end(); it++)
// 			last_to_end++;
// 		for (size_type i = 0; i < last_to_end; i++) {
// 			_alloc.destroy(&_array[begin_to_first + i]);
// 			_alloc.construct(&_array[begin_to_first + i], _array[begin_to_first + i + first_to_last]);
// 		}
// 		for (size_type i = 0; i < first_to_last; i++)
// 			_alloc.destroy(&_array[begin_to_first + last_to_end + i]);
// 		_size -= first_to_last;
// 		return first;
// 	}
// 	void swap(vector& x) {
// 		allocator_type temp_alloc = x._alloc;
// 		pointer_type temp_array = x._array;
// 		size_type temp_size = x._size;
// 		size_type temp_capacity = x._capacity;
// 		x._alloc = _alloc;
// 		x._array = _array;
// 		x._size = _size;
// 		x._capacity = _capacity;
// 		_alloc = temp_alloc;
// 		_array = temp_array;
// 		_size = temp_size;
// 		_capacity = temp_capacity;
// 	}
// 	void clear() {_size = 0;}

// //ALLOCATOR
// 	allocator_type get_allocator() const {return _alloc;}

// };

// //NON-MEMBER FUNCTION OVERLOADS
// 	template <class T, class Alloc>
// 	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
// 		if (lhs.size() != rhs.size())
// 			return false;
// 		return equal(lhs.begin(), lhs.end(), rhs.begin());
// 	}
// 	template <class T, class Alloc>
// 	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return !(lhs == rhs);}
// 	template <class T, class Alloc>
// 	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
// 		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
// 	}
// 	template <class T, class Alloc>
// 	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs < rhs || lhs == rhs);}
// 	template <class T, class Alloc>
// 	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return rhs < lhs;}
// 	template <class T, class Alloc>
// 	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {return (lhs > rhs || lhs == rhs);}
// 	template <class T, class Alloc>
// 	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}

// }

// #endif