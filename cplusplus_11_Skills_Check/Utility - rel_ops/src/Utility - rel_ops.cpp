//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <cmath>

class vector2d {
public:
  double x,y;
  vector2d(double px,double py) : x(px), y(py) {}
  double length() const { return std::sqrt(x*x+y*y); }
  bool operator == (const vector2d& rhs) const { return length() == rhs.length(); }
  bool operator < (const vector2d& rhs) const { return length() < rhs.length(); }
};

int main()
{
  using namespace std::rel_ops;

  vector2d a(10,10);
  vector2d b(15,20);

  std::cout << std::boolalpha;
  std::cout << "(a>b) is " << (a>b) << '\n';
  std::cout << "(a<b) is " << (a<b) << '\n';

  return 0;
}
