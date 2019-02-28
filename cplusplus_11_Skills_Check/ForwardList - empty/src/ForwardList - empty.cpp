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

int main()
{
  forward_list<int> fl;

  if ( fl.empty() ) cout << "List is empty." << endl;

  fl.emplace_front(1);

  cout << "after fl.emplace_front(1): ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << endl;
  cout << endl;

  if ( !fl.empty() ) cout << "fl.empty() says not empty!" << endl;

  return 0;
}
