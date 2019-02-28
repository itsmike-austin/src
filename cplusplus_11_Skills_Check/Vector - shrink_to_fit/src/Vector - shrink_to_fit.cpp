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
	vector<int> v(128);

	cout << "vector::shrink_to_fit" << endl;

	cout << "Initial capacity = " << v.capacity() << endl;

	cout << "executing v.resize(25);" << endl;

	v.resize(25);
	cout << "Capacity after resize = " << v.capacity() << endl;

	cout << "executing v.shrink_to_fit()" << endl;

	v.shrink_to_fit();
	cout << "Final capacity = " << v.capacity() << endl;

	return 0;
}
