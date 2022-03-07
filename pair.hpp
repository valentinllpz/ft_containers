/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:25:25 by vlugand-          #+#    #+#             */
/*   Updated: 2022/03/07 23:24:22 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

// https://www.cplusplus.com/reference/utility/pair/

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		/* ************************************************************************** */
		/*                     		    MEMBER TYPES                                  */
		/* ************************************************************************** */
		
		typedef T1			first_type;
		typedef T2			second_type;

		/* ************************************************************************** */
		/*                     		  MEMBER VARIABLES                                */
		/* ************************************************************************** */

		first_type			first;
		second_type			second;
		
		/* ************************************************************************** */
		/*                     		  MEMBER FUNCTIONS                                */
		/* ************************************************************************** */

		pair() : first(), second() {}
		template<class U, class V>	pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}
		~pair() {}

		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	/* ************************************************************************** */
	/*                   	NON-MEMBER OPERATOR OVERLOADS                         */
	/* ************************************************************************** */

	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs == rhs); }
	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs < lhs); }
	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (rhs < lhs); }
	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }
}

#endif