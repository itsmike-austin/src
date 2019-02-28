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

	cout << "vector::size" << endl;

	cout << "Initial vector size using v.size() = " << v.size() << endl;

	cout << "executing v.resize(128);" << endl;

	v.resize(128);
	cout << "Vector size after resize using v.size() = " << v.size() << endl << endl;

	return 0;
}
