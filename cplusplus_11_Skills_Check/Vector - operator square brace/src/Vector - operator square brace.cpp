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

	cout << "vector::operator []" << endl;

	cout << "acquiring v[i]" << endl;

	cout << "Outputting vector: ";
	for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
	cout << endl;

	return 0;
}
