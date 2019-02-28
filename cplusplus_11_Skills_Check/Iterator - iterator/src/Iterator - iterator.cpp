//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>

using namespace std;

class MyIterator : public iterator<input_iterator_tag,int> {
	int* p;
public:
	MyIterator(int* x) :p(x) {}
	MyIterator(const MyIterator& mit) : p(mit.p) {}
	MyIterator& operator++() { ++p; return *this; }
	MyIterator operator++(int) { MyIterator tmp(*this); operator++(); return tmp; }
	bool operator==(const MyIterator& rhs) { return p==rhs.p; }
	bool operator!=(const MyIterator& rhs) { return p!=rhs.p; }
	int& operator*() { return *p; }
};

int main() {
	int numbers[] = {1,2,3,4,5};

	MyIterator from(numbers);
	MyIterator until(numbers+5);

	cout << "Iterator - iterator: constructor" << endl;

	cout << "Original numbers array: ";
	for( auto it=begin(numbers) ; it != end(numbers) ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "MyIterator contents: for(it=from;it!=until;++it) using operator != : ";
	for( MyIterator it=from ; it != until ; ++it ) cout << *it << " ";
	cout << endl;
	return 0;
}
