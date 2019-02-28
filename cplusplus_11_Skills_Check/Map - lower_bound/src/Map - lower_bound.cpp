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
  // map::key_comp

  cout << "map::lower_bound." << endl;

  map<char,int> m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "auto it = m.lower_bound('b');" << endl;
  auto it = m.lower_bound('b');

  cout << "it->first << it->second" << endl;

  cout << "Lower bound is: " << "{" << it->first << "," << it->second << "}" << endl;

  return 0;
}
