/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:32:16 by vlugand-          #+#    #+#             */
/*   Updated: 2022/02/12 12:33:22 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	// https://www.cplusplus.com/reference/type_traits/is_integral/

	template <class T>
	struct is_integral { const static bool value = false; };
	template<>
	struct is_integral<bool> { const static bool value = true; };
	template<>
	struct is_integral<char> { const static bool value = true; };
	#if __APPLE__
	template<>
	struct is_integral<char16_t> { const static bool value = true; };
	template<>
	struct is_integral<char32_t> { const static bool value = true; };
	#endif
	template<>
	struct is_integral<wchar_t> { const static bool value = true; };
	template<>
	struct is_integral<signed char> { const static bool value = true; };
	template<>
	struct is_integral<short int> { const static bool value = true; };
	template<>
	struct is_integral<int> { const static bool value = true; };
	template<>
	struct is_integral<long int> { const static bool value = true; };
	template<>
	struct is_integral<long long int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned char> { const static bool value = true; };
	template<>
	struct is_integral<unsigned short int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned long int> { const static bool value = true; };
	template<>
	struct is_integral<unsigned long long int> { const static bool value = true; };


	// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if

	template<bool B, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };


	//https://www.cplusplus.com/reference/iterator/iterator_traits/

	template <class Iterator>
	class iterator_traits
	{
		public:

			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits <T *>
	{
		public:

			typedef std::ptrdiff_t							difference_type;
			typedef T										value_type;
			typedef T* 										pointer;
			typedef T&										reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	class iterator_traits <const T *>
	{
		public:
		
			typedef std::ptrdiff_t							difference_type;
			typedef T 										value_type;
			typedef const T*								pointer;
			typedef const T&								reference;
			typedef std::random_access_iterator_tag			iterator_category;
	};


	// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true; // Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
			++first1; ++first2;
		}
		return (first2!=last2);
	}


	// https://cplusplus.com/reference/algorithm/equal/

	template <class InputIterator1, class InputIterator2>
 	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	// https://www.cplusplus.com/reference/functional/binary_function/

	template <class Arg1, class Arg2, class Result>
  	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
  	};

	// https://www.cplusplus.com/reference/functional/less/

	template <class T> struct less : binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const {return x<y;}
	};
}

#endif
