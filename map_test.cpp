#include "map.hpp"
// #include <string>
// #include <map>
// #include <iostream>

// int main ()
// {
// 	ft::map<int, std::string> mymap;
// 	mymap.insert(ft::pair<int, std::string>(2, "lol"));
// 	mymap.insert(ft::pair<int, std::string>(1, "mdr"));
// 	mymap.insert(ft::pair<int, std::string>(3, "fuuf"));
// 				mymap.erase(mymap.begin());
// 	for (ft::map<int,std::string>::iterator it=mymap.begin(); it!=mymap.end(); it++)
//     {
// 		std::cout << it->first << " => " << it->second << '\n';
// 	}
	
// 	return (0);
// }

#include <iostream>
#include <map>

void ftlol()
{

  ft::map<char,int> first;
  ft::map<char,int> second;

  first['x']=8;
  first['y']=16;
  first['z']=32;

  second=first;                // second now contains 3 ints
  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';

  first=ft::map<char,int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';


}

int main ()
{


//   itlow=mymap.lower_bound (3);  // itlow points to b
//   itup=mymap.upper_bound (3);   // itup points to e (not d!)

// 	std::cout << itlow->first << " | " << itup->first << std::endl;
//   mymap.erase(itlow,itup);        // erases [itlow,itup)

//   // print content:
//   for (ft::map<int,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';
	ftlol();

  return 0;
}