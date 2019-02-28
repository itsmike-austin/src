//============================================================================
// Name        : Numeric.cpp
// Author      : MIke
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <functional>
#include <numeric>

int myFunction (int x,int y) { return x+2*y; }

struct myclass {
	int operator()(int x,int y) { return x+3*y; }
}myobject;

int main()
{
	int init = 100;
	int numbers[] = { 5, 10, 20 };

	std::cout << "using default accumulate: ";
	std::cout << std::accumulate(numbers,numbers+3,init);
	std::cout << "\n";

	std::cout << "using functional's minus: ";
	std::cout << std::accumulate(numbers,numbers+3,init,std::minus<int>());
	std::cout << "\n";

	std::cout << "using custom function: ";
	std::cout << std::accumulate(numbers,numbers+3,init,myFunction);
	std::cout << "\n";

	std::cout << "using custom object: ";
	std::cout << std::accumulate(numbers,numbers+3,init,myobject);
	std::cout << "\n";

	return 0;
}
