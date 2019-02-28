//============================================================================
// Name        : Valvarray.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <valarray>

int main()
{
  int init[] = {10,20,30,40};

  std::valarray<int> foo(init,4);
  std::valarray<int> bar(25,4);
  bar += foo;

  foo -= 10;

  std::valarray<bool> comp = (foo == bar);

  if ( comp.min() == true ) {
    std::cout << "foo and bar are equal.\n";
  }else{
    std::cout << "foo and bar are not equal.\n";
  }

  std::cout << "foo.length: " << foo.size() << '\n';
  std::cout << "bar.length: " << bar.size() << '\n';

  for( int& i : foo ) std::cout << "foo: " << i << '\n';
  for( int& i : bar ) std::cout << "bar: " << i << '\n';
  return 0;
 }
