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
	int *p = NULL;

	cout << "Allocate space for 5 vectors using v.get_allocator().allcate(5);" << endl;
	p = v.get_allocator().allocate(5);

	cout << "Assigning vectors using for(i=0;i<5;++i)p[i]=(i+1);" << endl;

	for( int i=0 ; i < 5 ; ++i ) p[i] = (i+1);

	cout << "Final new vector data: ";
	for( int i=0 ; i < 5 ; ++i ) cout << p[i] << " ";
	cout << endl << endl;

	return 0;
}
