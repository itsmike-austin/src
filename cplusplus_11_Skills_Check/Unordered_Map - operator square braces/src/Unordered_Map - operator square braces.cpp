//============================================================================
// Name        : Unordered_Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{

  // Unordered_Map::operator square braces

  cout << "Unordered_Map::operator square braces." << endl;

  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5}
  };

  cout << "Unordered map contains the following: " << endl;

  cout << "um['a'] = " << um['a'] << endl;
  cout << "um['b'] = " << um['b'] << endl;
  cout << "um['c'] = " << um['c'] << endl;
  cout << "um['d'] = " << um['d'] << endl;
  cout << "um['e'] = " << um['e'] << endl;

  cout << endl;

  // Unordered_Map::operator square braces - move version

  cout << "Unordered_Map::operator square braces - move version." << endl;

  cout << "um['a'] = move(um['a']);" << endl;

  cout << "um['a'] = " << move(um['a']) << endl;
  cout << "um['b'] = " << move(um['b']) << endl;
  cout << "um['c'] = " << move(um['c']) << endl;
  cout << "um['d'] = " << move(um['d']) << endl;
  cout << "um['e'] = " << move(um['e']) << endl;

  return 0;
}

