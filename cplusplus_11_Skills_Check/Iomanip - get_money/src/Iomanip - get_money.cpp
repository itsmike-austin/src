//============================================================================
// Name        : Iomanip.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

int main()
{
  long double price;

  std::cout << "Please, enter the price: ";
  std::cin >> std::get_money(price);

  if ( std::cin.fail() ) std::cout << "Error reading price\n";
  else std::cout << "The price entered is: " << price << '\n';

  return 0;
}
