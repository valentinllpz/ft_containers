/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:10:43 by valentin          #+#    #+#             */
/*   Updated: 2022/03/17 20:15:52 by vlugand-         ###   ########.fr       */
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

			container_type				c;
		
		public : 

		/* ************************************************************************** */
		/*                     		   MEMBER FUNCTIONS                               */
		/* ************************************************************************** */

			explicit	stack(const container_type& ctnr = container_type()) : c(ctnr) {}

			~stack() {}

			bool 				empty() const { return (c.empty()); }

			size_type 			size() const { return (c.size()); }

			value_type& 		top() { return (c.back()); }

			const value_type&	top() const { return (c.back()); }

			void 				push(const value_type& val) { c.push_back(val); }

			void				pop() { c.pop_back(); }

		/* ************************************************************************** */
		/*                       NON MEMBER FUNCTIONS OVERLOADS                       */
		/* ************************************************************************** */	

			// relational operators (here we have to use friend because our c variable is protected)
			friend bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c == rhs.c); }

			friend bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c != rhs.c); }

			friend bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c < rhs.c); }

			friend bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c <= rhs.c); }

			friend bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c > rhs.c); }
			
			friend bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ){ return (lhs.c >= rhs.c); }

	};
}

#endif
