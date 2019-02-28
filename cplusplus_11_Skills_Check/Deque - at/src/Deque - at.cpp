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
  deque<int> d = {1,2,3,4,5};

  cout << "Contents of d are: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  cout << "Contents of deque.at(3) are " << d.at(3) << endl;

  return 0;
}
