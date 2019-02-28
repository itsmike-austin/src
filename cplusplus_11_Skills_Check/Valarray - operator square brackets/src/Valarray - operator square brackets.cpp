//============================================================================
// Name        : Valarray.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <valarray>

int main()
{
  std::valarray<int> myarray(10);

  myarray[std::slice(2,3,3)] = 10;

  size_t lengths[] = {2,2};
  size_t strides[] = {6,2};

  myarray[std::gslice(1,std::valarray<size_t>(lengths,2),std::valarray<size_t>(strides,2))] = 20;

  std::valarray<bool> mymask(10);

  for( int i=0 ; i < 10 ; ++i ) mymask[i] = ((i%2)==0);

  myarray[mymask] += std::valarray<int>(3,5);

  // indirect:

  size_t sel[] = {2,5,7};
  std::valarray<size_t> myselection(sel,3);
  myarray[myselection] = 99;

  std::cout << "myarray: ";
  for( size_t i=0 ; i < myarray.size() ; ++i ) {
    std::cout << myarray[i] << ' ';
  }

  std::cout << '\n';

  return 0;
}
