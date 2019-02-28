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
  // map::operator equals -- copy version

  cout << "map:: operator equals -- copy version" << endl;

  cout << "map::lower_bound." << endl;

  map<char,int> m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  map<char,int> m2 = m;

  cout << "Source map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "map<char,int> m2=m1;" << endl;

  cout << "Copy map (m2): ";
  for( auto it=m2.begin() ; it != m2.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::operator equals -- move version

  cout << "map::operator equals -- move version." << endl;

  m2.clear();

  cout << "Source map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m2 = move(m1);" << endl;

  m2 = move(m);

  cout << "Final source map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "Dest map: ";
  for( auto it=m2.begin() ; it != m2.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::operator equals -- initializer list version

  cout << "map::operator equals -- initializer list version." << endl;


  m.clear();
  m2.clear();

  m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "m = {{'a',1},{'b',2},{'c',3},{'d',4},{'e',5},};" << endl;

  cout << "Dest map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  return 0;
}
