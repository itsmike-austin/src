//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <utility>
#include <iostream>

struct A {
  virtual int value() = 0;
};

class B : public A {
  int val_;
public:
  B(int i,int j) : val_(i*j) {}
  int value() { return val_; }
};

int main()
{
  decltype(std::declval<A>().value()) a;
  decltype(std::declval<B>().value()) b;
  a = b = B(100,20).value();
  std::cout << a << '\n';
  return 0;
}
