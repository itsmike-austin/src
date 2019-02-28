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
  int init[] = {10,50,30,60};

  std::valarray<int> first;
  std::valarray<int> second(5);
  std::valarray<int> third(10,3);
  std::valarray<int> fourth(init,4);
  std::valarray<int> fifth(fourth);
  std::valarray<int> sixth(fifth[std::slice(1,2,1)]);

  std::cout << "sixth sums " << sixth.sum() << '\n';

  return 0;
}
