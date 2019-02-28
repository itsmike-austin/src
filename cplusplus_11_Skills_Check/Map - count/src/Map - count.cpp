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

  cout << "map::count();" << endl;

  cout << "map: " << endl;
  for( auto it=m.begin(); it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m.count(\'a\'); = " << m.count('a') << endl;

  cout << "m.count(\'z\'); = " << m.count('z') << endl;

  cout << "m.size(); = " << m.size() << endl;

  return 0;
}
