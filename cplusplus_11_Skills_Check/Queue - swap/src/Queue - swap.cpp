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
	queue<int> q1,q2;

	cout << "Adding [1..5] to q1" << endl;
	for( int i=0 ; i < 5 ; ++i ) q1.push(i+1);

	cout << "Adding [150,300] to q2" << endl;
	for( int i=150 ; i < 450 ; i += 150 ) q2.push(i);

	cout << "Original q1: ";
	while( !q1.empty() ) {
		cout << q1.front() << " ";
		q1.pop();
	}
	cout << endl;

	cout << "Original q2: ";
	while( !q2.empty() ) {
		cout << q2.front() << " ";
		q2.pop();
	}
	cout << endl;

	for( int i=0 ; i < 5 ; ++i ) q1.push(i+1);
	for( int i=150 ; i < 450 ; i += 150 ) q2.push(i);

	cout << "q1.swap(q2);" << endl;

	q1.swap(q2);

	cout << "Final contents of q1: ";
	while( !q1.empty() ) {
		cout << q1.front() << " ";
		q1.pop();
	}
	cout << endl;

	cout << "Final contents of q2: ";
	while( !q2.empty() ) {
		cout << q2.front() << " ";
		q2.pop();
	}
	cout << endl;

	return 0;
}
