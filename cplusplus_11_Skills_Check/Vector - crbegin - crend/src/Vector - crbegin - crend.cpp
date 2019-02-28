//============================================================================
// Name        : Vector.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> v = {1,2,3,4,5};

	cout << "vector::crbegin - crend" << endl;

	cout << "Reverse list: ";
	for( auto it=v.crbegin() ; it != v.crend() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
