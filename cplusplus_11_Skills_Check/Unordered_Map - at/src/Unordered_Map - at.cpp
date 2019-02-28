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
  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Unordered_Map at"
       << endl
       << "Value of key um[\'a\'] = "
       << um.at('a')
       << endl
	   << "trying um.at(\'z\') where um is defined from [a-e];"
	   << endl;

  try {
    um.at('z');
  }catch (const out_of_range &e) {
    cerr << "Exception at " << e.what() << endl;
  }

  return 0;
}
