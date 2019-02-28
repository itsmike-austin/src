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
  int *p = NULL;

  p = d.get_allocator().allocate(5);

  for( std::size_t i=0 ; i < d.size() ; ++i ) p[i] = i+1;

  cout << "Contents of first que: ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Contents of new get_allocator().allocate(5) que: ";
  for( int i=0 ; i < 5 ; ++i ) cout << p[i] << " ";
  cout << endl;

  return 0;
}
