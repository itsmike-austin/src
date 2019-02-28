//============================================================================
// Name        : ForwardList.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <forward_list>

using namespace std;

bool foo(int n)
{
  return (n > 5);
}

int main()
{
  cout << "resize() and resize() - value version." << endl;

  forward_list<int> fl;

  fl.resize(5);

  cout << "fl.resize(5);" << endl;
  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl.clear();

  cout << "fl.resize(5,10); -- resize with value" << endl;

  fl.resize(5,10);

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
