//============================================================================
// Name        : Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>

using namespace std;

int main()
{
  map<char,int> m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "map::equal_range()" << endl;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "auto ret = map.equal_range(\'b\');" << endl;

  auto ret = m.equal_range('b');

  cout << "Lower bound is {" << ret.first->first << "," << ret.first->second << "}" << endl;

  cout << "Upper bound is {" << ret.second->first << "," << ret.second->second << "}" << endl;

  return 0;
}
