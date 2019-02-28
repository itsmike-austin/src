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

	cout << "vector::empty flag" << endl;

	cout << "vector v " << (v.empty() ? "is empty" : "is not empty") << endl;

	cout << "executing v.push_back(1);v.push_back(2);v.push_back(3);" << endl;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	cout << "vector v " << (v.empty() ? "is empty" : "is not empty") << endl;

	return 0;
}
