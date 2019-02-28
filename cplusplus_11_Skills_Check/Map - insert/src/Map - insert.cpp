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
  // map::insert -- single element

  cout << "map::insert -- single element." << endl;

  map<char,int> m = {
    {'a',1},
    {'b',2},
    {'c',3},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.insert(pair<char,int>('d',4));" << endl;
  cout << "m.insert(pair<char,int>('e',5));" << endl;

  m.insert(pair<char,int>('d',4));
  m.insert(pair<char,int>('e',5));

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  m.clear();

  // map::insert -- hint version

  cout << "map::insert -- hint version." << endl;

  m = {
    {'b',2},
    {'c',3},
    {'d',4},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.insert(m.begin(),pair<char,int>('a',1));" << endl;
  cout << "m.insert(m.begin(),pair<char,int>('e',5));" << endl;

  m.insert(m.begin(),pair<char,int>('a',1));
  m.insert(m.begin(),pair<char,int>('e',5));

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::insert -- range version

  cout << "map::insert -- range version." << endl;

  m.clear();

  m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  map<char,int> m2;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m2.size(); = " << m2.size() << endl;

  cout << "m2.insert(m1.begin(),m1.end());" << endl;

  m2.insert(m.begin(),m.end());

  cout << "Final map: ";
  for( auto it=m2.begin() ; it != m2.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::insert -- move hint version

  cout << "map::insert -- move hint version." << endl;

  m.clear();

  m = {
    {'b',2},
    {'c',3},
    {'d',4},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.insert(m.begin(),move(pair<char,int>('a',1)));" << endl;
  cout << "m.insert(m.end(),move(pair<char,int>('e',5)));" << endl;

  m.insert(m.begin(),move(pair<char,int>('a',1)));
  m.insert(m.end(),move(pair<char,int>('e',5)));

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::insert -- initializer list version

  cout << "map::insert -- initializer list version." << endl;

  m.clear();

  m = {
    {'b',2},
    {'c',3},
    {'d',4},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.insert({{'e',5},{'a',1}});" << endl;

  m.insert({{'e',5},{'a',1}});

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  return 0;
}
