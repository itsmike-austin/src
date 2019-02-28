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
  map<char,int> m;

  // map::emplace

  cout << "map::emplace();" << endl;
  cout << "map.size(); = " << m.size() << endl;

  cout << "m.emplace(\'a\',1); ... m.emplace('e',5);" << endl;

  m.emplace('a',1);
  m.emplace('b',2);
  m.emplace('c',3);
  m.emplace('d',4);
  m.emplace('e',5);

  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::emplace - hint version

  m.clear();

  m = {
    {'b',2},
    {'c',3},
    {'d',4},
  };

  cout << "map::emplace - hint version." << endl;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.emplace_hint(m.end(),'e',5);" << endl;
  cout << "m.emplace_hint(m.begin(),'a',1);" << endl;

  m.emplace_hint(m.end(),'e',5);
  m.emplace_hint(m.begin(),'a',1);

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  return 0;
}
