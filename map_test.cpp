#include "map.hpp"
#include <string>
#include <map>
#include <iostream>

int main ()
{
	ft::map<int, std::string> mymap;
	std::string t = "test";
	mymap.insert(ft::pair<int, std::string>(1, t));
 	for (ft::map<int,std::string>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';
	return (0);
}