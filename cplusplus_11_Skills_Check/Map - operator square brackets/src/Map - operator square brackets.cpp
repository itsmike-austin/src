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

  // map::operator square brackets

  cout << "map::operator square brackets -- copy version." << endl;

  cout << "Map contains these elements" << endl;

  cout << "m['a'] = " << m['a'] << endl;
  cout << "m['b'] = " << m['b'] << endl;
  cout << "m['c'] = " << m['c'] << endl;
  cout << "m['d'] = " << m['d'] << endl;
  cout << "m['e'] = " << m['e'] << endl << endl;

  return 0;
}
