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

  cout << "auto last = *m.rbegin();" << endl;
  cout << "auto it = m.begin();" << endl;

  auto last = *m.rbegin();
  auto it = m.begin();

  cout << "Map contains following elements. ";

  do
	  cout << "{" << it->first << "," << it->second << "} ";
  while( m.value_comp()(*it++,last));
  cout << endl;

  cout << "do ... while(m.value_comp()(*it++,last));" << endl << endl;

  return 0;
}
