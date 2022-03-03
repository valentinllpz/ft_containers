#include "map.hpp"
#include <string>
#include <map>
#include <iostream>

int main ()
{
	std::map<int, std::string> mymap;

 	for (std::map<int,std::string>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';
	return (0);
}