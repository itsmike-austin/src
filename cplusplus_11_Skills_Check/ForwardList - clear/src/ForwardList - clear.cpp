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
  forward_list<int> fl = {1,2,3,4,5};

  if ( !fl.empty() ) cout << "List is non-empty before clear operation." << endl;

  fl.clear();

  if ( fl.empty() ) cout << "List is empty after fl.clear()." << endl;

  return 0;
}
