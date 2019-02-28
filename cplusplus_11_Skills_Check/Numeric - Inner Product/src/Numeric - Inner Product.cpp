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

int myaccumulator(int x,int y) { return x-y; }
int myproduct(int x,int y) { return x+y; }

int main()
{
	int init = 100;
	int series1[] = {20,30,40};
	int series2[] = {1,2,3};

	std::cout << "Default inner_product: ";
	std::cout << std::inner_product(series1,series1+3,series2,init);
	std::cout << "\n";

	std::cout << "Functional operations: ";
	std::cout << std::inner_product(series1,series1+3,series2,init,std::minus<int>(),std::divides<int>());
	std::cout << "\n";

	std::cout << "Custom functions: ";
	std::cout << std::inner_product(series1,series1+3,series2,init,myaccumulator,myproduct);
	std::cout << "\n";

	return 0;
}

