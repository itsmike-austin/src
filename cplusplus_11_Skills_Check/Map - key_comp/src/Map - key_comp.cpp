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

  cout << "map::key_comp." << endl;

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

  cout << "auto comp = m.key_comp();" << endl;
  cout << "char last = m.rbegin()->first;" << endl;
  cout << "Use char due to map<char,int>" << endl;
  cout << "auto it = m.begin();" << endl;

  auto comp = m.key_comp();
  char last = m.rbegin()->first;
  auto it = m.begin();

  cout << "Map contains the following elements" << endl;

  do
    cout << "{" << it->first << "," << it->second << "} ";
  while( comp((*it++).first,last) );
  cout << endl;

  cout << "while(comp((*it++).first,last) )" << endl;

  return 0;
}
