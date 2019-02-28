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

	cout << "vector::at" << endl;

	cout << "v.at(i);";
	for( unsigned i=0 ; i < v.size() ; ++i ) cout << v.at(i) << " ";
	cout << endl << endl;

	return 0;
}
