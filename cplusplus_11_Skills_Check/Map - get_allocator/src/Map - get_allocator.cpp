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
  pair<const char,int> *p;

  // map::get_allocator

  cout << "map::get_allocator()" << endl;

  cout << "map.size();" << m.size() << endl;

  cout << "p = m.get_allocator().allocate(5)" << endl;

  p = m.get_allocator().allocate(5);

  cout << "Allocated size = " << sizeof(*p) * 5 << endl;

  return 0;
}
