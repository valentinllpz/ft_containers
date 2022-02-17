/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:10:43 by valentin          #+#    #+#             */
/*   Updated: 2022/02/17 15:28:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

// https://www.cplusplus.com/reference/stack/stack/

namespace ft
{
    template < typename T, typename Container = ft::vector<T> >
    class stack
    {
        public:

		/* ************************************************************************** */
		/*                     			   ALIASES                                    */
		/* ************************************************************************** */

			typedef T					value_type;
			typedef Container			container_type;
			typedef size_t				size_type;

		protected:

		/* ************************************************************************** */
		/*                     		       VARIABLE                                   */
		/* ************************************************************************** */

			container_type				_container;
		
		public : 

		/* ************************************************************************** */
		/*                     		   MEMBER FUNCTIONS                               */
		/* ************************************************************************** */

			explicit	stack(const container_type& ctnr = container_type()) : _container(ctnr) {}
			~stack() {}

			bool 				empty() const { return (_container.empty()); }
			size_type 			size() const { return (_container.size()); }
			value_type& 		top() { return (_container.back()); }
			const value_type&	top() const { return (_container.back()); }
			void 				push(const value_type& val) { _container.push_back(val); }
			void				pop() { _container.pop_back(); }

		/* ************************************************************************** */
		/*                       NON MEMBER FUNCTIONS OVERLOADS                       */
		/* ************************************************************************** */	

			// relational operators
			friend bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container == rhs._container); }
			friend bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container != rhs._container); }
			friend bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container < rhs._container); }
			friend bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container <= rhs._container); }
			friend bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container > rhs._container); }
			friend bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs._container >= rhs._container); }

	};
}

#endif
