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

int main ()
{
  std::map<int,int> mymap;
  std::map<int,int>::iterator itlow,itup;

  mymap[1]=20;
  mymap[2]=40;
  mymap[4]=60;
  mymap[5]=80;
  mymap[6]=100;

  itlow=mymap.lower_bound (3);  // itlow points to b
  itup=mymap.upper_bound (3);   // itup points to e (not d!)

	std::cout << itlow->first << " | " << itup->first << std::endl;
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (std::map<int,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  return 0;
}