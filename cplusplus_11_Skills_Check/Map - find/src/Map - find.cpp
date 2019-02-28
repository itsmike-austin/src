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

  // map::find

  cout << "map::find()" << endl;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "auto it = m.find('c');" << endl;

  auto it = m.find('c');

  cout << "Iterator points to {" << it->first << "," << it->second << "}" << endl;

  cout << "++iterator" << endl;
  ++it;

  cout << "Iterator points to {" << it->first << "," << it->second << "}" << endl;

  return 0;
}
