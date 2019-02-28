//============================================================================
// Name        : Queue.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>

using namespace std;

int main() {
	auto it1 = {3,1,5,2,4};
	auto it2 = {5,2,4};

	priority_queue<int> q1(less<int>(),it1);
	priority_queue<int> q2(less<int>(),it2);

	cout << "Original auto data1: ";
	for( auto ax=it1.begin() ; ax != it1.end() ; ++ax ) cout << *ax << " ";
	cout << endl;

	cout << "Original auto data2: ";
	for( auto ax=it2.begin() ; ax != it2.end() ; ++ax ) cout << *ax << " ";
	cout << endl;

	cout << "q1.swap(q2);" << endl;

	q1.swap(q2);

	cout << "Contents of q1 after the swap operation: ";
	while( !q1.empty() ) {
		cout << q1.top() << " ";
		q1.pop();
	}
	cout << endl;

	cout << "Contents of q2 after the swap operation: ";
	while( !q2.empty() ) {
		cout << q2.top() << " ";
		q2.pop();
	}
	cout << endl << endl;

	return 0;
}
