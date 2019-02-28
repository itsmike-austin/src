//============================================================================
// Name        : Deque.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <deque>

using namespace std;

int main()
{
  deque<int> d = {1,2,5};

  auto it = d.emplace(d.begin()+2,3);

  d.emplace(it,4);

  cout << "Contents of deque after deque.emplace(d.begin()+2,3) are ";

  for( auto it=d.crend() - 1 ; it >= d.crbegin() ; --it ) {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
