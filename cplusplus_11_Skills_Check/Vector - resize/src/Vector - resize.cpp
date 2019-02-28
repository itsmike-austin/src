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
	vector<int> v;

	cout << "vector::resize" << endl;

	cout << "Initial vector size from v.size(): " << v.size() << endl;

	cout << "executing: v.resize(5,10);" << endl;

	v.resize(5,10);

	cout << "Vector size after resize: " << v.size() << endl;

	cout << "Final vector: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
