#include "map.hpp"
#include <string>
#include <map>
#include <iostream>

int main ()
{
	ft::map<int, std::string> mymap;
	mymap.insert(ft::pair<int, std::string>(2, "lol"));
	mymap.insert(ft::pair<int, std::string>(1, "mdr"));
 	for (ft::map<int,std::string>::const_iterator it=mymap.begin(); it!=mymap.end(); it++)
    	std::cout << it->first << " => " << it->second << '\n';

	mymap.find(2);
	return (0);
}

/*
no matching conversion for functional-style cast from 
'const ft::map_iterator<ft::pair<const int, std::__1::basic_string<char> > >::node_pointer' (aka 'Node<ft::pair<const int, std::__1::basic_string<char> > > *const') to 
'map_iterator<const ft::map_iterator<ft::pair<const int, std::__1::basic_string<char> > >::value_type>' (aka 'map_iterator<const ft::pair<const int, std::__1::basic_string<char> > >')
*/