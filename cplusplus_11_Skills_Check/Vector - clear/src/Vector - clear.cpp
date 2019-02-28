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
	auto il = {1,2,3,4,5};
	vector<int> v(il);

	cout << "vector::clear()" << endl;

	cout << "Initial size of vector     = " << v.size() << endl;
	v.clear();
	cout << "Size of vector after clear = " << v.size() << endl;

	return 0;
}
