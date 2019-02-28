//============================================================================
// Name        : Algorithm.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int arr[10] = {0};

	cout << "Algorithm - generate_n" << endl;

	cout << "Original array: ";
	for( int i=0 ; i < 10 ; ++i ) cout << arr[i] << " ";
	cout << endl;

	// Assign value to first 5 elements

	cout << "generate_n(arr,5,rand);" << endl;

	generate_n(arr,5,rand);

	cout << "Final array: ";
	for( int i=0 ; i < 10 ; ++i ) cout << arr[i] << " ";
	cout << endl;

	return 0;
}
