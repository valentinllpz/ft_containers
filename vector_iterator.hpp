/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:45:04 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/02 16:30:42 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

// https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
// https://www.boost.org/sgi/stl/RandomAccessIterator.html

// namespace ft
// {
// 	template <typename T>
// 	class vector_iterator
// 	{
// 		public:

// 		/* ************************************************************************** */
// 		/*                     			   ALIASES                                    */
// 		/* ************************************************************************** */

// 			typedef T         								value_type;
// 			typedef std::random_access_iterator_tag  		iterator_category;
// 			typedef std::ptrdiff_t 							difference_type;
// 			typedef value_type *							pointer;
// 			typedef value_type & 							reference;
		
// 		protected: 

// 		/* ************************************************************************** */
// 		/*                     			  VARIABLE                                    */
// 		/* ************************************************************************** */

// 			pointer											_ptr;
// 			// we want the pointer to be "protected" because we want to allow children classes to access it
// 			// _ptr is also accessible between different instances of the same class

// 		public:
		
// 		/* ************************************************************************** */
// 		/*                     			CONSTRUCTORS                                  */
// 		/* ************************************************************************** */

// 			vector_iterator() : _ptr(NULL) {}
// 			vector_iterator(pointer ptr) : _ptr() {}
// 			vector_iterator(const vector_iterator & src) : _ptr(src._ptr) {}
// 			~vector_iterator() {}

// 		/* ************************************************************************** */
// 		/*                     		OPERATORS OVERLOADS                               */
// 		/* ************************************************************************** */

		// vector_iterator & operator=(vector_iterator const & rhs) {_pointer = rhs._pointer; return *this;}

// 		// Dereferencement operators:

// 			reference operator*() const { return *_ptr; }
// 			pointer operator->() { return _ptr; }	
// 			value_type operator[](size_t i) { return *(_ptr + i); }

// 		// Increment / decrement operators:

// 			vector_iterator & operator++() // Prefix increment
// 			{ 
// 				_ptr++;
// 				return (*this); // incremented value is returned (hence the use of reference in prototype)
// 			}
	
// 			vector_iterator operator++(int) // Postfix increment
// 			{
// 				vector_iterator tmp;

// 				tmp = *this;
// 				++(*this);
// 				return (tmp); // value before incrementation is returned
// 			}
			
// 			vector_iterator & operator--() // Prefix decrement
// 			{ 
// 				_ptr--;
// 				return (*this); // decremented value is returned (hence the use of reference in prototype)
// 			}
			
// 			vector_iterator operator--(int) // Postfix decrement
// 			{
// 				vector_iterator tmp;

// 				tmp = *this;
// 				--(*this);
// 				return (tmp); // value before decrementation is returned
// 			}

// 		// Comparison operators:

// 			bool operator==(const vector_iterator & rhs) const { return (_ptr == rhs._ptr); }
// 			bool operator!=(const vector_iterator & rhs) const { return (_ptr != rhs._ptr); }
// 			bool operator<=(const vector_iterator & rhs) const { return (_ptr <= rhs._ptr); }
// 			bool operator>=(const vector_iterator & rhs) const { return (_ptr >= rhs._ptr); }
// 			bool operator<(const vector_iterator & rhs) const { return (_ptr < rhs._ptr); }
// 			bool operator>(const vector_iterator & rhs) const { return (_ptr > rhs._ptr); }

// 		// Arithmetics operators:  (a and b are objects of this iterator type, n is a value of its difference type)

// 			/* here we need the "friend" keyword because the (+) operator comes from [n] which is not a member of this class) */
// 			friend vector_iterator<T> operator+(difference_type n, const vector_iterator & rhs) { return (n + rhs._ptr); } // [n + a]
// 			vector_iterator<T> operator+(difference_type n) const { return (_ptr + n); } // [a + n]
// 			vector_iterator<T> operator-(difference_type n) const { return (_ptr - n); } // [a - n]
// 			vector_iterator<T> operator-(const vector_iterator & rhs) const { return (_ptr - rhs._ptr); } // [a - b]

// 			/* when (=) is involved we need to return a pointer to the current modified instance (allows chaining a = b = c) */
// 			vector_iterator & operator=(vector_iterator const & rhs) // [a = b]
// 			{
// 				_ptr = rhs._ptr;
// 				return (*this);
// 			}

// 			vector_iterator<T> & operator+=(difference_type n) // [a += n]
// 			{ 
// 				// If n == 0, this is a null operation
// 				if (n < 0) // If n < 0, equivalent to executing --i n times. 
// 				{
// 					while (n < 0)
// 					{
// 						operator--();
// 						n++;
// 					}
// 				}
// 				else // If n > 0, equivalent to executing ++i n times.
// 				{
// 					while (n > 0)
// 					{
// 						operator++();
// 						n--;
// 					}
// 				}
// 				return (*this);
// 			}
			
// 			vector_iterator<T> & operator-=(difference_type n) // [a -= n]
// 			{
// 				_ptr += (-n);
// 				return (*this);
// 			}

// 		// Redirection operator

// 			/* here again we need the "friend" keyword because our class instance comes on the right hand side of the (<<) operator */
// 			friend std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs)
// 			{
// 				o << *rhs._ptr;
// 				return (o);
// 			}
// 	};

// }

template<typename T>
class vector_iterator {
public:
	typedef T value_type;
	typedef std::random_access_iterator_tag iterator_category;
	typedef std::ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	vector_iterator() : _pointer(NULL) {}
	vector_iterator(value_type * ptr) : _pointer(ptr) {}
	vector_iterator(vector_iterator const & src) : _pointer(src._pointer) {}
	~vector_iterator() {}
	vector_iterator & operator=(vector_iterator const & rhs) {_pointer = rhs._pointer; return *this;}
	value_type * get_ptr(void) const {return _pointer;}
	operator vector_iterator<value_type const>() const {return vector_iterator<value_type const>(_pointer);}

protected:
	value_type * _pointer;

public:
	vector_iterator& operator++() {
		_pointer++;
		return *this;
	}


				vector_iterator operator++(int) // Postfix increment
			{
				vector_iterator tmp;

				tmp = *this;
				++(*this);
				return (tmp); // value before incrementation is returned
				}

	vector_iterator& operator--() {
		_pointer--;
		return *this;
	}

	vector_iterator operator--(int) {
		vector_iterator it = *this;
		--(*this);
		return it;
	}

	value_type& operator[](int index) {return *(_pointer + index);}
	value_type* operator->() {return _pointer;}
	value_type& operator*() {return *_pointer;}

	bool operator==(const vector_iterator& other) const {return _pointer == other._pointer;}
	bool operator!=(const vector_iterator& other) const {return _pointer != other._pointer;}
	bool operator<(const vector_iterator& other) const {return _pointer < other._pointer;}
	bool operator<=(const vector_iterator& other) const {return _pointer <= other._pointer;}
	bool operator>(const vector_iterator& other) const {return _pointer > other._pointer;}
	bool operator>=(const vector_iterator& other) const {return _pointer >= other._pointer;}

	friend vector_iterator<T> operator+(difference_type n, const vector_iterator& rhs) {return n + rhs._pointer;} //n + a
	vector_iterator<T> operator+(difference_type n) const {return _pointer + n;} //a + n
	vector_iterator<T> operator-(difference_type n) const {return _pointer - n;} //a - n
	difference_type operator-(const vector_iterator& rhs) const {return _pointer - rhs._pointer;} //a - b
	vector_iterator<T> & operator+=(difference_type n) {_pointer += n; return *this;}
	vector_iterator<T> & operator-=(difference_type n) {_pointer -= n; return *this;}

	friend std::ostream & operator<<(std::ostream & o, vector_iterator<T> & rhs) {o << *rhs._pointer; return o;}
};

template<typename it1, typename it2>
bool operator==(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() == b.get_ptr();}
template<typename it1, typename it2>
bool operator!=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() != b.get_ptr();}
template<typename it1, typename it2>
bool operator<(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() < b.get_ptr();}
template<typename it1, typename it2>
bool operator<=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() <= b.get_ptr();}
template<typename it1, typename it2>
bool operator>(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() > b.get_ptr();}
template<typename it1, typename it2>
bool operator>=(const vector_iterator<it1>& a, const vector_iterator<it2>& b) {return a.get_ptr() >= b.get_ptr();}


#endif
