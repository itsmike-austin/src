//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>

struct Bad {
  Bad() {}
  Bad(Bad&&) {
    std::cout << "throwing move constructor called\n";
  }

  Bad(const Bad&) {
    std::cout << "Throwing copy constructor called\n";
  }
};

struct Good {
  Good() {}
  Good(Good&&) noexcept {
    std::cout << "Non-throwing move constructor called\n";
  }
  Good(const Good&) noexcept {
    std::cout << "Non-throwing copy constructor called\n";
  }
};

int main()
{
  Good g;
  Bad b;
  Good g2 = std::move_if_noexcept(g);
  Bad b2 = std::move_if_noexcept(b);
}
